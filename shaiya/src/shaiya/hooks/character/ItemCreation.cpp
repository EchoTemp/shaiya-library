#include <logging/log.hpp>
#include <shaiya/World.hpp>
#include <shaiya/hooks/character/ItemCreation.hpp>
#include <shaiya/models/stItemInfo.hpp>
#include <shaiya/utils/toml.hpp>

#include <sstream>

/**
 * The maximum slot value.
 */
constexpr auto MaxSlot = 23;

/**
 * The maximum bag value.
 */
constexpr auto MaxBag = 5;

/**
 * Initialise the combinations
 */
std::vector<Combination> ItemCreation::combinations_;

/**
 * Parses the ItemCombination.csv file.
 * @param path  The path to the item combination CSV.
 */
void ItemCreation::parse(const std::string& path)
{
    // Parse the combination file
    auto config       = toml::parse_file(path);
    auto combinations = config["combination"].as_table();

    // Loop through all of the combinations
    for (auto&& combination: *combinations)
    {
        auto data = *combination.second.as_table();

        auto type   = data["type"].value_or(std::string("create"));
        auto first  = data["first"].value_or(0);
        auto second = data["second"].value_or(0);
        auto third  = data["third"].value_or(0);
        auto result = data["result"].value_or(0);

        Combination itemCombo{};
        itemCombo.type   = type == "create" ? CombinationType::Create : CombinationType::Replace;
        itemCombo.first  = first;
        itemCombo.second = second;
        itemCombo.third  = third;
        itemCombo.result = result;
        combinations_.push_back(itemCombo);
    }

    LOG(INFO) << "Successfully parsed " << combinations_.size() << " item combinations";
}

/**
 * Handles the item creation at the Profession Blacksmith.
 * @param user      The user instance.
 * @param packet    The item creation packet.
 */
void ItemCreation::create(CUser* user, ItemCreationRequest* packet)
{
    for (auto&& bag: packet->bags)
    {
        if (bag > MaxBag)
            return;
    }

    for (auto&& slot: packet->slots)
    {
        if (slot > MaxSlot)
            return;
    }

    auto* first  = user->itemAtSlot(packet->bags[0], packet->slots[0]);
    auto* second = user->itemAtSlot(packet->bags[1], packet->slots[1]);
    auto* third  = user->itemAtSlot(packet->bags[2], packet->slots[2]);

    if (!first || !second || !third)
        return;

    if (first == second || first == third || second == third)
        return;

    for (auto&& combination: combinations_)
    {
        if (combination.first == first->itemId() && combination.second == second->itemId() &&
            combination.third == third->itemId())
        {
            CItem firstCopy(*user->itemAtSlot(packet->bags[0], packet->slots[0]));  // A copy of the first item's values.

            for (auto i = 0; i < packet->bags.size(); i++)
                user->deleteItem(packet->bags[i], packet->slots[i]);

            auto resultId = combination.result;
            auto type     = resultId / 1000;
            auto typeId   = resultId % 1000;

            auto definition = stItemInfo::forId(type, typeId);
            if (definition)
            {
                auto [resultBag, resultSlot] = user->firstFreeSlot();
                std::stringstream stream;
                stream << "Congratulations! You have successfully crafted a " << definition->name << "!";
                user->sendNotice(stream.str());

                user->createItem(type, typeId);
                auto resultItem = user->itemAtSlot(resultBag, resultSlot);

                if (combination.type == CombinationType::Replace)
                {
                    resultItem->lapis     = firstCopy.lapis;
                    resultItem->craftname = firstCopy.craftname;
                }

                // Inform the user of the created item
                ItemCreationUpdate update;
                update.bag       = resultBag;
                update.slot      = resultSlot;
                update.type      = resultItem->type;
                update.typeId    = resultItem->typeId;
                update.endurance = resultItem->endurance;
                update.lapis     = resultItem->lapis;
                update.quantity  = resultItem->quantity;
                update.craftname = resultItem->craftname;
                World::sendPacket(user, &update, sizeof(update));

                // Update the item in the database
                user->updateItem(resultBag, resultSlot);
            }
            return;
        }
    }
}
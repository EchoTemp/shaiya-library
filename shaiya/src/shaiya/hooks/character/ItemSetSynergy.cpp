#include <Shlwapi.h>
#include <logging/log.hpp>
#include <shaiya/hooks/character/ItemSetSynergy.hpp>
#include <shaiya/utils/toml.hpp>

#include <set>
#include <vector>

/**
 * Initialise the item synergies.
 */
std::vector<Synergy> ItemSetSynergy::synergies;

/**
 * A map of users, to the sets they are wearing.
 */
std::map<CUser*, std::vector<Craftname>> ItemSetSynergy::appliedSynergies;

/**
 * Parses the "setitem.csv" file which is used to define synergies.
 * @param path  The path to the synergy sets.
 */
void ItemSetSynergy::parse(const std::string& path)
{
    // Parse the synergy file
    auto config = toml::parse_file(path);
    auto sets   = config["set"].as_table();

    // Loop through all of the sets
    for (auto&& set: *sets)
    {
        auto data  = *set.second.as_table();
        auto name  = data["name"].value_or("Undefined");
        auto items = data["items"].as_array();

        // Assign the set name and worn items
        Synergy synergy{ .name = name };
        for (auto i = 0; i < items->size(); i++)
            synergy.items[i] = (*items->get(i)->as_integer()).get();

        // Loop through any worn bonus tables
        for (auto bonus = data.begin(); bonus != data.end(); bonus++)
        {
            int32_t wornCount;
            if (StrToIntEx(bonus->first.c_str(), STIF_SUPPORT_HEX, &wornCount))
            {
                auto bonuses = *bonus->second.as_table();

                // Parse the bonus status
                auto strength                  = bonuses["str"].value_or(0);
                auto dexterity                 = bonuses["dex"].value_or(0);
                auto resistance                = bonuses["rec"].value_or(0);
                auto intelligence              = bonuses["int"].value_or(0);
                auto wisdom                    = bonuses["wis"].value_or(0);
                auto luck                      = bonuses["luc"].value_or(0);
                auto hitpoints                 = bonuses["hp"].value_or(0);
                auto mana                      = bonuses["mp"].value_or(0);
                auto stamina                   = bonuses["sp"].value_or(0);
                synergy.bonuses[wornCount - 1] = Craftname{ .strength     = strength,
                                                            .dexterity    = dexterity,
                                                            .resistance   = resistance,
                                                            .intelligence = intelligence,
                                                            .wisdom       = wisdom,
                                                            .luck         = luck,
                                                            .hitpoints    = hitpoints,
                                                            .mana         = mana,
                                                            .stamina      = stamina };
            }
        }

        // Add the synergy set
        synergies.push_back(synergy);
        LOG(INFO) << "Loaded synergy set: " << synergy.name;
    }
    LOG(INFO) << "Successfully loaded " << synergies.size() << " synergy sets.";
}

/**
 * Parses a delimited input string to a craftname
 * @param input The input string
 * @return      The craftname
 */
Craftname ItemSetSynergy::parseCraftname(const std::string& input)
{
    if (input.empty() || input == "0")  // If the string is empty or just contains the number 0
        return {};

    // Split the string into a vector, using the delimiter of '|'
    std::vector<std::string> tokens;
    std::istringstream iss(input);
    while (iss.good())
    {
        std::string token;
        std::getline(iss, token, '|');
        tokens.push_back(token);
    }

    // Set the craftname values
    Craftname craftname{};
    craftname.strength     = std::stoi(tokens[0]);
    craftname.dexterity    = std::stoi(tokens[1]);
    craftname.resistance   = std::stoi(tokens[2]);
    craftname.intelligence = std::stoi(tokens[3]);
    craftname.wisdom       = std::stoi(tokens[4]);
    craftname.luck         = std::stoi(tokens[5]);
    craftname.hitpoints    = std::stoi(tokens[6]);
    craftname.mana         = std::stoi(tokens[7]);
    craftname.stamina      = std::stoi(tokens[8]);
    return craftname;
}

/**
 * Applies all worn synergies for the user.
 * @param user  The user instance.
 */
void ItemSetSynergy::applyWornSynergies(CUser* user)
{
    // Remove all existing synergies
    removeSynergies(user);

    // Get all worn synergies for the user
    auto wornSynergies = getWornSynergies(user);

    // Apply the synergy effects
    for (auto&& synergy: wornSynergies)
    {
        addSynergy(user, synergy);
        user->abilityStr += synergy.strength;
        user->abilityDex += synergy.dexterity;
        user->abilityRec += synergy.resistance;
        user->abilityInt += synergy.intelligence;
        user->abilityWis += synergy.wisdom;
        user->abilityLuc += synergy.luck;
        user->maxHitpoints += synergy.hitpoints;
        user->maxMana += synergy.mana;
        user->maxStamina += synergy.stamina;
    }
}

/**
 * Removes all worn synergies for the user
 * @param user  The user instance
 */
void ItemSetSynergy::removeSynergies(CUser* user)
{
    // Remove all previously applied synergies
    for (auto&& synergy: getAppliedSynergies(user))
    {
        user->abilityStr -= synergy.strength;
        user->abilityDex -= synergy.dexterity;
        user->abilityRec -= synergy.resistance;
        user->abilityInt -= synergy.intelligence;
        user->abilityWis -= synergy.wisdom;
        user->abilityLuc -= synergy.luck;
        user->maxHitpoints -= synergy.hitpoints;
        user->maxMana -= synergy.mana;
        user->maxStamina -= synergy.stamina;
    }

    // Remove the user from the list of applied synergies
    appliedSynergies.erase(user);
}

/**
 * Gets the craftname bonuses to apply for a user
 * @param user  The user instance
 * @return      The craftnames to apply
 */
std::vector<Craftname> ItemSetSynergy::getWornSynergies(CUser* user)
{
    if (user == nullptr)
        return {};

    // Calculate a set of item ids based on the users current equipment
    std::set<size_t> equipmentIds;
    for (auto&& item: user->equipment)
    {
        if (item == nullptr)
            continue;
        auto id = (item->type * 1000) + item->typeId;
        equipmentIds.insert(id);
    }

    // A vector which holds all of the worn synergy bonuses for the user
    std::vector<Craftname> wornSynergies;

    // Loop through all of the synergies
    for (auto&& synergy: synergies)
    {
        size_t wornCount = 0;  // The number of items in this synergy that the player is wearing
        for (auto&& id: synergy.items)
        {
            if (equipmentIds.count(id))
                wornCount += 1;
        }

        // Add the synergy is the user is wearing two or piece pieces.
        if (wornCount >= 2)
        {
            LOG(INFO) << user->name << " is found wearing " << wornCount << " pieces of " << synergy.name;
            wornSynergies.push_back(synergy.bonuses[wornCount - 1]);
        }
    }

    // Return the worn bonuses
    return wornSynergies;
}

/**
 * Adds an applied synergy effect for a user.
 * @param user          The user instance.
 * @param craftname     The synergy bonus.
 */
void ItemSetSynergy::addSynergy(CUser* user, Craftname craftname)
{
    if (appliedSynergies.count(user) == 0)
    {
        std::vector<Craftname> craftnames{};
        craftnames.push_back(craftname);
        appliedSynergies[user] = craftnames;
        return;
    }

    appliedSynergies[user].push_back(craftname);
}

/**
 * Gets all applied synergy effects for a user.
 * @param user  The user instance.
 * @return      The synergy bonuses.
 */
std::vector<Craftname> ItemSetSynergy::getAppliedSynergies(CUser* user)
{
    if (appliedSynergies.count(user) == 0)
        return {};

    return appliedSynergies[user];
}
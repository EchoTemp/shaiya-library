#include <shaiya/hooks/character/ItemSetSynergy.hpp>
#include <shaiya/utils/csv.hpp>
#include <logging/log.hpp>

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
    io::CSVReader<28> csv(path);
    csv.read_header(io::ignore_extra_column, "Setid", "setName", "Itemid_1", "Pieces1_value", "Itemid_2", "Pieces2_value", "Itemid_3", "Pieces3_value", "Itemid_4", "Pieces4_value", "Itemid_5", "Pieces5_value", "Itemid_6", "Pieces6_value", "Itemid_7", "Pieces7_value", "Itemid_8", "Pieces8_value", "Itemid_9", "Pieces9_value", "Itemid_10", "Pieces10_value", "Itemid_11", "Pieces11_value", "Itemid_12", "Pieces12_value", "Itemid_13", "Pieces13_value");

    // The row values
    size_t setId;
    std::string setName;
    size_t firstItem;
    std::string firstValue;
    size_t secondItem;
    std::string secondValue;
    size_t thirdItem;
    std::string thirdValue;
    size_t fourthItem;
    std::string fourthValue;
    size_t fifthItem;
    std::string fifthValue;
    size_t sixthItem;
    std::string sixthValue;
    size_t seventhItem;
    std::string seventhValue;
    size_t eighthItem;
    std::string eighthValue;
    size_t ninthItem;
    std::string ninthValue;
    size_t tenthItem;
    std::string tenthValue;
    size_t eleventhItem;
    std::string eleventhValue;
    size_t twelfthItem;
    std::string twelfthValue;
    size_t thirteenthItem;
    std::string thirteenthValue;

    // Read the rows
    while (csv.read_row(setId, setName, firstItem, firstValue, secondItem, secondValue, thirdItem, thirdValue, fourthItem, fourthValue, fifthItem, fifthValue, sixthItem, sixthValue, seventhItem, seventhValue, eighthItem, eighthValue, ninthItem, ninthValue, tenthItem, tenthValue, eleventhItem, eleventhValue, twelfthItem, twelfthValue, thirteenthItem, thirteenthValue))
    {
        // Create the synergy structure
        Synergy synergy { .id = setId, .name = setName };

        // Store the item ids
        auto& items = synergy.items;
        items[0] = firstItem;
        items[1] = secondItem;
        items[2] = thirdItem;
        items[3] = fourthItem;
        items[4] = fifthItem;
        items[5] = sixthItem;
        items[6] = seventhItem;
        items[7] = eighthItem;
        items[8] = ninthItem;
        items[9] = tenthItem;
        items[10] = eleventhItem;
        items[11] = twelfthItem;
        items[12] = thirteenthItem;

        // Store the bonus craftnames
        auto& craftnames = synergy.bonuses;
        craftnames[0]   = parseCraftname(firstValue);
        craftnames[1]   = parseCraftname(secondValue);
        craftnames[2]   = parseCraftname(thirdValue);
        craftnames[3]   = parseCraftname(fourthValue);
        craftnames[4]   = parseCraftname(fifthValue);
        craftnames[5]   = parseCraftname(sixthValue);
        craftnames[6]   = parseCraftname(seventhValue);
        craftnames[7]   = parseCraftname(eighthValue);
        craftnames[8]   = parseCraftname(ninthValue);
        craftnames[9]   = parseCraftname(tenthValue);
        craftnames[10]  = parseCraftname(eleventhValue);
        craftnames[11]  = parseCraftname(twelfthValue);
        craftnames[12]  = parseCraftname(thirteenthValue);

        // Store the synergy
        synergies.push_back(synergy);
        LOG(INFO) << "Loaded synergy set: " << setName;
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
    if (input.empty() || input == "0") // If the string is empty or just contains the number 0
        return { };

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
    Craftname craftname { };
    craftname.strength      = std::stoi(tokens[0]);
    craftname.dexterity     = std::stoi(tokens[1]);
    craftname.resistance    = std::stoi(tokens[2]);
    craftname.intelligence  = std::stoi(tokens[3]);
    craftname.wisdom        = std::stoi(tokens[4]);
    craftname.luck          = std::stoi(tokens[5]);
    craftname.hitpoints     = std::stoi(tokens[6]);
    craftname.mana          = std::stoi(tokens[7]);
    craftname.stamina       = std::stoi(tokens[8]);
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
        user->abilityStr    += synergy.strength;
        user->abilityDex    += synergy.dexterity;
        user->abilityRec    += synergy.resistance;
        user->abilityInt    += synergy.intelligence;
        user->abilityWis    += synergy.wisdom;
        user->abilityLuc    += synergy.luck;
        user->maxHitpoints  += synergy.hitpoints;
        user->maxMana       += synergy.mana;
        user->maxStamina    += synergy.stamina;
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
        user->abilityStr    -= synergy.strength;
        user->abilityDex    -= synergy.dexterity;
        user->abilityRec    -= synergy.resistance;
        user->abilityInt    -= synergy.intelligence;
        user->abilityWis    -= synergy.wisdom;
        user->abilityLuc    -= synergy.luck;
        user->maxHitpoints  -= synergy.hitpoints;
        user->maxMana       -= synergy.mana;
        user->maxStamina    -= synergy.stamina;
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
        size_t wornCount = 0; // The number of items in this synergy that the player is wearing
        for (auto&& id: synergy.items)
        {
            if (equipmentIds.count(id))
                wornCount += 1;
        }

        // Add the synergy is the user is wearing two or piece pieces.
        if (wornCount >= 2)
        {
            LOG(INFO) << user->name.data() << " is found wearing " << wornCount << " pieces of " << synergy.name;
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
        std::vector<Craftname> craftnames { };
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
        return { };

    return appliedSynergies[user];
}
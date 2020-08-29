#pragma once

#include <shaiya/models/CUser.hpp>
#include <shaiya/hooks/character/Synergy.hpp>

#include <string>
#include <vector>
#include <map>

/**
 * A utility class that is used for the parsing and management of item set synergy effects.
 */
class ItemSetSynergy
{
public:

    /**
     * Parses the itemset.csv file.
     * @param path  The path to the item set CSV.
     */
    static void parse(const std::string& path);

    /**
     * Applies all worn synergy effects for the user.
     * @param user  The user instance.
     */
    static void applyWornSynergies(CUser* user);

    /**
     * Removes all previously applied synergy effects.
     * @param user  The user instance.
     */
    static void removeSynergies(CUser* user);

private:

    /**
     * Gets all worn synergy effects.
     * @param user  The user instance.
     * @return      The synergy effects.
     */
    static std::vector<Craftname> getWornSynergies(CUser* user);

    /**
     * Adds an applied synergy effect.
     * @param user          The user instance.
     * @param craftname     The craftname of the synergy.
     */
    static void addSynergy(CUser* user, Craftname craftname);

    /**
     * Gets all previously applied synergy effects for a user.
     * @param user  The user instance
     * @return      The applied synergy effects.
     */
    static std::vector<Craftname> getAppliedSynergies(CUser* user);

    /**
     * Parses a craftname
     * @param input     The input string
     * @return          The craftname structure
     */
    static Craftname parseCraftname(const std::string& input);

    /**
     * A vector of all possible synergy effects.
     */
    static std::vector<Synergy> synergies;

    /**
     * A map of users to their applied synergies.
     */
    static std::map<CUser*, std::vector<Craftname>> appliedSynergies;
};
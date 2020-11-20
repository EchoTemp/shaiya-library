#pragma once
#include <shaiya/hooks/character/Combination.hpp>
#include <shaiya/models/CUser.hpp>
#include <shaiya/models/packets/ItemCreationPacket.hpp>

/**
 * A utility class for managing the item creation system.
 */
class ItemCreation
{
public:
    /**
     * Parses the ItemCombination.csv file.
     * @param path  The path to the item combination CSV.
     */
    static void parse(const std::string& path);

    /**
     * Handles the item creation at the Profession Blacksmith.
     * @param user      The user instance.
     * @param packet    The item creation packet.
     */
    static void create(CUser* user, ItemCreationRequest* packet);

private:
    /**
     * Represents a combination of items.
     */
    static std::vector<Combination> combinations_;
};
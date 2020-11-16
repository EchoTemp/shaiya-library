#pragma once

#include <shaiya/models/CItem.hpp>
#include <shaiya/models/Model.hpp>
#include <shaiya/models/VariableString.hpp>

#include <array>
#include <string>

/**
 * CUser likely stands for character user. This represents an active character instance
 * within the game world.
 */
#pragma pack(push, 1)
struct CUser
{
    PAD(208);
    float posX;
    float posY;
    float posZ;
    PAD(4);
    unsigned int zone;
    PAD(68);
    unsigned int charId;
    unsigned char slot;
    unsigned char faction;
    unsigned char family;
    unsigned char mode;
    unsigned char hair;
    unsigned char face;
    unsigned char height;
    unsigned char gender;
    unsigned short job;
    unsigned short level;
    unsigned short statpoints;
    unsigned short skillpoints;
    unsigned int experience;
    unsigned int money;
    PAD(4);
    unsigned int kills;
    unsigned int deaths;
    unsigned int victories;
    unsigned int defeats;
    unsigned int killRank;
    unsigned int deathRank;
    unsigned short map;
    unsigned short direction;
    unsigned short hg;
    unsigned short vg;
    unsigned char cg;
    unsigned char og;
    unsigned short ig;
    unsigned short strength;
    unsigned short dexterity;
    unsigned short intelligence;
    unsigned short wisdom;
    unsigned short resistance;
    unsigned short luck;
    unsigned int maxHitpoints;
    unsigned int maxMana;
    unsigned int maxStamina;
    VariableString<32> name;
    PAD(28);
    std::array<CItem*, 24> equipment;
    std::array<std::array<CItem*, 24>, 5> inventory;
    PAD(1712);
    unsigned int doubleWarehouse;
    PAD(1896);
    unsigned int abilityStr;
    unsigned int abilityDex;
    unsigned int abilityInt;
    unsigned int abilityWis;
    unsigned int abilityRec;
    unsigned int abilityLuc;
    unsigned int hitpoints;
    unsigned int mana;
    unsigned int stamina;

    /**
     * Sends a notice message to this user.
     * @param message   The message to send.
     */
    void sendNotice(const std::string& message);

    /**
     * Sends the user their Aeria Points.
     */
    void sendPoints();

    /**
     * Gets an item at a specific position.
     * @param user  The user instance.
     * @param bag   The bag id.
     * @param slot  The slot.
     * @return      The item instance.
     */
    CItem* itemAtSlot(int bag, int slot);

    /**
     * Creates an item for the user.
     * @param type      The type
     * @param typeId    The type id.
     * @param quantity  The number of items to create.
     */
    void createItem(int type, int typeId, int quantity = 1);

    /**
     * Deletes an item at a specified bag and slot
     * @param bag   The bag
     * @param slot  The slot
     */
    void deleteItem(int bag, int slot);
};
#pragma pack(pop)
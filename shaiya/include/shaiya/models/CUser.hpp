#pragma once

#include <shaiya/models/CGuild.hpp>
#include <shaiya/models/CItem.hpp>
#include <shaiya/models/CParty.hpp>
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
    PAD(24);
    unsigned int regenHitpoints;  // The amount of hitpoints the user will regenerate on the next tick
    unsigned int regenMana;
    unsigned int regenStamina;
    PAD(128);
    unsigned int attackPowerAdd;  // The additional attack power added to the user by abilities and lapis
    PAD(8);
    unsigned int attackRange;  // The attack range of the user.
    unsigned int attackSpeed;  // The attack speed of the user.
    unsigned int abilityMoveSpeed;
    unsigned int abilityCritChance;
    unsigned int potentialMotive;
    PAD(8);
    unsigned int numBagsUnlocked;
    PAD(116);
    unsigned int abilityHitChance;
    unsigned int abilityAttackPower;
    unsigned int abilityPhysicalEvasion;
    unsigned int abilityPhysicalDefenceReduction;
    PAD(4);
    unsigned int abilityRangeAttackPower;
    unsigned int abilityRangeEvasion;
    unsigned int abilityRangeDefenceReduction;
    unsigned int abilityMagicHitChance;
    unsigned int abilityMagicAttackPower;
    PAD(4);
    unsigned int abilityMagicResist;
    unsigned int abilityDarknessBlow;
    PAD(20);
    unsigned int minPhysicalAttack;
    PAD(4);
    unsigned int physicalDefence;
    PAD(8);
    unsigned int abilityDarknessBlow2;
    PAD(20);
    unsigned int minRangeAttack;
    PAD(4);
    unsigned int rangedDefence;
    PAD(8);
    unsigned int abilitySilentBlow;
    PAD(20);
    unsigned int minMagicAttack;
    PAD(4);
    unsigned int magicResist;
    PAD(20);
    bool isDead;
    PAD(7);
    unsigned char movementStatus;
    PAD(935);
    CParty* party;
    PAD(8);
    unsigned int guildId;
    unsigned int guildRank;
    PAD(8);
    CGuild* guild;
    PAD(15728);
    unsigned long lastEnterGrbTick;
    PAD(632);
    unsigned long sessionId;
    PAD(4);
    unsigned int adminStatus;
    PAD(8);
    bool isVisible;
    bool isAttackable;
    PAD(22);
    unsigned int userId;
    PAD(4);
    VariableString<21> username;
    PAD(107);
    unsigned int teleportType;
    unsigned int teleportDelay;
    unsigned int teleportMapId;
    float teleportDestX;
    float teleportDestY;
    float teleportDestZ;
    PAD(128);
    unsigned int abilityCharm;
    unsigned int abilityExtraGold;
    unsigned int abilityEndurance;
    unsigned int abilityPreventExpLoss;
    unsigned int abilityPreventItemDrop;
    unsigned int abilityPreventEquipDrop;
    unsigned int abilityWarehouseRecall;
    unsigned int abilityDoubleWarehouse;
    unsigned int abilityPvpExp;
    PAD(4);
    unsigned int abilityContiRes;
    PAD(328);
    unsigned int points;
    unsigned int isBuying;

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

    /**
     * Teleports the player to a destination
     * @param map   The map id
     * @param x     The x coordinate
     * @param z     The z coordinate
     */
    void teleport(uint16_t map, float x, float z);
};
#pragma pack(pop)
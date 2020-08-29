#pragma once
#include <shaiya/models/Model.hpp>
#include <shaiya/models/CItem.hpp>

#include <array>
#include <set>

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
    std::array<char, 32> name;
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
};
#pragma pack(pop)
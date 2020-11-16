#pragma once
#include <shaiya/models/VariableString.hpp>

/**
 * The function address to get the definition of an item
 */
constexpr auto CGamedataGetItemInfo = 0x4059B0;

#pragma pack(push, 1)
struct stItemInfo
{
    unsigned int itemId;
    VariableString<32> name;
    unsigned char type;
    unsigned char typeId;
    unsigned char faction;
    char job[6];
    char pad_0[1];
    unsigned short levelReq;
    unsigned char mode;
    char pad_1[1];
    unsigned char group;
    char pad_2[1];
    unsigned int variant;
    char pad_3[4];
    unsigned short lapisLevelReq;
    unsigned short maxReroll;
    char pad_4[2];
    unsigned short attackRange;
    unsigned short attackSpeed;
    unsigned char effect;
    unsigned char slots;
    unsigned char moveSpeed;
    unsigned char server;
    unsigned char rerollCount;
    unsigned char stackSize;

    /**
     * Gets an item for a specific type and id
     * @param itemType  The item type
     * @param typeId    The type id
     * @return          The definition
     */
    static stItemInfo* forId(int itemType, int typeId)
    {
        stItemInfo* definition = nullptr;
        __asm
        {
            mov ecx, typeId
            mov eax, itemType
            call CGamedataGetItemInfo
            mov definition, eax
        }
        return definition;
    }
};
#pragma pack(pop)

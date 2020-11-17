#include <shaiya/World.hpp>
#include <shaiya/models/CUser.hpp>
#include <shaiya/models/packets/AccountPoints.hpp>
#include <shaiya/models/packets/Notice.hpp>
#include <shaiya/models/stItemInfo.hpp>

/**
 * The address of the function to create an item for a user
 */
constexpr auto CUserItemCreate = 0x46BD10;

/**
 * The function for deleting an item from a user
 *
 * @param user	The user instance
 * @param bag	The bag to delete from
 * @param slot	The slot to delete from
 * @param move	If items should be moved?
 *
 * @return		If the item was successfully deleted
 */
typedef bool(__thiscall* _ItemDelete)(CUser* user, int bag, int slot, bool move);
_ItemDelete itemDelete = (_ItemDelete)0x4728E0;

/**
 * Sends a notice message to the user.
 * @param message   The message to send
 */
void CUser::sendNotice(const std::string& message)
{
    Notice notice{};
    notice.length = message.length();
    std::memcpy(notice.message.data(), message.c_str(), message.length());
    World::sendPacket(this, &notice, 3 + notice.length);
}

/**
 * Sends the user their Aeria Points.
 */
void CUser::sendPoints()
{
    AccountPoints points{ .points = 0 };
    World::sendPacket(this, &points, sizeof(points));
}

/**
 * Gets an item at a specific position.
 * @param user  The user instance.
 * @param bag   The bag id.
 * @param slot  The slot.
 * @return      The item instance.
 */
CItem* CUser::itemAtSlot(int bag, int slot)
{
    if (bag == 0)
        return equipment[slot];
    return inventory[bag - 1][slot];
}

/**
 * Creates an item for the user.
 * @param type      The type
 * @param typeId    The type id.
 * @param quantity  The number of items to create.
 */
void CUser::createItem(int itemType, int typeId, int quantity)
{
    auto definition = stItemInfo::forId(itemType, typeId);
    if (definition)
    {
        __asm
        {
            pushad
            pushfd

            mov ecx,this
            push quantity
            push definition
            call CUserItemCreate

            popfd
            popad
        }
    }
}

/**
 * Deletes an item at a specified bag and slot
 * @param bag   The bag
 * @param slot  The slot
 */
void CUser::deleteItem(int bag, int slot)
{
    itemDelete(this, bag, slot, false);
}

/**
 * Teleports the player to a destination
 * @param map   The map id
 * @param x     The x coordinate
 * @param z     The z coordinate
 */
void CUser::teleport(uint16_t map, float x, float z)
{
    teleportType  = 1;
    teleportMapId = map;
    teleportDestX = x;
    teleportDestZ = z;
    teleportDelay = 1000;  // 1s delay on the teleport
}
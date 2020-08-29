#include <shaiya/models/CUser.hpp>

#include <shaiya/World.hpp>

#include <shaiya/models/packets/Notice.hpp>
#include <shaiya/models/packets/AccountPoints.hpp>

/**
 * Sends a notice message to the user.
 * @param message   The message to send
 */
void CUser::sendNotice(const std::string &message)
{
    Notice notice { };
    notice.length = message.length();
    std::memcpy(notice.message.data(), message.c_str(), message.length());
    World::sendPacket(this, &notice, 3 + notice.length);
}

/**
 * Sends the user their Aeria Points.
 */
void CUser::sendPoints()
{
    AccountPoints points { .points = 0 };
    World::sendPacket(this, &points, sizeof(points));
}
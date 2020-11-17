using Binarysharp.MemoryManagement;
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;
using System;
using System.Runtime.InteropServices;
using System.Text;

namespace Shaiya.Web.Api.Models
{
    /// <summary>
    /// Represents a user in the game world.
    /// </summary>
    public struct CUser
    {

        /// <summary>
        /// The name of the user.
        /// </summary>
        public string Name { get; private set; }

        /// <summary>
        /// The character id of the user.
        /// </summary>
        public uint CharId { get; private set; }

        /// <summary>
        /// The x position of the user
        /// </summary>
        public float PosX { get; private set; }

        /// <summary>
        /// The y position of the user
        /// </summary>
        public float PosY { get; private set; }

        /// <summary>
        /// The z position of the user
        /// </summary>
        public float PosZ { get; private set; }

        /// <summary>
        /// The map id of the user
        /// </summary>
        public ushort Map { get; private set; }

        /// <summary>
        /// Reads the user struct.
        /// </summary>
        /// <param name="sharp">The memory sharp instance</param>
        /// <param name="address">The address of the player</param>
        public void Read(MemorySharp sharp, IntPtr address)
        {
            // Read the position of the user
            PosX = sharp.Read<float>(address + 0xD0, false);
            PosY = sharp.Read<float>(address + 0xD4, false);
            PosZ = sharp.Read<float>(address + 0xD8, false);
            Map = sharp.Read<ushort>(address + 0x160, false);

            // Read the character id
            CharId = sharp.Read<uint>(address + 0x128, false);

            // Read the character name
            var nameBytes = sharp.Read<byte>(address + 0x184, 21, false);
            Name = Encoding.ASCII.GetString(nameBytes);
            Name = Name.Trim('\0');
        }
    }
}

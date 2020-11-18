using Binarysharp.MemoryManagement;
using Binarysharp.MemoryManagement.Assembly.CallingConvention;
using Shaiya.Web.Api.Models;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Shaiya.Web.Api.Services
{
    /// <summary>
    /// A service that interacts with the ps_game process.
    /// </summary>
    public class GameService
    {
        /// <summary>
        /// The name of the game process.
        /// </summary>
        private static readonly string ProcessName = "ps_game";

        /// <summary>
        /// The base address to start from.
        /// </summary>
        private static readonly IntPtr BaseAddress = (IntPtr)0xA00000;

        /// <summary>
        /// Gets a list of online users.
        /// </summary>
        /// <returns>The list of online users.</returns>
        public List<CUser> GetOnlineUsers()
        {
            var list = new List<CUser>();

            var sharp = Memory();
            var cups = GetCups();
            if (cups == null || sharp == null)
                return list;

            var playerList = CupsList.Read(sharp.Read<byte>((IntPtr)cups?.UserListPointer, 4, false));

            for (var i = 0; i < playerList.capacity; i++)
            {
                if (list.Count >= playerList.quantity)
                    break;
                var userPointer = sharp.Read<int>((IntPtr)cups?.UserListPointer + 4 + (i * 4), false);
                if (userPointer != 0)
                {
                    var user = new CUser();
                    user.Read(sharp, (IntPtr)userPointer);
                    list.Add(user);
                }
            }

            return list;
        }

        /// <summary>
        /// Teleports a user by their name.
        /// </summary>
        /// <param name="name">The name to search for</param>
        /// <param name="map">The destination map</param>
        /// <param name="x">The destination x coordinate</param>
        /// <param name="z">The destination z coordinate</param>
        public void TeleportUserByName(string name, ushort map, float x, float z)
        {
            var cups = GetCups();
            var sharp = Memory();
            if (sharp == null || cups == null)
                return;

            sharp.Assembly.Execute((IntPtr) cups?.TeleportUserByName, CallingConventions.Cdecl, name, map, x, z);
        }

        /// <summary>
        /// Gets the memory sharp instance.
        /// </summary>
        /// <returns>The memory sharp instance</returns>
        private MemorySharp Memory()
        {
            var process = GetProcessByName(ProcessName);

            if (process == null)
                return null;

            return new MemorySharp(process);
        }

        /// <summary>
        /// Gets the cups data structure.
        /// </summary>
        /// <returns>The cups data structure</returns>
        private Cups? GetCups()
        {
            var sharp = Memory();
            if (sharp == null)
                return null;

            var cupsPointer = sharp.Read<int>(BaseAddress, false);
            if (cupsPointer == 0)
                return null;

            var cupsBuffer = sharp.Read<byte>((IntPtr)cupsPointer, 8, false);
            return Cups.Read(cupsBuffer);
        }

        /// <summary>
        /// Gets a process by it's name.
        /// </summary>
        /// <param name="name">The name of the process.</param>
        /// <returns>The process instance</returns>
        private Process GetProcessByName(string name)
        {
            var processes = Process.GetProcessesByName(name);
            return processes.FirstOrDefault();
        }
    }
}

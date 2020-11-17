using Binarysharp.MemoryManagement;
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
            var process = GetProcessByName(ProcessName);

            if (process == null)
                return list;

            var sharp = new MemorySharp(process);
            var cupsPointer = sharp.Read<int>(BaseAddress, false);
            if (cupsPointer == 0)
                return list;

            var cupsBuffer = sharp.Read<byte>((IntPtr) cupsPointer, 4, false);
            var cups = Cups.Read(cupsBuffer);
            var playerList = CupsList.Read(sharp.Read<byte>((IntPtr)cups.UserListPointer, 4, false));

            for (var i = 0; i < playerList.capacity; i++)
            {
                if (list.Count >= playerList.quantity)
                    break;
                var userPointer = sharp.Read<int>((IntPtr)cups.UserListPointer + 4 + (i * 4), false);
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

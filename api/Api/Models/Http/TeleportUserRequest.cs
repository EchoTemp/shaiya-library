using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Shaiya.Web.Api.Models.Http
{
    /// <summary>
    /// Represents a request to teleport a user.
    /// </summary>
    public class TeleportUserRequest
    {
        /// <summary>
        /// The name of the user.
        /// </summary>
        public string Name { get; set; }

        /// <summary>
        /// The destination map.
        /// </summary>
        public ushort Map { get; set; }

        /// <summary>
        /// The destination x coordinate.
        /// </summary>
        public float X { get; set; }

        /// <summary>
        /// The destination z coordinate.
        /// </summary>
        public float Z { get; set; }
    }
}

using System;

namespace Shaiya.Web.Api.Models
{
    /// <summary>
    /// The custom data structure.
    /// </summary>
    public unsafe struct Cups
    {
        /// <summary>
        /// A pointer to the user list.
        /// </summary>
        public UInt32 UserListPointer { get; set; }

        /// <summary>
        /// Reads this structure from a byte array.
        /// </summary>
        /// <param name="input">The byte array.</param>
        /// <returns>The structure</returns>
        public static Cups Read(byte[] input)
        {
            fixed (byte* pb = &input[0])
            {
                return *(Cups*)pb;
            }
        }
    }
}

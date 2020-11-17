using System;

namespace Shaiya.Web.Api.Models
{
    /// <summary>
    /// Represents a list of elements.
    /// </summary>
    public unsafe struct CupsList
    {
        /// <summary>
        /// The quantity of elements in this list.
        /// </summary>
        public UInt16 quantity { get; }

        /// <summary>
        /// The capacity of elements in this list.
        /// </summary>
        public UInt16 capacity { get; }

        /// <summary>
        /// Reads this structure from a byte array.
        /// </summary>
        /// <param name="input">The byte array.</param>
        /// <returns>The structure</returns>
        public static CupsList Read(byte[] input)
        {
            fixed (byte* pb = &input[0])
            {
                return *(CupsList*)pb;
            }
        }
    }
}

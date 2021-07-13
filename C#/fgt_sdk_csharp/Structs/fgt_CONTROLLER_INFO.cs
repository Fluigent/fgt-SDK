using fgt_sdk.Enums;
using System;
using System.Runtime.InteropServices;

namespace fgt_sdk.Structs
{
    /// <summary>
    /// Structure containing controller identification and details
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct fgt_CONTROLLER_INFO
    {
        /** Serial number */
        public ushort SN;
        /** Firmware version */
        public ushort Firmware;
        /** Index */
        public uint Id;
        /** Instrument type */
        public fgt_INSTRUMENT_TYPE InstrType;
        /// <summary>
        /// Prints the struct fields
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            return string.Join(Environment.NewLine, new string[] {
                $"Controller SN: {SN}",
                $"Firmware: {(Firmware >> 8) & 0xFF:x}.{Firmware & 0xFF:x2}",
                $"ID: {Id}",
                $"Type: {InstrType}",
            });
        }
    }
}

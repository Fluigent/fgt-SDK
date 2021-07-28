using fgt_sdk.Enums;
using System;

namespace fgt_sdk.Structs
{
    /// <summary>
    /// Structure containing pressure or sensor identification and details
    /// </summary>
    public struct fgt_CHANNEL_INFO
    {
        /** Serial number of this channel's controller */
        public ushort ControllerSN;
        /** Firmware version of this channel (0 if not applicable) */
        public ushort Firmware;
        /** Serial number of this channel (0 if not applicable) */
        public ushort DeviceSN;
        /** Position on controller */
        public uint Position;
        /** Channel index within its physical quantities family */
        public uint Index;
        /** Unique channel identifier */
        public uint IndexId;
        /** Type of the instrument */
        public fgt_INSTRUMENT_TYPE InstrType;
        /// <summary>
        /// Prints the struct fields
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            return string.Join(Environment.NewLine, new string[] {
                $"Controller SN: {ControllerSN}",
                $"Device SN: {DeviceSN}",
                $"Firmware: {(Firmware >> 8) & 0xFF:x}.{Firmware & 0xFF:x2}",
                $"Position: {Position}",
                $"Index: {Index}",
                $"ID: {IndexId}",
                $"Type: {InstrType}",
            });
        }
    }
}
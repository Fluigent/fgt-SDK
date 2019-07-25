using fgt_sdk.Enums;

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
    }
}
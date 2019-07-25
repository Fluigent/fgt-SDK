using fgt_sdk.Enums;
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
    }
}

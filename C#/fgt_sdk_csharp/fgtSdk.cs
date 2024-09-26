using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using fgt_sdk.Enums;
using fgt_sdk.Structs;

namespace fgt_sdk
{
    /// <summary>
    /// Contains the public functions of the Fluigent SDK
    /// </summary>
    public static class fgtSdk
    {
        private const string FGT_SDK = "FGT_SDK";
        private static IntPtr _nativeLibPointer = IntPtr.Zero;
        private static IntPtr ArchResolver(string libraryName, Assembly assembly, DllImportSearchPath? searchPath)
        {
            if (libraryName != FGT_SDK)
            {
                return IntPtr.Zero;
            }
            if (_nativeLibPointer != IntPtr.Zero)
            {
                return _nativeLibPointer;
            }

            var assemblyPath = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) ?? Path.GetDirectoryName(Process.GetCurrentProcess().MainModule.FileName);
            var basePath = Path.Combine(assemblyPath, "runtimes");
            string osFolder;
            string libFile;
            if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
            {
                osFolder = "win";
                libFile = "libfgt_SDK.dll";
            }
            else if (RuntimeInformation.IsOSPlatform(OSPlatform.Linux))
            {
                osFolder = "linux";
                libFile = "libfgt_SDK.so";
            }
            else if (RuntimeInformation.IsOSPlatform(OSPlatform.OSX))
            {
                osFolder = "osx";
                libFile = "libfgt_SDK.dylib";
            }
            else
            {
                throw new NotSupportedException("Operating system not supported");
            }

            var archFolder = RuntimeInformation.ProcessArchitecture switch
            {

                Architecture.X86 => "x86",
                Architecture.X64 => "x64",
                Architecture.Arm => "arm",
                Architecture.Arm64 => "arm64",
                Architecture arch => throw new NotSupportedException($"Architecture {arch} not supported"),
            };

            var libPath = Path.Combine(basePath, $"{osFolder}-{archFolder}", "native", libFile);
            if (!File.Exists(libPath))
            {
                libPath = Path.Combine(assemblyPath, libFile);
            }

            _nativeLibPointer = NativeLibrary.Load(libPath);
            return _nativeLibPointer;
        }

        #region Imported functions

        #region Init/close

        [DllImport(FGT_SDK)]
        private static extern byte fgt_init();

        [DllImport(FGT_SDK)]
        private static extern byte fgt_close();

        // unsigned char __stdcall fgt_detect(unsigned short SN[256], int type[256]);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_detect(ushort[] serialNumbers, int[] type);

        //unsigned char __stdcall fgt_initEx(unsigned short SN[256]);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_initEx(ushort[] serialNumbers);

        [DllImport(FGT_SDK)]
        private static extern byte fgt_create_simulated_instr(fgt_INSTRUMENT_TYPE type, ushort serial, ushort version, int[] config, int length);

        [DllImport(FGT_SDK)]
        private static extern byte fgt_remove_simulated_instr(fgt_INSTRUMENT_TYPE type, ushort serial);

        #endregion

        #region Channels info

        // unsigned char __stdcall fgt_get_controllersInfo(fgt_CONTROLLER_INFO info[256]);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_get_controllersInfo([Out, MarshalAs(UnmanagedType.LPArray, SizeConst = 256)] fgt_CONTROLLER_INFO[] controllersInfo);

        // unsigned char __stdcall fgt_get_pressureChannelCount(unsigned char* nbPChan);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_get_pressureChannelCount(ref byte count);

        // unsigned char __stdcall fgt_get_sensorChannelCount(unsigned char* nbSChan);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_get_sensorChannelCount(ref byte count);

        // unsigned char __stdcall fgt_get_TtlChannelCount(unsigned char* nbTtlChan);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_get_TtlChannelCount(ref byte count);

        // unsigned char FGT_API fgt_get_valveChannelCount(unsigned char* nbValveChan);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_get_valveChannelCount(ref byte count);

        // unsigned char __stdcall fgt_get_pressureChannelsInfo(fgt_CHANNEL_INFO info[256]);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_get_pressureChannelsInfo([Out, MarshalAs(UnmanagedType.LPArray, SizeConst = 256)] fgt_CHANNEL_INFO[] info);

        // unsigned char __stdcall fgt_get_sensorChannelsInfo(fgt_CHANNEL_INFO info[256], int sensorType[256]);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_get_sensorChannelsInfo([Out, MarshalAs(UnmanagedType.LPArray, SizeConst = 256)] fgt_CHANNEL_INFO[] info, int[] type);

        // unsigned char __stdcall fgt_get_TtlChannelsInfo(fgt_CHANNEL_INFO info[256], int sensorType[256]);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_get_TtlChannelsInfo([Out, MarshalAs(UnmanagedType.LPArray, SizeConst = 256)] fgt_CHANNEL_INFO[] info);

        // unsigned char FGT_API fgt_get_valveChannelsInfo(fgt_CHANNEL_INFO info[256], fgt_VALVE_TYPE valveType[256]);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_get_valveChannelsInfo([Out, MarshalAs(UnmanagedType.LPArray, SizeConst = 256)] fgt_CHANNEL_INFO[] info, int[] type);

        #endregion

        #region Basic functions

        // unsigned char __stdcall fgt_set_pressure(unsigned int pressureIndex, float pressure);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_set_pressure(uint pressureIndex, float pressure);

        // unsigned char __stdcall fgt_get_pressure(unsigned int pressureIndex, float* pressure);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_get_pressure(uint pressureIndex, ref float pressure);

        // unsigned char __stdcall fgt_get_pressureEx(unsigned int pressureIndex, float* pressure, unsigned short* timeStamp);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_get_pressureEx(uint pressureIndex, ref float pressure, ref ushort timeStamp);

        // unsigned char __stdcall fgt_set_sensorRegulation(unsigned int sensorIndex, unsigned int pressureIndex, float setpoint);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_set_sensorRegulation(uint sensorIndex, uint pressureIndex, float setpoint);

        // unsigned char __stdcall fgt_get_sensorValue(unsigned int sensorIndex, float* value);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_get_sensorValue(uint sensorIndex, ref float value);

        // unsigned char __stdcall fgt_get_sensorValueEx(unsigned int sensorIndex, float* value, unsigned short* timeStamp);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_get_sensorValueEx(uint sensorIndex, ref float value, ref ushort timeStamp);

        // unsigned char FGT_API fgt_get_valvePosition(unsigned int valveIndex, int* position);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_get_valvePosition(uint valveIndex, ref int position);

        // unsigned char FGT_API fgt_set_valvePosition(unsigned int valveIndex, int position, int direction, bool wait);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_set_valvePosition(uint valveIndex, int position, int direction, int wait);

        // uunsigned char FGT_API fgt_set_allValves(unsigned int controllerIndex, unsigned int moduleIndex, int position);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_set_allValves(uint controllerIndex, uint moduleIndex, int position);

        #endregion

        #region Unit, calibration and limits

        // unsigned char __stdcall fgt_set_sessionPressureUnit(char unit[140]);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_set_sessionPressureUnit(char[] unit);

        // unsigned char __stdcall fgt_set_pressureUnit(unsigned int presureIndex, char unit[140]);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_set_pressureUnit(uint pressureIndex, char[] unit);

        // unsigned char __stdcall fgt_get_pressureUnit(unsigned int pressureIndex, char unit[140]);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_get_pressureUnit(uint pressureIndex, [Out, MarshalAs(UnmanagedType.LPArray, SizeConst = 140)] char[] unit);

        // unsigned char __stdcall fgt_set_sensorUnit(unsigned int sensorIndex, char unit[140]);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_set_sensorUnit(uint sensorIndex, char[] unit);

        // unsigned char __stdcall fgt_get_sensorUnit(unsigned int sensorIndex, char unit[140]);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_get_sensorUnit(uint sensorIndex, [Out, MarshalAs(UnmanagedType.LPArray, SizeConst = 140)] char[] unit);

        // unsigned char __stdcall fgt_set_sensorCalibration(unsigned int sensorIndex, int calibration);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_set_sensorCalibration(uint sensorIndex, int calibration);

        // unsigned char __stdcall fgt_get_sensorCalibration(unsigned int sensorIndex, int* calibration);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_get_sensorCalibration(uint sensorIndex, ref int calibration);

        // unsigned char __stdcall fgt_set_sensorCustomScale(unsigned int sensorIndex, float a, float b, float c);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_set_sensorCustomScale(uint sensorIndex, float a, float b, float c);

        // unsigned char __stdcall fgt_set_sensorCustomScaleEx(unsigned int sensorIndex, float a, float b, float c, float SMax);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_set_sensorCustomScaleEx(uint sensorIndex, float a, float b, float c, float sMax);

        // unsigned char __stdcall fgt_calibratePressure(unsigned int pressureIndex);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_calibratePressure(uint pressureIndex);

        // unsigned char __stdcall fgt_set_customSensorRegulation(float measure, float setpoint, float maxSensorRange, unsigned int pressureIndex);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_set_customSensorRegulation(float measure, float setpoint, float maxSensorRange, uint pressureIndex);

        // unsigned char __stdcall fgt_get_pressureRange(unsigned int pressureIndex, float* Pmin, float* Pmax);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_get_pressureRange(uint pressureIndex, ref float pMin, ref float pMax);

        // unsigned char __stdcall fgt_get_sensorRange(unsigned int sensorIndex, float* Smin, float* Smax);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_get_sensorRange(uint sensorIndex, ref float sMin, ref float sMax);

        // unsigned char FGT_API fgt_get_valveRange(unsigned int valveIndex, int* posMax);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_get_valveRange(uint valveIndex, ref int posMax);

        // unsigned char __stdcall fgt_set_pressureLimit(unsigned int pressureIndex, float PlimMin, float PlimMax);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_set_pressureLimit(uint pressureIndex, float pLimMin, float pLimMax);

        #endregion

        #region Regulation settings

        // unsigned char __stdcall fgt_set_sensorRegulationResponse(unsigned int sensorIndex, unsigned int responseTime);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_set_sensorRegulationResponse(uint sensorIndex, uint responseTime);

        // unsigned char __stdcall fgt_set_pressureResponse(unsigned int pressureIndex, unsigned char value);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_set_pressureResponse(uint pressureIndex, byte value);

        #endregion

        #region Status information

        // unsigned char __stdcall fgt_get_pressureStatus(unsigned int pressureIndex, int* type, unsigned short* controllerSN, unsigned char* infoCode, char detail[140]);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_get_pressureStatus(uint pressureIndex, ref int type, ref ushort controllerSN, ref byte infoCode, [Out, MarshalAs(UnmanagedType.LPArray, SizeConst = 140)] char[] detail);

        // unsigned char __stdcall fgt_get_sensorStatus(unsigned int sensorIndex, int* type, unsigned short* controllerSN, unsigned char* infoCode, char detail[140]);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_get_sensorStatus(uint sensorIndex, ref int type, ref ushort controllerSN, ref byte infoCode, [Out, MarshalAs(UnmanagedType.LPArray, SizeConst = 140)] char[] detail);

        // unsigned char __stdcall fgt_set_power(unsigned int controllerIndex, unsigned char powerState);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_set_power(uint controllerIndex, byte powerState);

        // unsigned char __stdcall fgt_get_power(unsigned int controllerIndex, unsigned char* powerState);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_get_power(uint controllerIndex, ref byte powerState);

        #endregion

        #region TTL functions

        // unsigned char __stdcall fgt_set_TtlMode(unsigned int TtlIndex, int mode);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_set_TtlMode(uint TtlIndex, int mode);

        // unsigned char __stdcall fgt_read_Ttl(unsigned int TtlIndex, unsigned int* state);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_read_Ttl(uint TtlIndex, ref uint state);

        // unsigned char __stdcall fgt_trigger_Ttl(unsigned int TtlIndex);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_trigger_Ttl(uint TtlIndex);

        #endregion

        #region Specific functions

        // unsigned char __stdcall fgt_set_purge(unsigned int controllerIndex, unsigned char purge);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_set_purge(uint controllerIndex, byte purge);

        // unsigned char __stdcall fgt_set_manual(unsigned int pressureIndex, float value);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_set_manual(uint pressureIndex, float value);

        // unsigned char __stdcall fgt_set_digitalOutput(unsigned int controllerIndex, unsigned char state);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_set_digitalOutput(uint controllerIndex, byte port, byte state);

        // unsigned char __stdcall fgt_get_sensorAirBubbleFlag(unsigned int sensorIndex, unsigned char* detected);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_get_sensorAirBubbleFlag(uint pressureIndex, ref byte detected);

        // unsigned char __stdcall fgt_get_inletPressure(unsigned int pressureIndex, float* pressure);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_get_inletPressure(uint pressureIndex, ref float pressure);

        // unsigned char __stdcall fgt_get_differentialPressureRange(unsigned int sensorIndex, float* Pmin, float* Pmax);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_get_differentialPressureRange(uint sensorIndex, ref float pMin, ref float pMax);

        // unsigned char __stdcall fgt_get_differentialPressure(unsigned int sensorIndex, float* Pdiff);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_get_differentialPressure(uint sensorIndex, ref float pDiff);

        // unsigned char __stdcall fgt_get_absolutePressureRange(unsigned int sensorIndex, float* Pmin, float* Pmax);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_get_absolutePressureRange(uint sensorIndex, ref float pMin, ref float pMax);

        // unsigned char __stdcall fgt_get_absolutePressure(unsigned int sensorIndex, float* Pabs);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_get_absolutePressure(uint sensorIndex, ref float pAbs);

        // unsigned char __stdcall fgt_get_sensorBypassValve(unsigned int sensorIndex, unsigned char* state)
        [DllImport(FGT_SDK)]
        private static extern byte fgt_get_sensorBypassValve(uint sensorIndex, ref byte state);

        // unsigned char __stdcall fgt_set_sensorBypassValve(unsigned int sensorIndex, unsigned char state)
        [DllImport(FGT_SDK)]
        private static extern byte fgt_set_sensorBypassValve(uint sensorIndex, byte state);

        #endregion

        #region Logging
        // unsigned char FGT_API fgt_set_log_verbosity(unsigned int verbosity);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_set_log_verbosity(uint verbosity);

        // unsigned char FGT_API fgt_set_log_output_mode(unsigned char output_to_file, unsigned char output_to_stderr, unsigned char output_to_queue);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_set_log_output_mode(byte output_to_file, byte output_to_stderr, byte output_to_queue);

        // unsigned char FGT_API fgt_get_next_log(char log[2000]);
        [DllImport(FGT_SDK)]
        private static extern byte fgt_get_next_log([Out, MarshalAs(UnmanagedType.LPArray, SizeConst = 2000)] char[] detail);
        #endregion

        #endregion

        private static fgt_ERROR_REPORT_MODE _errorReportMode;
        static fgtSdk()
        {
            NativeLibrary.SetDllImportResolver(typeof(fgtSdk).Assembly, ArchResolver);
            _errorReportMode = fgt_ERROR_REPORT_MODE.Print;
        }

        #region Private methods

        /// <summary>
        /// This method logs to the console detailed information in case an error code has been returned by a low level function
        /// </summary>
        /// <param name="errorCode">Error code returned by a low level call</param>
        /// <param name="type">Type of check to perform</param>
        /// <param name="index">Pressure or sensor index the low level function used</param>
        /// <param name="memberName"></param>
        /// <returns>The error code <see cref="fgt_ERROR_CODE"/> that was returned by the low level function</returns>
        private static fgt_ERROR_CODE ErrCheck(fgt_ERROR_CODE errorCode, fgt_ERRCHECK_TYPE type, uint index = 0, [System.Runtime.CompilerServices.CallerMemberName] string memberName = "")
        {
            if (_errorReportMode == fgt_ERROR_REPORT_MODE.None || errorCode == fgt_ERROR_CODE.OK)
            {
                return errorCode;
            }

            fgt_ERROR_CODE localErrorCode;
            fgt_INSTRUMENT_TYPE instrumentType;
            ushort controllerSerialNumber;
            bool locallyControlled;
            string details;

            switch (type)
            {
                case fgt_ERRCHECK_TYPE.Generic:
                    Console.WriteLine($"{memberName} method returned {errorCode} error");
                    break;
                case fgt_ERRCHECK_TYPE.Pressure:
                    (localErrorCode, instrumentType, controllerSerialNumber, locallyControlled, details) = Fgt_get_pressureStatus(index);
                    Console.WriteLine($"{memberName} method called on pressure channel {index} of type {instrumentType} returned an error {localErrorCode}. Details: {details}, Controller S/N: {controllerSerialNumber} was {(locallyControlled ? "locally" : "remotely")} controlled");
                    break;
                case fgt_ERRCHECK_TYPE.Sensor:
                    (localErrorCode, instrumentType, controllerSerialNumber, locallyControlled, details) = Fgt_get_sensorStatus(index);
                    Console.WriteLine($"{memberName} method called on pressure channel {index} of type {instrumentType} returned an error {localErrorCode}. Details: {details}, Controller S/N: {controllerSerialNumber} was {(locallyControlled ? "locally" : "remotely")} controlled");
                    break;
                default:
                    throw new ArgumentOutOfRangeException(nameof(type), type, null);
            }

            // Error always traverses this method
            return errorCode;
        }

        #endregion

        #region Public methods

        #region Init/close

        /// <summary>
        /// Initialize or reinitialize (if already opened) Fluigent SDK instance. All detected Fluigent instruments (MFCS, MFCS-EZ, FRP, LineUP, IPS) are initialized.
        /// This function is optional, directly calling a function will automatically creates the instance.
        /// Only one instance can be opened at a time. If called again, any new instruments are added to the same instance.
        /// </summary>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/></returns>
        public static fgt_ERROR_CODE Fgt_init()
        {
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_init(), fgt_ERRCHECK_TYPE.Generic);
            return errCode;
        }

        /// <summary>
        /// Close communication with Fluigent instruments and free memory.
        /// This function is mandatory, if not called the dll will will generate an exception will generate an exception when exiting your application.
        /// Using this function will remove session preferences such as units and limits.If any regulation is running it will stop pressure control.
        /// </summary>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/></returns>
        public static fgt_ERROR_CODE Fgt_close()
        {
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_close(), fgt_ERRCHECK_TYPE.Generic);
            return errCode;
        }

        /// <summary>
        /// Detects all connected Fluigent instrument(s)
        /// </summary>
        /// <returns>Instruments count and their serial numbers and types</returns>
        public static (byte count, List<(ushort serialNumber, fgt_INSTRUMENT_TYPE type)> instruments) Fgt_detect()
        {
            var serialNumbers = new ushort[256];
            var types = new int[256];
            var count = fgt_detect(serialNumbers, types);

            var tuplesList = new List<(ushort, fgt_INSTRUMENT_TYPE)>();

            for (var i = 0; i < serialNumbers.Length; i++)
            {
                if (serialNumbers[i] != 0)
                {
                    tuplesList.Add((serialNumbers[i], (fgt_INSTRUMENT_TYPE)types[i]));
                }
            }
            return (count, tuplesList);
        }

        /// <summary>
        /// Initialize specific Fluigent instrument(s) from their unique serial number.
        /// This function can be used when multiple instruments are connected in order to select your device(s)
        /// </summary>
        /// <param name="serialNumbers">List of instruments' serial numbers</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/></returns>
        public static fgt_ERROR_CODE Fgt_initEx(List<ushort> serialNumbers)
        {
            var sns = new ushort[256];

            try
            {
                for (var i = 0; i < serialNumbers.Count; i++)
                {
                    sns[i] = serialNumbers[i];
                }
            }
            catch (IndexOutOfRangeException e)
            {
                Console.WriteLine(e);
                throw;
            }

            return ErrCheck((fgt_ERROR_CODE)fgt_initEx(sns), fgt_ERRCHECK_TYPE.Generic);
        }

        /// <summary>
        /// Creates a simulated Fluigent instrument, which can be detected and initialized like a real one,
        /// for the purposes of testing and demonstrations.
        /// </summary>
        /// <param name="type">Type of instrument to simulate</param>
        /// <param name="serial">Serial number for the simulated instrument</param>
        /// <param name="version">Firmware version for the simulated instrument. Set to 0 to use the default version</param>
        /// <param name="config">Array describing the instrument's configuration</param>
        /// <returns></returns>
        public static fgt_ERROR_CODE Fgt_create_simulated_instr(fgt_INSTRUMENT_TYPE type, ushort serial, ushort version, int[] config)
        {
            return ErrCheck((fgt_ERROR_CODE)fgt_create_simulated_instr(type, serial, version, config, config.Length), fgt_ERRCHECK_TYPE.Generic);
        }

        /// <summary>
        /// Removes a simulated instrument that had been previously created. If it had already been initialized
        /// by the SDK, the controller and channels will remain in the respective lists, but they will act as if
        /// the instrument is missing. This is equivalent to physically disconnecting a real instrument.
        /// </summary>
        /// <param name="type">Type of instrument to remove</param>
        /// <param name="serial">Serial number of the simulated instrument</param>
        /// <returns></returns>
        public static fgt_ERROR_CODE Fgt_remove_simulated_instr(fgt_INSTRUMENT_TYPE type, ushort serial)
        {
            return ErrCheck((fgt_ERROR_CODE)fgt_remove_simulated_instr(type, serial), fgt_ERRCHECK_TYPE.Generic);
        }

        #endregion

        #region Channels info

        /// <summary>
        /// Retrieve information about session controllers. Controllers are MFCS, Flowboard, Link, IPS, and Switchboard.
        /// </summary>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/> and a list of <see cref="fgt_CONTROLLER_INFO"/></returns>
        public static (fgt_ERROR_CODE errCode, List<fgt_CONTROLLER_INFO> info) Fgt_get_controllersInfo()
        {
            var controllersInfo = new fgt_CONTROLLER_INFO[256];
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_get_controllersInfo(controllersInfo), fgt_ERRCHECK_TYPE.Generic);
            var controllersInfoList = controllersInfo.Where(c => c.SN != 0).ToList();
            return (errCode, controllersInfoList);
        }

        /// <summary>
        /// Get total number of initialized pressure channels. It is the sum of all MFCS, MFCS-EZ and FlowEZ pressure controllers
        /// </summary>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/> and pressure channels count</returns>
        public static (fgt_ERROR_CODE errCode, int count) Fgt_get_pressureChannelCount()
        {
            byte count = 0;
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_get_pressureChannelCount(ref count), fgt_ERRCHECK_TYPE.Generic);
            return (errCode, count);
        }

        /// <summary>
        /// Get total number of initialized sensor channels. It is the sum of all connected flow-units on Flowboard and FlowEZ, and IPS sensors
        /// </summary>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/> and sensor channels count</returns>
        public static (fgt_ERROR_CODE errCode, int count) Fgt_get_sensorChannelCount()
        {
            byte count = 0;
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_get_sensorChannelCount(ref count), fgt_ERRCHECK_TYPE.Generic);
            return (errCode, count);
        }

        /// <summary>
        /// Get total number of initialized TTL channels. It is the sum of all connected Link TTL ports
        /// </summary>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/> and Ttl channels count</returns>
        public static (fgt_ERROR_CODE errCode, int count) Fgt_get_TtlChannelCount()
        {
            byte count = 0;
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_get_TtlChannelCount(ref count), fgt_ERRCHECK_TYPE.Generic);
            return (errCode, count);
        }

        /// <summary>
        /// Get total number of initialized valve channels. It is the sum of all connected Two-Switch,
        /// L-Switch and M-Switch valves connected to Switchboard or Switch EZ devices, as well
        /// as individual P-Switch outputs(8 per device).
        /// </summary>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/> and valve channels count</returns>
        public static (fgt_ERROR_CODE errCode, int count) Fgt_get_valveChannelCount()
        {
            byte count = 0;
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_get_valveChannelCount(ref count), fgt_ERRCHECK_TYPE.Generic);
            return (errCode, count);
        }

        /// <summary>
        /// Retrieve information about each initialized pressure channel. This function is useful in order to get channels order, controller, unique ID and intrument type.
        /// By default this array is built with MFCS first, MFCS-EZ second and FlowEZ last.If only one instrument is used, index is the default channel indexing starting at 0.
        /// You can initialize instruments in specific order using <see cref="Fgt_initEx"/> function
        /// </summary>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/> and a list of <see cref="fgt_CHANNEL_INFO"/></returns>
        public static (fgt_ERROR_CODE errCode, List<fgt_CHANNEL_INFO> info) Fgt_get_pressureChannelsInfo()
        {
            var info = new fgt_CHANNEL_INFO[256];
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_get_pressureChannelsInfo(info), fgt_ERRCHECK_TYPE.Generic);
            var controllersInfoList = info.Where(c => c.ControllerSN != 0).ToList();
            return (errCode, controllersInfoList);
        }

        /// <summary>
        /// Retrieve information about each initialized sensor channel.This function is useful in order to get channels order, controller, unique ID and instrument type.
        /// By default this array is built with FRP Flow Units first, followed by Flow EZ Flow Units, followed by IPS modules. If only one instrument is used, index is the default channel indexing starting at 0.
        /// You can initialize instruments in specific order using <see cref="Fgt_initEx"/> function
        /// </summary>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/> and a list of <see cref="fgt_CHANNEL_INFO"/> <see cref="fgt_SENSOR_TYPE"/> tuples</returns>
        public static (fgt_ERROR_CODE errCode, List<(fgt_CHANNEL_INFO channelInfo, fgt_SENSOR_TYPE sensorType)> info) Fgt_get_sensorChannelsInfo()
        {
            var info = new fgt_CHANNEL_INFO[256];
            var type = new int[256];
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_get_sensorChannelsInfo(info, type), fgt_ERRCHECK_TYPE.Generic);
            var tuplesList = new List<(fgt_CHANNEL_INFO, fgt_SENSOR_TYPE)>();
            for (var index = 0; index < info.Length; index++)
            {
                if (info[index].ControllerSN != 0)
                {
                    tuplesList.Add((info[index], (fgt_SENSOR_TYPE)type[index]));
                }
            }

            return (errCode, tuplesList);
        }

        /// <summary>
        /// Retrieve information about each initialized TTL channel. This function is useful in order to get channels order, controller, unique ID and instrument type.
        /// TTL channels are only available for LineUP Series, 2 ports for each connected Link
        /// </summary>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/> and a list of <see cref="fgt_CHANNEL_INFO"/></returns>
        public static (fgt_ERROR_CODE errCode, List<fgt_CHANNEL_INFO> info) Fgt_get_TtlChannelsInfo()
        {
            var info = new fgt_CHANNEL_INFO[256];
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_get_TtlChannelsInfo(info), fgt_ERRCHECK_TYPE.Generic);
            var controllersInfoList = info.Where(c => c.ControllerSN != 0).ToList();
            return (errCode, controllersInfoList);
        }

        /// <summary>
        /// Retrieve information about each initialized valve channel. This function is useful in order to get channels order, controller, unique ID and instrument type.
        /// You can initialize instruments in specific order using <see cref="Fgt_initEx"/> function
        /// </summary>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/> and a list of <see cref="fgt_CHANNEL_INFO"/> <see cref="fgt_VALVE_TYPE"/> tuples</returns>
        public static (fgt_ERROR_CODE errCode, List<(fgt_CHANNEL_INFO channelInfo, fgt_VALVE_TYPE sensorType)> info) Fgt_get_valveChannelsInfo()
        {
            var info = new fgt_CHANNEL_INFO[256];
            var type = new int[256];
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_get_valveChannelsInfo(info, type), fgt_ERRCHECK_TYPE.Generic);
            var tuplesList = new List<(fgt_CHANNEL_INFO, fgt_VALVE_TYPE)>();
            for (var index = 0; index < info.Length; index++)
            {
                if (info[index].ControllerSN != 0)
                {
                    tuplesList.Add((info[index], (fgt_VALVE_TYPE)type[index]));
                }
            }

            return (errCode, tuplesList);
        }

        #endregion

        #region Basic functions

        /// <summary>
        /// Send pressure command to selected device
        /// </summary>
        /// <param name="pressureIndex">Index of pressure channel or unique ID</param>
        /// <param name="pressure">Pressure order in selected unit, default is "mbar"</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/></returns>
        public static fgt_ERROR_CODE Fgt_set_pressure(uint pressureIndex, float pressure)
        {
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_set_pressure(pressureIndex, pressure), fgt_ERRCHECK_TYPE.Pressure, pressureIndex);
            return errCode;
        }

        /// <summary>
        /// Read pressure value of selected device
        /// </summary>
        /// <param name="pressureIndex">Index of pressure channel or unique ID</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/> and current pressure</returns>
        public static (fgt_ERROR_CODE errCode, float pressure) Fgt_get_pressure(uint pressureIndex)
        {
            var pressure = 0.0f;
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_get_pressure(pressureIndex, ref pressure), fgt_ERRCHECK_TYPE.Pressure, pressureIndex);
            return (errCode, pressure);
        }

        /// <summary>
        /// Read pressure value and time stamp of selected device. Time stamp is the device internal timer.
        /// </summary>
        /// <param name="pressureIndex">Index of pressure channel or unique ID</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/>, current pressure and device internal timer value</returns>
        public static (fgt_ERROR_CODE errCode, float pressure, ushort timeStamp) Fgt_get_pressureEx(uint pressureIndex)
        {
            var pressure = 0.0f;
            ushort timestamp = 0;
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_get_pressureEx(pressureIndex, ref pressure, ref timestamp), fgt_ERRCHECK_TYPE.Pressure, pressureIndex);
            return (errCode, pressure, timestamp);
        }

        /// <summary>
        /// Start closed loop regulation between a flowrate sensor and a pressure controller. Pressure will be regulated in order to reach sensor setpoint.
        /// Call again this function in order to change the setpoint.Calling fgt_set_pressure on same pressureIndex will stop regulation.
        /// </summary>
        /// <param name="sensorIndex">Index of sensor channel or unique ID</param>
        /// <param name="pressureIndex">Index of pressure channel or unique ID</param>
        /// <param name="setpoint">Regulation value to be reached in selected unit, default is "µl/min" for flowrate sensors</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/></returns>
        public static fgt_ERROR_CODE Fgt_set_sensorRegulation(uint sensorIndex, uint pressureIndex, float setpoint)
        {
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_set_sensorRegulation(sensorIndex, pressureIndex, setpoint), fgt_ERRCHECK_TYPE.Sensor, sensorIndex);
            return errCode;
        }

        /// <summary>
        /// Read sensor value of selected device
        /// </summary>
        /// <param name="sensorIndex">Index of sensor channel or unique ID</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/> and current sensor measurement in selected unit, default is "µl/min" for flowrate sensors and 'mbar' for pressure sensors</returns>
        public static (fgt_ERROR_CODE errCode, float value) Fgt_get_sensorValue(uint sensorIndex)
        {
            var value = 0.0f;
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_get_sensorValue(sensorIndex, ref value), fgt_ERRCHECK_TYPE.Sensor, sensorIndex);
            return (errCode, value);
        }

        /// <summary>
        /// Read sensor value and timestamp of selected device. Time stamp is the device internal timer.
        /// </summary>
        /// <param name="sensorIndex">Index of sensor channel or unique ID</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/>, current sensor measurement and device internal timer value</returns>
        public static (fgt_ERROR_CODE errCode, float value, ushort timeStamp) Fgt_get_sensorValueEx(uint sensorIndex)
        {
            var value = 0.0f;
            ushort timestamp = 0;
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_get_sensorValueEx(sensorIndex, ref value, ref timestamp), fgt_ERRCHECK_TYPE.Sensor, sensorIndex);
            return (errCode, value, timestamp);
        }

        /// <summary>
        /// Read the position of a specific valve channel.
        /// </summary>
        /// <param name="valveIndex">Index of valve channel or unique ID</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/> and current position</returns>
        public static (fgt_ERROR_CODE errCode, int position) Fgt_get_valvePosition(uint valveIndex)
        {
            var position = 0;
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_get_valvePosition(valveIndex, ref position), fgt_ERRCHECK_TYPE.Generic, valveIndex);
            return (errCode, position);
        }

        /// <summary>
        /// Set the position of a specific valve channel.
        /// </summary>
        /// <param name="valveIndex">Index of valve channel or unique ID</param>
        /// <param name="position">position Desired valve position</param>
        /// <param name="direction">Direction of the movement (applies only for M-Switch valve type)</param>
        /// <param name="wait">Flag indicating if function should wait until the desired position is reached or not</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/></returns>
        public static fgt_ERROR_CODE Fgt_set_valvePosition(uint valveIndex, int position, fgt_SWITCH_DIRECTION direction = fgt_SWITCH_DIRECTION.Shortest, bool wait = true)
        {
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_set_valvePosition(valveIndex, position, (int)direction, wait ? 1 : 0), fgt_ERRCHECK_TYPE.Generic, valveIndex);
            return errCode;
        }

        /// <summary>
        /// Set the position of all two positional valves connected to specified controller / module.
        /// </summary>
        /// <param name="controllerIndex">Index of sensor channel or unique ID</param>
        /// <param name="moduleIndex">Index of the module (supported only by P-Switch)</param>
        /// <param name="position">Desired position (0 or 1)</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/></returns>
        public static fgt_ERROR_CODE Fgt_set_allValves(uint controllerIndex, uint moduleIndex, int position)
        {
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_set_allValves(controllerIndex, moduleIndex, position), fgt_ERRCHECK_TYPE.Generic, controllerIndex);
            return errCode;
        }

        #endregion

        #region Unit, calibration and limits

        /// <summary>
        /// Set pressure unit for all initialized channels, default value is "mbar". If type is invalid an error is returned.
        /// Every pressure read value and sent command will then use this unit.
        /// </summary>
        /// <param name="unit">Unit to use. Example: "mbar", "millibar", "kPa" ...</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/></returns>
        public static fgt_ERROR_CODE Fgt_set_sessionPressureUnit(string unit)
        {
            var unitArray = unit.ToCharArray();
            var pressureUnit = new char[140];

            try
            {
                unitArray.CopyTo(pressureUnit, 0);
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                throw;
            }

            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_set_sessionPressureUnit(pressureUnit), fgt_ERRCHECK_TYPE.Pressure);
            return errCode;
        }

        /// <summary>
        /// Set pressure unit on selected pressure device, default value is "mbar". If type is invalid an error is returned.
        /// Every pressure read value and sent command will then use this unit.
        /// </summary>
        /// <param name="pressureIndex">Index of pressure channel or unique ID</param>
        /// <param name="unit">Unit to use. Example: "mbar", "millibar", "kPa" ...</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/></returns>
        public static fgt_ERROR_CODE Fgt_set_pressureUnit(uint pressureIndex, string unit)
        {
            var unitArray = unit.ToCharArray();
            var pressureUnit = new char[140];

            try
            {
                unitArray.CopyTo(pressureUnit, 0);
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                throw;
            }

            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_set_pressureUnit(pressureIndex, pressureUnit), fgt_ERRCHECK_TYPE.Pressure, pressureIndex);
            return errCode;
        }

        /// <summary>
        /// Get current unit on selected pressure device, default value is "mbar".
        /// Every pressure read value and sent command use this unit.
        /// </summary>
        /// <param name="pressureIndex">Index of pressure channel or unique ID</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/> and the current unit string</returns>
        public static (fgt_ERROR_CODE errCode, string unit) Fgt_get_pressureUnit(uint pressureIndex)
        {
            var pressureUnit = new char[140];
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_get_pressureUnit(pressureIndex, pressureUnit), fgt_ERRCHECK_TYPE.Pressure, pressureIndex);

            var unitString = new string(pressureUnit.TakeWhile(c => c != '\0').ToArray());
            return (errCode, unitString);
        }

        /// <summary>
        /// Set sensor unit on selected sensor device, default value is "µl/min" for flowrate sensors and "mbar" for pressure sensors. If type is invalid an error is returned.
        /// Every sensor read value and regulation command will then use this unit.
        /// </summary>
        /// <param name="sensorIndex">Index of sensor channel or unique ID</param>
        /// <param name="sensorUnit">Sensor unit string. Example: "µl/h", "ulperDay", "microliter/hour" ...</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/></returns>
        public static fgt_ERROR_CODE Fgt_set_sensorUnit(uint sensorIndex, string sensorUnit)
        {
            var unitArray = sensorUnit.ToCharArray();
            var unit = new char[140];

            try
            {
                unitArray.CopyTo(unit, 0);
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                throw;
            }

            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_set_sensorUnit(sensorIndex, unit), fgt_ERRCHECK_TYPE.Sensor, sensorIndex);
            return errCode;
        }

        /// <summary>
        /// Get current unit on selected sensor device, default value is "µl/min" for flowunits and 'mbar' for pressure sensors.
        /// Every sensor read value and regulation command use this unit.
        /// </summary>
        /// <param name="sensorIndex">Index of sensor channel or unique ID</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/> and the current unit string</returns>
        public static (fgt_ERROR_CODE errCode, string unit) Fgt_get_sensorUnit(uint sensorIndex)
        {
            var unit = new char[140];
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_get_sensorUnit(sensorIndex, unit), fgt_ERRCHECK_TYPE.Sensor, sensorIndex);

            var unitString = new string(unit.TakeWhile(c => c != '\0').ToArray());
            return (errCode, unitString);
        }

        /// <summary>
        /// Set sensor internal calibration table.
        /// Function is only available for IPS (to set new reference value "zero") and specific flowrate sensors (dual type) such as the flow-unit M accepting H2O and IPA
        /// </summary>
        /// <param name="sensorIndex">Index of sensor channel or unique ID</param>
        /// <param name="table">New calibration table</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/></returns>
        public static fgt_ERROR_CODE Fgt_set_sensorCalibration(uint sensorIndex, fgt_SENSOR_CALIBRATION table)
        {
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_set_sensorCalibration(sensorIndex, (int)table), fgt_ERRCHECK_TYPE.Sensor, sensorIndex);
            return errCode;
        }

        /// <summary>
        /// Get sensor's current calibration table. Not supported by IPS.
        /// </summary>
        /// <param name="sensorIndex">Index of sensor channel or unique ID</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/> and the current calibration table <see cref="fgt_SENSOR_CALIBRATION"/></returns>
        public static (fgt_ERROR_CODE errCode, fgt_SENSOR_CALIBRATION table) Fgt_get_sensorCalibration(uint sensorIndex)
        {
            var table = 0;
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_get_sensorCalibration(sensorIndex, ref table), fgt_ERRCHECK_TYPE.Sensor, sensorIndex);

            return (errCode, (fgt_SENSOR_CALIBRATION)table);
        }

        /// <summary>
        /// Apply a custom scale factor on sensor read value. This function is useful in order to adapt read sensor value to physical measurement.
        /// For example if a flow-unit is used with a special oil and it's calibration table is set to H2O, read flowrate is not correct.
        /// Scale factor is applied using following formula: scaled_value = a* sensor_value + b* sensor_value^2 + c* sensor_value^3
        /// Note that this scale is also used for the regulation. Not supported by IPS.
        /// </summary>
        /// <param name="sensorIndex">sensorIndex Index of sensor channel or unique ID</param>
        /// <param name="scale">New scale to use - a*x + b*x² + c*x³ </param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/></returns>
        public static fgt_ERROR_CODE Fgt_set_sensorCustomScale(uint sensorIndex, (float a, float b, float c) scale)
        {
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_set_sensorCustomScale(sensorIndex, scale.a, scale.b, scale.c), fgt_ERRCHECK_TYPE.Sensor, sensorIndex);
            return errCode;
        }

        /// <summary>
        /// Apply a custom scale factor on sensor measurement. This function is useful in order to adapt read sensor value to physical measurement.
        /// For example if a flow-unit is used with a special oil and it's calibration table is set to H2O, read flowrate is not correct.
        /// Scale factor is applied using following formula: scaled_value = a* sensor_value + b* sensor_value^2 + c* sensor_value^3
        /// When applying a custom scale factor, sensor range may increase very rapidly, SMax parameter is meant to limit this maximal value.
        /// This function purpose is to be used with the regulation in order to avoid too high maximum range on the sensor. Not supported by IPS.
        /// </summary>
        /// <param name="sensorIndex">Index of sensor channel or unique ID</param>
        /// <param name="scale">New scale to use - a*x + b*x² + c*x³ </param>
        /// <param name="sMax">SMax after scale maximal value (saturation)</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/></returns>
        public static fgt_ERROR_CODE Fgt_set_sensorCustomScaleEx(uint sensorIndex, (float a, float b, float c) scale, float sMax)
        {
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_set_sensorCustomScaleEx(sensorIndex, scale.a, scale.b, scale.c, sMax), fgt_ERRCHECK_TYPE.Sensor, sensorIndex);
            return errCode;
        }

        /// <summary>
        /// Calibrate internal pressure sensor depending on atmospheric pressure. After calling this function 0 pressure value corresponds to atmospheric pressure.
        /// During calibration step no pressure order is accepted.Total duration vary from 3s to 8s.
        /// </summary>
        /// <param name="pressureIndex">Index of pressure channel or unique ID</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/></returns>
        public static fgt_ERROR_CODE Fgt_calibratePressure(uint pressureIndex)
        {
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_calibratePressure(pressureIndex), fgt_ERRCHECK_TYPE.Pressure, pressureIndex);
            return errCode;
        }

        /// <summary>
        /// Start closed loop regulation between a sensor and a pressure controller. Pressure will be regulated in order to reach sensor setpoint.
        /// Custom sensors, outside Fluigent ones, can be used such as different flow-units, pressure, level ...
        /// However we do not guarantee full compatibility with all sensors. Regulation quality is linked to sensor precision and your set-up.
        /// In order to use this function, custom used sensor maximum range and measured values has to be updated at least once per second.
        /// Directly setting pressure on same pressureIndex will stop regulation. Not supported by IPS.
        /// This function must be called at 1Hz minimum or the regulation will stop.
        /// </summary>
        /// <param name="measure">Custom sensor measured value, no unit is required</param>
        /// <param name="setpoint">Custom sensor regulation goal value, no unit is required</param>
        /// <param name="maxSensorRange">Custom sensor maximum range, no unit is required</param>
        /// <param name="pressureIndex">Index of pressure channel or unique ID</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/></returns>
        public static fgt_ERROR_CODE Fgt_set_customSensorRegulation(float measure, float setpoint, float maxSensorRange, uint pressureIndex)
        {
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_set_customSensorRegulation(measure, setpoint, maxSensorRange, pressureIndex), fgt_ERRCHECK_TYPE.Generic);
            return errCode;
        }

        /// <summary>
        /// Get pressure controller minimum and maximum range. Returned values takes into account set unit, default value is 'mbar'.
        /// </summary>
        /// <param name="pressureIndex">Index of pressure channel or unique ID</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/> and pressure range min and max</returns>
        public static (fgt_ERROR_CODE errCode, float pMin, float pMax) Fgt_get_pressureRange(uint pressureIndex)
        {
            float pMin = 0, pMax = 0;
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_get_pressureRange(pressureIndex, ref pMin, ref pMax), fgt_ERRCHECK_TYPE.Pressure, pressureIndex);
            return (errCode, pMin, pMax);
        }

        /// <summary>
        /// Get sensor minimum and maximum range. Returned values takes into account set unit, default value is 'µl/min' in case of flow-units and 'mbar' for pressure sensors.
        /// </summary>
        /// <param name="sensorIndex">Index of sensor channel or unique ID</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/> and sensor range min and max</returns>
        public static (fgt_ERROR_CODE errCode, (float sMin, float sMax) range) Fgt_get_sensorRange(uint sensorIndex)
        {
            float sMin = 0, sMax = 0;
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_get_sensorRange(sensorIndex, ref sMin, ref sMax), fgt_ERRCHECK_TYPE.Sensor, sensorIndex);
            return (errCode, (sMin, sMax));
        }

        /// <summary>
        /// Get valve maximum position. Position indexing starts at 0.
        /// </summary>
        /// <param name="valveIndex">Index of valve channel or unique ID</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/> and Maximum position of this valve</returns>
        public static (fgt_ERROR_CODE errCode, int posMax) Fgt_get_valveRange(uint valveIndex)
        {
            var posMax = 0;
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_get_valveRange(valveIndex, ref posMax), fgt_ERRCHECK_TYPE.Sensor, valveIndex);
            return (errCode, posMax);
        }

        /// <summary>
        /// Set pressure working range and ensure that pressure will never exceed this limit. It takes into account current unit, default value is 'mbar'.
        /// </summary>
        /// <param name="pressureIndex">Index of pressure channel or unique ID</param>
        /// <param name="limits">Min/max pressure working range values</param>
        /// <returns></returns>
        public static fgt_ERROR_CODE Fgt_set_pressureLimit(uint pressureIndex, (float pMin, float pMax) limits)
        {
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_set_pressureLimit(pressureIndex, limits.pMin, limits.pMax), fgt_ERRCHECK_TYPE.Pressure, pressureIndex);
            return errCode;
        }

        #endregion

        #region Regulation settings

        /// <summary>
        /// Set on a running regulation pressure response time. Minimal value is 2 for FlowEZ, 6 for MFCS controllers.
        /// This function is useful if a more smooth response is wanted. Not supported by IPS.
        /// </summary>
        /// <param name="sensorIndex">Index of sensor channel or unique ID</param>
        /// <param name="responseTime">Pressure response time in seconds</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/></returns>
        public static fgt_ERROR_CODE Fgt_set_sensorRegulationResponse(uint sensorIndex, uint responseTime)
        {
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_set_sensorRegulationResponse(sensorIndex, responseTime), fgt_ERRCHECK_TYPE.Sensor, sensorIndex);
            return errCode;
        }

        /// <summary>
        /// Set pressure controller response. This function can be used to customise response time for your set-up.
        /// For FlowEZ available values are 0: use of fast switch valves or 1: do not use fast switch valves. Default value is 0.
        /// For MFCS available values are from 1 to 255. The bigger the value, the longer is the response time. Default value is 5.
        /// </summary>
        /// <param name="pressureIndex">Index of pressure channel or unique ID</param>
        /// <param name="value"></param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/></returns>
        public static fgt_ERROR_CODE Fgt_set_pressureResponse(uint pressureIndex, byte value)
        {
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_set_pressureResponse(pressureIndex, value), fgt_ERRCHECK_TYPE.Pressure, pressureIndex);
            return errCode;
        }

        #endregion

        #region Status information

        /// <summary>
        /// Get detailed information of pressure channel status. This function is meant to be invoked after calling a pressure related function which returns an error code.
        /// Retrieved information of last error contains controller position and a string detail.
        /// </summary>
        /// <param name="pressureIndex">Index of pressure channel or unique ID</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/>, the controller type and serial number, the locally controlled information boolean and a string describing the error</returns>
        public static (fgt_ERROR_CODE errCode, fgt_INSTRUMENT_TYPE type, ushort controllerSN, bool locallyControlled, string details) Fgt_get_pressureStatus(uint pressureIndex)
        {
            var type = 0;
            ushort controllerSn = 0;
            byte infoCode = 0;
            var details = new char[140];

            var errCode = fgt_get_pressureStatus(pressureIndex, ref type, ref controllerSn, ref infoCode, details);

            var detailsString = new string(details.TakeWhile(c => c != '\0').ToArray());

            return ((fgt_ERROR_CODE)errCode, (fgt_INSTRUMENT_TYPE)type, controllerSN: controllerSn, infoCode == 1, detailsString);
        }

        /// <summary>
        /// Get detailed information of sensor status. This function is meant to be invoked after calling a sensor related function which returns an error code.
        /// Retrieved information of last error contains sensor position and a string detail.
        /// </summary>
        /// <param name="sensorIndex">Index of sensor channel or unique ID</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/>, the controller type and serial number, the locally controlled information boolean and a string describing the error</returns>
        public static (fgt_ERROR_CODE errCode, fgt_INSTRUMENT_TYPE type, ushort controllerSN, bool locallyControlled, string details) Fgt_get_sensorStatus(uint sensorIndex)
        {
            var type = 0;
            ushort controllerSn = 0;
            byte infoCode = 0;
            var details = new char[140];

            var errCode = fgt_get_sensorStatus(sensorIndex, ref type, ref controllerSn, ref infoCode, details);

            var detailsString = new string(details.TakeWhile(c => c != '\0').ToArray());

            return ((fgt_ERROR_CODE)errCode, (fgt_INSTRUMENT_TYPE)type, controllerSN: controllerSn, infoCode == 1, detailsString);
        }

        /// <summary>
        /// Set power ON or OFF on a controller (such as Link, MFCS, Flowboard). 
        /// Not all controllers support this functionality.
        /// </summary>
        /// <param name="controllerIndex">Index of controller or unique ID</param>
        /// <param name="state">New controller power state</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/></returns>
        public static fgt_ERROR_CODE Fgt_set_power(uint controllerIndex, fgt_POWER state)
        {
            return (fgt_ERROR_CODE)fgt_set_power(controllerIndex, (byte)state);
        }

        /// <summary>
        /// Get power information about a controller (such as Link, MFCS, Flowboard).  
        /// Not all controllers support this functionality.
        /// </summary>
        /// <param name="controllerIndex">Index of controller or unique ID</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/> and the controller's power state</returns>
        public static (fgt_ERROR_CODE errCode, fgt_POWER state) Fgt_get_power(uint controllerIndex)
        {
            byte state = 0;
            var errCode = fgt_get_power(controllerIndex, ref state);
            return ((fgt_ERROR_CODE)errCode, (fgt_POWER)state);
        }

        #endregion

        #region TTL functions

        /// <summary>
        /// Configure a specific TTL port (BNC ports) as input, output, rising or falling edge.
        /// </summary>
        /// <param name="TtlIndex">Index of TTL port or unique ID</param>
        /// <param name="mode">New TTL mode</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/></returns>
        public static fgt_ERROR_CODE Fgt_set_TtlMode(uint TtlIndex, fgt_TTL_MODE mode)
        {
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_set_TtlMode(TtlIndex, (int)mode), fgt_ERRCHECK_TYPE.Generic);
            return errCode;
        }

        /// <summary>
        /// Read TTL port (BNC port) if set as input.
        /// </summary>
        /// <param name="ttlIndex">Index of TTL port or unique ID</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/> and a boolean indicating if an event (edge) has occured</returns>
        public static (fgt_ERROR_CODE errCode, bool ttlEvent) Fgt_read_Ttl(uint ttlIndex)
        {
            uint state = 0;
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_read_Ttl(ttlIndex, ref state), fgt_ERRCHECK_TYPE.Generic);
            return (errCode, Convert.ToBoolean(state));
        }

        /// <summary>
        /// Trigger a specific TTL port (BNC ports) if set as output.
        /// </summary>
        /// <param name="ttlIndex">Index of TTL port or unique ID</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/> and a boolean indicating if an event (edge) has occured</returns>
        public static fgt_ERROR_CODE Fgt_trigger_Ttl(uint ttlIndex)
        {
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_trigger_Ttl(ttlIndex), fgt_ERRCHECK_TYPE.Generic);
            return errCode;
        }

        #endregion

        #region Specific functions

        /// <summary>
        /// Activate/deactivate purge function.
        /// This feature is only available on MFCS devices equipped with special valve.
        /// </summary>
        /// <param name="controllerIndex">Index of controller or unique ID</param>
        /// <param name="purge">Purge state</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/></returns>
        public static fgt_ERROR_CODE Fgt_set_purge(uint controllerIndex, bool purge)
        {
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_set_purge(controllerIndex, (byte)(purge ? 1 : 0)), fgt_ERRCHECK_TYPE.Generic);
            return errCode;
        }

        /// <summary>
        /// Manually set internal solenoid valve voltage.
        /// This stops pressure regulation on the channel until a new pressure or 
        /// flow rate command is set.
        /// </summary>
        /// <param name="pressureIndex">Index of pressure channel or unique ID</param>
        /// <param name="value">Applied valve voltage from 0 to 100(%)</param>
        /// <returns></returns>
        public static fgt_ERROR_CODE Fgt_set_manual(uint pressureIndex, float value)
        {
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_set_manual(pressureIndex, value), fgt_ERRCHECK_TYPE.Pressure, pressureIndex);
            return errCode;
        }

        /// <summary>
        /// Set the digital output ON or OFF on a controller
        /// This feature is only available on the F-OEM device.
        /// </summary>
        /// <param name="controllerIndex">Index of controller or unique ID</param>
        /// <param name="port">Address of the digital output to toggle. For F-OEM: 0: Pump, 1: LED</param>
        /// <param name="state">True to turn on the output, false to turn off</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/></returns>
        public static fgt_ERROR_CODE Fgt_set_digitalOutput(uint controllerIndex, byte port, bool state)
        {
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_set_digitalOutput(controllerIndex, port, (byte)(state ? 1 : 0)), fgt_ERRCHECK_TYPE.Generic);
            return errCode;
        }

        /// <summary>
        /// Read the flag indicating whether the flow rate sensor detects an air bubble. Only 
        /// available on Flow Unit sensor ranges M+ and L+.
        /// </summary>
        /// <param name="sensorIndex">Index of sensor channel or unique ID</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/> and a boolean which is true if the sensor detects an air bubble</returns>
        public static (fgt_ERROR_CODE errCode, bool detected) Fgt_get_sensorAirBubbleFlag(uint sensorIndex)
        {
            byte detected = 0;
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_get_sensorAirBubbleFlag(sensorIndex, ref detected), fgt_ERRCHECK_TYPE.Sensor, sensorIndex);
            return (errCode, detected != 0);
        }

        /// <summary>
        /// Returns the pressure measured at the device's inlet. 
        /// This feature is only available on LineUP Flow EZ and FOEM Pressure Module instruments.
        /// </summary>
        /// <param name="pressureIndex">Index of pressure channel or unique ID</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/> and current inlet pressure</returns>
        public static (fgt_ERROR_CODE errCode, float pressure) Fgt_get_inletPressure(uint pressureIndex)
        {
            var pressure = 0.0f;
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_get_inletPressure(pressureIndex, ref pressure), fgt_ERRCHECK_TYPE.Pressure, pressureIndex);
            return (errCode, pressure);
        }

        /// <summary>
        /// Returns the range of the differential pressure sensor.
        /// This feature is only available on NIFS devices.
        /// </summary>
        /// <param name="sensorIndex">Index of sensor channel or unique ID</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/></returns>
        public static (fgt_ERROR_CODE errCode, float pMin, float pMax) Fgt_get_differentialPressureRange(uint sensorIndex)
        {
            float pMin = 0, pMax = 0;
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_get_differentialPressureRange(sensorIndex, ref pMin, ref pMax), fgt_ERRCHECK_TYPE.Sensor);
            return (errCode, pMin, pMax);
        }

        /// <summary>
        /// Returns the current differential pressure measurement
        /// This feature is only available on NIFS devices.
        /// </summary>
        /// <param name="sensorIndex">Index of sensor channel or unique ID</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/> and differential pressure</returns>
        public static (fgt_ERROR_CODE errCode, float pDiff) Fgt_get_differentialPressure(uint sensorIndex)
        {
            float pDiff = 0;
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_get_differentialPressure(sensorIndex, ref pDiff), fgt_ERRCHECK_TYPE.Sensor);
            return (errCode, pDiff);
        }

        /// <summary>
        /// Returns the range of the absolute pressure sensor.
        /// This feature is only available on NIFS devices.
        /// </summary>
        /// <param name="sensorIndex">Index of sensor channel or unique ID</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/></returns>
        public static (fgt_ERROR_CODE errCode, float pMin, float pMax) Fgt_get_absolutePressureRange(uint sensorIndex)
        {
            float pMin = 0, pMax = 0;
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_get_absolutePressureRange(sensorIndex, ref pMin, ref pMax), fgt_ERRCHECK_TYPE.Sensor);
            return (errCode, pMin, pMax);
        }

        /// <summary>
        /// Returns the current absolute pressure measurement
        /// This feature is only available on NIFS devices.
        /// </summary>
        /// <param name="sensorIndex">Index of sensor channel or unique ID</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/> and absolute pressure</returns>
        public static (fgt_ERROR_CODE errCode, float pAbs) Fgt_get_absolutePressure(uint sensorIndex)
        {
            float pAbs = 0;
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_get_absolutePressure(sensorIndex, ref pAbs), fgt_ERRCHECK_TYPE.Sensor);
            return (errCode, pAbs);
        }

        /// <summary>
        /// Returns the current state of the bypass valve.
        /// This feature is only available on NIFS devices.
        /// </summary>
        /// <param name="sensorIndex">Index of sensor channel or unique ID</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/> and boolean value which is true if the valve is open and false otherwise</returns>
        public static (fgt_ERROR_CODE errCode, bool state) Fgt_get_sensorBypassValve(uint sensorIndex)
        {
            byte state = 0;
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_get_sensorBypassValve(sensorIndex, ref state), fgt_ERRCHECK_TYPE.Sensor);
            return (errCode, state != 0);
        }

        /// <summary>
        /// Sets the state of the sensor's bypass valve.
        /// This feature is only available on NIFS devices.
        /// </summary>
        /// <param name="sensorIndex">Index of sensor channel or unique ID</param>
        /// <param name="state">True to open the valve, false to close</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/> and boolean value which is true if the valve is open and false otherwise</returns>
        public static fgt_ERROR_CODE Fgt_set_sensorBypassValve(uint sensorIndex, bool state)
        {
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_set_sensorBypassValve(sensorIndex, (byte)(state ? 1 : 0)), fgt_ERRCHECK_TYPE.Sensor);
            return errCode;
        }

        #endregion

        #region Logging
        /// <summary>
        /// Sets the verbosity of the logging feature, i.e., how much data is logged.
        /// </summary>
        /// <param name="verbosity">The amount of data to log. Set to 0 to disable logging (default). 
        /// Set to 5 to log the maximum amount of data.</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/></returns>
        public static fgt_ERROR_CODE Fgt_set_log_verbosity(uint verbosity)
        {
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_set_log_verbosity(verbosity), fgt_ERRCHECK_TYPE.Generic);
            return errCode;
        }

        /// <summary>
        /// Sets how the SDK outputs the log entries.
        /// </summary>
        /// <param name="output_to_file">Output log entries to a file in the current directory. Default: enabled.</param>
        /// <param name="output_to_stderr">Output log entries to the stderr pipe (console). Default: disabled.</param>
        /// <param name="output_to_queue">Store log entries in memory. They can be retrieved via the <see cref="Fgt_get_next_log"/> function. Default: disabled.</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/></returns>
        public static fgt_ERROR_CODE Fgt_set_log_output_mode(bool output_to_file, bool output_to_stderr, bool output_to_queue)
        {
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_set_log_output_mode((byte)(output_to_file ? 1 : 0), (byte)(output_to_stderr ? 1 : 0), (byte)(output_to_queue ? 1 : 0)), fgt_ERRCHECK_TYPE.Generic);
            return errCode;
        }

        /// <summary>
        /// Returns the next log entry stored in memory, if any, and removes it from the queue.
        /// Will return an error if the queue is empty.Logs are only stored in memory if the corresponding
        /// option is set with the <see cref="Fgt_set_log_output_mode"/> function.
        /// Call this function repeatedly until an error is returned to retrieve all log entries.
        /// </summary>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/></returns>
        public static (fgt_ERROR_CODE, string log) Fgt_get_next_log()
        {
            var log = new char[2000];
            var errCode = ErrCheck((fgt_ERROR_CODE)fgt_get_next_log(log), fgt_ERRCHECK_TYPE.Generic);
            if (errCode != fgt_ERROR_CODE.OK) { return (errCode, string.Empty); }
            var logString = new string(log.TakeWhile(c => c != '\0').ToArray());
            return (errCode, logString);
        }
        #endregion

        /// <summary>
        /// Sets a flag that defines how SDK errors should be reported.
        /// </summary>
        /// <remarks>
        /// None: Only return the error code enum.
        /// Print: Output the error message to the console.
        /// </remarks>
        /// <param name="mode">Report mode</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/></returns>
        public static fgt_ERROR_CODE Fgt_set_errorReportMode(fgt_ERROR_REPORT_MODE mode)
        {
            _errorReportMode = mode;
            return fgt_ERROR_CODE.OK;
        }

        #endregion

        #region Destructor
        private static readonly Destructor Finalise = new Destructor();

        private sealed class Destructor
        {
            ~Destructor()
            {
                Fgt_close();
            }
        }
        #endregion
    }
}

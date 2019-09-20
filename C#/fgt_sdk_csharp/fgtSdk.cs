using fgt_sdk.Structs;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using fgt_sdk.Enums;

namespace fgt_sdk
{
    public static class fgtSdk
    {
        #region Native calls

        [DllImport("kernel32.dll")]
        private static extern IntPtr LoadLibrary(string dllToLoad);

        [DllImport("kernel32.dll")]
        private static extern IntPtr GetProcAddress(IntPtr hModule, string procedureName);

        [DllImport("kernel32.dll")]
        private static extern bool FreeLibrary(IntPtr hModule);

        #endregion

        #region Delegates + pointers

        #region Init/close

        //unsigned char __stdcall fgt_init(void);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_init();

        private static fgt_init _fgt_init;

        // unsigned char __stdcall fgt_close(void);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_close();

        private static fgt_close _fgt_close;

        // unsigned char __stdcall fgt_detect(unsigned short SN[256], int type[256]);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_detect(ushort[] serialNumbers, int[] type);

        private static fgt_detect _fgt_detect;

        //unsigned char __stdcall fgt_initEx(unsigned short SN[256]);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_initEx(ushort[] serialNumbers);

        private static fgt_initEx _fgt_initEx;

        #endregion

        #region Channels info

        // unsigned char __stdcall fgt_get_controllersInfo(fgt_CONTROLLER_INFO info[256]);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_get_controllersInfo([Out, MarshalAs(UnmanagedType.LPArray, SizeConst = 256)] fgt_CONTROLLER_INFO[] controllersInfo);

        private static fgt_get_controllersInfo _fgt_get_controllersInfo;

        // unsigned char __stdcall fgt_get_pressureChannelCount(unsigned char* nbPChan);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_get_pressureChannelCount(ref byte count);

        private static fgt_get_pressureChannelCount _fgt_get_pressureChannelCount;

        // unsigned char __stdcall fgt_get_sensorChannelCount(unsigned char* nbSChan);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_get_sensorChannelCount(ref byte count);

        private static fgt_get_sensorChannelCount _fgt_get_sensorChannelCount;

        // unsigned char __stdcall fgt_get_TtlChannelCount(unsigned char* nbTtlChan);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_get_TtlChannelCount(ref byte count);

        private static fgt_get_TtlChannelCount _fgt_get_TtlChannelCount;

        // unsigned char __stdcall fgt_get_pressureChannelsInfo(fgt_CHANNEL_INFO info[256]);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_get_pressureChannelsInfo([Out, MarshalAs(UnmanagedType.LPArray, SizeConst = 256)] fgt_CHANNEL_INFO[] info);

        private static fgt_get_pressureChannelsInfo _fgt_get_pressureChannelsInfo;

        // unsigned char __stdcall fgt_get_sensorChannelsInfo(fgt_CHANNEL_INFO info[256], int sensorType[256]);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_get_sensorChannelsInfo([Out, MarshalAs(UnmanagedType.LPArray, SizeConst = 256)] fgt_CHANNEL_INFO[] info, int[] type);

        private static fgt_get_sensorChannelsInfo _fgt_get_sensorChannelsInfo;

        // unsigned char __stdcall fgt_get_TtlChannelsInfo(fgt_CHANNEL_INFO info[256], int sensorType[256]);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_get_TtlChannelsInfo([Out, MarshalAs(UnmanagedType.LPArray, SizeConst = 256)] fgt_CHANNEL_INFO[] info);

        private static fgt_get_TtlChannelsInfo _fgt_get_TtlChannelsInfo;

        #endregion

        #region Basic functions

        // unsigned char __stdcall fgt_set_pressure(unsigned int pressureIndex, float pressure);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_set_pressure(uint pressureIndex, float pressure);

        private static fgt_set_pressure _fgt_set_pressure;

        // unsigned char __stdcall fgt_get_pressure(unsigned int pressureIndex, float* pressure);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_get_pressure(uint pressureIndex, ref float pressure);

        private static fgt_get_pressure _fgt_get_pressure;

        // unsigned char __stdcall fgt_get_pressureEx(unsigned int pressureIndex, float* pressure, unsigned short* timeStamp);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_get_pressureEx(uint pressureIndex, ref float pressure, ref ushort timeStamp);

        private static fgt_get_pressureEx _fgt_get_pressureEx;

        // unsigned char __stdcall fgt_set_sensorRegulation(unsigned int sensorIndex, unsigned int pressureIndex, float setpoint);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_set_sensorRegulation(uint sensorIndex, uint pressureIndex, float setpoint);

        private static fgt_set_sensorRegulation _fgt_set_sensorRegulation;

        // unsigned char __stdcall fgt_get_sensorValue(unsigned int sensorIndex, float* value);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_get_sensorValue(uint sensorIndex, ref float value);

        private static fgt_get_sensorValue _fgt_get_sensorValue;

        // unsigned char __stdcall fgt_get_sensorValueEx(unsigned int sensorIndex, float* value, unsigned short* timeStamp);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_get_sensorValueEx(uint sensorIndex, ref float value, ref ushort timeStamp);

        private static fgt_get_sensorValueEx _fgt_get_sensorValueEx;

        #endregion

        #region Unit, calibration and limits

        // unsigned char __stdcall fgt_set_sessionPressureUnit(char unit[140]);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_set_sessionPressureUnit(char[] unit);

        private static fgt_set_sessionPressureUnit _fgt_set_sessionPressureUnit;

        // unsigned char __stdcall fgt_set_pressureUnit(unsigned int presureIndex, char unit[140]);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_set_pressureUnit(uint pressureIndex, char[] unit);

        private static fgt_set_pressureUnit _fgt_set_pressureUnit;

        // unsigned char __stdcall fgt_get_pressureUnit(unsigned int pressureIndex, char unit[140]);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_get_pressureUnit(uint pressureIndex, [Out, MarshalAs(UnmanagedType.LPArray, SizeConst = 140)] char[] unit);

        private static fgt_get_pressureUnit _fgt_get_pressureUnit;

        // unsigned char __stdcall fgt_set_sensorUnit(unsigned int sensorIndex, char unit[140]);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_set_sensorUnit(uint sensorIndex, char[] unit);

        private static fgt_set_sensorUnit _fgt_set_sensorUnit;

        // unsigned char __stdcall fgt_get_sensorUnit(unsigned int sensorIndex, char unit[140]);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_get_sensorUnit(uint sensorIndex, [Out, MarshalAs(UnmanagedType.LPArray, SizeConst = 140)] char[] unit);

        private static fgt_get_sensorUnit _fgt_get_sensorUnit;

        // unsigned char __stdcall fgt_set_sensorCalibration(unsigned int sensorIndex, int calibration);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_set_sensorCalibration(uint sensorIndex, int calibration);

        private static fgt_set_sensorCalibration _fgt_set_sensorCalibration;

        // unsigned char __stdcall fgt_get_sensorCalibration(unsigned int sensorIndex, int* calibration);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_get_sensorCalibration(uint sensorIndex, ref int calibration);

        private static fgt_get_sensorCalibration _fgt_get_sensorCalibration;

        // unsigned char __stdcall fgt_set_sensorCustomScale(unsigned int sensorIndex, float a, float b, float c);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_set_sensorCustomScale(uint sensorIndex, float a, float b, float c);

        private static fgt_set_sensorCustomScale _fgt_set_sensorCustomScale;

        // unsigned char __stdcall fgt_set_sensorCustomScaleEx(unsigned int sensorIndex, float a, float b, float c, float SMax);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_set_sensorCustomScaleEx(uint sensorIndex, float a, float b, float c, float sMax);

        private static fgt_set_sensorCustomScaleEx _fgt_set_sensorCustomScaleEx;

        // unsigned char __stdcall fgt_calibratePressure(unsigned int pressureIndex);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_calibratePressure(uint pressureIndex);

        private static fgt_calibratePressure _fgt_calibratePressure;

        // unsigned char __stdcall fgt_set_customSensorRegulation(float measure, float setpoint, float maxSensorRange, unsigned int pressureIndex);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_set_customSensorRegulation(float measure, float setpoint, float maxSensorRange, uint pressureIndex);

        private static fgt_set_customSensorRegulation _fgt_set_customSensorRegulation;

        // unsigned char __stdcall fgt_get_pressureRange(unsigned int pressureIndex, float* Pmin, float* Pmax);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_get_pressureRange(uint pressureIndex, ref float pMin, ref float pMax);

        private static fgt_get_pressureRange _fgt_get_pressureRange;

        // unsigned char __stdcall fgt_get_sensorRange(unsigned int sensorIndex, float* Smin, float* Smax);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_get_sensorRange(uint sensorIndex, ref float sMin, ref float sMax);

        private static fgt_get_sensorRange _fgt_get_sensorRange;

        // unsigned char __stdcall fgt_set_pressureLimit(unsigned int pressureIndex, float PlimMin, float PlimMax);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_set_pressureLimit(uint pressureIndex, float pLimMin, float pLimMax);

        private static fgt_set_pressureLimit _fgt_set_pressureLimit;

        #endregion

        #region Regulation settings

        // unsigned char __stdcall fgt_set_sensorRegulationResponse(unsigned int sensorIndex, unsigned int responseTime);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_set_sensorRegulationResponse(uint sensorIndex, uint responseTime);

        private static fgt_set_sensorRegulationResponse _fgt_set_sensorRegulationResponse;

        // unsigned char __stdcall fgt_set_pressureResponse(unsigned int pressureIndex, unsigned char value);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_set_pressureResponse(uint pressureIndex, byte value);

        private static fgt_set_pressureResponse _fgt_set_pressureResponse;

        #endregion

        #region Status information

        // unsigned char __stdcall fgt_get_pressureStatus(unsigned int pressureIndex, int* type, unsigned short* controllerSN, unsigned char* infoCode, char detail[140]);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_get_pressureStatus(uint pressureIndex, ref int type, ref ushort controllerSN, ref byte infoCode, [Out, MarshalAs(UnmanagedType.LPArray, SizeConst = 140)] char[] detail);

        private static fgt_get_pressureStatus _fgt_get_pressureStatus;

        // unsigned char __stdcall fgt_get_sensorStatus(unsigned int sensorIndex, int* type, unsigned short* controllerSN, unsigned char* infoCode, char detail[140]);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_get_sensorStatus(uint sensorIndex, ref int type, ref ushort controllerSN, ref byte infoCode, [Out, MarshalAs(UnmanagedType.LPArray, SizeConst = 140)] char[] detail);

        private static fgt_get_sensorStatus _fgt_get_sensorStatus;

        // unsigned char __stdcall fgt_set_power(unsigned int controllerIndex, unsigned char powerState);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_set_power(uint controllerIndex, byte powerState);

        private static fgt_set_power _fgt_set_power;

        // unsigned char __stdcall fgt_get_power(unsigned int controllerIndex, unsigned char* powerState);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_get_power(uint controllerIndex, ref byte powerState);

        private static fgt_get_power _fgt_get_power;

        #endregion

        #region TTL functions

        // unsigned char __stdcall fgt_set_TtlMode(unsigned int TtlIndex, int mode);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_set_TtlMode(uint TtlIndex, int mode);

        private static fgt_set_TtlMode _fgt_set_TtlMode;

        // unsigned char __stdcall fgt_read_Ttl(unsigned int TtlIndex, unsigned int* state);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_read_Ttl(uint TtlIndex, ref uint state);

        private static fgt_read_Ttl _fgt_read_Ttl;

        // unsigned char __stdcall fgt_trigger_Ttl(unsigned int TtlIndex);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_trigger_Ttl(uint TtlIndex);

        private static fgt_trigger_Ttl _fgt_trigger_Ttl;

        #endregion

        #region Specific functions

        // unsigned char __stdcall fgt_set_purge(unsigned int controllerIndex, unsigned char purge);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_set_purge(uint controllerIndex, byte purge);

        private static fgt_set_purge _fgt_set_purge;

        // unsigned char __stdcall fgt_set_manual(unsigned int pressureIndex, float value);
        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate byte fgt_set_manual(uint pressureIndex, float value);

        private static fgt_set_manual _fgt_set_manual;

        #endregion

        #endregion

        static fgtSdk()
        {
            var libname = $"fgt_sdk_{(Environment.Is64BitProcess ? "64" : "32")}.dll";

            try
            {
                var pDll = LoadLibrary(Path.Combine("fgt_sdk_dlls", libname));

                if (pDll == IntPtr.Zero)
                    throw new Exception($"Unable to load library {libname}. The file is probable missing");

                #region Pointers retrieval

                #region Init/Close

                var p_fgt_init = GetProcAddress(pDll, "fgt_init");
                _fgt_init = (fgt_init) Marshal.GetDelegateForFunctionPointer(p_fgt_init, typeof(fgt_init));

                var p_fgt_close = GetProcAddress(pDll, "fgt_close");
                _fgt_close = (fgt_close) Marshal.GetDelegateForFunctionPointer(p_fgt_close, typeof(fgt_close));

                var p_fgt_detect = GetProcAddress(pDll, "fgt_detect");
                _fgt_detect = (fgt_detect) Marshal.GetDelegateForFunctionPointer(p_fgt_detect, typeof(fgt_detect));

                var p_fgt_initEx = GetProcAddress(pDll, "fgt_initEx");
                _fgt_initEx = (fgt_initEx) Marshal.GetDelegateForFunctionPointer(p_fgt_initEx, typeof(fgt_initEx));

                #endregion

                #region Channels info

                var p_fgt_get_controllersInfo = GetProcAddress(pDll, "fgt_get_controllersInfo");
                _fgt_get_controllersInfo = Marshal.GetDelegateForFunctionPointer<fgt_get_controllersInfo>(p_fgt_get_controllersInfo);

                var p_fgt_get_pressureChannelCount = GetProcAddress(pDll, "fgt_get_pressureChannelCount");
                _fgt_get_pressureChannelCount = Marshal.GetDelegateForFunctionPointer<fgt_get_pressureChannelCount>(p_fgt_get_pressureChannelCount);

                var p_fgt_get_sensorChannelCount = GetProcAddress(pDll, "fgt_get_sensorChannelCount");
                _fgt_get_sensorChannelCount = Marshal.GetDelegateForFunctionPointer<fgt_get_sensorChannelCount>(p_fgt_get_sensorChannelCount);

                var p_fgt_get_TtlChannelCount = GetProcAddress(pDll, "fgt_get_TtlChannelCount");
                _fgt_get_TtlChannelCount = Marshal.GetDelegateForFunctionPointer<fgt_get_TtlChannelCount>(p_fgt_get_TtlChannelCount);

                var p_fgt_get_pressureChannelsInfo = GetProcAddress(pDll, "fgt_get_pressureChannelsInfo");
                _fgt_get_pressureChannelsInfo = Marshal.GetDelegateForFunctionPointer<fgt_get_pressureChannelsInfo>(p_fgt_get_pressureChannelsInfo);

                var p_fgt_get_sensorChannelsInfo = GetProcAddress(pDll, "fgt_get_sensorChannelsInfo");
                _fgt_get_sensorChannelsInfo = Marshal.GetDelegateForFunctionPointer<fgt_get_sensorChannelsInfo>(p_fgt_get_sensorChannelsInfo);

                var p_fgt_get_TtlChannelsInfo = GetProcAddress(pDll, "fgt_get_TtlChannelsInfo");
                _fgt_get_TtlChannelsInfo = Marshal.GetDelegateForFunctionPointer<fgt_get_TtlChannelsInfo>(p_fgt_get_TtlChannelsInfo);

                #endregion

                #region Basic functions

                var p_fgt_set_pressure = GetProcAddress(pDll, "fgt_set_pressure");
                _fgt_set_pressure = Marshal.GetDelegateForFunctionPointer<fgt_set_pressure>(p_fgt_set_pressure);

                var p_fgt_get_pressure = GetProcAddress(pDll, "fgt_get_pressure");
                _fgt_get_pressure = Marshal.GetDelegateForFunctionPointer<fgt_get_pressure>(p_fgt_get_pressure);

                var p_fgt_get_pressureEx = GetProcAddress(pDll, "fgt_get_pressureEx");
                _fgt_get_pressureEx = Marshal.GetDelegateForFunctionPointer<fgt_get_pressureEx>(p_fgt_get_pressureEx);

                var p_fgt_set_sensorRegulation = GetProcAddress(pDll, "fgt_set_sensorRegulation");
                _fgt_set_sensorRegulation = Marshal.GetDelegateForFunctionPointer<fgt_set_sensorRegulation>(p_fgt_set_sensorRegulation);

                var p_fgt_get_sensorValue = GetProcAddress(pDll, "fgt_get_sensorValue");
                _fgt_get_sensorValue = Marshal.GetDelegateForFunctionPointer<fgt_get_sensorValue>(p_fgt_get_sensorValue);

                var p_fgt_get_sensorValueEx = GetProcAddress(pDll, "fgt_get_sensorValueEx");
                _fgt_get_sensorValueEx = Marshal.GetDelegateForFunctionPointer<fgt_get_sensorValueEx>(p_fgt_get_sensorValueEx);

                #endregion

                #region Unit, calibration and limits

                var p_fgt_set_sessionPressureUnit = GetProcAddress(pDll, "fgt_set_sessionPressureUnit");
                _fgt_set_sessionPressureUnit = Marshal.GetDelegateForFunctionPointer<fgt_set_sessionPressureUnit>(p_fgt_set_sessionPressureUnit);

                var p_fgt_set_pressureUnit = GetProcAddress(pDll, "fgt_set_pressureUnit");
                _fgt_set_pressureUnit = Marshal.GetDelegateForFunctionPointer<fgt_set_pressureUnit>(p_fgt_set_pressureUnit);

                var p_fgt_get_pressureUnit = GetProcAddress(pDll, "fgt_get_pressureUnit");
                _fgt_get_pressureUnit = Marshal.GetDelegateForFunctionPointer<fgt_get_pressureUnit>(p_fgt_get_pressureUnit);

                var p_fgt_set_sensorUnit = GetProcAddress(pDll, "fgt_set_sensorUnit");
                _fgt_set_sensorUnit = Marshal.GetDelegateForFunctionPointer<fgt_set_sensorUnit>(p_fgt_set_sensorUnit);

                var p_fgt_get_sensorUnit = GetProcAddress(pDll, "fgt_get_sensorUnit");
                _fgt_get_sensorUnit = Marshal.GetDelegateForFunctionPointer<fgt_get_sensorUnit>(p_fgt_get_sensorUnit);

                var p_fgt_set_sensorCalibration = GetProcAddress(pDll, "fgt_set_sensorCalibration");
                _fgt_set_sensorCalibration = Marshal.GetDelegateForFunctionPointer<fgt_set_sensorCalibration>(p_fgt_set_sensorCalibration);

                var p_fgt_get_sensorCalibration = GetProcAddress(pDll, "fgt_get_sensorCalibration");
                _fgt_get_sensorCalibration = Marshal.GetDelegateForFunctionPointer<fgt_get_sensorCalibration>(p_fgt_get_sensorCalibration);

                var p_fgt_set_sensorCustomScale = GetProcAddress(pDll, "fgt_set_sensorCustomScale");
                _fgt_set_sensorCustomScale = Marshal.GetDelegateForFunctionPointer<fgt_set_sensorCustomScale>(p_fgt_set_sensorCustomScale);

                var p_fgt_set_sensorCustomScaleEx = GetProcAddress(pDll, "fgt_set_sensorCustomScaleEx");
                _fgt_set_sensorCustomScaleEx = Marshal.GetDelegateForFunctionPointer<fgt_set_sensorCustomScaleEx>(p_fgt_set_sensorCustomScaleEx);

                var p_fgt_calibratePressure = GetProcAddress(pDll, "fgt_calibratePressure");
                _fgt_calibratePressure = Marshal.GetDelegateForFunctionPointer<fgt_calibratePressure>(p_fgt_calibratePressure);

                var p_fgt_set_customSensorRegulation = GetProcAddress(pDll, "fgt_set_customSensorRegulation");
                _fgt_set_customSensorRegulation = Marshal.GetDelegateForFunctionPointer<fgt_set_customSensorRegulation>(p_fgt_set_customSensorRegulation);

                var p_fgt_get_pressureRange = GetProcAddress(pDll, "fgt_get_pressureRange");
                _fgt_get_pressureRange = Marshal.GetDelegateForFunctionPointer<fgt_get_pressureRange>(p_fgt_get_pressureRange);

                var p_fgt_get_sensorRange = GetProcAddress(pDll, "fgt_get_sensorRange");
                _fgt_get_sensorRange = Marshal.GetDelegateForFunctionPointer<fgt_get_sensorRange>(p_fgt_get_sensorRange);

                var p_fgt_set_pressureLimit = GetProcAddress(pDll, "fgt_set_pressureLimit");
                _fgt_set_pressureLimit = Marshal.GetDelegateForFunctionPointer<fgt_set_pressureLimit>(p_fgt_set_pressureLimit);

                #endregion

                #region Regulation settings

                var p_fgt_set_sensorRegulationResponse = GetProcAddress(pDll, "fgt_set_sensorRegulationResponse");
                _fgt_set_sensorRegulationResponse = Marshal.GetDelegateForFunctionPointer<fgt_set_sensorRegulationResponse>(p_fgt_set_sensorRegulationResponse);

                var p_fgt_set_pressureResponse = GetProcAddress(pDll, "fgt_set_pressureResponse");
                _fgt_set_pressureResponse = Marshal.GetDelegateForFunctionPointer<fgt_set_pressureResponse>(p_fgt_set_pressureResponse);

                #endregion

                #region Status information

                var p_fgt_get_pressureStatus = GetProcAddress(pDll, "fgt_get_pressureStatus");
                _fgt_get_pressureStatus = Marshal.GetDelegateForFunctionPointer<fgt_get_pressureStatus>(p_fgt_get_pressureStatus);

                var p_fgt_get_sensorStatus = GetProcAddress(pDll, "fgt_get_sensorStatus");
                _fgt_get_sensorStatus = Marshal.GetDelegateForFunctionPointer<fgt_get_sensorStatus>(p_fgt_get_sensorStatus);

                var p_fgt_set_power = GetProcAddress(pDll, "fgt_set_power");
                _fgt_set_power = Marshal.GetDelegateForFunctionPointer<fgt_set_power>(p_fgt_set_power);

                var p_fgt_get_power = GetProcAddress(pDll, "fgt_get_power");
                _fgt_get_power = Marshal.GetDelegateForFunctionPointer<fgt_get_power>(p_fgt_get_power);

                #endregion

                #region TTL functions

                var p_fgt_set_TtlMode = GetProcAddress(pDll, "fgt_set_TtlMode");
                _fgt_set_TtlMode = Marshal.GetDelegateForFunctionPointer<fgt_set_TtlMode>(p_fgt_set_TtlMode);

                var p_fgt_read_Ttl = GetProcAddress(pDll, "fgt_read_Ttl");
                _fgt_read_Ttl = Marshal.GetDelegateForFunctionPointer<fgt_read_Ttl>(p_fgt_read_Ttl);

                var p_fgt_trigger_Ttl = GetProcAddress(pDll, "fgt_trigger_Ttl");
                _fgt_trigger_Ttl = Marshal.GetDelegateForFunctionPointer<fgt_trigger_Ttl>(p_fgt_trigger_Ttl);

                #endregion

                #region Specific functions

                var p_fgt_set_purge = GetProcAddress(pDll, "fgt_set_purge");
                _fgt_set_purge = Marshal.GetDelegateForFunctionPointer<fgt_set_purge>(p_fgt_set_purge);

                var p_fgt_set_manual = GetProcAddress(pDll, "fgt_set_manual");
                _fgt_set_manual = Marshal.GetDelegateForFunctionPointer<fgt_set_manual>(p_fgt_set_manual);

                #endregion
            }
            catch (Exception e)
            {
                Console.Write(e);
                throw;
            }

            #endregion
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
            if (errorCode == fgt_ERROR_CODE.OK) return errorCode;

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
        /// Initialize or reinitialize (if already opened) Fluigent SDK instance. All detected Fluigent instruments (MFCS, MFCS-EZ, FRP, LineUP) are initialized.
        /// This function is optional, directly calling a function will automatically creates the instance.
        /// Only one instance can be opened at once.If called again, session is reinitialized.
        /// </summary>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/></returns>
        public static fgt_ERROR_CODE Fgt_init()
        {
            var errCode = ErrCheck((fgt_ERROR_CODE) _fgt_init(), fgt_ERRCHECK_TYPE.Generic);
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
            var errCode = ErrCheck((fgt_ERROR_CODE) _fgt_close(), fgt_ERRCHECK_TYPE.Generic);
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
            var count = _fgt_detect(serialNumbers, types);

            var tuplesList = new List<(ushort, fgt_INSTRUMENT_TYPE)>();

            for (var i = 0; i < serialNumbers.Length; i++)
            {
                if (serialNumbers[i] != 0)
                {
                    tuplesList.Add((serialNumbers[i], (fgt_INSTRUMENT_TYPE) types[i]));
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

            return ErrCheck((fgt_ERROR_CODE) _fgt_initEx(sns), fgt_ERRCHECK_TYPE.Generic);
        }

        #endregion

        #region Channels info

        /// <summary>
        /// Retrieve information about session controllers. Controllers are MFCS, Flowboard, Link in an array.
        /// </summary>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/> and a list of <see cref="fgt_CONTROLLER_INFO"/></returns>
        public static (fgt_ERROR_CODE errCode, List<fgt_CONTROLLER_INFO> info) Fgt_get_controllersInfo()
        {
            var controllersInfo = new fgt_CONTROLLER_INFO[256];
            var errCode = ErrCheck((fgt_ERROR_CODE) _fgt_get_controllersInfo(controllersInfo), fgt_ERRCHECK_TYPE.Generic);
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
            var errCode = ErrCheck((fgt_ERROR_CODE) _fgt_get_pressureChannelCount(ref count), fgt_ERRCHECK_TYPE.Generic);
            return (errCode, count);
        }

        /// <summary>
        /// Get total number of initialized sensor channels. It is the sum of all connected flow-units on Flowboard and FlowEZ
        /// </summary>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/> and sensor channels count</returns>
        public static (fgt_ERROR_CODE errCode, int count) Fgt_get_sensorChannelCount()
        {
            byte count = 0;
            var errCode = ErrCheck((fgt_ERROR_CODE) _fgt_get_sensorChannelCount(ref count), fgt_ERRCHECK_TYPE.Generic);
            return (errCode, (int) count);
        }

        /// <summary>
        /// Get total number of initialized TTL channels. It is the sum of all connected Link TTL ports
        /// </summary>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/> and Ttl channels count</returns>
        public static (fgt_ERROR_CODE errCode, int count) Fgt_get_TtlChannelCount()
        {
            byte count = 0;
            var errCode = ErrCheck((fgt_ERROR_CODE) _fgt_get_TtlChannelCount(ref count), fgt_ERRCHECK_TYPE.Generic);
            return (errCode, (int) count);
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
            var errCode = ErrCheck((fgt_ERROR_CODE) _fgt_get_pressureChannelsInfo(info), fgt_ERRCHECK_TYPE.Generic);
            var controllersInfoList = info.Where(c => c.ControllerSN != 0).ToList();
            return (errCode, controllersInfoList);
        }

        /// <summary>
        /// Retrieve information about each initialized sensor channel.This function is useful in order to get channels order, controller, unique ID and instrument type.
        /// By default this array is built with FRP first then FlowEZ and contains flow-units.If only one instrument is used, index is the default channel indexing starting at 0.
        /// You can initialize instruments in specific order using <see cref="Fgt_initEx"/> function
        /// </summary>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/> and a list of <see cref="fgt_CHANNEL_INFO"/> <see cref="fgt_SENSOR_TYPE"/> tuples</returns>
        public static (fgt_ERROR_CODE errCode, List<(fgt_CHANNEL_INFO channelInfo, fgt_SENSOR_TYPE sensorType)> info) Fgt_get_sensorChannelsInfo()
        {
            var info = new fgt_CHANNEL_INFO[256];
            var type = new int[256];
            var errCode = ErrCheck((fgt_ERROR_CODE) _fgt_get_sensorChannelsInfo(info, type), fgt_ERRCHECK_TYPE.Generic);
            var tuplesList = new List<(fgt_CHANNEL_INFO, fgt_SENSOR_TYPE)>();
            for (var index = 0; index < info.Length; index++)
            {
                if (info[index].ControllerSN != 0)
                {
                    tuplesList.Add((info[index], (fgt_SENSOR_TYPE) type[index]));
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
            var errCode = ErrCheck((fgt_ERROR_CODE) _fgt_get_TtlChannelsInfo(info), fgt_ERRCHECK_TYPE.Generic);
            var controllersInfoList = info.Where(c => c.ControllerSN != 0).ToList();
            return (errCode, controllersInfoList);
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
            var errCode = ErrCheck((fgt_ERROR_CODE) _fgt_set_pressure(pressureIndex, pressure), fgt_ERRCHECK_TYPE.Pressure, pressureIndex);
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
            var errCode = ErrCheck((fgt_ERROR_CODE) _fgt_get_pressure(pressureIndex, ref pressure), fgt_ERRCHECK_TYPE.Pressure, pressureIndex);
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
            var errCode = ErrCheck((fgt_ERROR_CODE) _fgt_get_pressureEx(pressureIndex, ref pressure, ref timestamp), fgt_ERRCHECK_TYPE.Pressure, pressureIndex);
            return (errCode, pressure, timestamp);
        }

        /// <summary>
        /// Start closed loop regulation between a sensor and a pressure controller. Pressure will be regulated in order to reach sensor setpoint.
        /// Call again this function in order to change the setpoint.Calling fgt_set_pressure on same pressureIndex will stop regulation.
        /// </summary>
        /// <param name="sensorIndex">Index of sensor channel or unique ID</param>
        /// <param name="pressureIndex">Index of pressure channel or unique ID</param>
        /// <param name="setpoint">Regulation value to be reached in selected unit, default is "µl/min" for flowrate sensors</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/></returns>
        public static fgt_ERROR_CODE Fgt_set_sensorRegulation(uint sensorIndex, uint pressureIndex, float setpoint)
        {
            var errCode = ErrCheck((fgt_ERROR_CODE) _fgt_set_sensorRegulation(sensorIndex, pressureIndex, setpoint), fgt_ERRCHECK_TYPE.Sensor, sensorIndex);
            return errCode;
        }

        /// <summary>
        /// Read sensor value of selected device
        /// </summary>
        /// <param name="sensorIndex">Index of sensor channel or unique ID</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/> and current sensor measurement</returns>
        public static (fgt_ERROR_CODE errCode, float value) Fgt_get_sensorValue(uint sensorIndex)
        {
            var value = 0.0f;
            var errCode = ErrCheck((fgt_ERROR_CODE) _fgt_get_sensorValue(sensorIndex, ref value), fgt_ERRCHECK_TYPE.Sensor, sensorIndex);
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
            var errCode = ErrCheck((fgt_ERROR_CODE) _fgt_get_sensorValueEx(sensorIndex, ref value, ref timestamp), fgt_ERRCHECK_TYPE.Sensor, sensorIndex);
            return (errCode, value, timestamp);
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

            var errCode = ErrCheck((fgt_ERROR_CODE) _fgt_set_sessionPressureUnit(pressureUnit), fgt_ERRCHECK_TYPE.Pressure);
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

            var errCode = ErrCheck((fgt_ERROR_CODE) _fgt_set_pressureUnit(pressureIndex, pressureUnit), fgt_ERRCHECK_TYPE.Pressure, pressureIndex);
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
            var errCode = ErrCheck((fgt_ERROR_CODE) _fgt_get_pressureUnit(pressureIndex, pressureUnit), fgt_ERRCHECK_TYPE.Pressure, pressureIndex);

            var unitString = new string(pressureUnit.TakeWhile(c => c != '\0').ToArray());
            return (errCode, unitString);
        }

        /// <summary>
        /// Set sensor unit on selected sensor device, default value is "µl/min" for flowunits. If type is invalid an error is returned.
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

            var errCode = ErrCheck((fgt_ERROR_CODE) _fgt_set_sensorUnit(sensorIndex, unit), fgt_ERRCHECK_TYPE.Sensor, sensorIndex);
            return errCode;
        }

        /// <summary>
        /// Get current unit on selected sensor device, default value is "µl/min" for flowunits.
        /// Every sensor read value and regulation command use this unit.
        /// </summary>
        /// <param name="sensorIndex">Index of sensor channel or unique ID</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/> and the current unit string</returns>
        public static (fgt_ERROR_CODE errCode, string unit) Fgt_get_sensorUnit(uint sensorIndex)
        {
            var unit = new char[140];
            var errCode = ErrCheck((fgt_ERROR_CODE) _fgt_get_sensorUnit(sensorIndex, unit), fgt_ERRCHECK_TYPE.Sensor, sensorIndex);

            var unitString = new string(unit.TakeWhile(c => c != '\0').ToArray());
            return (errCode, unitString);
        }

        /// <summary>
        /// Set used sensor internal calibration table.
        /// Function is only available for specific sensors (dual type) such as the flow-unit M accepting H2O and IPA
        /// </summary>
        /// <param name="sensorIndex">Index of sensor channel or unique ID</param>
        /// <param name="table">New calibration table</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/></returns>
        public static fgt_ERROR_CODE Fgt_set_sensorCalibration(uint sensorIndex, fgt_SENSOR_CALIBRATION table)
        {
            var errCode = ErrCheck((fgt_ERROR_CODE) _fgt_set_sensorCalibration(sensorIndex, (int) table), fgt_ERRCHECK_TYPE.Sensor, sensorIndex);
            return errCode;
        }

        /// <summary>
        /// Get sensor's current calibration table.
        /// </summary>
        /// <param name="sensorIndex">Index of sensor channel or unique ID</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/> and the current calibration table <see cref="fgt_SENSOR_CALIBRATION"/></returns>
        public static (fgt_ERROR_CODE errCode, fgt_SENSOR_CALIBRATION table) Fgt_get_sensorCalibration(uint sensorIndex)
        {
            var table = 0;
            var errCode = ErrCheck((fgt_ERROR_CODE) _fgt_get_sensorCalibration(sensorIndex, ref table), fgt_ERRCHECK_TYPE.Sensor, sensorIndex);

            return (errCode, (fgt_SENSOR_CALIBRATION) table);
        }

        /// <summary>
        /// Apply a custom scale factor on sensor read value. This function is useful in order to adapt read sensor value to physical measurement.
        /// For example if a flow-unit is used with a special oil and it's calibration table is set to H2O, read flowrate is not correct.
        /// Scale factor is applied using following formula: scaled_value = a* sensor_value + b* sensor_value^2 + c* sensor_value^3
        /// Note that this scale is also used for the regulation.
        /// </summary>
        /// <param name="sensorIndex">sensorIndex Index of sensor channel or unique ID</param>
        /// <param name="scale">New scale to use - a*x + b*x² + c*x³ </param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/></returns>
        public static fgt_ERROR_CODE Fgt_set_sensorCustomScale(uint sensorIndex, (float a, float b, float c) scale)
        {
            var errCode = ErrCheck((fgt_ERROR_CODE) _fgt_set_sensorCustomScale(sensorIndex, scale.a, scale.b, scale.c), fgt_ERRCHECK_TYPE.Sensor, sensorIndex);
            return errCode;
        }

        /// <summary>
        /// Apply a custom scale factor on sensor measurement. This function is useful in order to adapt read sensor value to physical measurement.
        /// For example if a flow-unit is used with a special oil and it's calibration table is set to H2O, read flowrate is not correct.
        /// Scale factor is applied using following formula: scaled_value = a* sensor_value + b* sensor_value^2 + c* sensor_value^3
        /// When applying a custom scale factor, sensor range may increase very rapidly, SMax parameter is meant to limit this maximal value.
        /// This function purpose is to be used with the regulation in order to avoid too high maximum range on the sensor.
        /// </summary>
        /// <param name="sensorIndex">Index of sensor channel or unique ID</param>
        /// <param name="scale">New scale to use - a*x + b*x² + c*x³ </param>
        /// <param name="sMax">SMax after scale maximal value (saturation)</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/></returns>
        public static fgt_ERROR_CODE Fgt_set_sensorCustomScaleEx(uint sensorIndex, (float a, float b, float c) scale, float sMax)
        {
            var errCode = ErrCheck((fgt_ERROR_CODE) _fgt_set_sensorCustomScaleEx(sensorIndex, scale.a, scale.b, scale.c, sMax), fgt_ERRCHECK_TYPE.Sensor, sensorIndex);
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
            var errCode = ErrCheck((fgt_ERROR_CODE) _fgt_calibratePressure(pressureIndex), fgt_ERRCHECK_TYPE.Pressure, pressureIndex);
            return errCode;
        }

        /// <summary>
        /// Start closed loop regulation between a sensor and a pressure controller. Pressure will be regulated in order to reach sensor setpoint.
        /// Custom sensors, outside Fluigent ones, can be used such as different flow-units, pressure, level ...
        /// However we do not guarantee full compatibility with all sensors.Regulation quality is linked to sensor precision and your set-up.
        /// In order to use this function, custom used sensor maximum range and measured values has to be updated at least once per second.
        /// Directly setting pressure on same pressureIndex will stop regulation.
        /// This function must be called at 1Hz minimum or the regulation will stop.
        /// </summary>
        /// <param name="measure">Custom sensor measured value, no unit is required</param>
        /// <param name="setpoint">Custom sensor regulation goal value, no unit is required</param>
        /// <param name="maxSensorRange">Custom sensor maximum range, no unit is required</param>
        /// <param name="pressureIndex">Index of pressure channel or unique ID</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/></returns>
        public static fgt_ERROR_CODE Fgt_set_customSensorRegulation(float measure, float setpoint, float maxSensorRange, uint pressureIndex)
        {
            var errCode = ErrCheck((fgt_ERROR_CODE) _fgt_set_customSensorRegulation(measure, setpoint, maxSensorRange, pressureIndex), fgt_ERRCHECK_TYPE.Generic);
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
            var errCode = ErrCheck((fgt_ERROR_CODE) _fgt_get_pressureRange(pressureIndex, ref pMin, ref pMax), fgt_ERRCHECK_TYPE.Pressure, pressureIndex);
            return (errCode, pMin, pMax);
        }

        /// <summary>
        /// Get sensor minimum and maximum range. Returned values takes into account set unit, default value is 'µl/min' in case of flow-units.
        /// </summary>
        /// <param name="sensorIndex">Index of sensor channel or unique ID</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/> and sensor range min and max</returns>
        public static (fgt_ERROR_CODE errCode, (float sMin, float sMax) range) Fgt_get_sensorRange(uint sensorIndex)
        {
            float sMin = 0, sMax = 0;
            var errCode = ErrCheck((fgt_ERROR_CODE) _fgt_get_sensorRange(sensorIndex, ref sMin, ref sMax), fgt_ERRCHECK_TYPE.Sensor, sensorIndex);
            return (errCode, (sMin, sMax));
        }

        /// <summary>
        /// Set pressure working range and ensure that pressure will never exceed this limit. It takes into account current unit, default value is 'mbar'.
        /// </summary>
        /// <param name="pressureIndex">Index of pressure channel or unique ID</param>
        /// <param name="limits">Min/max pressure working range values</param>
        /// <returns></returns>
        public static fgt_ERROR_CODE Fgt_set_pressureLimit(uint pressureIndex, (float pMin, float pMax) limits)
        {
            var errCode = ErrCheck((fgt_ERROR_CODE) _fgt_set_pressureLimit(pressureIndex, limits.pMin, limits.pMax), fgt_ERRCHECK_TYPE.Pressure, pressureIndex);
            return errCode;
        }

        #endregion

        #region Regulation settings

        /// <summary>
        /// Set on a running regulation pressure response time. Minimal value is 2 for FlowEZ, 6 for MFCS controllers.
        /// </summary>
        /// <param name="sensorIndex">Index of sensor channel or unique ID</param>
        /// <param name="responseTime">Pressure response time in seconds</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/></returns>
        public static fgt_ERROR_CODE Fgt_set_sensorRegulationResponse(uint sensorIndex, uint responseTime)
        {
            var errCode = ErrCheck((fgt_ERROR_CODE) _fgt_set_sensorRegulationResponse(sensorIndex, responseTime), fgt_ERRCHECK_TYPE.Sensor, sensorIndex);
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
            var errCode = ErrCheck((fgt_ERROR_CODE) _fgt_set_pressureResponse(pressureIndex, value), fgt_ERRCHECK_TYPE.Pressure, pressureIndex);
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

            var errCode = _fgt_get_pressureStatus(pressureIndex, ref type, ref controllerSn, ref infoCode, details);

            var detailsString = new string(details.TakeWhile(c => c != '\0').ToArray());

            return ((fgt_ERROR_CODE) errCode, (fgt_INSTRUMENT_TYPE) type, controllerSN: controllerSn, infoCode == 1, detailsString);
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

            var errCode = _fgt_get_sensorStatus(sensorIndex, ref type, ref controllerSn, ref infoCode, details);

            var detailsString = new string(details.TakeWhile(c => c != '\0').ToArray());

            return ((fgt_ERROR_CODE) errCode, (fgt_INSTRUMENT_TYPE) type, controllerSN: controllerSn, infoCode == 1, detailsString);
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
            return (fgt_ERROR_CODE) _fgt_set_power(controllerIndex, (byte) state);
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
            var errCode = _fgt_get_power(controllerIndex, ref state);
            return ((fgt_ERROR_CODE) errCode, (fgt_POWER) state);
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
            var errCode = ErrCheck((fgt_ERROR_CODE) _fgt_set_TtlMode(TtlIndex, (int) mode), fgt_ERRCHECK_TYPE.Generic);
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
            var errCode = ErrCheck((fgt_ERROR_CODE) _fgt_read_Ttl(ttlIndex, ref state), fgt_ERRCHECK_TYPE.Generic);
            return ((fgt_ERROR_CODE) errCode, Convert.ToBoolean(state));
        }

        /// <summary>
        /// Trigger a specific TTL port (BNC ports) if set as output.
        /// </summary>
        /// <param name="ttlIndex">Index of TTL port or unique ID</param>
        /// <returns>Error code <see cref="fgt_ERROR_CODE"/> and a boolean indicating if an event (edge) has occured</returns>
        public static fgt_ERROR_CODE Fgt_trigger_Ttl(uint ttlIndex)
        {
            var errCode = ErrCheck((fgt_ERROR_CODE) _fgt_trigger_Ttl(ttlIndex), fgt_ERRCHECK_TYPE.Generic);
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
            var errCode = ErrCheck((fgt_ERROR_CODE) _fgt_set_purge(controllerIndex, (byte) (purge ? 1 : 0)), fgt_ERRCHECK_TYPE.Generic);
            return errCode;
        }

        /// <summary>
        /// Manually activate internal electrovalve. This stops pressure regulation.
        /// This feature is only available on MFCS and MFCS-EZ devices.
        /// </summary>
        /// <param name="pressureIndex">Index of pressure channel or unique ID</param>
        /// <param name="value">Applied valve voltage from 0 to 100(%)</param>
        /// <returns></returns>
        public static fgt_ERROR_CODE Fgt_set_manual(uint pressureIndex, float value)
        {
            var errCode = ErrCheck((fgt_ERROR_CODE) _fgt_set_manual(pressureIndex, value), fgt_ERRCHECK_TYPE.Pressure, pressureIndex);
            return errCode;
        }

        #endregion

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

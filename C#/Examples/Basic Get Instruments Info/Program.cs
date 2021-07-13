using System;
using System.Collections.Generic;
using System.Linq;
using fgt_sdk;
using fgt_sdk.Enums;
using fgt_sdk.Structs;

namespace fgt_sdk_example_basic_get_instruments_info
{
    /// <summary>
    /// This example shows how to retrieve information about Fluigent instruments: type, controller, serial number, unique ID...
    /// At least one Fluigent pressure or sensor module
    /// </summary>
    static class Program
    {
        static void Main(string[] args)
        {
            // Get total number , SN and type of detected Fluigent instrument controller
            var (controllersCount, instruments) = fgtSdk.Fgt_detect();
            Console.WriteLine($"Total number of controller(s): {controllersCount}");

            fgt_ERROR_CODE errCode;
            int pressureChannelsCount, sensorChannelsCount, ttlChannelsCount, valveChannelsCount;

            if (controllersCount > 0)
            {
                // List all found controllers serial number and type
                for (var index = 0; index < controllersCount; index++)
                {
                    Console.WriteLine($"Detected instrument at index: {index}");
                    Console.WriteLine($"Controller SN: {instruments[index].serialNumber}");
                    Console.WriteLine($"Type: {instruments[index].type}{Environment.NewLine}");
                }

                // Initialize only specific instrument controllers here
                // If you do not want a controller in the list or if you want a specific order (e.g. LineUP before MFCS instruments)
                //	rearrange parsed SN table
                fgtSdk.Fgt_initEx(instruments.Select(i => i.serialNumber).ToList());

                // Get total number of initialized pressure channel(s)
                (errCode, pressureChannelsCount) = fgtSdk.Fgt_get_pressureChannelCount();
                Console.WriteLine($"Total number of pressure channels: {pressureChannelsCount}");

                // Get total number of initialized pressure channel(s)
                (errCode, sensorChannelsCount) = fgtSdk.Fgt_get_sensorChannelCount();
                Console.WriteLine($"Total number of sensor channels: {sensorChannelsCount}");

                // Get total number of initialized TTL channel(s)
                (errCode, ttlChannelsCount) = fgtSdk.Fgt_get_TtlChannelCount();
                Console.WriteLine($"Total number of TTL channels: {ttlChannelsCount}");

                // Get total number of initialized TTL channel(s)
                (errCode, valveChannelsCount) = fgtSdk.Fgt_get_valveChannelCount();
                Console.WriteLine($"Total number of valve channels: {valveChannelsCount}");

                Console.WriteLine("");

                // Get detailed information about all controller(s)
                List<fgt_CONTROLLER_INFO> controllerInfos;
                (errCode, controllerInfos) = fgtSdk.Fgt_get_controllersInfo();

                for (var index = 0; index < controllersCount; index++)
                {
                    Console.WriteLine($"Controller info at index: {index}");
                    Console.WriteLine(controllerInfos[index]);
                    Console.WriteLine("");
                }

                // Get detailed information about all pressure channels
                List<fgt_CHANNEL_INFO> pressureChannelInfo;
                (errCode, pressureChannelInfo) = fgtSdk.Fgt_get_pressureChannelsInfo();
                for (var index = 0; index < pressureChannelsCount; index++)
                {
                    Console.WriteLine($"Pressure channel info at index: {index}");
                    Console.WriteLine(pressureChannelInfo[index]);
                    Console.WriteLine("");
                }

                // Get detailed information about all sensor channels
                List<(fgt_CHANNEL_INFO channelInfo, fgt_SENSOR_TYPE sensorType)> sensorChannelsInfo;
                (errCode, sensorChannelsInfo) = fgtSdk.Fgt_get_sensorChannelsInfo();
                for (var index = 0; index < sensorChannelsCount; index++)
                {
                    Console.WriteLine($"Sensor channel info at index: {index}");
                    Console.WriteLine(sensorChannelsInfo[index].channelInfo);
                    Console.WriteLine($"Sensor type: {sensorChannelsInfo[index].sensorType}{Environment.NewLine}");
                }

                // Get detailed information about all ttl channels
                List<fgt_CHANNEL_INFO> ttlChannelsInfo;
                (errCode, ttlChannelsInfo) = fgtSdk.Fgt_get_TtlChannelsInfo();
                for (var index = 0; index < ttlChannelsCount; index++)
                {
                    Console.WriteLine($"TTL channel info at index: {index}");
                    Console.WriteLine(ttlChannelsInfo[index]);
                    Console.WriteLine("");
                }

                // Get detailed information about all valve channels
                List<(fgt_CHANNEL_INFO channelInfo, fgt_VALVE_TYPE valveType)> valveChannelsInfo;
                (errCode, valveChannelsInfo) = fgtSdk.Fgt_get_valveChannelsInfo();
                for (var index = 0; index < valveChannelsCount; index++)
                {
                    Console.WriteLine($"Valve channel info at index: {index}");
                    Console.WriteLine(valveChannelsInfo[index].channelInfo);
                    Console.WriteLine($"Valve type: {valveChannelsInfo[index].valveType}{Environment.NewLine}");
                }
            }
            else
            {
                Console.WriteLine("Please make sure that your hardware setup matches this example's requirements and that all instruments are connected to the computer");
            }

            fgtSdk.Fgt_close(); // Close session

            Console.WriteLine("Close this console by pressing enter");
            Console.ReadLine();
        }
    }
}

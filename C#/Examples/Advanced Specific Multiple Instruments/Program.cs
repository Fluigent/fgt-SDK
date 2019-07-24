using System;
using System.Collections.Generic;
using System.Linq;
using fgt_sdk;
using fgt_sdk.Structs;

namespace advanced_specific_multiple_instruments
{
    /// <summary>
    /// This example shows how to use specific channels ID and multiple connected instruments
    /// Hardware setup: At least two Fluigent pressure modules
    /// </summary>
    class Program
    {
        static void Main(string[] args)
        {
            // Get total number , SN and type of detected Fluigent instrument controller
            var (controllersCount, instruments) = fgtSdk.Fgt_detect();
            Console.WriteLine($"Total number of controller(s): {controllersCount}");

            if (controllersCount > 0)
            {
                // List all found controllers serial number and type
                for (var index = 0; index < controllersCount; index++)
                {
                    Console.WriteLine($"Detected instrument at index: {index}{Environment.NewLine}" +
                                      $"Controller SN: {instruments[index].serialNumber}{Environment.NewLine}" +
                                      $"Type: {instruments[index].type}{Environment.NewLine}");
                }

                // Initialize only specific instrument controllers here
                // If you do not want a controller in the list or if you want a specific order (e.g. LineUP before MFCS instruments)
                //	rearrange parsed SN table
                // Function Fgt_initEx can be called again, without need of Fgt_close() before. 
                fgtSdk.Fgt_initEx(instruments.Select(i => i.serialNumber).ToList());

                // Get total number of initialized pressure channel(s)
                var (errCode, pressureChannelsCount) = fgtSdk.Fgt_get_pressureChannelCount();
                Console.WriteLine($"Total number of pressure channels: {pressureChannelsCount}");
                if (pressureChannelsCount >= 2)
                {
                    // Get detailed information about all controller(s)
                    List<fgt_CONTROLLER_INFO> controllerInfos;
                    (errCode, controllerInfos) = fgtSdk.Fgt_get_controllersInfo();
                    for (var index = 0; index < controllersCount; index++)
                    {
                        Console.WriteLine($"Controller info at index: {index}{Environment.NewLine}" +
                                          $"SN: {controllerInfos[index].SN}{Environment.NewLine}" +
                                          $"Firmware: {controllerInfos[index].Firmware}{Environment.NewLine}" +
                                          $"ID: {controllerInfos[index].Id}{Environment.NewLine}" +
                                          $"Type: {controllerInfos[index].InstrType}{Environment.NewLine}");
                    }

                    // Get detailed information about all pressure channels
                    List<fgt_CHANNEL_INFO> pressureChannelsInfo;
                    (errCode, pressureChannelsInfo) = fgtSdk.Fgt_get_pressureChannelsInfo();
                    for (var index = 0; index < pressureChannelsCount; index++)
                    {
                        Console.WriteLine($"Pressure channel info at index: {index}{Environment.NewLine}" +
                                          $"Controller SN: {pressureChannelsInfo[index].ControllerSN}{Environment.NewLine}" +
                                          $"Device SN: {pressureChannelsInfo[index].DeviceSN}{Environment.NewLine}" +
                                          $"Firmware: {pressureChannelsInfo[index].Firmware}{Environment.NewLine}" +
                                          $"Position: {pressureChannelsInfo[index].Position}{Environment.NewLine}" +
                                          $"Index: {pressureChannelsInfo[index].Index}{Environment.NewLine}" +
                                          $"ID: {pressureChannelsInfo[index].IndexId}{Environment.NewLine}" +
                                          $"Type: {pressureChannelsInfo[index].InstrType}{Environment.NewLine}");
                    }

                    // If you want to address a specific channel, unique ID can be used. However if hardware changed channel may not be found

                    // Read pressure
                    float pressure;
                    (errCode, pressure) = fgtSdk.Fgt_get_pressure(pressureChannelsInfo[0].IndexId);
                    Console.WriteLine($"Read pressure from ID {pressureChannelsInfo[0].IndexId}: Pressure: {pressure}");
                    (errCode, pressure) = fgtSdk.Fgt_get_pressure(pressureChannelsInfo[1].IndexId);
                    Console.WriteLine($"Read pressure from ID {pressureChannelsInfo[1].IndexId}: Pressure: {pressure}");
                }
                else
                {
                    Console.WriteLine("Please make sure that your hardware setup matches this example's requirements and that all instruments are connected to the computer");
                }
            }
            else
            {
                Console.WriteLine("Please make sure that your hardware setup matches this example's requirements and that all instruments are connected to the computer");
            }

            // Close session
            fgtSdk.Fgt_close();

            Console.WriteLine("Close this console by pressing enter");
            Console.ReadLine();
        }
    }
}

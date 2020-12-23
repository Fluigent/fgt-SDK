using System;
using System.Collections.Generic;
using System.Threading;
using fgt_sdk;
using fgt_sdk.Enums;
using fgt_sdk.Structs;

namespace Basic_Read_Sensor_Data
{
    class Program
    {
        /// <summary>
        /// This example shows how to retrieve a data from the sensor channel
        /// Hardware setup: One or more connected devices with sensor channel(s) or standalone sensor device(s).
        /// </summary>
        /// <param name="args"></param>
        static void Main(string[] args)
        {
            fgt_ERROR_CODE errCode;

            // Initialize session with all detected Fluigent instrument(s)
            // This step is optional, if not called session will be automatically created
            errCode = fgtSdk.Fgt_init();

            if (errCode == fgt_ERROR_CODE.OK)
            {
                int sensorChannelsCount;
                // Get total number of initialized sensor channel(s)
                (errCode, sensorChannelsCount) = fgtSdk.Fgt_get_sensorChannelCount();
                Console.WriteLine($"Status: {errCode} ### Total number of sensor channels detected: {sensorChannelsCount}");

                List<(fgt_CHANNEL_INFO channelInfo, fgt_SENSOR_TYPE sensorType)> sensorChannelsInfo;
                // Get information about the connected sensor channel(s)
                (errCode, sensorChannelsInfo) = fgtSdk.Fgt_get_sensorChannelsInfo();
                Console.WriteLine($"Status: {errCode} ### Retrieved information about {sensorChannelsInfo.Count} sensor channel(s)");

                // Display the sensor(s) general information in console
                foreach (var channel in sensorChannelsInfo)
                {
                    uint index = channel.channelInfo.Index;
                    Console.WriteLine($"{Environment.NewLine} ### Index: {index}{Environment.NewLine}" +
                      $" ### Device SN: {channel.channelInfo.DeviceSN}{Environment.NewLine}" +
                      $" ### Firmware: {channel.channelInfo.Firmware}{Environment.NewLine}" +
                      $" ### ID: {channel.channelInfo.IndexId}{Environment.NewLine}" +
                      $" ### Type: {channel.channelInfo.InstrType}{Environment.NewLine}" +
                      $" ### Sensor type: {channel.sensorType}{Environment.NewLine}");

                    string unit;
                    // Retrieve the sensor unit 
                    (errCode, unit) = fgtSdk.Fgt_get_sensorUnit(index);
                    Console.WriteLine($"Status: {errCode} ### Sensor {index} unit {unit}");

                    float pmin, pmax;
                    // Get information about the sensor range
                    (errCode, (pmin, pmax)) = fgtSdk.Fgt_get_sensorRange(index);
                    Console.WriteLine($"Status: {errCode} ### Sensor {index} range from {pmin:0} to {pmax:0} {unit}");

                    float value;
                    // Read sensor data
                    for (int i = 0; i < 5; i++)
                    {
                        // Retrieve value from sensor
                        (errCode, value) = fgtSdk.Fgt_get_sensorValue(index);
                        Console.WriteLine($"Status: {errCode} ### Sensor {index} returned value {value:0.0} {unit}");

                        // Add a small delay between value read
                        Thread.Sleep(200);
                    }
                }
            }
            else
            {
                Console.WriteLine($"Status: {errCode} ### Please make sure that your hardware setup matches this example's requirements and that all instruments are connected to the computer");
            }

            fgtSdk.Fgt_close(); // Close session

            Console.WriteLine($"{Environment.NewLine}Close this console by pressing enter");
            Console.ReadLine();
        }
    }
}

using System;
using System.Threading;
using fgt_sdk;
using fgt_sdk.Enums;

namespace Advanced_Custom_Sensor_Regulation
{
    /// <summary>
    /// This example shows how to use a custom sensor, different from Fluigent ones and regulate pressure in order to reach setpoint.
    /// Different sensor type and range can be used (e.g.liquid pressure,  water level, l/min flow meter...) however we do not guarantee  full compatibility with all sensors.
    /// For this demonstration a Fluigent flow-unit is used for more simplicity
    /// Hardware setup: At least one Fluigent pressure controller (MFCS, MFCS-EZ or FlowEZ) and at least one Fluigent sensor(flow-unit connected to FRP or FlowEZ
    /// </summary>
    static class Program
    {
        static void Main(string[] args)
        {
            // Initialize session with all detected Fluigent instrument(s)
            // This step is optional, if not called session will be automatically created
            var errCode = fgtSdk.Fgt_init();

            if (errCode == fgt_ERROR_CODE.OK)
            {
                // Get sensor range
                // When using a custom sensor, it's range has to be known.
                (float sMin, float sMax) range;
                (errCode, range) = fgtSdk.Fgt_get_sensorRange(0); 
                // Replace this function with your custom sensor interface
                // Loop for 10 seconds waiting 100ms between each sensor update
                for (var index = 0; index < 100; index++)
                {
                    // Read sensor value
                    // Replace this function with your custom sensor interface
                    float value;
                    (errCode, value) = fgtSdk.Fgt_get_sensorValue(0); 

                    // Update regulation with sensor values. Here setpoint is set to 50% of sensor range, first pressure channel of the list is used
                    Console.WriteLine($"Running custom regulation, read: {value}, setpoint: {range.sMax/2}");
                    fgtSdk.Fgt_set_customSensorRegulation(value, range.sMax / 2, range.sMax, 0);

                    // Wait 100 milliseconds. Wait time between two successive updates should be 1 seconds or less, otherwise pressure regulation is stopped
                    Thread.Sleep(100);
                }

                // Set pressure to 0 before close, it also stops running regulation, otherwise it will automatically stop after 1s
                fgtSdk.Fgt_set_pressure(0, 0); 
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

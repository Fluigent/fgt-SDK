using System;
using System.Threading;
using fgt_sdk;
using fgt_sdk.Enums;

namespace fgt_sdk_example_basic_sensor_regulation
{
    /// <summary>
    /// This example shows how to set a sensor regulation and generate a sinusoidal profile on the first sensor and pressure module of the chain
    /// Hardware setup: At least one Fluigent pressure controller(MFCS, MFCS-EZ or FlowEZ) and at least one Fluigent sensor(flow-unit connected to FRP or FlowEZ)
    /// </summary>
    static class Program
    {
        static void Main(string[] args)
        {
            // Initialize session with all detected Fluigent instrument(s)
            // This step is optional, if not called session will be automatically created
            fgtSdk.Fgt_init();

            // Get sensor range
            fgt_ERROR_CODE errCode;
            float sMin;
            float sMax;
            (errCode, (sMin, sMax)) = fgtSdk.Fgt_get_sensorRange(0);

            if (errCode == fgt_ERROR_CODE.OK)
            {
                // Read sensor value
                float value;
                (errCode, value) = fgtSdk.Fgt_get_sensorValue(0);
                Console.WriteLine($"Read sensor value: {value}");

                // Start regulation between pressure controller with sensor
                Console.WriteLine($"Start sensor regulation to {sMax / 10} (ul/min is the default unit) using first pressure controller and sensor");
                fgtSdk.Fgt_set_sensorRegulation(0, 0, sMax / 10);

                // Wait 5 seconds letting pressure to establish
                Console.WriteLine("Waiting 5 seconds...");
                Thread.Sleep(5000);

                // Read sensor value
                (errCode, value) = fgtSdk.Fgt_get_sensorValue(0);
                Console.WriteLine($"Read sensor value: {value}");

                // Create a sinusoidal profile from 0 to device maximal sensor range
                Console.WriteLine("Set sinusoidal orders from 0 to device maximal sensor range");
                for (var loop = 0; loop < 360; loop += 10)
                {
                    // Set regulation
                    var setPoint = (float) Math.Sin(loop * Math.PI / 360) * sMax;
                    Console.WriteLine($"Set sensor regulation: {setPoint}");
                    fgtSdk.Fgt_set_sensorRegulation(0, 0, setPoint);

                    // Wait 1 second
                    Thread.Sleep(1000);

                    // Read sensor value
                    (errCode, value) = fgtSdk.Fgt_get_sensorValue(0);
                    Console.WriteLine($"Read sensor value: {value}");
                }

                // Set pressure to 0 before close, it also stops running regulation
                fgtSdk.Fgt_set_pressure(0, 0);
            }
            else
            {
                if(errCode == fgt_ERROR_CODE.No_instr_found)
                    Console.WriteLine("Please make sure that your hardware setup matches this example's requirements and that all instruments are connected to the computer");
            }

            // Close session
            fgtSdk.Fgt_close();

            Console.WriteLine("Close this console by pressing enter");
            Console.ReadLine();
        }
    }
}

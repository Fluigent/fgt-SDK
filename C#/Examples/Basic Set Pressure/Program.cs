using System;
using System.Threading;
using fgt_sdk;
using fgt_sdk.Enums;

namespace fgt_sdk_example_basic_set_pressure
{
    static class Program
    {
        /// <summary>
        /// This example shows how to set a pressure order and generate a ramp on the first pressure module of the chain
        /// Hardware setup: At least one Fluigent pressure controller (MFCS, MFCS-EZ or FlowEZ)
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
                // Set pressure to 20 (mBar in default unit) on first pressure channel of the list
                Console.WriteLine("Set pressure to 20 (mBar is the default unit) on first pressure channel of the list");
                fgtSdk.Fgt_set_pressure(0, 20);

                // Wait 5 seconds letting pressure to establish
                Console.WriteLine("Waiting 5 seconds...");
                Thread.Sleep(5000);

                // Read pressure value

                float pressure;
                (errCode, pressure) = fgtSdk.Fgt_get_pressure(0);
                Console.WriteLine($"Read pressure: {pressure}");

                // Get pressure controller range
                float pMin;
                float pMax;
                (errCode, pMin, pMax) = fgtSdk.Fgt_get_pressureRange(0);

                // Create a pressure ramp profile from device minimal to maximal pressure range
                Console.WriteLine("Send a pressure ramp from device minimal to maximal pressure range");

                // (max(maxPressure, abs(minPressure))/10 increment allows example to run both on positive and vacuum pressure controllers
                for (var rampPressure = pMin; rampPressure < pMax; rampPressure += (Math.Max(pMax, Math.Abs(pMin)) / 10))
                {
                    // Set pressure
                    Console.WriteLine($"Set pressure: {rampPressure}");
                    fgtSdk.Fgt_set_pressure(0, rampPressure);

                    // Wait 1 second
                    Thread.Sleep(1000);

                    // Read pressure
                    (errCode, pressure) = fgtSdk.Fgt_get_pressure(0);
                    Console.WriteLine($"Read pressure: {pressure}");
                }

                fgtSdk.Fgt_set_pressure(0, 0); // Set pressure to 0 before close
            }
            else
            {
                if (errCode == fgt_ERROR_CODE.No_instr_found)
                    Console.WriteLine("Please make sure that your hardware setup matches this example's requirements and that all instruments are connected to the computer");
            }

            fgtSdk.Fgt_close(); // Close session

            Console.WriteLine("Close this console by pressing enter");
            Console.ReadLine();
        }
    }
}

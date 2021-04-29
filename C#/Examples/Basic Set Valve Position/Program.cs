using fgt_sdk;
using fgt_sdk.Enums;
using System;

namespace fgt_sdk_example_basic_set_valve_position
{
    internal static class Program
    {
        /// <summary>
        /// This example shows how to change the position of a valve
        /// Hardware setup: at least one Fluigent valve controller(M-Switch, L-Switch,
        /// 2-Switch or P-Switch)
        /// </summary>
        /// <param name="args"></param>
        private static void Main(string[] args)
        {
            fgt_ERROR_CODE errCode;

            // Initialize session with all detected Fluigent instrument(s)
            // This step is optional, if not called session will be automatically created
            errCode = fgtSdk.Fgt_init();

            if (errCode == fgt_ERROR_CODE.OK)
            {
                // Get number of valves
                int valveCount;
                (_, valveCount) = fgtSdk.Fgt_get_valveChannelCount();

                for (uint valveIndex = 0U; valveIndex < valveCount; valveIndex++)
                {
                    (fgt_ERROR_CODE _, int currentPosition) = fgtSdk.Fgt_get_valvePosition(valveIndex);
                    Console.WriteLine($"Valve {valveIndex} is at position {currentPosition}");
                    // Get all available positions for this valve
                    (fgt_ERROR_CODE _, int maxPosition) = fgtSdk.Fgt_get_valveRange(valveIndex);
                    // Set valve to each of the available positions, waiting for it to switch each time
                    for (int position = 0; position <= maxPosition; position++)
                    {
                        fgtSdk.Fgt_set_valvePosition(valveIndex, position);
                        (_, currentPosition) = fgtSdk.Fgt_get_valvePosition(valveIndex);
                        Console.WriteLine($"Valve {valveIndex} is at position {currentPosition}");
                    }
                    // Return valve to default position
                    fgtSdk.Fgt_set_valvePosition(valveIndex, 0);
                }
            }
            else
            {
                if (errCode == fgt_ERROR_CODE.No_instr_found)
                {
                    Console.WriteLine("Please make sure that your hardware setup matches this example's requirements and that all instruments are connected to the computer");
                }
            }

            // Close session
            fgtSdk.Fgt_close();
        }
    }
}

using System;
using System.Threading;
using fgt_sdk;
using fgt_sdk.Enums;

namespace Advanced_Features
{
    /// <summary>
    /// This example shows advanced features such as limits, units and calibration.
    /// Hardware setup: At least one Fluigent pressure controller (MFCS, MFCS-EZ or FlowEZ) and/or one Fluigent sensor(flow-unit connected to FRP or FlowEZ)
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
                #region Unit change

                // Read pressure value
                float pressure;
                string unit;
                (errCode, pressure) = fgtSdk.Fgt_get_pressure(0);
                (errCode, unit) = fgtSdk.Fgt_get_pressureUnit(0);
                Console.WriteLine($"Read pressure: {pressure} {unit}");

                // Read sensor value
                float value;
                (errCode, value) = fgtSdk.Fgt_get_sensorValue(0);
                (errCode, unit) = fgtSdk.Fgt_get_sensorUnit(0);
                Console.WriteLine($"Read sensor: {value} {unit}");

                // Change pressure and sensor unit
                fgtSdk.Fgt_set_pressureUnit(0, "kPa"); // Note that if incorrect or invalid unit is used an error is returned.
                fgtSdk.Fgt_set_sensorUnit(0, "ulperhour"); // When unit is changed, all values are then in set unit
                Console.WriteLine("Changed pressure and sensor unit");

                // Read pressure value again
                (errCode, pressure) = fgtSdk.Fgt_get_pressure(0);
                (errCode, unit) = fgtSdk.Fgt_get_pressureUnit(0);
                Console.WriteLine($"Read pressure: {pressure} {unit}");

                // Read sensor value again
                (errCode, value) = fgtSdk.Fgt_get_sensorValue(0);
                (errCode, unit) = fgtSdk.Fgt_get_sensorUnit(0);
                Console.WriteLine($"Read sensor: {value} {unit}");

                #endregion

                #region Limit change

                // Get pressure controller range
                float pMin;
                float pMax;
                (errCode, pMin, pMax) = fgtSdk.Fgt_get_pressureRange(0);

                fgtSdk.Fgt_set_pressureLimit(0, (pMin / 2, pMax / 2));
                Console.WriteLine($"Changed pressure limits to [{pMin / 2}; {pMax / 2}]");
                Console.WriteLine($"Trying to set pressure at {(pMax == 0 ? pMin : pMax)}");
                fgtSdk.Fgt_set_pressure(0, pMax == 0 ? pMin : pMax);

                #endregion

                #region Calibration

                // Calibrate pressure channel
                fgtSdk.Fgt_calibratePressure(0);
                Thread.Sleep(1000);
                Console.WriteLine("Pressure channel calibration pending... Now trying to send pressure order at same time");
                // An error is thrown, during calibration step pressure orders are not expected
                errCode = fgtSdk.Fgt_set_pressure(0, pMax == 0 ? pMin / 2 : pMax / 2);

                // Read sensor calibration table
                fgt_SENSOR_CALIBRATION table;
                (errCode, table) = fgtSdk.Fgt_get_sensorCalibration(0);
                Console.WriteLine($"Read sensor calibration: {table}");

                // Change sensor calibration
                // WARNING: For IPS use only when current pressure is 0 mbar. This function will set current pressure as a reference point. Enum parameter fgt_SENSOR_CALIBRATION is irrelevant for IPS
                fgtSdk.Fgt_set_sensorCalibration(0, fgt_SENSOR_CALIBRATION.H2O); // Note that if calibration is not supported, an error is thrown
                Console.WriteLine($"Setting sensor calibration to {fgt_SENSOR_CALIBRATION.H2O}...");
                Thread.Sleep(1000); // As for pressure calibration, this step needs few moments before read values are correct. Same error is thrown.
                (errCode, table) = fgtSdk.Fgt_get_sensorCalibration(0);
                Console.WriteLine($"Read sensor calibration: {table}");

                #endregion
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

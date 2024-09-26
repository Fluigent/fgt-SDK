/*============================================================================
*               Fluigent Software Developement Kit for C++
*----------------------------------------------------------------------------
*         Copyright (c) Fluigent 2021.  All Rights Reserved.
*----------------------------------------------------------------------------
*
* Title:   Advanced Features.cpp
* Purpose: This example shows advanced features such as limits, units and calibration.
*
* Software: fgt_SDK is the library managing all Fluigent instruments
*			"fgt_SDK_Cpp.h" is the wrapper to fgt_SDK dll
* Hardware setup: At least one Fluigent pressure controller (MFCS, MFCS-EZ or FlowEZ)
*					and/or one Fluigent sensor (flow-unit connected to FRP or FlowEZ)
* Version: 21.0.0.0
* Date:	04/2021
*============================================================================*/


#include <iostream>
#include <thread>
#include "fgt_SDK_Cpp.h"			// include wrapper to fgt_SDK dll, functions can also be accessed by loading the dll

int main()
{
	// Variables declaration
	float pressure;					// used to read returned pressure value
	float sensorValue;				// used to read returned sensor value
	float maxPressure;				// min/max pressure controller range
	float minPressure;
	std::string pressure_unit;
	std::string sensor_unit;
	fgt_SENSOR_CALIBRATION sensor_calibration;	// Sensor returned calibration. See fgt_SDK.h file for types definition
	fgt_ERROR_CODE returnCode;

	unsigned int pressure_index = 0;// Pressure channel index, 0 if first detected channel of the list
	unsigned int sensor_index = 0;	// Pressure channel index, 0 if first detected channel of the list

	Fgt_init();						// Initialize session with all detected Fluigent instrument(s)
									// This step is optional, if not called session will be automatically created

	/** ------- Unit change -------- */
	// Read pressure value
	Fgt_get_pressure(pressure_index, &pressure);
	Fgt_get_pressureUnit(pressure_index, &pressure_unit);
	std::cout << "Read pressure: " << pressure << " " << pressure_unit << std::endl;

	// Read sensor value
	Fgt_get_sensorValue(sensor_index, &sensorValue);
	Fgt_get_sensorUnit(sensor_index, &sensor_unit);
	std::cout << "Read sensor: " << sensorValue << " " << sensor_unit << std::endl;

	// Change pressure and sensor unit
	Fgt_set_pressureUnit(pressure_index, "PSI");				// Note that if incorrect or invalid unit is used an error is returned.
	Fgt_set_sensorUnit(sensor_index, "ulperhour");				// When unit is changed, all values are then in set unit
	std::cout << "Changed pressure and sensor unit" << std::endl;

	// Read pressure value again
	Fgt_get_pressure(pressure_index, &pressure);
	Fgt_get_pressureUnit(pressure_index, &pressure_unit);
	std::cout << "Read pressure: " << pressure << " " << pressure_unit << std::endl;

	// Read sensor value again
	Fgt_get_sensorValue(sensor_index, &sensorValue);
	Fgt_get_sensorUnit(sensor_index, &sensor_unit);
	std::cout << "Read sensor: " << sensorValue << " " << sensor_unit << std::endl << std::endl;

	/** ------- Limit change -------- */
	// Get pressure controller range
	Fgt_get_pressureRange(0, &minPressure, &maxPressure);

	Fgt_set_pressureLimit(pressure_index, minPressure / 2, maxPressure / 2);
	std::cout << "Changed pressure limit to " << minPressure / 2 << " - " << maxPressure / 2 << std::endl;
	std::cout << "Trying to set pressure at " << maxPressure << std::endl;
	Fgt_set_pressure(pressure_index, maxPressure);
	std::cout << std::endl;

	/** ------- Calibration -------- */
	// Calibrate pressure channel
	Fgt_calibratePressure(pressure_index);
	std::cout << "Calibrating pressure channel... trying to send pressure order in same time" << std::endl;
	Fgt_set_pressure(pressure_index, maxPressure/2);			// An error is thrown, set pressure orders are not accepted during calibration
	std::cout << std::endl;

	// Read sensor calibration table
	Fgt_get_sensorCalibration(sensor_index, &sensor_calibration);
	std::cout << "Read sensor calibration: " << sensor_calibration << std::endl;

	// Change sensor calibration
	// WARNING: For IPS use only when current pressure is 0 mbar. This function will set current pressure as a reference point. Enum parameter fgt_SENSOR_CALIBRATION is irrelevant for IPS
	Fgt_set_sensorCalibration(sensor_index, fgt_SENSOR_CALIBRATION::H2O);	// Note that if calibration is not supported, an error is thrown
	std::cout << "Setting sensor calibration..." << std::endl;

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));										// As for pressure calibration, this step needs a few moments before the read values are correct. The same error is thrown.
	
	returnCode = Fgt_get_sensorCalibration(sensor_index, &sensor_calibration);	// Note that each function returns a number, it can be managed locally or globally by "Fgt_Manage_Sensor_Status" function of fgt_SDK_Cpp.cpp file
	std::cout << "Read sensor calibration: " << sensor_calibration << " ,error code: " << returnCode << std::endl;

	Fgt_set_pressure(pressure_index, 0);						// Set pressure to 0 before close
	Fgt_close();								// Close session

}

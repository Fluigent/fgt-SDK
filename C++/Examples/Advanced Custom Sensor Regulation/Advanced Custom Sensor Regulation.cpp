/*============================================================================
*               Fluigent Software Developement Kit for C++
*----------------------------------------------------------------------------
*         Copyright (c) Fluigent 2021.  All Rights Reserved.
*----------------------------------------------------------------------------
*
* Title:   Advanced Custom Sensor Regulation.cpp
* Purpose: This example shows how to use a custom sensor, different from
*			Fluigent ones and regulate pressure in order to reach the setpoint.
*			Different sensor types and ranges can be used (e.g. liquid pressure,
*			water level, l/min flow meter...), however, we do not guarantee 
*			full compatibility with all sensors.
*			For this demonstration, a Fluigent Flow Unit is used for more simplicity.
*
* Software: fgt_SDK is the library managing all Fluigent instruments
*			"fgt_SDK_Cpp.h" is the wrapper to fgt_SDK dll
* Hardware setup: At least one Fluigent pressure controller (MFCS, MFCS-EZ or Flow EZ)
*					and at least one Fluigent sensor (Flow Unit connected to
*					FRP or Flow EZ
* Version: 21.0.0.0
* Date:	04/2021
*============================================================================*/


#include <iostream>
#include <thread>
#include "fgt_SDK_Cpp.h"			// include wrapper to fgt_SDK dll, functions can also be accessed by loading the dll

int main()
{
	// Variables declaration
	float sensorRead;				// used to read returned sensor value
	float maxSensor;				// min/max custom sensor range
	float minSensor;

	Fgt_init();						// Initialize session with all detected Fluigent instrument(s)
									// This step is optional, if not called session will be automatically created

	// Get sensor range
	Fgt_get_sensorRange(0, &minSensor, &maxSensor);		// When using a custom sensor, its range has to be known.
																	// Replace this function with your custom sensor interface
	// Loop for 10 seconds waiting 100ms between each sensor update
	for(unsigned int loop = 0; loop < 100; loop++)
	{
		// Read sensor value
		Fgt_get_sensorValue(0, &sensorRead);						// Replace this function with your custom sensor interface

		// Update regulation with sensor values. Here setpoint is set to 50% of sensor range, first pressure channel of the list is used
		std::cout << "Running custom regulation, read: " << sensorRead << ", setpoint: " << maxSensor / 2 << std::endl;
		Fgt_set_customSensorRegulation(sensorRead, maxSensor/2 , maxSensor, 0);

		// Wait 100 milliseconds. Wait time between two successive updates should be 1 seconds or less, otherwise pressure regulation is stopped
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	Fgt_set_pressure(0, 0);	// Set pressure to 0 before close, it also stops running regulation, otherwise it will automatically stop after 1s

	Fgt_close();								// Close session
}

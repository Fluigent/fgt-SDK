/*============================================================================
*               Fluigent Software Developement Kit for C++
*----------------------------------------------------------------------------
*         Copyright (c) Fluigent 2019.  All Rights Reserved.
*----------------------------------------------------------------------------
*
* Title:   Basic Sensor Regulation.cpp
* Purpose: This example shows how to set a sensor regulation and generate a
*			sinusoidal profile on the first sensor and pressure module of the chain
*
* Software: fgt_SDK_*.dll is the dynamic linked library managing all Fluigent
*			 instruments (pressure and sensors)
*			"fgt_SDK_Cpp.h" is the wrapper to fgt_SDK dll
* Hardware setup: At least one Fluigent pressure controller (MFCS, MFCS-EZ or FlowEZ)
*					and at least one Fluigent sensor (flow-unit connected to 
*					FRP or FlowEZ)
* Version: 19.0.0.0
* Date:	06/2019
*============================================================================*/


#include <iostream>
#include <math.h>
#include "../fgt_SDK_Cpp.h"			// include wrapper to fgt_SDK dll, functions can also be accessed by loading the dll

#define PI 3.14159265

int main()
{
	// Variables declaration
	float sensorRead;				// used to read returned sensor value
	float maxSensor;				// min/max pressure controller range
	float minSensor;

	Fgt_init();						// Initialize session with all detected Fluigent instrument(s)
									// This step is optional, if not called session will be automatically created

	// Get sensor range
	Fgt_get_sensorRange(0, &minSensor, &maxSensor);

	// Read sensor value
	Fgt_get_sensorValue(0, &sensorRead);
	std::cout << "Read sensor value: " << sensorRead << std::endl;

	// Start regulation between pressure controller with sensor
	std::cout << "Start sensor regulation to " << maxSensor/10 << " (ul/min is the default unit) using first pressure controller and sensor" << std::endl;
	Fgt_set_sensorRegulation(0, 0, maxSensor / 10);

	// Wait 5 seconds letting pressure to establish
	std::cout << "Waiting 5 seconds..." << std::endl;
	Sleep(5000);

	// Read sensor value
	Fgt_get_sensorValue(0, &sensorRead);
	std::cout << "Read sensor value: " << sensorRead << std::endl;

	Fgt_set_sensorCustomScale(0, -1, 0, 0);
	std::cout << "Apply scale factor scaled_value = -sensor_value" << std::endl;

	// Create a sinusoidal profile from 0 to device maximal sensor range
	std::cout << "Set sinusoidal orders from 0 to device maximal sensor range" << std::endl;
	for (int loop = 0; loop < 360; loop+=10)
	{
		// Set regulation
		std::cout << "Set sensor regulation: " << sin(loop * PI / 360) * maxSensor << std::endl;
		Fgt_set_sensorRegulation(0, 0, sin(loop * PI / 360)* maxSensor);

		// Wait 1 second
		Sleep(1000);

		// Read sensor value
		Fgt_get_sensorValue(0, &sensorRead);
		std::cout << "Read sensor value: " << sensorRead << std::endl;
	}

	Fgt_set_pressure(0, 0);	// Set pressure to 0 before close, it also stops running regulation

	Fgt_close();								// Close session

	system("PAUSE");
}

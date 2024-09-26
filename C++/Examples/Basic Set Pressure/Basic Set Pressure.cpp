/*============================================================================
*               Fluigent Software Developement Kit for C++                   
*----------------------------------------------------------------------------
*         Copyright (c) Fluigent 2021.  All Rights Reserved.                 
*----------------------------------------------------------------------------
*                                                                            
* Title:   Basic Set Pressure.cpp                                            
* Purpose: This example shows how to set a pressure order and generate a ramp
*			on the first pressure module of the chain			  									  
*			
* Software: fgt_SDK is the library managing all Fluigent instruments
*			"fgt_SDK_Cpp.h" is the wrapper to fgt_SDK dll
* Hardware setup: At least one Fluigent pressure controller (MFCS, MFCS-EZ or Flow EZ)
* Version: 21.0.0.0                                                          
* Date:	04/2021														  
*============================================================================*/


#include <iostream>
#include <thread>
#include <algorithm>
#include "fgt_SDK_Cpp.h"			// include wrapper to fgt_SDK dll, functions can also be accessed by loading the dll

int main()
{
	// Variables declaration
	float pressure;					// used to read returned pressure value
	float maxPressure;				// min/max pressure controller range
	float minPressure;

	Fgt_init();						// Initialize session with all detected Fluigent instrument(s)
									// This step is optional, if not called session will be automatically created

	// Set pressure to 20 (mbar in default unit) on first pressure channel of the list
	std::cout << "Set pressure to 20 (mbar is the default unit) on first pressure channel of the list" << std::endl;
	Fgt_set_pressure(0, 20);

	// Wait 5 seconds for the pressure to settle
	std::cout << "Waiting 5 seconds..." << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(5000));

	// Read pressure value
	Fgt_get_pressure(0, &pressure);
	std::cout << "Read pressure: " << pressure << std::endl;

	// Get pressure controller range
	Fgt_get_pressureRange(0, &minPressure, &maxPressure);

	// Create a pressure ramp profile from device minimal to maximal pressure range
	std::cout << "Send a pressure ramp from device minimal to maximal pressure range" << std::endl;
	for(float loop = minPressure; loop <= maxPressure; loop += (std::max(maxPressure, std::abs(minPressure))/10))		// (max(maxPressure, abs(minPressure))/10 increment allows example to run on both positive and vacuum pressure controllers
	{ 
		// Set pressure
		std::cout << "Set pressure: " << loop << std::endl;
		Fgt_set_pressure(0, loop);

		// Wait 1 second
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));

		// Read pressure
		Fgt_get_pressure(0, &pressure);
		std::cout << "Read pressure: " << pressure << std::endl;
	}

	Fgt_set_pressure(0, 0);	// Set pressure to 0 before close

	Fgt_close();								// Close session
}

/*============================================================================
*               Fluigent Software Developement Kit for C++
*----------------------------------------------------------------------------
*         Copyright (c) Fluigent 2021.  All Rights Reserved.
*----------------------------------------------------------------------------
*
* Title:   Basic Read Sensor Data.cpp
* Purpose: Quick example to retrieve the data from the sensor channel
*
* Software: fgt_SDK is the library managing all Fluigent instruments
*			"fgt_SDK_Cpp.h" is the wrapper to fgt_SDK dll
* Hardware setup: At least one Fluigent pressure or sensor module
* Version: 21.0.0.0
* Date:	04/2021
*============================================================================*/


#include <iostream>
#include <iomanip>					// include iomanip for improved console output formatting
#include <thread>
#include "fgt_SDK_Cpp.h"			// include wrapper to fgt_SDK dll, functions can also be accessed by loading the dll

int main()
{
	// Variables declaration
	fgt_CHANNEL_INFO sensor_info[256];
	fgt_SENSOR_TYPE sensor_type[256];
	unsigned char sensor_number = 0;
	std::string unit = "";
	float range_min = 0;
	float range_max = 0;
	float sensor_value = 0;
	fgt_ERROR_CODE errCode = fgt_ERROR_CODE::OK;

	// Initialize session with all detected Fluigent instrument(s)
	// This step is optional, if not called session will be automatically created
	errCode = Fgt_init();

	if (errCode == fgt_ERROR_CODE::OK)
	{		
		// Get total number of initialized sensor channel(s)
		errCode = Fgt_get_sensorChannelCount(&sensor_number);
		std::cout << "Status: " << errCode << " ### Total number of sensor channels detected: " << int(sensor_number) << std::endl;

		// Get information about the connected sensor channel(s)
		errCode = Fgt_get_sensorChannelsInfo(sensor_info, sensor_type);
		std::cout << "Status: " << errCode << " ### Retrieved information about sensor channel(s)" << std::endl;

		for (unsigned char index = 0; index < sensor_number; index++) 
		{
			std::cout << "\n  ### Index: " << int(index) << "\n"
			<< "  ### Device SN: " << sensor_info[index].DeviceSN << "\n"
			<< "  ### Firmware: " << sensor_info[index].firmware << "\n"
			<< "  ### ID: " << sensor_info[index].indexID << "\n"
			<< "  ### Type: " << sensor_info[index].InstrType << "\n"
			<< "  ### Sensor type: " << sensor_type[index] << "\n" << std::endl;

			// Retrieve the sensor unit 
			errCode = Fgt_get_sensorUnit(index, &unit);
			std::cout << "Status: " << errCode << " ### Sensor " << int(index) << " unit " << unit << std::endl;

			// Get information about the sensor range
			errCode = Fgt_get_sensorRange(index, &range_min, &range_max);
			std::cout << "Status: " << errCode << " ### Sensor " << int(index) << " range from " << range_min << " to " << range_max << " " << unit << std::endl;	

			// Read sensor data
			for (int i = 0; i < 5; i++) 
			{
				// Retrieve value from sensor
				errCode = Fgt_get_sensorValue(index, &sensor_value);
				std::cout << "Status: " << errCode << " ### Sensor " << int(index) << " returned value " << std::fixed<<std::setprecision(2) << sensor_value << " " << unit << std::endl;

				// Add a small delay between value read
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
			}
		
		}
	}
	else 
	{
		std::cout << "Please make sure that your hardware setup matches this example's requirements and that all instruments are connected to the computer" << std::endl;
	}

	// Close session
	Fgt_close();
	
}


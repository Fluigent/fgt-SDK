/*============================================================================
*               Fluigent Software Developement Kit for C++
*----------------------------------------------------------------------------
*         Copyright (c) Fluigent 2021.  All Rights Reserved.
*----------------------------------------------------------------------------
*
* Title:   Basic Get Instruments Info.cpp
* Purpose: This example shows how to retrieve information about Fluigent 
*			instruments: type, controller, serial number, unique ID...
*
* Software: fgt_SDK is the library managing all Fluigent instruments
*			"fgt_SDK_Cpp.h" is the wrapper to fgt_SDK dll
* Hardware setup: At least one Fluigent pressure or sensor module
* Version: 21.0.0.0
* Date:	04/2021
*============================================================================*/


#include <iostream>
#include "fgt_SDK_Cpp.h"			// include wrapper to fgt_SDK dll, functions can also be accessed by loading the dll

int main()
{

	// Variables declaration
	fgt_CHANNEL_INFO pressure_info[256];		// Structure containing generic channel information
	fgt_CHANNEL_INFO sensor_info[256];
	fgt_CHANNEL_INFO Ttl_info[256];
	fgt_CHANNEL_INFO valve_info[256];
	fgt_CONTROLLER_INFO controller_info[256];
	fgt_INSTRUMENT_TYPE instrument_type[256];	// Enumeration of all types of supported instruments
	fgt_SENSOR_TYPE sensor_type[256];			// Enumeration of all types of supported sensors
	fgt_VALVE_TYPE valve_type[256];			// Enumeration of all types of supported valves
	unsigned short SN[256];

	unsigned char controller_number = 0;		// Returned value of channel number
	unsigned char pressure_number = 0;
	unsigned char sensor_number = 0;
	unsigned char ttl_number = 0;
	unsigned char valve_number = 0;


	// Get total number , SN and type of detected Fluigent instrument controller
	controller_number = Fgt_detect(SN, instrument_type);
	while (SN[controller_number]) controller_number++;
	std::cout << "Total number of controller(s): " << int(controller_number) << std::endl;

	// List all found controllers' serial number and type
	for (unsigned char loop = 0; loop < controller_number; loop++)
	{
		std::cout << "Detected instrument at index: " << int(loop) << ", ControllerSN: " << SN[loop] << ", type: " << instrument_type[loop] << std::endl;
	}

	Fgt_initEx(SN);				// Initialize only specific instrument controllers here
								// If you do not want a controller in the list or if you want a specific order (e.g. LineUP before MFCS instruments),
								//	rearrange parsed SN table

	// Get total number of initialized pressure channel(s)
	Fgt_get_pressureChannelCount(&pressure_number);
	std::cout << "Total number of pressure channels: " << int(pressure_number) << std::endl;

	// Get total number of initialized sensor channel(s)
	Fgt_get_sensorChannelCount(&sensor_number);
	std::cout << "Total number of sensor channels: " << int(sensor_number) << std::endl;

	// Get total number of initialized TTL channel(s)
	Fgt_get_TtlChannelCount(&ttl_number);
	std::cout << "Total number of TTL channels: " << int(ttl_number) << std::endl;

	// Get total number of initialized valve channel(s)
	Fgt_get_valveChannelCount(&valve_number);
	std::cout << "Total number of valve channels: " << int(valve_number) << std::endl << std::endl;

	// Get detailed information about all controller(s)
	Fgt_get_controllersInfo(controller_info);
	for (unsigned char loop = 0; loop < controller_number; loop++)
	{
		std::cout << "Controller info at index: " << int(loop) << "\n"
			<< controller_info[loop] << "\n\n";
	}

	// Get detailed information about all pressure channels
	Fgt_get_pressureChannelsInfo(pressure_info);
	for (unsigned char loop = 0; loop < pressure_number; loop++)
	{
		std::cout << "Pressure channel info at index: " << int(loop) << "\n" 
			<< pressure_info[loop] << "\n\n";
	}

	// Get detailed information about all sensor channels
	Fgt_get_sensorChannelsInfo(sensor_info, sensor_type);
	for (unsigned char loop = 0; loop < sensor_number; loop++)
	{
		std::cout << "Sensor channel info at index: " << int(loop) << "\n"
			<< sensor_info[loop] << "\n"
			<< "Sensor type: " << sensor_type[loop] << "\n\n";
	}

	// Get detailed information about all TTL channels
	Fgt_get_TtlChannelsInfo(Ttl_info);
	for (unsigned char loop = 0; loop < ttl_number; loop++)
	{
		std::cout << "TTL channel info at index: " << int(loop) << "\n"
			<< Ttl_info[loop] << "\n\n";
	}

	// Get detailed information about all valve channels
	Fgt_get_valveChannelsInfo(valve_info, valve_type);
	for (unsigned char loop = 0; loop < valve_number; loop++)
	{
		std::cout << "Valve channel info at index: " << int(loop) << "\n"
			<< valve_info[loop] << "\n"
			<< "Valve type: " << valve_type[loop] << "\n\n";
	}

	// Close session
	Fgt_close();

}


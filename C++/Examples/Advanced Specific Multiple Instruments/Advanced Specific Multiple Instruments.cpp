/*============================================================================
*               Fluigent Software Developement Kit for C++
*----------------------------------------------------------------------------
*         Copyright (c) Fluigent 2021.  All Rights Reserved.
*----------------------------------------------------------------------------
*
* Title:   Advanced Specific Multiple Instruments.cpp
* Purpose: This example shows how to use specific channels ID and multiple
*			connected instruments
*
* Software: fgt_SDK is the library managing all Fluigent instruments
*			"fgt_SDK_Cpp.h" is the wrapper to fgt_SDK dll
* Hardware setup: At least two Fluigent pressure modules
* Version: 21.0.0.0
* Date:	04/2021
*============================================================================*/


#include <iostream>
#include "fgt_SDK_Cpp.h"			// include wrapper to fgt_SDK dll, functions can also be accessed by loading the dll

int main()
{

	// Variables declaration
	fgt_CHANNEL_INFO pressure_info[256];		// Structure containing generic channel information
	fgt_CONTROLLER_INFO controller_info[256];
	fgt_INSTRUMENT_TYPE instrument_type[256];	// Enumeration of all types of supported instruments
	
	unsigned short SN[256];

	unsigned char controller_number = 0;		// Returned value of channel number
	unsigned char pressure_number = 0;
	float pressure;

	// Get total number , SN and type of detected Fluigent instrument controller
	controller_number = Fgt_detect(SN, instrument_type);
	std::cout << "Total number of controller(s): " << int(controller_number) << std::endl;

	// List all found controllers serial number and type
	for (unsigned char loop = 0; loop < controller_number; loop++)
	{
		std::cout << "Detected instrument at index: " << int(loop) << ", ControllerSN: " << SN[loop] << ", type: " << instrument_type[loop] << std::endl;
	}

	Fgt_initEx(SN);				// Initialize only specific instrument controllers here
								// If you do not want a controller in the list or if you want a specific order (e.g. LineUP before MFCS instruments)
								//	rearrange parsed SN table
	// Function Fgt_initEx can be called again, without the need of calling Fgt_close() before. 

	// Get total number of initialized pressure channel(s)
	Fgt_get_pressureChannelCount(&pressure_number);
	std::cout << "Total number of pressure channels: " << int(pressure_number) << std::endl;

	// Get detailed information about all controller(s)
	Fgt_get_controllersInfo(controller_info);
	for (unsigned char loop = 0; loop < controller_number; loop++)
	{
		std::cout << "Controller info at index: " << int(loop) << " SN: " << controller_info[loop].SN
			<< " Firmware: " << controller_info[loop].Firmware << " ID: " << controller_info[loop].id
			<< " type: " << controller_info[loop].InstrType << std::endl;
	}

	// Get detailed information about all pressure channels
	Fgt_get_pressureChannelsInfo(pressure_info);
	for (unsigned char loop = 0; loop < pressure_number; loop++)
	{
		std::cout << "Pressure channel info at index: " << int(loop) << " ,Controller SN: " << pressure_info[loop].ControllerSN
			<< " DeviceSN: " << pressure_info[loop].DeviceSN << " firmware: " << pressure_info[loop].firmware
			<< " position: " << pressure_info[loop].position << " index: " << pressure_info[loop].index
			<< " ID: " << pressure_info[loop].indexID << " InstrType: " << pressure_info[loop].InstrType << std::endl;
	}

	/** If you want to address a specific channel, unique ID can be used. However if hardware changed channel may not be found */

	// Read pressure
	Fgt_get_pressure(pressure_info[0].indexID, &pressure);
	std::cout << "Read pressure from ID " << pressure_info[0].indexID << ": " << pressure << std::endl;
	Fgt_get_pressure(pressure_info[1].indexID, &pressure);
	std::cout << "Read pressure from ID " << pressure_info[1].indexID << ": " << pressure << std::endl;

	Fgt_close();								// Close session

}


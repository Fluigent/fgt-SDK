/*============================================================================
*               Fluigent Software Developement Kit for C++
*----------------------------------------------------------------------------
*         Copyright (c) Fluigent 2019.  All Rights Reserved.
*----------------------------------------------------------------------------
*
* Title:   Basic Get Instruments Info.cpp
* Purpose: This example shows how to retrieve information about Fluigent 
*			instruments: type, controller, serial number, unique ID...
*
* Software: fgt_SDK_*.dll is the dynamic linked library managing all Fluigent
*			 instruments (pressure and sensors)
*			"fgt_SDK_Cpp.h" is the wrapper to fgt_SDK dll
* Hardware setup: At least one Fluigent pressure or sensor module
* Version: 19.0.0.0
* Date:	06/2019
*============================================================================*/


#include <iostream>
#include "../fgt_SDK_Cpp.h"			// include wrapper to fgt_SDK dll, functions can also be accessed by loading the dll

int main()
{

	// Variables declaration
	fgt_CHANNEL_INFO pressure_info[256];		// Structure containing generic channel information
	fgt_CHANNEL_INFO sensor_info[256];
	fgt_CHANNEL_INFO Ttl_info[256];
	fgt_CONTROLLER_INFO controller_info[256];
	fgt_INSTRUMENT_TYPE instrument_type[256];	// Enumeration of all types of supported instruments
	fgt_SENSOR_TYPE sensor_type[256];			// Enumeration of all types of supported sensors
	unsigned short SN[256];

	unsigned char controller_number = 0;		// Returned value of channel number
	unsigned char pressure_number = 0;
	unsigned char sensor_number = 0;
	unsigned char ttl_number = 0;


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

	// Get total number of initialized pressure channel(s)
	Fgt_get_pressureChannelCount(&pressure_number);
	std::cout << "Total number of pressure channels: " << int(pressure_number) << std::endl;

	// Get total number of initialized pressure channel(s)
	Fgt_get_sensorChannelCount(&sensor_number);
	std::cout << "Total number of sensor channels: " << int(sensor_number) << std::endl;

	// Get total number of initialized TTL channel(s)
	Fgt_get_TtlChannelCount(&ttl_number);
	std::cout << "Total number of TTL channels: " << int(ttl_number) << std::endl << std::endl;


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

	// Get detailed information about all sensor channels
	Fgt_get_sensorChannelsInfo(sensor_info, sensor_type);
	for (unsigned char loop = 0; loop < sensor_number; loop++)
	{
		std::cout << "Sensor channel info at index: " << int(loop) << " ,ControllerSN: " << sensor_info[loop].ControllerSN
			<< " DeviceSN: " << sensor_info[loop].DeviceSN << " firmware: " << sensor_info[loop].firmware
			<< " position: " << sensor_info[loop].position << " index: " << sensor_info[loop].index
			<< " ID: " << sensor_info[loop].indexID << " InstrType: " << sensor_info[loop].InstrType << " sensor SensorType: " << sensor_type[loop] << std::endl;
	}

	// Get detailed information about all ttl channels
	Fgt_get_TtlChannelsInfo(Ttl_info);
	for (unsigned char loop = 0; loop < ttl_number; loop++)
	{
		std::cout << "TTL channel info at index: " << int(loop) << " ControllerSN: " << Ttl_info[loop].ControllerSN
			<< " DeviceSN: " << Ttl_info[loop].DeviceSN << " firmware: " << Ttl_info[loop].firmware
			<< " position: " << Ttl_info[loop].position << " index: " << Ttl_info[loop].index
			<< " ID: " << Ttl_info[loop].indexID << " InstrType: " << Ttl_info[loop].InstrType << std::endl;
	}

	Fgt_close();								// Close session

	system("PAUSE");
}


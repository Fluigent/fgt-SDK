/*============================================================================
*               Fluigent Software Developement Kit for C++                  
*----------------------------------------------------------------------------
*         Copyright (c) Fluigent 2022.  All Rights Reserved.                 
*----------------------------------------------------------------------------
*                                                                            
* Title:    fgt_SDK_Cpp.cpp                                                  
* Purpose:  Wrapper to fgt_SDK library			                          
*			Contains an interface to each dll function and type conversions	  
* Version:  22.2.0.0                                                         
* Date:	    11/2022															 
*============================================================================*/

#include <iostream>
#include <cstdio>
#include "fgt_SDK_Cpp.h"

/*============================================================================*/
/*-------------  Custom definitions and functions section  -------------------*/
/*============================================================================*/


/** Overload << operator for more intuitive enum display */
/** fgt_ERROR_CODE: enumerator of all returned codes */
std::ostream& operator<<(std::ostream& str, fgt_ERROR_CODE errCode)
{
	switch (errCode)
	{
	case fgt_ERROR_CODE::OK: str << "OK";    break;
	case fgt_ERROR_CODE::USB_error: str << "USB_error"; break;
	case fgt_ERROR_CODE::Wrong_command: str << "Wrong_command"; break;
	case fgt_ERROR_CODE::No_module_at_index: str << "No_module_at_index"; break;
	case fgt_ERROR_CODE::Wrong_module: str << "Wrong_module"; break;
	case fgt_ERROR_CODE::Module_is_sleep: str << "Module_is_sleep"; break;
	case fgt_ERROR_CODE::Master_error: str << "Master_error"; break;
	case fgt_ERROR_CODE::Failed_init_all_instr: str << "Failed_init_all_instr"; break;
	case fgt_ERROR_CODE::Wrong_parameter: str << "Wrong_parameter"; break;
	case fgt_ERROR_CODE::Overpressure: str << "Overpressure"; break;
	case fgt_ERROR_CODE::Underpressure: str << "Underpressure"; break;
	case fgt_ERROR_CODE::No_instr_found: str << "No_instr_found"; break;
	case fgt_ERROR_CODE::No_modules_found: str << "No_modules_found"; break;
	case fgt_ERROR_CODE::No_pressure_controller_found: str << "No_pressure_controller_found"; break;
	case fgt_ERROR_CODE::Calibrating: str << "Calibrating"; break;
	case fgt_ERROR_CODE::Dll_dependency_error: str << "Dll_dependency_error"; break;
	case fgt_ERROR_CODE::Processing: str << "Processing"; break;
	default: str << "Unknown error code (" << int(errCode) << ")";
	}
	return str;
}

/** fgt_INSTRUMENT_TYPE: Fluigent instrument type */
std::ostream& operator<<(std::ostream& str, fgt_INSTRUMENT_TYPE instrType)
{
	switch (instrType)
	{
	case fgt_INSTRUMENT_TYPE::None: str << "None";    break;
	case fgt_INSTRUMENT_TYPE::MFCS: str << "MFCS"; break;
	case fgt_INSTRUMENT_TYPE::MFCS_EZ: str << "MFCS_EZ"; break;
	case fgt_INSTRUMENT_TYPE::FRP: str << "FRP"; break;
	case fgt_INSTRUMENT_TYPE::LineUP: str << "LineUP"; break;
	case fgt_INSTRUMENT_TYPE::IPS: str << "IPS"; break;
	case fgt_INSTRUMENT_TYPE::ESS: str << "ESS"; break;
    case fgt_INSTRUMENT_TYPE::F_OEM: str << "F_OEM"; break;
    case fgt_INSTRUMENT_TYPE::CFU: str << "CFU"; break;
	case fgt_INSTRUMENT_TYPE::NIFS: str << "NIFS"; break;
	default: str << "Unknown instrument type (" << int(instrType) << ")";
	}
	return str;
}

/** fgt_SENSOR_TYPE: type of te sensor */
std::ostream& operator<<(std::ostream& str, fgt_SENSOR_TYPE sensorType)
{
	switch (sensorType)
	{
	case fgt_SENSOR_TYPE::None: str << "None";    break;
	case fgt_SENSOR_TYPE::Flow_XS_single: str << "Flow_XS_single"; break;
	case fgt_SENSOR_TYPE::Flow_S_single: str << "Flow_S_single"; break;
	case fgt_SENSOR_TYPE::Flow_S_dual: str << "Flow_S_dual"; break;
	case fgt_SENSOR_TYPE::Flow_M_single: str << "Flow_M_single"; break;
	case fgt_SENSOR_TYPE::Flow_M_dual: str << "Flow_M_dual"; break;
	case fgt_SENSOR_TYPE::Flow_L_single: str << "Flow_L_single"; break;
	case fgt_SENSOR_TYPE::Flow_L_dual: str << "Flow_L_dual"; break;
	case fgt_SENSOR_TYPE::Flow_XL_single: str << "Flow_XL_single"; break;
	case fgt_SENSOR_TYPE::Pressure_S: str << "Pressure_S"; break;
	case fgt_SENSOR_TYPE::Pressure_M: str << "Pressure_M"; break;
	case fgt_SENSOR_TYPE::Pressure_XL: str << "Pressure_XL"; break;
	case fgt_SENSOR_TYPE::Flow_M_plus_dual: str << "Flow_M_plus_dual"; break;
	case fgt_SENSOR_TYPE::Flow_L_plus_dual: str << "Flow_L_plus_dual"; break;
	case fgt_SENSOR_TYPE::Flow_L_CFU: str << "Flow_L_CFU"; break;
	case fgt_SENSOR_TYPE::Flow_L_NIFS: str << "Flow_L_NIFS"; break;
	default: str << "Unknown sensor type (" << int(sensorType) << ")";
	}
	return str;
}

/** fgt_SENSOR_CALIBRATION: calibration table of sensors */
std::ostream& operator<<(std::ostream& str, fgt_SENSOR_CALIBRATION calibration)
{
	switch (calibration)
	{
	case fgt_SENSOR_CALIBRATION::None: str << "None";    break;
	case fgt_SENSOR_CALIBRATION::H2O: str << "H2O"; break;
	case fgt_SENSOR_CALIBRATION::IPA: str << "IPA"; break;
	case fgt_SENSOR_CALIBRATION::HFE: str << "HFE"; break;
	case fgt_SENSOR_CALIBRATION::FC40: str << "FC40"; break;
	case fgt_SENSOR_CALIBRATION::OIL: str << "OIL"; break;
	default: str << "Unknown sensor calibration (" << int(calibration) << ")";
	}
	return str;
}

/** fgt_POWER: power state of device */
std::ostream& operator<<(std::ostream& str, fgt_POWER powerState)
{
	switch (powerState)
	{
	case fgt_POWER::POWER_OFF: str << "POWER_OFF";    break;
	case fgt_POWER::POWER_ON: str << "POWER_ON"; break;
	case fgt_POWER::SLEEP: str << "SLEEP"; break;
	default: str << "Unknown power state (" << int(powerState) << ")";
	}
	return str;
}

/** fgt_TTL_MODE: TTL behaviour setting on BNC port */
std::ostream& operator<<(std::ostream& str, fgt_TTL_MODE TtlMode)
{
	switch (TtlMode)
	{
	case fgt_TTL_MODE::DETECT_RISING_EDGE: str << "DETECT_RISING_EDGE";    break;
	case fgt_TTL_MODE::DETECT_FALLING_EDGE: str << "DETECT_FALLING_EDGE"; break;
	case fgt_TTL_MODE::OUTPUT_PULSE_LOW: str << "OUTPUT_PULSE_LOW"; break;
	case fgt_TTL_MODE::OUTPUT_PULSE_HIGH: str << "OUTPUT_PULSE_HIGH"; break;
	default: str << "Unknown ttl mode (" << int(TtlMode) << ")";
	}
	return str;
}

/** fgt_VALVE_TYPE: type of valve */
std::ostream& operator<<(std::ostream& str, fgt_VALVE_TYPE valveType)
{
	switch (valveType)
	{
	case fgt_VALVE_TYPE::None: str << "None";    break;
	case fgt_VALVE_TYPE::MSwitch: str << "MSwitch"; break;
	case fgt_VALVE_TYPE::TwoSwitch: str << "TwoSwitch"; break;
	case fgt_VALVE_TYPE::LSwitch: str << "LSwitch"; break;
	case fgt_VALVE_TYPE::PSwitch: str << "PSwitch"; break;
	case fgt_VALVE_TYPE::M_X: str << "M_X"; break;
	case fgt_VALVE_TYPE::Two_X: str << "Two_X"; break;
	case fgt_VALVE_TYPE::L_X: str << "L_X"; break;
    case fgt_VALVE_TYPE::Bypass: str << "Bypass"; break;
	default: str << "Unknown valve type (" << int(valveType) << ")";
	}
	return str;
}

/** fgt_SWITCH_DIRECTION: switch direction for rotating switches */
std::ostream& operator<<(std::ostream& str, fgt_SWITCH_DIRECTION direction)
{
	switch (direction)
	{
	case fgt_SWITCH_DIRECTION::Shortest: str << "Shortest";    break;
	case fgt_SWITCH_DIRECTION::Anticlockwise: str << "Anticlockwise"; break;
	case fgt_SWITCH_DIRECTION::Clockwise: str << "Clockwise"; break;
	default: str << "Unknown switch direction (" << int(direction) << ")";
	}
	return str;
}

std::string format_firmware_version(unsigned short bcd_version)
{
	char buf[10]{};
	std::snprintf(buf, 10, "%x.%02x", bcd_version >> 8, bcd_version & 0xff);
	return std::string(buf);
}

std::ostream& operator<<(std::ostream& str, const fgt_CONTROLLER_INFO& info)
{
	str << "SN: " << info.SN << "\n"
		<< "Firmware: " << format_firmware_version(info.Firmware) << "\n"
		<< "Unique ID: " << info.id << "\n"
		<< "Type: " << info.InstrType;
	return str;
}

std::ostream& operator<<(std::ostream& str, const fgt_CHANNEL_INFO& info)
{
	str << "Controller SN: " << info.ControllerSN << "\n"
		<< "Device SN: " << info.DeviceSN << "\n"
		<< "Firmware: " << format_firmware_version(info.firmware) << "\n"
		<< "Position: " << info.position << "\n"
		<< "Unique ID: " << info.indexID << "\n"
		<< "Type: " << info.InstrType;
	return str;
}

fgt_ERROR_REPORT_MODE error_report_mode = fgt_ERROR_REPORT_MODE::Print;

/** Manage pressure error and status, display details 
 *  Change this function for custom error management, returned fgt_ERROR_CODE can directly be used in main application
 *  This functions calls Fgt_get_pressureStatus and displays error details */
void Fgt_Manage_Pressure_Status(unsigned int pressureIndex, std::string calledFunctionName)
{
	if (error_report_mode == fgt_ERROR_REPORT_MODE::None) return;
	fgt_INSTRUMENT_TYPE type;
	unsigned short controllerSN;
	unsigned char information;
	std::string detail;
	std::string info;

	fgt_ERROR_CODE error = Fgt_get_pressureStatus(pressureIndex, &type, &controllerSN, &information, &detail);

	if (information == 0) info = "info: remote control";
	if (information == 1) info = "info: local control";

	if(error != fgt_ERROR_CODE::OK)
	{
		std::cout << calledFunctionName << " pressure channel " << pressureIndex << " of type " << type << " error " << int(error) << ": " << error << " - " << detail << ", Controller SN: " << controllerSN <<
			", " << info << std::endl;
	}
}

/** Manage sensor error and status, display details
 *  Change this function for custom error management, returned fgt_ERROR_CODE can directly be used in main application
 *  This functions calls Fgt_get_sensorStatus and displays error details */
void Fgt_Manage_Sensor_Status(unsigned int sensorIndex, std::string calledFunctionName)
{
	if (error_report_mode == fgt_ERROR_REPORT_MODE::None) return;
	fgt_INSTRUMENT_TYPE type;
	unsigned short controllerSN;
	unsigned char information;
	std::string detail;
	std::string info;

	fgt_ERROR_CODE error = Fgt_get_sensorStatus(sensorIndex, &type, &controllerSN, &information, &detail);

	if (error != fgt_ERROR_CODE::OK)
	{
		std::cout << calledFunctionName << " sensor channel " << sensorIndex << " of type " << type << " error " << int(error) << ": " << error << " - " << detail << ", Controller SN: " << controllerSN <<
			", info: " << int(information) << std::endl;
	}
}

/** Manage generic functions error and status, display details
 *  Change this function for custom error management, returned fgt_ERROR_CODE can directly be used in main application */
void Fgt_Manage_Generic_Status(fgt_ERROR_CODE error, std::string calledFunctionName)
{
	if (error_report_mode == fgt_ERROR_REPORT_MODE::None) return;
	// If error display it
	if (error != fgt_ERROR_CODE::OK) std::cout << calledFunctionName << " error " << int(error) << " - " << error << std::endl;
}


/*============================================================================*/
/*--------------------------  DLL Wrapper section  ---------------------------*/
/*============================================================================*/

/*============================================================================*/
/*-------------------------------  Init/close  -------------------------------*/
/*============================================================================*/

/**
 * @Description Initialize or reinitialize (if already opened) Fluigent SDK instance. All detected Fluigent instruments are initialized.
 * This function is optional, directly calling a function will automatically creates the instance.
 * Only one instance can be opened at a time. If called again, any new instruments are added to the same instance.
 * @param void
 * @return fgt_ERROR_CODE
 * @see fgt_close
 * @see fgt_initEx
 */
fgt_ERROR_CODE Fgt_init(void)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_init());					// Call function
	Fgt_Manage_Generic_Status(returnCode, "Fgt_init");			// Manage function return code, change this function for custom behaviour
	return returnCode;
}

/**
 * @Description Close communication with Fluigent instruments and free memory.
 * This function is mandatory, if not called the dll will be automatically closed when exiting your application.
 * Using this function will remove session preferences such as units and limits. If any regulation is running it will stop pressure control.
 */
fgt_ERROR_CODE Fgt_close(void)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_close());
	Fgt_Manage_Generic_Status(returnCode, "Fgt_close");
	return returnCode;
}

/**
 * @Description Detects all connected Fluigent instrument(s), return their serial number and type
 * @param [SN]: Array of controllers serial number. This is a 256 pre-allocated table tailed with 0's when no instrument
 * @param [InstrType] : fgt_INSTRUMENT_TYPE. This is a 256 pre-allocated table tailed with 'None' value when no instrument
 * @return total number of detected instruments
 * @see fgt_initEx for specific initialization
 */
unsigned char Fgt_detect(unsigned short SN[256], fgt_INSTRUMENT_TYPE type[256])
{
	int localType[256] = {0};
	unsigned int localLoop = 0;
	unsigned char returnCode;

	//initialize array before
	for (localLoop = 0; localLoop < 256; localLoop++)	localType[localLoop] = 0;
	for (localLoop = 0; localLoop < 256; localLoop++) SN[localLoop] = 0;

	returnCode = fgt_detect(SN, localType);
	for(unsigned char loop = 0; loop < 255; loop++) type[loop] = fgt_INSTRUMENT_TYPE(localType[loop]);		// Convert type from dll int to C++ enum fgt_INSTRUMENT_TYPE
	return returnCode;
}

/**
 * @Description Initialize specific Fluigent instrument(s) from their unique serial number. This function can be used when multiple instruments are connected in order to select your device(s)
 * @param [SN] Array of controllers serial number
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_initEx(unsigned short SN[256])
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_initEx(SN));
	Fgt_Manage_Generic_Status(returnCode, "Fgt_initEx");
	return returnCode;
}

fgt_ERROR_CODE Fgt_create_simulated_instr(fgt_instrument_t type, unsigned short serial, unsigned short version, int* config, int length)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_create_simulated_instr(type, serial, version, config, length));
	Fgt_Manage_Generic_Status(returnCode, __func__);
	return returnCode;
}

fgt_ERROR_CODE Fgt_remove_simulated_instr(fgt_instrument_t type, unsigned short serial)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_remove_simulated_instr(type, serial));
	Fgt_Manage_Generic_Status(returnCode, __func__);
	return returnCode;
}

/*============================================================================*/
/*------------------------------  Channels info  -----------------------------*/
/*============================================================================*/

/**
 * @Description Retrieve information about session Fluigent controller devices.
 * @param [info] Array of structure of fgt_CONTROLLER_INFO
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_get_controllersInfo(fgt_CONTROLLER_INFO info[256])
{
	unsigned int localLoop = 0;

	//initialize array before
	for (localLoop = 0; localLoop < 256; localLoop++) {
		info[localLoop].Firmware = 0;
		info[localLoop].id = 0;
		info[localLoop].InstrType = fgt_INSTRUMENT_TYPE::None;
		info[localLoop].SN = 0;
	}

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_get_controllersInfo(info));
	Fgt_Manage_Generic_Status(returnCode, "Fgt_get_controllersInfo");
	return returnCode;
}

/**
 * @Description Get total number of initialized pressure channels. It is the sum of all MFCS, MFCS-EZ and FlowEZ pressure controllers
 * @param *nbPChan Total number of initialized pressure channels
 * @see fgt_get_pressureChannelsInfo array size is equal to nbPChan
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_get_pressureChannelCount(unsigned char* nbPChan)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_get_pressureChannelCount(nbPChan));
	Fgt_Manage_Generic_Status(returnCode, "Fgt_get_pressureChannelCount");
	return returnCode;
}

/**
 * @Description Get total number of initialized sensor channels. It is the sum of all connected flow-units on Flowboard and FlowEZ
 * @param *nbQChan Total number of initialized sensor channels
 * @return fgt_ERROR_CODE
 * @see fgt_get_sensorChannelsInfo array size is equal to nbSChan
 */
fgt_ERROR_CODE Fgt_get_sensorChannelCount(unsigned char* nbSChan)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_get_sensorChannelCount(nbSChan));
	Fgt_Manage_Generic_Status(returnCode, "Fgt_get_sensorChannelCount");
	return returnCode;
}


/**
 * @Description Get total number of initialized TTL channels. It is the sum of all connected Link TTL ports
 * @param *nbTtlChan Total number of initialized TTL channels
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_get_TtlChannelCount(unsigned char* nbTtlChan)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_get_TtlChannelCount(nbTtlChan));
	Fgt_Manage_Generic_Status(returnCode, "Fgt_get_TtlChannelCount");
	return returnCode;
}

/**
 * @Description Get total number of initialized valve channels
 * @param *nbvalveChan Total number of initialized valve channels
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_get_valveChannelCount(unsigned char* nbvalveChan)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_get_valveChannelCount(nbvalveChan));
	Fgt_Manage_Generic_Status(returnCode, "fgt_get_valveChannelCount");
	return returnCode;
}

/**
 * @Description: Retrieve information about each initialized pressure channel. This function is useful in order to get channels order, controller, unique ID and instrument type.
 * By default this array is built with MFCS first, MFCS-EZ second and FlowEZ last. If only one instrument is used, index is the default channel indexing starting at 0.
 * You can initialize instruments in specific order using fgt_initEx function
 * @param info Array of structure of fgt_CHANNEL_INFO
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_get_pressureChannelsInfo(fgt_CHANNEL_INFO info[256])
{
	unsigned int localLoop = 0;

	//initialize array before
	for (localLoop = 0; localLoop < 256; localLoop++) {
		info[localLoop].ControllerSN = 0;
		info[localLoop].DeviceSN = 0;
		info[localLoop].InstrType = fgt_INSTRUMENT_TYPE::None;
		info[localLoop].firmware = 0;
		info[localLoop].index = 0;
		info[localLoop].indexID = 0;
		info[localLoop].position = 0;
	}

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_get_pressureChannelsInfo(info));
	Fgt_Manage_Generic_Status(returnCode, "Fgt_get_pressureChannelsInfo");
	return returnCode;
}

/**
 * @Description: Retrieve information about each initialized sensor channel. This function is useful in order to get channels order, controller, unique ID and instrument type.
 * By default this array is built with FRP first then FlowEZ and contains flow-units. If only one instrument is used, index is the default channel indexing starting at 0.
 * You can initialize instruments in specific order using fgt_initEx function
 * @param info Array of structure of fgt_CHANNEL_INFO
 * @param sensorType Array of fgt_SENSOR_TYPE
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_get_sensorChannelsInfo(fgt_CHANNEL_INFO info[256], fgt_SENSOR_TYPE sensorType[256])
{
	unsigned int localLoop = 0;
	fgt_SENSOR_TYPE localSensorType[256]{};

	//initialize array before
	for (localLoop = 0; localLoop < 256; localLoop++) {
		info[localLoop].ControllerSN = 0;
		info[localLoop].DeviceSN = 0;
		info[localLoop].InstrType = fgt_INSTRUMENT_TYPE::None;
		info[localLoop].firmware = 0;
		info[localLoop].index = 0;
		info[localLoop].indexID = 0;
		info[localLoop].position = 0;
		sensorType[localLoop] = fgt_SENSOR_TYPE::None;
	}

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_get_sensorChannelsInfo(info, localSensorType));
	for (unsigned char loop = 0; loop < 255; loop++) sensorType[loop] = fgt_SENSOR_TYPE(localSensorType[loop]);
	Fgt_Manage_Generic_Status(returnCode, "Fgt_get_sensorChannelsInfo");
	return returnCode;
}

/**
 * @Description: Retrieve information about each initialized TTL channel. This function is useful in order to get channels order, controller, unique ID and instrument type.
 * TTL channels are only available for LineUP Series, 2 ports for each connected Link
 * @param info Array of structure of fgt_CHANNEL_INFO
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_get_TtlChannelsInfo(fgt_CHANNEL_INFO info[256])
{
	unsigned int localLoop = 0;

	//initialize array before
	for (localLoop = 0; localLoop < 256; localLoop++) {
		info[localLoop].ControllerSN = 0;
		info[localLoop].DeviceSN = 0;
		info[localLoop].InstrType = fgt_INSTRUMENT_TYPE::None;
		info[localLoop].firmware = 0;
		info[localLoop].index = 0;
		info[localLoop].indexID = 0;
		info[localLoop].position = 0;
	}

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_get_TtlChannelsInfo(info));
	Fgt_Manage_Generic_Status(returnCode, "Fgt_get_TtlChannelsInfo");
	return returnCode;
}

fgt_ERROR_CODE Fgt_get_valveChannelsInfo(fgt_CHANNEL_INFO info[256], fgt_VALVE_TYPE valveType[256])
{
	unsigned int localLoop = 0;
	fgt_VALVE_TYPE localValveType[256]{};
	//initialize array before
	for (localLoop = 0; localLoop < 256; localLoop++) {
		info[localLoop].ControllerSN = 0;
		info[localLoop].DeviceSN = 0;
		info[localLoop].InstrType = fgt_INSTRUMENT_TYPE::None;
		info[localLoop].firmware = 0;
		info[localLoop].index = 0;
		info[localLoop].indexID = 0;
		info[localLoop].position = 0;
		valveType[localLoop] = fgt_VALVE_TYPE::None;
	}

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_get_valveChannelsInfo(info, localValveType));
	for (unsigned char loop = 0; loop < 255; loop++) valveType[loop] = fgt_VALVE_TYPE(localValveType[loop]);
	Fgt_Manage_Generic_Status(returnCode, "fgt_get_valveChannelsInfo");
	return returnCode;
}



/*============================================================================*/
/*-----------------------------  Basic functions  ----------------------------*/
/*============================================================================*/

/**
 * @Description Send pressure command to selected device
 * @param pressureIndex Index of pressure channel or unique ID
 * @param pressure Pressure order in selected unit, default is "mbar"
 * @return errorCode
 * @see fgt_set_sensorRegulation
 * @see fgt_get_pressureStatus
 */
fgt_ERROR_CODE Fgt_set_pressure(unsigned int pressureIndex, float pressure)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_set_pressure(pressureIndex, pressure));
	Fgt_Manage_Pressure_Status(pressureIndex, "Fgt_set_pressure");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Read pressure value of selected device
 * @param pressureIndex Index of pressure channel or unique ID
 * @param *pressure Read pressure value in selected unit, default is "mbar"
 * @return errorCode
 * @see fgt_get_pressureEx
 * @see fgt_get_pressureStatus
 */
fgt_ERROR_CODE Fgt_get_pressure(unsigned int pressureIndex, float* pressure)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_get_pressure(pressureIndex, pressure));
	Fgt_Manage_Pressure_Status(pressureIndex, "Fgt_get_pressure");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Read pressure value and time stamp of selected device. Time stamp is the device internal timer.
 * @param pressureIndex Index of pressure channel or unique ID
 * @param *pressure Read pressure value in selected unit, default is "mbar"
 * @param *timeStamp Hardware timer in ms
 * @return fgt_ERROR_CODE
 * @see fgt_get_pressure
 * @see fgt_get_pressureStatus
 */
fgt_ERROR_CODE Fgt_get_pressureEx(unsigned int pressureIndex, float* pressure, unsigned short* timeStamp)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_get_pressureEx(pressureIndex, pressure, timeStamp));
	Fgt_Manage_Pressure_Status(pressureIndex, "Fgt_get_pressureEx");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Start closed loop regulation between a sensor and a pressure controller. Pressure will be regulated in order to reach sensor setpoint.
 * Call again this function in order to change the setpoint. Calling fgt_set_pressure on same pressureIndex will stop regulation.
 * @param sensorIndex Index of sensor channel or unique ID
 * @param pressureIndex Index of pressure channel or unique ID
 * @param setpoint Regulation value to be reached in selected unit, default is "�l/min" for flowrate sensors
 * @return fgt_ERROR_CODE
 * @see fgt_set_pressure
 * @see fgt_set_customSensorRegulation
 * @see fgt_set_sensorRegulationResponse
 */
fgt_ERROR_CODE Fgt_set_sensorRegulation(unsigned int sensorIndex, unsigned int pressureIndex, float setpoint)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_set_sensorRegulation(sensorIndex, pressureIndex, setpoint));
	Fgt_Manage_Sensor_Status(sensorIndex, "Fgt_set_sensorRegulation");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Read sensor value of selected device
 * @param sensorIndex Index of sensor channel or unique ID
 * @param *value Read sensor value in selected unit, default is "�l/min" for flowrate sensors
 * @return fgt_ERROR_CODE
 * @see fgt_get_sensorStatus
 */
fgt_ERROR_CODE Fgt_get_sensorValue(unsigned int sensorIndex, float* value)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_get_sensorValue(sensorIndex, value));
	Fgt_Manage_Sensor_Status(sensorIndex, "Fgt_get_sensorValue");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Read sensor value and timestamp of selected device. Time stamp is the device internal timer.
 * @param sensorIndex Index of sensor channel or unique ID
 * @param *value Read sensor value in selected unit, default is "�l/min" for flowrate sensors
 * @param *timeStamp Hardware timer in ms
 * @return fgt_ERROR_CODE
 * @see fgt_get_sensorStatus
 */
fgt_ERROR_CODE Fgt_get_sensorValueEx(unsigned int sensorIndex, float* value, unsigned short* timeStamp)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_get_sensorValueEx(sensorIndex, value, timeStamp));
	Fgt_Manage_Sensor_Status(sensorIndex, "Fgt_get_sensorValueEx");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Read the position of a specific valve channel.
 * @param valveIndex Index of valve channel
 * @out position Valve position
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_get_valvePosition(unsigned int valveIndex, int* position)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_get_valvePosition(valveIndex, position));
	Fgt_Manage_Generic_Status(returnCode, "Fgt_get_sensorValue");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Set the position of a specific valve channel.
 * @param valveIndex Index of valve channel
 * @param position Desired valve position
 * @param direction Direction of the movement (applies only for M-Switch valve type)
 * @param wait Flag indicating if function should wait until the desired position is reached or not
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_set_valvePosition(unsigned int valveIndex, int position, fgt_SWITCH_DIRECTION direction, bool wait)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_set_valvePosition(valveIndex, position, direction, wait? 1 : 0));
	Fgt_Manage_Generic_Status(returnCode, "Fgt_set_valvePosition");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Set the position of a all two positional valves connected to specified controller / module.
 * @param controllerIndex Index of the controller (supported only by LineUp and ESS)
 * @param moduleIndex Index of the module (supported only by P-Switch)
 * @param position Desired position (0 or 1)
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_set_allValves(unsigned int controllerIndex, unsigned int moduleIndex, int position)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_set_allValves(controllerIndex, moduleIndex, position));
	Fgt_Manage_Generic_Status(returnCode, "Fgt_set_allValves");											// Manage error if occured
	return returnCode;
}


/*============================================================================*/
/*--------------------   Unit, calibration and limits  -----------------------*/
/*============================================================================*/

/**
 * @Description Set pressure unit for all initialized channels, default value is "mbar". If type is invalid an error is returned.
 * Every pressure read value and sent command will then use this unit.
 * Example: "mbar", "millibar", "kPa" ...
 * @param unit Unit string
 * @return fgt_ERROR_CODE
 * @see fgt_get_pressureStatus
 */
fgt_ERROR_CODE Fgt_set_sessionPressureUnit(std::string unit)
{
	char localUnit[140] = { 0 };
	strcpy(localUnit, unit.c_str());
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_set_sessionPressureUnit(localUnit));
	Fgt_Manage_Pressure_Status(0, "Fgt_set_sessionPressureUnit");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Set pressure unit on selected pressure device, default value is "mbar". If type is invalid an error is returned.
 * Every pressure read value and sent command will then use this unit.
 * Example: "mbar", "millibar", "kPa" ...
 * @param presureIndex Index of pressure channel or unique ID
 * @param unit channel unit string
 * @return fgt_ERROR_CODE
 * @see fgt_get_pressureStatus
 */
fgt_ERROR_CODE Fgt_set_pressureUnit(unsigned int pressureIndex, std::string unit)
{
	char localUnit[140] = { 0 };
	strcpy(localUnit, unit.c_str());

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_set_pressureUnit(pressureIndex, localUnit));
	Fgt_Manage_Pressure_Status(pressureIndex, "Fgt_set_pressureUnit");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Get used unit on selected pressure device, default value is "mbar".
 * Every pressure read value and sent command use this unit.
 * @param pressureIndex Index of pressure channel or unique ID
 * @param unit channel unit string
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_get_pressureUnit(unsigned int pressureIndex, std::string* unit)
{
	char localUnit[140] = { 0 };

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_get_pressureUnit(pressureIndex, localUnit));
	*unit = localUnit;
	Fgt_Manage_Pressure_Status(pressureIndex, "Fgt_get_pressureUnit");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Set sensor unit on selected sensor device, default value is "�l/min" for flowunits. If type is invalid an error is returned.
 * Every sensor read value and regulation command will then use this unit.
 * Example: "�l/h", "ulperDay", "microliter/hour" ...
 * @param sensorIndex Index of sensor channel or unique ID
 * @param unit channel unit string
 * @return fgt_ERROR_CODE
 * @see fgt_set_sensorStatus
 */
fgt_ERROR_CODE Fgt_set_sensorUnit(unsigned int sensorIndex, std::string unit)
{
	char localUnit[140] = {0};
	strcpy(localUnit, unit.c_str());

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_set_sensorUnit(sensorIndex, localUnit));
	Fgt_Manage_Sensor_Status(sensorIndex, "Fgt_set_sensorUnit");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Get used unit on selected sensor device, default value is "�l/min" for flowunits.
 * Every sensor read value and regulation command use this unit.
 * @param sensorIndex Index of sensor channel or unique ID
 * @param unit channel unit string
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_get_sensorUnit(unsigned int sensorIndex, std::string* unit)
{
	char localUnit[140] = { 0 };

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_get_sensorUnit(sensorIndex, localUnit));
	*unit = localUnit;
	Fgt_Manage_Sensor_Status(sensorIndex, "Fgt_get_sensorUnit");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Set used sensor internal calibration table. Function is only available for specific sensors such as the flow-unit M accepting H2O and IPA
 * @param sensorIndex Index of sensor channel or unique ID
 * @param calibration fgt_SENSOR_CALIBRATION
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_set_sensorCalibration(unsigned int sensorIndex, fgt_SENSOR_CALIBRATION calibration)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_set_sensorCalibration(sensorIndex, calibration));
	Fgt_Manage_Sensor_Status(sensorIndex, "Fgt_set_sensorCalibration");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Get internal calibration table used by the sensor.
 * @param sensorIndex Index of sensor channel or unique ID
 * @param *calibration fgt_SENSOR_CALIBRATION
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_get_sensorCalibration(unsigned int sensorIndex, fgt_SENSOR_CALIBRATION* calibration)
{
	fgt_SENSOR_CALIBRATION localCalibration;

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_get_sensorCalibration(sensorIndex, &localCalibration));
	*calibration = fgt_SENSOR_CALIBRATION(localCalibration);
	Fgt_Manage_Sensor_Status(sensorIndex, "Fgt_get_sensorCalibration");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Apply a custom scale factor on sensor read value. This function is useful in order to adapt read sensor value to physical measurement.
 * For example if a flow-unit is used with a special oil and it's calibration table is set to H2O, read flowrate is not correct.
 * Scale factor is applied using following formula: scaled_value = a*sensor_value + b*sensor_value^2 + c*sensor_value^3
 * Note that this scale is also used for the regulation.
 * @param sensorIndex Index of sensor channel or unique ID
 * @param float a proportional multiplier value
 * @param float b square multiplier value
 * @param float c cubic multiplier value
 * @return fgt_ERROR_CODE
 * @see fgt_set_sensorCustomScaleEx
 */
fgt_ERROR_CODE Fgt_set_sensorCustomScale(unsigned int sensorIndex, float a, float b, float c)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_set_sensorCustomScale(sensorIndex, a, b, c));
	Fgt_Manage_Sensor_Status(sensorIndex, "Fgt_set_sensorCustomScale");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Apply a custom scale factor on sensor measurement. This function is useful in order to adapt read sensor value to physical measurement.
 * For example if a flow-unit is used with a special oil and it's calibration table is set to H2O, read flowrate is not correct.
 * Scale factor is applied using following formula: scaled_value = a*sensor_value + b*sensor_value^2 + c*sensor_value^3
 * When applying a custom scale factor, sensor range may increase very rapidly, SMax parameter is meant to limit this maximal value.
 * This function purpose is to be used with the regulation in order to avoid too high maximum range on the sensor.
 * @param sensorIndex Index of sensor channel or unique ID
 * @param float a proportional multiplier value
 * @param float b square multiplier value
 * @param float c cubic multiplier value
 * @param float SMax after scale maximal value (saturation)
 * @return fgt_ERROR_CODE
 * @see fgt_set_sensorCustomScale
 */
fgt_ERROR_CODE Fgt_set_sensorCustomScaleEx(unsigned int sensorIndex, float a, float b, float c, float SMax)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_set_sensorCustomScaleEx(sensorIndex, a, b, c, SMax));
	Fgt_Manage_Sensor_Status(sensorIndex, "Fgt_set_sensorCustomScaleEx");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Calibrate internal pressure sensor depending on atmospheric pressure. After calling this function 0 pressure value corresponds to atmospheric pressure.
 * During calibration step no pressure order is accepted. Total duration vary from 3s to 8s.
 * @param pressureIndex Index of pressure channel or unique ID
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_calibratePressure(unsigned int pressureIndex)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_calibratePressure(pressureIndex));
	Fgt_Manage_Pressure_Status(pressureIndex, "Fgt_calibratePressure");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Start closed loop regulation between a sensor and a pressure controller. Pressure will be regulated in order to reach sensor setpoint.
 * Custom sensors, outside Fluigent ones, can be used such as different flow-units, pressure, level ...
 * However we do not guarantee full compatibility with all sensors. Regulation quality is linked to sensor precision and your set-up.
 * In order to use this function, custom used sensor maximum range and measured values has to be updated at least once per second.
 * Directly setting pressure on same pressureIndex will stop regulation.
 * This function must be called at 1Hz minimum or the regulation will stop.
 * @param measure custom sensor measured value, no unit is required
 * @param setpoint custom sensor regulation goal value, no unit is required
 * @param pressureIndex Index of pressure channel or unique ID
 * @param maxSensorRange custom sensor maximum range, no unit is required
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_set_customSensorRegulation(float measure, float setpoint, float maxSensorRange, unsigned int pressureIndex)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_set_customSensorRegulation(measure, setpoint, maxSensorRange, pressureIndex));
	Fgt_Manage_Generic_Status(returnCode, "Fgt_set_customSensorRegulation");
	return returnCode;
}

/**
 * @Description Get pressure controller minimum and maximum range. Returned values takes into account set unit, default value is 'mbar'.
 * @param pressureIndex Index of pressure channel or unique ID
 * @param *Pmin minim device pressure
 * @param *Pmax maximum device pressure
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_get_pressureRange(unsigned int pressureIndex, float* Pmin, float* Pmax)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_get_pressureRange(pressureIndex, Pmin, Pmax));
	Fgt_Manage_Pressure_Status(pressureIndex, "Fgt_get_pressureRange");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Get sensor minimum and maximum range. Returned values takes into account set unit, default value is '�l/min' in case of flow-units.
 * @param sensorIndex Index of sensor channel or unique ID
 * @param *Smin minimum measured sensor value
 * @param *Smax maximum measured sensor value
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_get_sensorRange(unsigned int sensorIndex, float* Smin, float* Smax)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_get_sensorRange(sensorIndex, Smin, Smax));
	Fgt_Manage_Sensor_Status(sensorIndex, "Fgt_get_sensorRange");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Get valve maximum position. Position indexing starts at 0.
 * @param valveIndex Index of valve channel
 * @out posMax Maximum position of this valve
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_get_valveRange(unsigned int valveIndex, int* posMax)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_get_valveRange(valveIndex, posMax));
	Fgt_Manage_Generic_Status(returnCode, "Fgt_get_valveRange");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Set pressure working range and ensure that pressure will never exceed this limit. It takes into account current unit, default value is 'mbar'.
 * This function is useful to protect your microfluidic system.
 * @param pressureIndex Index of pressure channel or unique ID
 * @param PlimMin minimum admissible device pressure
 * @param PlimMax maximum admissible device pressure
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_set_pressureLimit(unsigned int pressureIndex, float PlimMin, float PlimMax)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_set_pressureLimit(pressureIndex, PlimMin, PlimMax));
	Fgt_Manage_Pressure_Status(pressureIndex, "Fgt_set_pressure");											// Manage error if occured
	return returnCode;
}


/*============================================================================*/
/*------------------------   Regulation settings   ---------------------------*/
/*============================================================================*/

/**
 * @Description Set on a running regulation pressure response time. Minimal value is 2 for FlowEZ, 6 for MFCS controllers.
 * This function is useful if a more smooth response is wanted.
 * @param sensorIndex Index of sensor channel or unique ID
 * @param responseTime pressure response time in seconds
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_set_sensorRegulationResponse(unsigned int sensorIndex, unsigned int responseTime)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_set_sensorRegulationResponse(sensorIndex, responseTime));
	Fgt_Manage_Sensor_Status(sensorIndex, "Fgt_set_sensorRegulation");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Set pressure controller response. This function can be used to customise response time for your set-up.
 * For FlowEZ available values are 0: use of fast switch valves or 1: do not use fast switch valves. Default value is 0.
 * For MFCS available values are from 1 to 255. Higher the value, longer is the response time. Default value is 5.
 * @param pressureIndex Index of pressure channel or unique ID
 * @param value desired pressure controller response time, this depends on controller type
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_set_pressureResponse(unsigned int pressureIndex, unsigned char value)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_set_pressureResponse(pressureIndex, value));
	Fgt_Manage_Pressure_Status(pressureIndex, "Fgt_set_pressure");											// Manage error if occured
	return returnCode;
}

/*============================================================================*/
/*------------------------   Status information   ----------------------------*/
/*============================================================================*/

/**
 * @Description Get detailed information of pressure channel status. This function is meant to be invoked after calling a pressure related function which returns an error code.
 * Retrieved information of last error contains controller position and a string detail.
 * @param pressureIndex Index of pressure channel or unique ID
 * @param *type fgt_INSTRUMENT_TYPE, controller type
 * @param *controllerSN serial number of controller (such as Link, MFCS)
 * @param *information information status code, 1 if pressure module is controller locally
 * @param detail detailed string about the error or state
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_get_pressureStatus(unsigned int pressureIndex, fgt_INSTRUMENT_TYPE* type, unsigned short* controllerSN, unsigned char* infoCode, std::string* detail)
{
	char localDetail[140] = "";
	fgt_INSTRUMENT_TYPE localType = fgt_INSTRUMENT_TYPE::None;

	fgt_ERROR_CODE error = fgt_ERROR_CODE(fgt_get_pressureStatus(pressureIndex, &localType, controllerSN, infoCode, localDetail));
	*type = fgt_INSTRUMENT_TYPE(localType);
	*detail = localDetail;
	return error;
}

/**
 * @Description Get detailed information of sensor status. This function is meant to be invoked after calling a sensor related function which returns an error code.
 * Retrieved information of last error contains sensor position and a string detail.
 * @param sensorIndex Index of sensor channel or unique ID
 * @param *InstrType fgt_INSTRUMENT_TYPE, controller type
 * @param *controllerSN serial number of controller (such as Link, Flowboard)
 * @param *information information status code when regulating 0: No regulation; 1: Regulating; otherwise regulation might not be optimal
 * @param detail detailed string about the error or state
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_get_sensorStatus(unsigned int sensorIndex, fgt_INSTRUMENT_TYPE* type, unsigned short* controllerSN, unsigned char* infoCode, std::string* detail)
{
	char localDetail[140] = "";
	fgt_INSTRUMENT_TYPE localType = fgt_INSTRUMENT_TYPE::None;

	fgt_ERROR_CODE error = fgt_ERROR_CODE(fgt_get_sensorStatus(sensorIndex, &localType, controllerSN, infoCode, localDetail));
	*type = fgt_INSTRUMENT_TYPE(localType);
	*detail = localDetail;
	return error;
}

/**
 * @Description Set power ON or OFF on a controller (such as Link, MFCS, Flowboard).
 * Not all controllers support this functionality.
 * @param controllerIndex Index of controller or unique ID
 * @param powerState fgt_POWER
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_set_power(unsigned int controllerIndex, fgt_POWER powerState)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_set_power(controllerIndex, (unsigned char)powerState));
	Fgt_Manage_Generic_Status(returnCode, "Fgt_set_power");
	return returnCode;
}

/**
 * @Description Get power information about a controller (such as Link, MFCS, Flowboard).
 * Not all controllers support this functionality.
 * @param controllerIndex Index of controller or unique ID
 * @param *powerState fgt_POWER
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_get_power(unsigned int controllerIndex, fgt_POWER* powerState)
{
	unsigned char localPowerState;

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_get_power(controllerIndex, &localPowerState));
	*powerState = fgt_POWER(localPowerState);
	Fgt_Manage_Generic_Status(returnCode, "Fgt_get_power");
	return returnCode;
}


/*============================================================================*/
/*-----------------------------  TTL functions  ------------------------------*/
/*============================================================================*/

/**
 * @Description Configure a specific TTL port (BNC ports) as input, output, rising or falling edge.
 * @param TtlIndex Index of TTL port or unique ID
 * @param mode fgt_TTL_MODE
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_set_TtlMode(unsigned int TtlIndex, fgt_TTL_MODE mode)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_set_TtlMode(TtlIndex, mode));
	Fgt_Manage_Generic_Status(returnCode, "Fgt_set_TtlMode");
	return returnCode;
}

/**
 * @Description Read TTL ports (BNC ports) if set as input.
 * @param TtlIndex Index of TTL port or unique ID
 * @param *state 0: no edge was detected; 1: an edge is detected
 * @return fgt_ERROR_CODE
 * @see fgt_set_TtlMode
 */
fgt_ERROR_CODE Fgt_read_Ttl(unsigned int TtlIndex, unsigned int* state)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_read_Ttl(TtlIndex, state));
	Fgt_Manage_Generic_Status(returnCode, "Fgt_read_Ttl");
	return returnCode;
}

/**
 * @Description Trigger a specific TTL port (BNC ports) if set as output.
 * @param TtlIndex Index of TTL port or unique ID
 * @return fgt_ERROR_CODE
 * @see fgt_set_TtlMode
 */
fgt_ERROR_CODE Fgt_trigger_Ttl(unsigned int TtlIndex)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_trigger_Ttl(TtlIndex));
	Fgt_Manage_Generic_Status(returnCode, "Fgt_trigger_Ttl");
	return returnCode;
}

/*============================================================================*/
/*-------------------------  Specific functions  -----------------------------*/
/*============================================================================*/

/**
 * @Description Activate/deactivate purge function.
 * This feature is only available on MFCS devices equipped with special valve.
 * @param controllerIndex Index of controller or unique ID
 * @param purge 0: OFF, 1:ON
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_set_purge(unsigned int controllerIndex, unsigned char purge)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_set_purge(controllerIndex, purge));
	Fgt_Manage_Generic_Status(returnCode, "Fgt_set_purge");
	return returnCode;
}

/**
 * @Description Manually set internal solenoid valve voltage. 
 *  This stops pressure regulation on the channel until a new pressure or
 *  flow rate command is set.
 * @param pressureIndex Index of pressure channel or unique ID
 * @param value applied valve voltage from 0 to 100(%)
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_set_manual(unsigned int pressureIndex, float value)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_set_manual(pressureIndex, value));
	Fgt_Manage_Pressure_Status(pressureIndex, "Fgt_set_manual");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Set the digital output ON or OFF on a controller
 * This feature is only available on the F-OEM device.
 * @param controllerIndex Index of controller or unique ID
 * @param port Address of the digital output to toggle. For F-OEM: 0: Pump, 1: LED
 * @param state 0: OFF, 1:ON
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_set_digitalOutput(unsigned int controllerIndex, unsigned char port, unsigned char state)
{
    fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_set_digitalOutput(controllerIndex, port, state));
	Fgt_Manage_Generic_Status(returnCode, "Fgt_set_digitalOutput");
	return returnCode;
}

/**
 * @Description Read the flag indicating whether the flow rate sensor detects an air bubble. Only 
    available on Flow Unit sensor ranges M+ and L+.
 * @param sensorIndex Index of sensor channel or unique ID
 * @out detected 1 if an air bubble was detected, 0 otherwise.
 * @return fgt_ERROR_CODE
 * @see fgt_get_sensorStatus
 */
fgt_ERROR_CODE Fgt_get_sensorAirBubbleFlag(unsigned int sensorIndex, unsigned char* detected)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_get_sensorAirBubbleFlag(sensorIndex, detected));
	Fgt_Manage_Sensor_Status(sensorIndex, "Fgt_get_sensorAirBubbleFlag");
	return returnCode;
}

/**
 * @Description Returns the pressure measured at the device's inlet.
 * This feature is only available on LineUP Flow EZ and FOEM Pressure Module instruments.
 * @param pressureIndex Index of pressure channel or unique ID
 * @param *pressure Inlet pressure value in selected unit, default is "mbar"
 * @return errorCode
 * @see fgt_get_pressureStatus
 */
fgt_ERROR_CODE Fgt_get_inletPressure(unsigned int pressureIndex, float* pressure)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_get_inletPressure(pressureIndex, pressure));
	Fgt_Manage_Pressure_Status(pressureIndex, "Fgt_get_inletPressure");
	return returnCode;
}

/**
 * @Description Returns the range of the differential pressure sensor in mbar
 * This feature is only available on NIFS devices.
 * @param sensorIndex Index of sensor or unique ID
 * @out Pmin minimum differential pressure in mbar
 * @out Pmax maximum differential pressure in mbar
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_get_differentialPressureRange(unsigned int sensorIndex, float* Pmin, float* Pmax)
{
    fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_get_differentialPressureRange(sensorIndex, Pmin, Pmax));
	Fgt_Manage_Sensor_Status(sensorIndex, "Fgt_get_differentialPressureRange");
	return returnCode;
}

/**
 * @Description Returns the current differential pressure measurement in mbar
 * This feature is only available on NIFS devices.
 * @param sensorIndex Index of sensor or unique ID
 * @out Pdiff differential pressure in mbar
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_get_differentialPressure(unsigned int sensorIndex, float* Pdiff)
{
    fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_get_differentialPressure(sensorIndex, Pdiff));
	Fgt_Manage_Sensor_Status(sensorIndex, "Fgt_get_differentialPressure");
	return returnCode;
}

/**
 * @Description Returns the range of the absolute pressure sensor in mbar
 * This feature is only available on NIFS devices.
 * @param sensorIndex Index of sensor or unique ID
 * @out Pmin minimum absolute pressure in mbar
 * @out Pmax maximum absolute pressure in mbar
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_get_absolutePressureRange(unsigned int sensorIndex, float* Pmin, float* Pmax)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_get_absolutePressureRange(sensorIndex, Pmin, Pmax));
	Fgt_Manage_Sensor_Status(sensorIndex, "Fgt_get_absolutePressureRange");
	return returnCode;
}

/**
 * @Description Returns the current absolute pressure measurement in mbar
 * This feature is only available on NIFS devices.
 * @param sensorIndex Index of sensor or unique ID
 * @out Pdiff absolute pressure in mbar
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_get_absolutePressure(unsigned int sensorIndex, float* Pabs)
{
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_get_absolutePressure(sensorIndex, Pabs));
	Fgt_Manage_Sensor_Status(sensorIndex, "Fgt_get_absolutePressure");
	return returnCode;
}

/**
 * @Description Returns the current state of the bypass valve.
 * This feature is only available on NIFS devices.
 * @param sensorIndex Index of sensor or unique ID
 * @out state 1 if the valve is open, 0 if it is closed.
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_get_sensorBypassValve(unsigned int sensorIndex, unsigned char* state) {
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_get_sensorBypassValve(sensorIndex, state));
	Fgt_Manage_Sensor_Status(sensorIndex, "Fgt_get_sensorBypassValve");
	return returnCode;
}

/**
 * @Description Sets the state of the sensor's bypass valve.
 * This feature is only available on NIFS devices.
 * @param sensorIndex Index of sensor or unique ID
 * @param state 1 to open, 0 to close.
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_set_sensorBypassValve(unsigned int sensorIndex, unsigned char state) {
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_set_sensorBypassValve(sensorIndex, state));
	Fgt_Manage_Sensor_Status(sensorIndex, "Fgt_set_sensorBypassValve");
	return returnCode;
}

/**
 * @Description Sets the verbosity of the logging feature, i.e., how much data is logged.
 * @param verbosity The amount of data to log. Set to 0 to disable logging (default).
 * Set to 5 to log the maximum amount of data.
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_set_log_verbosity(unsigned int verbosity){
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_set_log_verbosity(verbosity));
	return returnCode;
}

/**
 * @Description Sets how the SDK outputs the log entries.
 * @param output_to_file Output log entries to a file in the current directory. 1 to enable, 0 to disable. Default: enabled.
 * @param output_to_stderr Output log entries to the stderr pipe (console). 1 to enable, 0 to disable. Default: disabled.
 * @param output_to_queue Store log entries in memory. They can be retrieved via the fgt_get_next_log function. 1 to enable, 0 to disable. Default: disabled.
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_set_log_output_mode(unsigned char output_to_file, unsigned char output_to_stderr, unsigned char output_to_queue){
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_set_log_output_mode(output_to_file, output_to_stderr, output_to_queue));
	return returnCode;
}

/**
 * @Description Returns the next log entry stored in memory, if any, and removes it from the queue.
 * Will return an error if the queue is empty. Logs are only stored in memory if the corresponding option is set with the
 * fgt_set_log_output_mode function. Call this function repeatedly until an error is returned to retrieve all log entries.
 * @param log char array provided by the user, on which the log string will be copied.
 *  Must have at least 2000 bytes of available space.
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_get_next_log(std::string* log_entry){
	char buffer[2000] = { 0 };
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(fgt_get_next_log(buffer));
	*log_entry = buffer;
	return returnCode;
}

fgt_ERROR_CODE Fgt_set_errorReportMode(fgt_ERROR_REPORT_MODE mode)
{
	error_report_mode = mode;
	return fgt_ERROR_CODE::OK;
}


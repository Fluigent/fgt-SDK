/*============================================================================*/
/*               Fluigent Software Developement Kit for C++                   */
/*----------------------------------------------------------------------------*/
/*         Copyright (c) Fluigent 2019.  All Rights Reserved.                 */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Title:   fgt_SDK_Cpp.c                                                     */
/* Purpose: Wrapper to fgt_SDK_*.dll				                          */
/*			Contains an interface to each dll function and type conversions	  */
/* Version: 1.0.0.0                                                           */
/* Date:	06/2019															  */
/*============================================================================*/

#include <iostream>
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
	default: str.setstate(std::ios_base::failbit);
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
	default: str.setstate(std::ios_base::failbit);
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
	default: str.setstate(std::ios_base::failbit);
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
	default: str.setstate(std::ios_base::failbit);
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
	default: str.setstate(std::ios_base::failbit);
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
	default: str.setstate(std::ios_base::failbit);
	}
	return str;
}


/** Internal function used to load fgt_SDK_*.dll file */
HINSTANCE fgt_Dll_Handle(void)
{
	if (proc_fgt_dll == NULL)
	{

#ifdef _WIN64
		proc_fgt_dll = LoadLibraryA("fgt_SDK_64.dll");
#else
		proc_fgt_dll = LoadLibraryA("fgt_SDK_32.dll");
#endif
		if(proc_fgt_dll == NULL)
		{
			std::cout << "fgt_SDK_*.dll not found" << std::endl;
			return NULL;
		}
		return proc_fgt_dll;
	}
	else return proc_fgt_dll;
}

/** Manage pressure error and status, display details 
 *  Change this function for custom error management, returned fgt_ERROR_CODE can directly be used in main application
 *  This functions calls Fgt_get_pressureStatus and displays error details */
void Fgt_Manage_Pressure_Status(unsigned int pressureIndex, std::string calledFunctionName)
{
	fgt_INSTRUMENT_TYPE type;
	unsigned short controllerSN;
	unsigned char information;
	std::string detail;

	fgt_ERROR_CODE error = Fgt_get_pressureStatus(pressureIndex, &type, &controllerSN, &information, &detail);

	if(error != fgt_ERROR_CODE::OK)
	{
		std::cout << calledFunctionName << " pressure channel " << pressureIndex << " of type " << type << " error " << int(error) << ": " << error << " - " << detail << ", Controller SN: " << controllerSN <<
			", info code: " << int(information) << std::endl;
	}
}

/** Manage sensor error and status, display details
 *  Change this function for custom error management, returned fgt_ERROR_CODE can directly be used in main application 
 *  This functions calls Fgt_get_sensorStatus and displays error details */
void Fgt_Manage_Sensor_Status(unsigned int sensorIndex, std::string calledFunctionName)
{
	fgt_INSTRUMENT_TYPE type;
	unsigned short controllerSN;
	unsigned char information;
	std::string detail;

	fgt_ERROR_CODE error = Fgt_get_pressureStatus(sensorIndex, &type, &controllerSN, &information, &detail);

	if (error != fgt_ERROR_CODE::OK)
	{
		std::cout << calledFunctionName << " sensor channel " << sensorIndex << " of type " << type << " error " << int(error) << ": " << error << " - " << detail << ", Controller SN: " << controllerSN <<
			", info code: " << int(information) << std::endl;
	}
}

/** Manage generic functions error and status, display details
 *  Change this function for custom error management, returned fgt_ERROR_CODE can directly be used in main application */
void Fgt_Manage_Generic_Status(fgt_ERROR_CODE error, std::string calledFunctionName)
{
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
 * @Description Initialize or reinitialize (if already opened) Fluigent SDK instance. All detected Fluigent instruments (MFCS, MFCS-EZ, FRP, LineUP) are initialized.
 * This function is optional, directly calling a function will automatically creates the instance.
 * @param void
 * @return fgt_ERROR_CODE
 * @see fgt_close
 * @see fgt_initEx
 */
fgt_ERROR_CODE Fgt_init(void)
{
	typedef unsigned char(__stdcall * fgt_init)(void);							// Declare function prototype
	fgt_init pfgt_init = (fgt_init)GetProcAddress(fgt_Dll_Handle(), "fgt_init");		// Link with dll function

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_init());					// Call function
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
	typedef unsigned char(__stdcall * fgt_close)(void);
	fgt_close pfgt_close = (fgt_close)GetProcAddress(fgt_Dll_Handle(), "fgt_close");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_close());
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
fgt_ERROR_CODE Fgt_detect(unsigned short SN[256], fgt_INSTRUMENT_TYPE type[256])
{
	int localType[256] = {0};
	fgt_ERROR_CODE returnCode;
	typedef unsigned char(__stdcall * fgt_detect)(unsigned short SN[], int type[]);
	fgt_detect pfgt_detect = (fgt_detect)(GetProcAddress(fgt_Dll_Handle(), "fgt_detect"));

	returnCode = fgt_ERROR_CODE(pfgt_detect(SN, localType));
	for(unsigned char loop = 0; loop < 255; loop++) type[loop] = fgt_INSTRUMENT_TYPE(localType[loop]);		// Convert type from dll int to C++ enum fgt_INSTRUMENT_TYPE
	Fgt_Manage_Generic_Status(returnCode, "Fgt_detect");
	return returnCode;
}

/**
 * @Description Initialize specific Fluigent instrument(s) from their unique serial number. This function can be used when multiple instruments are connected in order to select your device(s)
 * @param [SN] Array of controllers serial number
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_initEx(unsigned short SN[256])
{
	typedef unsigned char(__stdcall * fgt_initEx)(unsigned short SN[]);
	fgt_initEx pfgt_initEx = (fgt_initEx)GetProcAddress(fgt_Dll_Handle(), "fgt_initEx");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_initEx(SN));
	Fgt_Manage_Generic_Status(returnCode, "Fgt_initEx");
	return returnCode;
}

/*============================================================================*/
/*------------------------------  Channels info  -----------------------------*/
/*============================================================================*/

/**
 * @Description Retrieve information about session controllers. Controllers are MFCS, Flowboard, Link in an array.
 * @out [info] Array of structure of fgt_CONTROLLER_INFO
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_get_controllersInfo(fgt_CONTROLLER_INFO info[256])
{
	typedef unsigned char(__stdcall * fgt_get_controllersInfo)(fgt_CONTROLLER_INFO info[]);
	fgt_get_controllersInfo pfgt_get_controllersInfo = (fgt_get_controllersInfo)GetProcAddress(fgt_Dll_Handle(), "fgt_get_controllersInfo");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_get_controllersInfo(info));
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
	typedef unsigned char(__stdcall * fgt_get_pressureChannelCount)(unsigned char* nbPChan);
	fgt_get_pressureChannelCount pfgt_get_pressureChannelCount = (fgt_get_pressureChannelCount)GetProcAddress(fgt_Dll_Handle(), "fgt_get_pressureChannelCount");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_get_pressureChannelCount(nbPChan));
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
	typedef unsigned char(__stdcall * fgt_get_sensorChannelCount)(unsigned char* nbSChan);
	fgt_get_sensorChannelCount pfgt_get_sensorChannelCount = (fgt_get_sensorChannelCount)GetProcAddress(fgt_Dll_Handle(), "fgt_get_sensorChannelCount");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_get_sensorChannelCount(nbSChan));
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
	typedef unsigned char(__stdcall * fgt_get_TtlChannelCount)(unsigned char* nbTTLChan);
	fgt_get_TtlChannelCount pfgt_get_TtlChannelCount = (fgt_get_TtlChannelCount)GetProcAddress(fgt_Dll_Handle(), "fgt_get_TtlChannelCount");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_get_TtlChannelCount(nbTtlChan));
	Fgt_Manage_Generic_Status(returnCode, "Fgt_get_TtlChannelCount");
	return returnCode;
}

/**
 * @Description: Retrieve information about each initialized pressure channel. This function is useful in order to get channels order, controller, unique ID and InstrType.
 * By default this array is built with MFCS first, MFCS-EZ second and FlowEZ last. If only one instrument is used, index is the default channel indexing starting at 0.
 * You can initialize instruments in specific order using fgt_initEx function
 * @param info Array of structure of fgt_CHANNEL_INFO
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_get_pressureChannelsInfo(fgt_CHANNEL_INFO info[256])
{
	typedef unsigned char(__stdcall * fgt_get_pressureChannelsInfo)(fgt_CHANNEL_INFO info[]);
	fgt_get_pressureChannelsInfo pfgt_get_pressureChannelsInfo = (fgt_get_pressureChannelsInfo)GetProcAddress(fgt_Dll_Handle(), "fgt_get_pressureChannelsInfo");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_get_pressureChannelsInfo(info));
	Fgt_Manage_Generic_Status(returnCode, "Fgt_get_pressureChannelsInfo");
	return returnCode;
}

/**
 * @Description: Retrieve information about each initialized sensor channel. This function is useful in order to get channels order, controller, unique ID and InstrType.
 * By default this array is built with FRP first then FlowEZ and contains flow-units. If only one instrument is used, index is the default channel indexing starting at 0.
 * You can initialize instruments in specific order using fgt_initEx function
 * @param info Array of structure of fgt_CHANNEL_INFO
 * @param sensorType Array of fgt_SENSOR_TYPE
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_get_sensorChannelsInfo(fgt_CHANNEL_INFO info[256], fgt_SENSOR_TYPE sensorType[256])
{
	int localSensorType[256] = {0};
	typedef unsigned char(__stdcall * fgt_get_sensorChannelsInfo)(fgt_CHANNEL_INFO info[], int sensorType[256]);
	fgt_get_sensorChannelsInfo pfgt_get_sensorChannelsInfo = (fgt_get_sensorChannelsInfo)GetProcAddress(fgt_Dll_Handle(), "fgt_get_sensorChannelsInfo");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_get_sensorChannelsInfo(info, localSensorType));
	for (unsigned char loop = 0; loop < 255; loop++) sensorType[loop] = fgt_SENSOR_TYPE(localSensorType[loop]);
	Fgt_Manage_Generic_Status(returnCode, "Fgt_get_sensorChannelsInfo");
	return returnCode;
}

/**
 * @Description: Retrieve information about each initialized TTL channel. This function is useful in order to get channels order, controller, unique ID and InstrType.
 * TTL channels are only available for LineUP Series, 2 ports for each connected Link
 * @param info Array of structure of fgt_CHANNEL_INFO
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_get_TtlChannelsInfo(fgt_CHANNEL_INFO info[256])
{
	typedef unsigned char(__stdcall * fgt_get_TtlChannelsInfo)(fgt_CHANNEL_INFO info[]);
	fgt_get_TtlChannelsInfo pfgt_get_TtlChannelsInfo = (fgt_get_TtlChannelsInfo)GetProcAddress(fgt_Dll_Handle(), "fgt_get_TtlChannelsInfo");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_get_TtlChannelsInfo(info));
	Fgt_Manage_Generic_Status(returnCode, "Fgt_get_TtlChannelsInfo");
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
	typedef unsigned char(__stdcall * fgt_set_pressure)(unsigned int pressureIndex, float pressure);
	fgt_set_pressure pfgt_set_pressure = (fgt_set_pressure)GetProcAddress(fgt_Dll_Handle(), "fgt_set_pressure");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_set_pressure(pressureIndex, pressure));
	Fgt_Manage_Pressure_Status(pressureIndex, "Fgt_set_pressure");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Read pressure value of selected device
 * @param pressureIndex Index of pressure channel or unique ID
 * @out *pressure Read pressure value in selected unit, default is "mbar"
 * @return errorCode
 * @see fgt_get_pressureEx
 * @see fgt_get_pressureStatus
 */
fgt_ERROR_CODE Fgt_get_pressure(unsigned int pressureIndex, float* pressure)
{
	typedef unsigned char(__stdcall * fgt_get_pressure)(unsigned int pressureIndex, float* pressure);
	fgt_get_pressure pfgt_get_pressure = (fgt_get_pressure)GetProcAddress(fgt_Dll_Handle(), "fgt_get_pressure");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_get_pressure(pressureIndex, pressure));
	Fgt_Manage_Pressure_Status(pressureIndex, "Fgt_get_pressure");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Read pressure value and time stamp of selected device
 * @param pressureIndex Index of pressure channel or unique ID
 * @out *pressure Read pressure value in selected unit, default is "mbar"
 * @out *timeStamp Hardware timer in ms
 * @return fgt_ERROR_CODE
 * @see fgt_get_pressure
 * @see fgt_get_pressureStatus
 */
fgt_ERROR_CODE Fgt_get_pressureEx(unsigned int pressureIndex, float* pressure, unsigned short* timeStamp)
{
	typedef unsigned char(__stdcall * fgt_get_pressureEx)(unsigned int pressureIndex, float* pressure, unsigned short* timeStamp);
	fgt_get_pressureEx pfgt_get_pressureEx = (fgt_get_pressureEx)GetProcAddress(fgt_Dll_Handle(), "fgt_get_pressureEx");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_get_pressureEx(pressureIndex, pressure, timeStamp));
	Fgt_Manage_Pressure_Status(pressureIndex, "Fgt_get_pressureEx");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Start closed loop regulation between a sensor and a pressure controller. Pressure will be regulated in order to reach sensor setpoint.
 * Call again this function in order to change the setpoint. Calling fgt_set_pressure on same pressureIndex will stop regulation.
 * @param sensorIndex Index of sensor channel or unique ID
 * @param pressureIndex Index of pressure channel or unique ID
 * @param setpoint Regulation value to be reached in selected unit, default is "µl/min" for flowrate sensors
 * @return fgt_ERROR_CODE
 * @see fgt_set_pressure
 * @see fgt_set_customSensorRegulation
 * @see fgt_set_sensorRegulationResponse
 */
fgt_ERROR_CODE Fgt_set_sensorRegulation(unsigned int sensorIndex, unsigned int pressureIndex, float setpoint)
{
	typedef unsigned char(__stdcall * fgt_set_sensorRegulation)(unsigned int sensorIndex, unsigned int pressureIndex, float setpoint);
	fgt_set_sensorRegulation pfgt_set_sensorRegulation = (fgt_set_sensorRegulation)GetProcAddress(fgt_Dll_Handle(), "fgt_set_sensorRegulation");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_set_sensorRegulation(sensorIndex, pressureIndex, setpoint));
	Fgt_Manage_Sensor_Status(sensorIndex, "Fgt_set_sensorRegulation");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Read sensor value of selected device
 * @param sensorIndex Index of sensor channel or unique ID
 * @out value Read sensor value in selected unit, default is "µl/min" for flowrate sensors
 * @return fgt_ERROR_CODE
 * @see fgt_get_sensorStatus
 */
fgt_ERROR_CODE Fgt_get_sensorValue(unsigned int sensorIndex, float* value)
{
	typedef unsigned char(__stdcall * fgt_get_sensorValue)(unsigned int sensorIndex, float* value);
	fgt_get_sensorValue pfgt_get_sensorValue = (fgt_get_sensorValue)GetProcAddress(fgt_Dll_Handle(), "fgt_get_sensorValue");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_get_sensorValue(sensorIndex, value));
	Fgt_Manage_Sensor_Status(sensorIndex, "Fgt_get_sensorValue");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Read sensor value and timestamp of selected device
 * @param sensorIndex Index of sensor channel or unique ID
 * @out value Read sensor value in selected unit, default is "µl/min" for flowrate sensors
 * @out timeStamp Hardware timer in ms
 * @return fgt_ERROR_CODE
 * @see fgt_get_sensorStatus
 */
fgt_ERROR_CODE Fgt_get_sensorValueEx(unsigned int sensorIndex, float* value, unsigned short* timeStamp)
{
	typedef unsigned char(__stdcall * fgt_get_sensorValueEx)(unsigned int sensorIndex, float* value, unsigned short* timeStamp);
	fgt_get_sensorValueEx pfgt_get_sensorValueEx = (fgt_get_sensorValueEx)GetProcAddress(fgt_Dll_Handle(), "fgt_get_sensorValueEx");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_get_sensorValueEx(sensorIndex, value, timeStamp));
	Fgt_Manage_Sensor_Status(sensorIndex, "Fgt_get_sensorValueEx");											// Manage error if occured
	return returnCode;
}


/*============================================================================*/
/*--------------------   Unit, calibration and limits  -----------------------*/
/*============================================================================*/

/**
 * @Description Set pressure unit for all initialized channels, default value is "mbar". If type is invalid an error is returned.
 * Every pressure read value and sent command will then use this unit.
 * Example of type: "mbar", "millibar", "kPa" ...
 * @param unit Array of char containing a unit string
 * @return fgt_ERROR_CODE
 * @see fgt_get_pressureStatus
 */
fgt_ERROR_CODE Fgt_set_sessionPressureUnit(std::string unit)
{
	char localUnit[140] = { 0 };
	strcpy_s(localUnit, unit.c_str());
	typedef unsigned char(__stdcall * fgt_set_sessionPressureUnit)(char* unit);
	fgt_set_sessionPressureUnit pfgt_set_sessionPressureUnit = (fgt_set_sessionPressureUnit)GetProcAddress(fgt_Dll_Handle(), "fgt_set_sessionPressureUnit");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_set_sessionPressureUnit(localUnit));
	Fgt_Manage_Pressure_Status(0, "Fgt_set_sessionPressureUnit");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Set pressure unit on selected pressure device, default value is "mbar". If type is invalid an error is returned.
 * Every pressure read value and sent command will then use this unit.
 * Example of type: "mbar", "millibar", "kPa" ...
 * @param presureIndex Index of pressure channel or unique ID
 * @param unit[] Array of char containing a unit string
 * @return fgt_ERROR_CODE
 * @see fgt_get_pressureStatus
 */
fgt_ERROR_CODE Fgt_set_pressureUnit(unsigned int pressureIndex, std::string unit)
{
	char localUnit[140] = { 0 };
	strcpy_s(localUnit, unit.c_str());
	typedef unsigned char(__stdcall * fgt_set_pressureUnit)(unsigned int presureIndex, char* unit);
	fgt_set_pressureUnit pfgt_set_pressureUnit = (fgt_set_pressureUnit)GetProcAddress(fgt_Dll_Handle(), "fgt_set_pressureUnit");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_set_pressureUnit(pressureIndex, localUnit));
	Fgt_Manage_Pressure_Status(pressureIndex, "Fgt_set_pressureUnit");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Get used unit on selected pressure device, default value is "mbar".
 * Every pressure read value and sent command use this unit.
 * @param pressureIndex Index of pressure channel or unique ID
 * @out unit[] Array of char containing a unit string
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_get_pressureUnit(unsigned int pressureIndex, std::string* unit)
{
	char localUnit[140] = { 0 };
	typedef unsigned char(__stdcall * fgt_get_pressureUnit)(unsigned int pressureIndex, char* unit);
	fgt_get_pressureUnit pfgt_get_pressureUnit = (fgt_get_pressureUnit)GetProcAddress(fgt_Dll_Handle(), "fgt_get_pressureUnit");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_get_pressureUnit(pressureIndex, localUnit));
	*unit = localUnit;
	Fgt_Manage_Pressure_Status(pressureIndex, "Fgt_get_pressureUnit");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Set sensor unit on selected sensor device, default value is "µl/min" for flowunits. If type is invalid an error is returned.
 * Every sensor read value and regulation command will then use this unit.
 * Example of type: "µl/h", "ulperDay", "microliter/hour" ...
 * @param pressureIndex Index of pressure channel or unique ID
 * @param unit[] Array of char containing a unit string
 * @return fgt_ERROR_CODE
 * @see fgt_set_sensorStatus
 */
fgt_ERROR_CODE Fgt_set_sensorUnit(unsigned int sensorIndex, std::string unit)
{
	char localUnit[140] = {0};
	strcpy_s(localUnit, unit.c_str());
	typedef unsigned char(__stdcall * fgt_set_sensorUnit)(unsigned int sensorIndex, char* unit);
	fgt_set_sensorUnit pfgt_set_sensorUnit = (fgt_set_sensorUnit)GetProcAddress(fgt_Dll_Handle(), "fgt_set_sensorUnit");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_set_sensorUnit(sensorIndex, localUnit));
	Fgt_Manage_Sensor_Status(sensorIndex, "Fgt_set_sensorUnit");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Get used unit on selected sensor device, default value is "µl/min" for flowunits.
 * Every sensor read value and regulation command use this unit.
 * @param sensorIndex Index of sensor channel or unique ID
 * @out unit[] Array of char containing a unit string
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_get_sensorUnit(unsigned int sensorIndex, std::string* unit)
{
	char localUnit[140] = { 0 };
	typedef unsigned char(__stdcall * fgt_get_sensorUnit)(unsigned int sensorIndex, char* unit);
	fgt_get_sensorUnit pfgt_get_sensorUnit = (fgt_get_sensorUnit)GetProcAddress(fgt_Dll_Handle(), "fgt_get_sensorUnit");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_get_sensorUnit(sensorIndex, localUnit));
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
	typedef unsigned char(__stdcall * fgt_set_sensorCalibration)(unsigned int sensorIndex, int calibration);
	fgt_set_sensorCalibration pfgt_set_sensorCalibration = (fgt_set_sensorCalibration)GetProcAddress(fgt_Dll_Handle(), "fgt_set_sensorCalibration");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_set_sensorCalibration(sensorIndex, int(calibration)));
	Fgt_Manage_Sensor_Status(sensorIndex, "Fgt_set_sensorCalibration");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Get internal used calibration table by the sensor.
 * @param sensorIndex Index of sensor channel or unique ID
 * @out *calibration fgt_SENSOR_CALIBRATION
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_get_sensorCalibration(unsigned int sensorIndex, fgt_SENSOR_CALIBRATION* calibration)
{
	int localCalibration;
	typedef unsigned char(__stdcall * fgt_get_sensorCalibration)(unsigned int sensorIndex, int* calibration);
	fgt_get_sensorCalibration pfgt_get_sensorCalibration = (fgt_get_sensorCalibration)GetProcAddress(fgt_Dll_Handle(), "fgt_get_sensorCalibration");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_get_sensorCalibration(sensorIndex, &localCalibration));
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
	typedef unsigned char(__stdcall * fgt_set_sensorCustomScale)(unsigned int sensorIndex, float a, float b, float c);
	fgt_set_sensorCustomScale pfgt_set_sensorCustomScale = (fgt_set_sensorCustomScale)GetProcAddress(fgt_Dll_Handle(), "fgt_set_sensorCustomScale");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_set_sensorCustomScale(sensorIndex, a, b, c));
	Fgt_Manage_Sensor_Status(sensorIndex, "Fgt_set_sensorCustomScale");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Apply a custom scale factor on sensor read value. This function is useful in order to adapt read sensor value to physical measurement.
 * For example if a flow-unit is used with a special oil and it's calibration table is set to H2O, read flowrate is not correct.
 * Scale factor is applied using following formula: scaled_value = a*sensor_value + b*sensor_value^2 + c*sensor_value^3
 * When applying a custom scale factor, sensor range may increase very rapidly, SMax parameter is ment to limit this maximal value.
 * This function purpose is to be used with the regulation in order to avoid too high maximum range on the sensor.
 * @param sensorIndex Index of sensor channel or unique ID
 * @param float a proportional multiplier value
 * @param float b square multiplier value
 * @param float c cubic multiplier value
 * @param float SMax maximal tolerance of scale factor
 * @return fgt_ERROR_CODE
 * @see fgt_set_sensorCustomScale
 */
fgt_ERROR_CODE Fgt_set_sensorCustomScaleEx(unsigned int sensorIndex, float a, float b, float c, float SMax)
{
	typedef unsigned char(__stdcall * fgt_set_sensorCustomScaleEx)(unsigned int sensorIndex, float a, float b, float c, float SMax);
	fgt_set_sensorCustomScaleEx pfgt_set_sensorCustomScaleEx = (fgt_set_sensorCustomScaleEx)GetProcAddress(fgt_Dll_Handle(), "fgt_set_sensorCustomScaleEx");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_set_sensorCustomScaleEx(sensorIndex, a, b, c, SMax));
	Fgt_Manage_Sensor_Status(sensorIndex, "Fgt_set_sensorCustomScaleEx");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Calibrate internal pressure depending on atmospheric pressure. After calling this function 0 pressure value corresponds to atmospheric pressure.
 * During calibration step no pressure order is accepted. Total duration vary from 3s to 8s.
 * @param pressureIndex Index of pressure channel or unique ID
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_calibratePressure(unsigned int pressureIndex)
{
	typedef unsigned char(__stdcall * fgt_calibratePressure)(unsigned int pressureIndex);
	fgt_calibratePressure pfgt_calibratePressure = (fgt_calibratePressure)GetProcAddress(fgt_Dll_Handle(), "fgt_calibratePressure");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_calibratePressure(pressureIndex));
	Fgt_Manage_Pressure_Status(pressureIndex, "Fgt_calibratePressure");											// Manage error if occured
	return returnCode;
}


/**
 * @Description Start closed loop regulation between a sensor and a pressure controller. Pressure will be regulated in order to reach sensor setpoint.
 * Custom sensors, outside Fluigent ones, can be used such as different flow-units, pressure, level ...
 * However we do not guarantee full compatibility with all sensors. Regulation quality is linked to sensor precision and your set-up.
 * In order to use this function, custom used sensor maximum range and measured values has to be updated at least once per second.
 * Calling fgt_set_pressure on same pressureIndex or not updating sensor value over 1s will stop regulation.
 * @param measure custom sensor measured value, no unit is required
 * @param setpoint custom sensor regulation goal value, no unit is required
 * @param pressureIndex Index of pressure channel or unique ID
 * @param maxSensorRange custom sensor maximum range, no unit is required
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_set_customSensorRegulation(float measure, float setpoint, float maxSensorRange, unsigned int pressureIndex)
{
	typedef unsigned char(__stdcall * fgt_set_customSensorRegulation)(float measure, float setpoint, float maxSensorRange, unsigned int pressureIndex);
	fgt_set_customSensorRegulation pfgt_set_customSensorRegulation = (fgt_set_customSensorRegulation)GetProcAddress(fgt_Dll_Handle(), "fgt_set_customSensorRegulation");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_set_customSensorRegulation(measure, setpoint, maxSensorRange, pressureIndex));
	Fgt_Manage_Generic_Status(returnCode, "Fgt_set_customSensorRegulation");
	return returnCode;
}

/**
 * @Description Get pressure controller minimum and maximum range. Returned values takes into account set unit, default value is 'mbar'.
 * @param pressureIndex Index of pressure channel or unique ID
 * @out Pmin minim device pressure
 * @out Pmax maximum device pressure
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_get_pressureRange(unsigned int pressureIndex, float* Pmin, float* Pmax)
{
	typedef unsigned char(__stdcall * fgt_get_pressureRange)(unsigned int pressureIndex, float* Pmin, float* Pmax);
	fgt_get_pressureRange pfgt_get_pressureRange = (fgt_get_pressureRange)GetProcAddress(fgt_Dll_Handle(), "fgt_get_pressureRange");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_get_pressureRange(pressureIndex, Pmin, Pmax));
	Fgt_Manage_Pressure_Status(pressureIndex, "Fgt_get_pressureRange");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Get sensor minimum and maximum range. Returned values takes into account set unit, default value is 'µl/min' in case of flow-units.
 * @param sensorIndex Index of sensor channel or unique ID
 * @out Smin minimum measured sensor value
 * @out Smax maximum measured sensor value
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_get_sensorRange(unsigned int sensorIndex, float* Smin, float* Smax)
{
	typedef unsigned char(__stdcall * fgt_get_sensorRange)(unsigned int sensorIndex, float* Qmin, float* Qmax);
	fgt_get_sensorRange pfgt_get_sensorRange = (fgt_get_sensorRange)GetProcAddress(fgt_Dll_Handle(), "fgt_get_sensorRange");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_get_sensorRange(sensorIndex, Smin, Smax));
	Fgt_Manage_Sensor_Status(sensorIndex, "Fgt_get_sensorRange");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Set a limit, not to exceed on a pressure controller. It takes into account set unit, default value is 'mbar'.
 * This function is usefull when wanting to be sure not to go over a certain pressure value or during regulation.
 * Setting a limit is used for next called functions. Limits can not exceed controller range.
 * @param pressureIndex Index of pressure channel or unique ID
 * @param PlimMin minim admissible device pressure
 * @param PlimMax maximum admissible device pressure
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_set_pressureLimit(unsigned int pressureIndex, float PlimMin, float PlimMax)
{
	typedef unsigned char(__stdcall * fgt_set_pressureLimit)(unsigned int pressureIndex, float PlimMin, float PlimMax);
	fgt_set_pressureLimit pfgt_set_pressureLimit = (fgt_set_pressureLimit)GetProcAddress(fgt_Dll_Handle(), "fgt_set_pressureLimit");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_set_pressureLimit(pressureIndex, PlimMin, PlimMax));
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
	typedef unsigned char(__stdcall * fgt_set_sensorRegulationResponse)(unsigned int sensorIndex, unsigned int responseTime);
	fgt_set_sensorRegulationResponse pfgt_set_sensorRegulationResponse = (fgt_set_sensorRegulationResponse)GetProcAddress(fgt_Dll_Handle(), "fgt_set_sensorRegulationResponse");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_set_sensorRegulationResponse(sensorIndex, responseTime));
	Fgt_Manage_Sensor_Status(sensorIndex, "Fgt_set_sensorRegulation");											// Manage error if occured
	return returnCode;
}

/**
 * @Description Set pressure controller response. This function can be used to customise response time for your set-up.
 * For FlowEZ available values are 0: use of fast switch vales or 1: do not use fast switch vales. Default value is 0.
 * For MFCS available values are from 1 to 255. Higher the value, longer is the response time. Default value is 5.
 * @param pressureIndex Index of pressure channel or unique ID
 * @param value desired pressure controller response time
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_set_pressureResponse(unsigned int pressureIndex, unsigned char value)
{
	typedef unsigned char(__stdcall * fgt_set_pressureResponse)(unsigned int pressureIndex, unsigned char value);
	fgt_set_pressureResponse pfgt_set_pressureResponse = (fgt_set_pressureResponse)GetProcAddress(fgt_Dll_Handle(), "fgt_set_pressureResponse");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_set_pressureResponse(pressureIndex, value));
	Fgt_Manage_Pressure_Status(pressureIndex, "Fgt_set_pressure");											// Manage error if occured
	return returnCode;
}

/*============================================================================*/
/*------------------------   Status information   ----------------------------*/
/*============================================================================*/

/**
 * @Description Get detailed information of pressure channel status. This function is ment to be invoked after calling a pressure related function which returns an error code.
 * Retrieved information of last error contains controller position and a string detail.
 * @param pressureIndex Index of pressure channel or unique ID
 * @out InstrType fgt_INSTRUMENT_TYPE, controller type
 * @out controllerSN serial number of controller (such as Link, MFCS)
 * @out information information status code, 1 if pressure module is controller locally
 * @out detail array of characters which details the error
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_get_pressureStatus(unsigned int pressureIndex, fgt_INSTRUMENT_TYPE* type, unsigned short* controllerSN, unsigned char* infoCode, std::string* detail)
{
	char localDetail[140] = "";
	int localType = 0;

	typedef unsigned char(__stdcall * fgt_get_pressureStatus)(unsigned int pressureIndex, int* type, unsigned short* controllerSN, unsigned char* information, char detail[140]);
	fgt_get_pressureStatus pfgt_get_pressureStatus = (fgt_get_pressureStatus)GetProcAddress(fgt_Dll_Handle(), "fgt_get_pressureStatus");

	fgt_ERROR_CODE error = fgt_ERROR_CODE(pfgt_get_pressureStatus(pressureIndex, &localType, controllerSN, infoCode, localDetail));
	*detail = localDetail;
	return error;
}

/**
 * @Description Get detailed information of sensor status. This function is ment to be invoked after calling a sensor related function which returns an error code.
 * Retrieved information of last error contains sensor position and a string detail.
 * @param sensorIndex Index of sensor channel or unique ID
 * @out InstrType fgt_INSTRUMENT_TYPE, controller type
 * @out controllerSN serial number of controller (such as Link, Flowboard)
 * @out information information status code when regulating 0: Ok otherwise regulation might not be optimal
 * @out detail array of characters which details the error
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_get_sensorStatus(unsigned int sensorIndex, fgt_INSTRUMENT_TYPE* type, unsigned short* controllerSN, unsigned char* infoCode, std::string* detail)
{
	char localDetail[140] = "";
	int localType = 0;

	typedef unsigned char(__stdcall * fgt_get_sensorStatus)(unsigned int sensorIndex, int* type, unsigned short* controllerSN, unsigned char* information, char detail[140]);
	fgt_get_sensorStatus pfgt_get_sensorStatus = (fgt_get_sensorStatus)GetProcAddress(fgt_Dll_Handle(), "fgt_get_sensorStatus");

	fgt_ERROR_CODE error = fgt_ERROR_CODE(pfgt_get_sensorStatus(sensorIndex, &localType, controllerSN, infoCode, localDetail));
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
fgt_ERROR_CODE Fgt_set_power(unsigned short controllerIndex, fgt_POWER powerState)
{
	typedef unsigned char(__stdcall * fgt_set_power)(unsigned short controllerIndex, unsigned char powerState);
	fgt_set_power pfgt_set_power = (fgt_set_power)GetProcAddress(fgt_Dll_Handle(), "fgt_set_power");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_set_power(controllerIndex, unsigned char(powerState)));
	Fgt_Manage_Generic_Status(returnCode, "Fgt_set_power");
	return returnCode;
}

/**
 * @Description Get power information about a controller (such as Link, MFCS, Flowboard).
 * Not all controllers support this functionality.
 * @param controllerIndex Index of controller or unique ID
 * @out powerState fgt_POWER
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_get_power(unsigned short controllerIndex, fgt_POWER* powerState)
{
	unsigned char localPowerState;
	typedef unsigned char(__stdcall * fgt_get_power)(unsigned short controllerIndex, unsigned char * powerState);
	fgt_get_power pfgt_get_power = (fgt_get_power)GetProcAddress(fgt_Dll_Handle(), "fgt_get_power");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_get_power(controllerIndex, &localPowerState));
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
	typedef unsigned char(__stdcall * fgt_set_TtlMode)(unsigned int TTLIndex, int mode);
	fgt_set_TtlMode pfgt_set_TtlMode = (fgt_set_TtlMode)GetProcAddress(fgt_Dll_Handle(), "fgt_set_TtlMode");
	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_set_TtlMode(TtlIndex, int(mode)));
	Fgt_Manage_Generic_Status(returnCode, "Fgt_set_TtlMode");
	return returnCode;
}

/**
 * @Description Read TTL ports (BNC ports) if set as input.
 * @param TtlIndex Index of TTL port or unique ID
 * @out state 0: no edge was detected; 1: an edge is detected
 * @return fgt_ERROR_CODE
 * @see fgt_set_TtlMode
 */
fgt_ERROR_CODE Fgt_read_Ttl(unsigned int TtlIndex, unsigned int* state)
{
	typedef unsigned char(__stdcall * fgt_read_Ttl)(unsigned int TTLIndex, unsigned int* state);
	fgt_read_Ttl pfgt_read_Ttl = (fgt_read_Ttl)GetProcAddress(fgt_Dll_Handle(), "fgt_read_Ttl");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_read_Ttl(TtlIndex, state));
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
	typedef unsigned char(__stdcall * fgt_trigger_Ttl)(unsigned int TTLIndex);
	fgt_trigger_Ttl pfgt_trigger_Ttl = (fgt_trigger_Ttl)GetProcAddress(fgt_Dll_Handle(), "fgt_trigger_Ttl");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_trigger_Ttl(TtlIndex));
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
fgt_ERROR_CODE Fgt_set_purge(unsigned short controllerIndex, unsigned char purge)
{
	typedef unsigned char(__stdcall * fgt_set_purge)(unsigned short controllerIndex, unsigned char purge);
	fgt_set_purge pfgt_set_purge = (fgt_set_purge)GetProcAddress(fgt_Dll_Handle(), "fgt_set_purge");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_set_purge(controllerIndex, purge));
	Fgt_Manage_Generic_Status(returnCode, "Fgt_set_purge");
	return returnCode;
}

/**
 * @Description Manually activate internal electrovalve. This stops pressure regulation.
 * This feature is only available on MFCS and MFCS-EZ devices.
 * @param pressureIndex Index of pressure channel or unique ID
 * @param value applied valve voltage from 0 to 100(%)
 * @return fgt_ERROR_CODE
 */
fgt_ERROR_CODE Fgt_set_manual(unsigned int pressureIndex, float value)
{
	typedef unsigned char(__stdcall * fgt_set_manual)(unsigned int pressureIndex, float value);
	fgt_set_manual pfgt_set_manual = (fgt_set_manual)GetProcAddress(fgt_Dll_Handle(), "fgt_set_manual");

	fgt_ERROR_CODE returnCode = fgt_ERROR_CODE(pfgt_set_manual(pressureIndex, value));
	Fgt_Manage_Pressure_Status(pressureIndex, "Fgt_set_manual");											// Manage error if occured
	return returnCode;
}


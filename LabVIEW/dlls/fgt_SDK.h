/*============================================================================
*                   Fluigent Software Developement Kit                       
*----------------------------------------------------------------------------
*         Copyright (c) Fluigent 2023.  All Rights Reserved.                 
*----------------------------------------------------------------------------
*                                                                            
* Title:   fgt_SDK.h                                                         
* Purpose: Functions API for Fluigent instruments                            
* Version: 23.0.0.0
* Date:	05/2023
*============================================================================*/

#ifndef _FGT_SDK_H
#define _FGT_SDK_H

// Generic helper definitions for shared library support
#if defined _WIN32 || defined __CYGWIN__
	#define FGT_DLL_IMPORT __declspec(dllimport) __stdcall
	#define FGT_DLL_EXPORT __declspec(dllexport)
#else
	#if __GNUC__ >= 4
		#define FGT_DLL_IMPORT __attribute__ ((visibility ("default")))
		#define FGT_DLL_EXPORT __attribute__ ((visibility ("default")))
	#else
		#define FGT_DLL_IMPORT
		#define FGT_DLL_EXPORT
	#endif
#endif

#ifdef FGTSDK_EXPORTS // defined if we are building the library (instead of using it)
#define FGT_API FGT_DLL_EXPORT
#else
#define FGT_API FGT_DLL_IMPORT
#endif


#ifdef __cplusplus
extern "C"
{
#endif

	/*============================================================================*/
	/*----------------------------  Types definition  ----------------------------*/
	/*============================================================================*/

#ifndef STRING_MAX_SIZE
#define STRING_MAX_SIZE 140
#endif

#if defined(__cplusplus)
	/** @Description Returned error codes from dll functions */
	enum class fgt_ERROR_CODE
	{							
		OK,								/** No error */
		USB_error,						/** USB communication error */
		Wrong_command,					/** Wrong command was sent */
		No_module_at_index,				/** There is no module initialized at selected index */
		Wrong_module,					/** Wrong module was selected, unavailable feature */
		Module_is_sleep,				/** Module is in sleep mode, orders are not taken into account */
		Master_error,					/** Controller error */
		Failed_init_all_instr,			/** Some instruments failed to initialize */
		Wrong_parameter,				/** Function parameter is not correct or out of the bounds*/
		Overpressure,					/** Pressure module is in overpressure protection */
		Underpressure,					/** Pressure module is in underpressure protection */
		No_instr_found,					/** No Fluigent instrument was found */
		No_modules_found,				/** No Fluigent pressure or sensor module was found */
		No_pressure_controller_found,	/** No Fluigent pressure controller was found */
		Calibrating,					/** Pressure or sensor module is calibrating, read value may be incorrect */
		Dll_dependency_error,			/** Some dependencies are not found */
		Processing						/** M-Switch is still turning */
	};

	/** @Description Instrument controller type */
	enum class fgt_INSTRUMENT_TYPE { None, MFCS, MFCS_EZ, FRP, LineUP, IPS, ESS, F_OEM, CFU, NIFS };

	/** @Description Sensor type */
	enum class fgt_SENSOR_TYPE { 
		None, 
		Flow_XS_single, Flow_S_single, Flow_S_dual, Flow_M_single, Flow_M_dual, Flow_L_single, Flow_L_dual, Flow_XL_single, 
		Pressure_S, Pressure_M, Pressure_XL,
		Flow_M_plus_dual, Flow_L_plus_dual,
		Flow_L_CFU, Flow_L_NIFS,
	};

	/** @Description Sensor calibration table */
	enum class fgt_SENSOR_CALIBRATION { None, H2O, IPA, HFE, FC40, OIL };

	/** @Description Power state */
	enum class fgt_POWER { POWER_OFF, POWER_ON, SLEEP };

	/** @Description TTL setting mode */
	enum class fgt_TTL_MODE { DETECT_RISING_EDGE, DETECT_FALLING_EDGE, OUTPUT_PULSE_LOW, OUTPUT_PULSE_HIGH };

	/** @Description Link module type */
	enum class fgt_LINK_MODULE { None, FlowEZ, PSwitch = 3, SwitchEZ = 4 };

	/** @Description Valve type */
	enum class fgt_VALVE_TYPE { None, MSwitch, TwoSwitch, LSwitch, PSwitch, M_X, Two_X, L_X, Bypass };

	/** @Description Switch direction type */
	enum class fgt_SWITCH_DIRECTION { Shortest, Anticlockwise, Clockwise };

	using fgt_instrument_t = fgt_INSTRUMENT_TYPE;
	using fgt_sensor_t = fgt_SENSOR_TYPE;
	using fgt_valve_t = fgt_VALVE_TYPE;
	using fgt_ttl_mode_t = fgt_TTL_MODE;
	using fgt_calibration_t = fgt_SENSOR_CALIBRATION;
	using fgt_switch_direction_t = fgt_SWITCH_DIRECTION;
#else
	typedef int fgt_instrument_t;
	typedef int fgt_sensor_t;
	typedef int fgt_valve_t;
	typedef int fgt_ttl_mode_t;
	typedef int fgt_calibration_t;
	typedef int fgt_switch_direction_t;
#endif

	/** @Description Structure containing pressure or sensor identification and details */
typedef struct
{
	/** Serial number of this channel's controller */
	unsigned short ControllerSN; 
	/** Firmware version of this channel in BCD (0 if not applicable) */
	unsigned short firmware;
	/** Serial number of this channel (0 if not applicable) */
	unsigned short DeviceSN;
	/** Position on controller */
	unsigned int position;
	/** Channel index within its physical quantities family */
	unsigned int index;
	/** Unique channel identifier */
	unsigned int indexID;
	/** Type of the instrument */
	fgt_instrument_t InstrType;
} fgt_CHANNEL_INFO;

/** @Description Structure containing controller identification and details */
typedef struct
{
	/** Serial number */
	unsigned short SN;
	/** Firmware version in BCD */
	unsigned short Firmware;
	/** Index */
	unsigned int id;
	/** Instrument type */
	fgt_instrument_t InstrType;
} fgt_CONTROLLER_INFO;

	/*============================================================================*/
	/*-------------------------------  Init/close  -------------------------------*/
	/*============================================================================*/

	/**
	 * @Description Initialize or reinitialize (if already opened) Fluigent SDK instance. All detected Fluigent instruments (MFCS, MFCS-EZ, FRP, LineUP, IPS, ESS) are initialized.
	 * This function is optional, directly calling a function will automatically creates the instance.
	 * Only one instance can be opened at a time. If called again, any new instruments are added to the same instance.
	 * @param void
	 * @return fgt_ERROR_CODE
	 * @see fgt_close
	 * @see fgt_initEx
	 */
	unsigned char FGT_API fgt_init(void);

	/**
	 * @Description Close communication with Fluigent instruments and free memory.
	 * This function is mandatory, if not called the dll will will generate an exception will generate an exceptiongenerate an exception when exiting your application.
	 * Using this function will remove session preferences such as units and limits. If any regulation is running it will stop pressure control.
	 */
	unsigned char FGT_API fgt_close(void);


	/**
	 * @Description Detects all connected Fluigent instrument(s), return their serial number and type
	 * @param [SN]: Array of controllers serial number. This is a 256 pre-allocated table tailed with 0's when no instrument
	 * @param [InstrType] : fgt_INSTRUMENT_TYPE. This is a 256 pre-allocated table tailed with 'None' value when no instrument
	 * @return total number of detected instruments
	 * @see fgt_initEx for specific initialization
	 */
	unsigned char FGT_API fgt_detect(unsigned short SN[256], int type[256]);

	/**
	 * @Description Initialize specific Fluigent instrument(s) from their unique serial number. This function can be used when multiple instruments are connected in order to select your device(s)
	 * @param [SN] Array of controllers serial number
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_initEx(unsigned short SN[256]);

	/**
	 * @Description Creates a simulated Fluigent instrument, which can be detected and initialized like a real one, for the purposes
	 * of testing and demonstrations.
	 * @param [type] Type of instrument to simulate
	 * @param [serial] Serial number for the simulated instrument
	 * @param [version] Firmware version for the simulated instrument. Set to 0 to use the default version
	 * @param [config] Array describing the instrument's configuration
	 * @param [length] Length of the config array
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_create_simulated_instr(fgt_instrument_t type, unsigned short serial, unsigned short version, int* config, int length);

	/**
	 * @Description Removes a simulated instrument that had been previously created. If it had already been initialized by the SDK,
	 * the controller and channels will remain in the respective lists, but they will act as if the instrument is missing. This is
	   equivalent to physically disconnecting a real instrument.
	 * @param [type] Type of instrument to remove
	 * @param [serial] Serial number of the simulated instrument
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_remove_simulated_instr(fgt_instrument_t type, unsigned short serial);

	/*============================================================================*/
	/*-----------------------------  Channels info  ------------------------------*/
	/*============================================================================*/

	/**
	 * @Description Retrieve information about session controllers. Controllers are MFCS, Flowboard, Link, IPS in an array.
	 * @out [info] Array of structure of fgt_CONTROLLER_INFO
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_get_controllersInfo(fgt_CONTROLLER_INFO info[256]);

	/**
	 * @Description Get total number of initialized pressure channels. It is the sum of all MFCS, MFCS-EZ and FlowEZ pressure controllers
	 * @param *nbPChan Total number of initialized pressure channels
	 * @see fgt_get_pressureChannelsInfo array size is equal to nbPChan
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_get_pressureChannelCount(unsigned char* nbPChan);

	/**
	 * @Description Get total number of initialized sensor channels. It is the sum of all connected flow-units on Flowboard and FlowEZ, and IPS sensors.
	 * @param *nbQChan Total number of initialized sensor channels
	 * @return fgt_ERROR_CODE
	 * @see fgt_get_sensorChannelsInfo array size is equal to nbSChan
	 */
	unsigned char FGT_API fgt_get_sensorChannelCount(unsigned char* nbSChan);


	/**
	 * @Description Get total number of initialized TTL channels. It is the sum of all connected Link TTL ports
	 * @param *nbTtlChan Total number of initialized TTL channels
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_get_TtlChannelCount(unsigned char* nbTtlChan);

	/**
	 * @Description Get total number of initialized valve channels
	 * @param *nbTtlChan Total number of initialized valve channels
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_get_valveChannelCount(unsigned char* nbValveChan);

	/**
	 * @Description: Retrieve information about each initialized pressure channel. This function is useful in order to get channels order, controller, unique ID and intrument type.
	 * By default this array is built with MFCS first, MFCS-EZ second and FlowEZ last. If only one instrument is used, index is the default channel indexing starting at 0.
	 * You can initialize instruments in specific order using fgt_initEx function
	 * @param info Array of structure of fgt_CHANNEL_INFO
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_get_pressureChannelsInfo(fgt_CHANNEL_INFO info[256]);

	/**
	 * @Description: Retrieve information about each initialized sensor channel. This function is useful in order to get channels order, controller, unique ID and instrument type.
	 * By default this array is built with FRP Flow Units first, followed by Flow EZ Flow Units, followed by IPS modules. If only one instrument is used, index is the default channel indexing starting at 0.
	 * You can initialize instruments in specific order using fgt_initEx function
	 * @param info Array of structure of fgt_CHANNEL_INFO 
	 * @param sensorType Array of fgt_SENSOR_TYPE
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_get_sensorChannelsInfo(fgt_CHANNEL_INFO info[256], fgt_sensor_t sensorType[256]);

	/**
	 * @Description: Retrieve information about each initialized TTL channel. This function is useful in order to get channels order, controller, unique ID and instrument type.
	 * TTL channels are only available for LineUP Series, 2 ports for each connected Link
	 * @param info Array of structure of fgt_CHANNEL_INFO 
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_get_TtlChannelsInfo(fgt_CHANNEL_INFO info[256]);

	/**
	 * @Description: Retrieve information about each initialized valve channel. This function is useful in order to get channels order, controller, unique ID and instrument type.
	 * By default this array is built with LineUp valves first (connected to SwitchEz or P-Switch) followed by ESS Switchboard valves. If only one instrument is used, index is the default channel indexing starting at 0.
	 * You can initialize instruments in specific order using fgt_initEx function
	 * @param info Array of structure of fgt_CHANNEL_INFO
	 * @param valveType Array of fgt_VALVE_TYPE
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_get_valveChannelsInfo(fgt_CHANNEL_INFO info[256], fgt_valve_t valveType[256]);


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
	unsigned char FGT_API fgt_set_pressure(unsigned int pressureIndex, float pressure);

	/**
	 * @Description Read pressure value of selected device
	 * @param pressureIndex Index of pressure channel or unique ID
	 * @out *pressure Read pressure measurement value in selected unit, default is "mbar"
	 * @return errorCode
	 * @see fgt_get_pressureEx
	 * @see fgt_get_pressureStatus
	 */
	unsigned char FGT_API fgt_get_pressure(unsigned int pressureIndex, float* pressure);

	/**
	 * @Description Read pressure value and time stamp of selected device. Time stamp is the device internal timer.
	 * @param pressureIndex Index of pressure channel or unique ID
	 * @out *pressure Read pressure measurement value in selected unit, default is "mbar"
	 * @out *timeStamp Hardware timer in ms
	 * @return fgt_ERROR_CODE
	 * @see fgt_get_pressure
	 * @see fgt_get_pressureStatus
	 */
	unsigned char FGT_API fgt_get_pressureEx(unsigned int pressureIndex, float* pressure, unsigned short* timeStamp);

	/**
	 * @Description Start closed loop regulation between a flowrate sensor and a pressure controller. Pressure will be regulated in order to reach sensor setpoint.
	 * Call again this function in order to change the setpoint. Calling fgt_set_pressure on same pressureIndex will stop regulation. 
	 * @param sensorIndex Index of sensor channel or unique ID
	 * @param pressureIndex Index of pressure channel or unique ID
	 * @param setpoint Regulation value to be reached in selected unit, default is "µl/min" for flowrate sensors
	 * @return fgt_ERROR_CODE
	 * @see fgt_set_pressure
	 * @see fgt_set_customSensorRegulation
	 * @see fgt_set_sensorRegulationResponse
	 */
	unsigned char FGT_API fgt_set_sensorRegulation(unsigned int sensorIndex, unsigned int pressureIndex, float setpoint);

	/**
	 * @Description Read sensor value of selected device
	 * @param sensorIndex Index of sensor channel or unique ID
	 * @out value Read sensor value in selected unit, default is "µl/min" for flowrate sensors and 'mbar' for pressure sensors
	 * @return fgt_ERROR_CODE
	 * @see fgt_get_sensorStatus
	 */
	unsigned char FGT_API fgt_get_sensorValue(unsigned int sensorIndex, float* value);

	/**
	 * @Description Read flowrate sensor value and timestamp of selected device. Time stamp is the device internal timer.
	 * @param sensorIndex Index of sensor channel or unique ID
	 * @out value Read sensor value in selected unit, default is "µl/min" for flowrate sensors
	 * @out timeStamp Hardware timer in ms
	 * @return fgt_ERROR_CODE
	 * @see fgt_get_sensorStatus
	 */
	unsigned char FGT_API fgt_get_sensorValueEx(unsigned int sensorIndex, float* value, unsigned short* timeStamp);

	/**
	 * @Description Read the flag indicating whether the flow rate sensor detects an air bubble. Only 
		available on Flow Unit sensor ranges M+ and L+.
	 * @param sensorIndex Index of sensor channel or unique ID
	 * @out detected 1 if an air bubble was detected, 0 otherwise.
	 * @return fgt_ERROR_CODE
	 * @see fgt_get_sensorStatus
	 */
	unsigned char FGT_API fgt_get_sensorAirBubbleFlag(unsigned int sensorIndex, unsigned char* detected);

	/**
	 * @Description Read the position of a specific valve channel.
	 * @param valveIndex Index of valve channel
	 * @out position Valve position
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_get_valvePosition(unsigned int valveIndex, int* position);

	/**
	 * @Description Set the position of a specific valve channel.
	 * @param valveIndex Index of valve channel
	 * @param position Desired valve position
	 * @param direction Direction of the movement (applies only for M-Switch valve type)
	 * @param wait Flag indicating if function should wait until the desired position is reached or not
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_set_valvePosition(unsigned int valveIndex, int position, fgt_switch_direction_t direction, int wait);

	/**
	 * @Description Set the position of a all two positional valves connected to specified controller / module.
	 * @param controllerIndex Index of the controller (supported only by LineUp and ESS)
	 * @param moduleIndex Index of the module (supported only by P-Switch)
	 * @param position Desired position (0 or 1)
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_set_allValves(unsigned int controllerIndex, unsigned int moduleIndex, int position);


	/*============================================================================*/
	/*--------------------   Unit, calibration and limits  -----------------------*/
	/*============================================================================*/
	/**
	 * @Description Set pressure unit for all initialized channels, default value is "mbar". If type is invalid an error is returned.
	 * Every pressure read value and sent command will then use this unit.
	 * Example: "mbar", "millibar", "kPa" ...
	 * @param unit Array of char containing a unit string
	 * @return fgt_ERROR_CODE
	 * @see fgt_get_pressureStatus
	 */
	unsigned char FGT_API fgt_set_sessionPressureUnit(char unit[STRING_MAX_SIZE]);

	/**
	 * @Description Set pressure unit on selected pressure device, default value is "mbar". If type is invalid an error is returned.
	 * Every pressure read value and sent command will then use this unit.
	 * Example: "mbar", "millibar", "kPa" ...
	 * @param presureIndex Index of pressure channel or unique ID
	 * @param unit[] Array of char containing a unit string
	 * @return fgt_ERROR_CODE
	 * @see fgt_get_pressureStatus
	 */
	unsigned char FGT_API fgt_set_pressureUnit(unsigned int presureIndex, char unit[STRING_MAX_SIZE]);

	/**
	 * @Description Get current unit on selected pressure device, default value is "mbar".
	 * Every pressure read value and sent command use this unit.
	 * @param pressureIndex Index of pressure channel or unique ID
	 * @out unit[] Array of char containing a unit string
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_get_pressureUnit(unsigned int pressureIndex, char unit[STRING_MAX_SIZE]);

	/**
	 * @Description Set sensor unit on selected sensor device, default value is "µl/min" for flowrate sensors and "mbar" for pressure sensors. If type is invalid an error is returned.
	 * Every sensor read value and regulation command will then use this unit. 
	 * Example: "µl/h", "ulperDay", "microliter/hour" ...
	 * @param sensorIndex Index of sensor channel or unique ID
	 * @param unit[] Array of char containing a unit string
	 * @return fgt_ERROR_CODE
	 * @see fgt_set_sensorStatus
	 */
	unsigned char FGT_API fgt_set_sensorUnit(unsigned int sensorIndex, char unit[STRING_MAX_SIZE]);

	/**
	 * @Description Get current unit on selected sensor device, default value is "µl/min" for flowunits and 'mbar' for pressure sensors.
	 * Every sensor read value and regulation command use this unit.
	 * @param sensorIndex Index of sensor channel or unique ID
	 * @out unit[] Array of char containing a unit string
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_get_sensorUnit(unsigned int sensorIndex, char unit[STRING_MAX_SIZE]);

	/**
	 * @Description Set sensor internal calibration table. Function is only available for IPS (to set new reference value "zero") and specific flowrate sensors (dual type) such as the flow-unit M accepting H2O and IPA
	 * @param sensorIndex Index of sensor channel or unique ID
	 * @param calibration fgt_SENSOR_CALIBRATION
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_set_sensorCalibration(unsigned int sensorIndex, fgt_calibration_t calibration);

	/**
	 * @Description Get sensor's current calibration table. Only applicable to Flow Unit sensors.
	 * @param sensorIndex Index of sensor channel or unique ID
	 * @out *calibration fgt_SENSOR_CALIBRATION
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_get_sensorCalibration(unsigned int sensorIndex, fgt_calibration_t* calibration);

	/**
	 * @Description Apply a custom scale factor on sensor read value. This function is useful in order to adapt read sensor value to physical measurement.
	 * For example if a flow-unit is used with a special oil and it's calibration table is set to H2O, read flowrate is not correct.
	 * Scale factor is applied using following formula: scaled_value = a*sensor_value + b*sensor_value^2 + c*sensor_value^3
	 * Note that this scale is also used for the regulation. Only applicable to Flow Unit sensors.
	 * @param sensorIndex Index of sensor channel or unique ID
	 * @param float a proportional multiplier value
	 * @param float b square multiplier value
	 * @param float c cubic multiplier value
	 * @return fgt_ERROR_CODE
	 * @see fgt_set_sensorCustomScaleEx
	 */
	unsigned char FGT_API fgt_set_sensorCustomScale(unsigned int sensorIndex, float a, float b, float c);

	/**
	 * @Description Apply a custom scale factor on flowrate sensor measurement. This function is useful in order to adapt read sensor value to physical measurement.
	 * For example if a flow-unit is used with a special oil and it's calibration table is set to H2O, read flowrate is not correct.
	 * Scale factor is applied using following formula: scaled_value = a*sensor_value + b*sensor_value^2 + c*sensor_value^3
	 * When applying a custom scale factor, sensor range may increase very rapidly, SMax parameter is meant to limit this maximal value.
	 * This function purpose is to be used with the regulation in order to avoid too high maximum range on the sensor. Only applicable to Flow Unit sensors.
	 * @param sensorIndex Index of sensor channel or unique ID
	 * @param float a proportional multiplier value
	 * @param float b square multiplier value
	 * @param float c cubic multiplier value
	 * @param float SMax after scale maximal value (saturation)
	 * @return fgt_ERROR_CODE
	 * @see fgt_set_sensorCustomScale
	 */
	unsigned char FGT_API fgt_set_sensorCustomScaleEx(unsigned int sensorIndex, float a, float b, float c, float SMax);

	/**
	 * @Description Calibrate internal pressure sensor depending on atmospheric pressure. After calling this function 0 pressure value corresponds to atmospheric pressure.
	 * During calibration step no pressure order is accepted. Total duration vary from 3s to 8s.
	 * @param pressureIndex Index of pressure channel or unique ID
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_calibratePressure(unsigned int pressureIndex);


	/**
	 * @Description Start closed loop regulation between a sensor and a pressure controller. Pressure will be regulated in order to reach sensor setpoint.
	 * Custom sensors, outside Fluigent ones, can be used such as different flow-units, pressure, level ... 
	 * However we do not guarantee full compatibility with all sensors. Regulation quality is linked to sensor precision and your set-up.
	 * In order to use this function, custom used sensor maximum range and measured values has to be updated at least once per second.
	 * Directly setting pressure on same pressureIndex will stop regulation.
	 * This function must be called at least once per second to update the sensor measurement,
	 * or the regulation will stop.
	 * @param measure custom sensor measured value, no unit is required
	 * @param setpoint custom sensor regulation goal value, no unit is required
	 * @param pressureIndex Index of pressure channel or unique ID
	 * @param maxSensorRange custom sensor maximum range, no unit is required
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_set_customSensorRegulation(float measure, float setpoint, float maxSensorRange, unsigned int pressureIndex);

	/**
	 * @Description Get pressure controller minimum and maximum range. Returned values takes into account set unit, default value is 'mbar'.
	 * @param pressureIndex Index of pressure channel or unique ID
	 * @out Pmin minim device pressure
	 * @out Pmax maximum device pressure
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_get_pressureRange(unsigned int pressureIndex, float* Pmin, float* Pmax);

	/**
	 * @Description Get sensor minimum and maximum range. Returned values takes into account set unit, default value is 'µl/min' in case of Flow Units and 'mbar' for pressure sensors.
	 * @param sensorIndex Index of sensor channel or unique ID
	 * @out Smin minimum measured sensor value
	 * @out Smax maximum measured sensor value
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_get_sensorRange(unsigned int sensorIndex, float* Smin, float* Smax);

	/**
	 * @Description Get valve maximum position. Position indexing starts at 0.
	 * @param valveIndex Index of valve channel
	 * @out posMax Maximum position of this valve
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_get_valveRange(unsigned int valveIndex, int* posMax);

	/**
	 * @Description Set pressure working range and ensure that pressure will never exceed this limit. It takes into account current unit, default value is 'mbar'.
	 * This function is useful to protect your microfluidic system.
	 * @param pressureIndex Index of pressure channel or unique ID
	 * @param PlimMin minimum admissible device pressure
	 * @param PlimMax maximum admissible device pressure
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_set_pressureLimit(unsigned int pressureIndex, float PlimMin, float PlimMax);

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
	unsigned char FGT_API fgt_set_sensorRegulationResponse(unsigned int sensorIndex, unsigned int responseTime);

	/**
	 * @Description Set pressure controller response. This function can be used to customise response time for your set-up.
	 * For FlowEZ available values are 0: use of fast switch valves or 1: do not use fast switch valves. Default value is 0.
	 * For MFCS available values are from 1 to 255. Higher the value, longer is the response time. Default value is 5.
	 * @param pressureIndex Index of pressure channel or unique ID
	 * @param value desired pressure controller response time, this depends on controller type
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_set_pressureResponse(unsigned int pressureIndex, unsigned char value);

	/*============================================================================*/
	/*------------------------   Status information   ----------------------------*/
	/*============================================================================*/

	/**
	 * @Description Get detailed information of pressure channel status. This function is meant to be invoked after calling a pressure related function which returns an error code.
	 * Retrieved information of last error contains controller position and a string detail.
	 * @param pressureIndex Index of pressure channel or unique ID
	 * @out type fgt_INSTRUMENT_TYPE, controller type
	 * @out controllerSN serial number of controller (such as Link, MFCS) 
	 * @out information information status code, 1 if pressure module is controller locally
	 * @out detail array of characters which details the error
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_get_pressureStatus(unsigned int pressureIndex, fgt_instrument_t* type, unsigned short* controllerSN, unsigned char* infoCode, char detail[STRING_MAX_SIZE]);

	/**
	 * @Description Get detailed information of sensor status. This function is meant to be invoked after calling a sensor related function which returns an error code.
	 * Retrieved information of last error contains sensor position and a string detail.
	 * @param sensorIndex Index of sensor channel or unique ID
	 * @out InstrType fgt_INSTRUMENT_TYPE, controller type
	 * @out controllerSN serial number of controller (such as Link, Flowboard)
	 * @out information information status code when regulating 0: No regulation; 1: Regulating; otherwise regulation might not be optimal
	 * @out detail array of characters which details the error
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_get_sensorStatus(unsigned int sensorIndex, fgt_instrument_t* type, unsigned short* controllerSN, unsigned char* infoCode, char detail[STRING_MAX_SIZE]);

	/**
	 * @Description Set power ON or OFF on a controller (such as Link, MFCS, Flowboard). 
	 * Not all controllers support this functionality.
	 * @param controllerIndex Index of controller or unique ID
	 * @param powerState fgt_POWER
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_set_power(unsigned int controllerIndex, unsigned char powerState);

	/**
	 * @Description Get power information about a controller (such as Link, MFCS, Flowboard). 
	 * Not all controllers support this functionality.
	 * @param controllerIndex Index of controller or unique ID
	 * @out powerState fgt_POWER
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_get_power(unsigned int controllerIndex, unsigned char* powerState);


	/*============================================================================*/
	/*-----------------------------  TTL functions  ------------------------------*/
	/*============================================================================*/

	/**
	 * @Description Configure a specific TTL port (BNC ports) as input, output, rising or falling edge.
	 * @param TtlIndex Index of TTL port or unique ID
	 * @param mode fgt_TTL_MODE
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_set_TtlMode(unsigned int TtlIndex, fgt_ttl_mode_t mode);

	/**
	 * @Description Read TTL port (BNC port) if set as input.
	 * @param TtlIndex Index of TTL port or unique ID
	 * @out state 0: no edge was detected; 1: an edge is detected
	 * @return fgt_ERROR_CODE
	 * @see fgt_set_TtlMode
	 */
	unsigned char FGT_API fgt_read_Ttl(unsigned int TtlIndex, unsigned int* state);

	/**
	 * @Description Trigger a specific TTL port (BNC ports) if set as output.
	 * @param TtlIndex Index of TTL port or unique ID
	 * @return fgt_ERROR_CODE
	 * @see fgt_set_TtlMode
	 */
	unsigned char FGT_API fgt_trigger_Ttl(unsigned int TtlIndex);


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
	unsigned char FGT_API fgt_set_purge(unsigned int controllerIndex, unsigned char purge);

	/**
	 * @Description Manually set the voltage of the pressure channel's input solenoid valve.
	 * This stops pressure regulation.
	 * @param pressureIndex Index of pressure channel or unique ID
	 * @param value applied valve voltage from 0 to 100(%)
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_set_manual(unsigned int pressureIndex, float value);

	/**
	 * @Description Set the digital output ON or OFF on a controller
	 * This feature is only available on the F-OEM device.
	 * @param controllerIndex Index of controller or unique ID
	 * @param port Address of the digital output to toggle. For F-OEM: 0: Pump, 1: LED
	 * @param state 0: OFF, 1:ON
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_set_digitalOutput(unsigned int controllerIndex, unsigned char port, unsigned char state);

	/**
	 * @Description Returns the pressure measured at the device's inlet.
	 * This feature is only available on LineUP Flow EZ and FOEM Pressure Module instruments.
	 * @param pressureIndex Index of pressure channel or unique ID
	 * @out pressure Inlet pressure value in selected unit, default is "mbar"
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_get_inletPressure(unsigned int pressureIndex, float* pressure);
	/**
	 * @Description Returns the range of the differential pressure sensor in mbar
	 * This feature is only available on NIFS devices.
	 * @param sensorIndex Index of sensor or unique ID
	 * @out Pmin minimum differential pressure in mbar
	 * @out Pmax maximum differential pressure in mbar
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_get_differentialPressureRange(unsigned int sensorIndex, float* Pmin, float* Pmax);

	/**
	 * @Description Returns the current differential pressure measurement in mbar
	 * This feature is only available on NIFS devices.
	 * @param sensorIndex Index of sensor or unique ID
	 * @out Pdiff differential pressure in mbar
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_get_differentialPressure(unsigned int sensorIndex, float* Pdiff);

	/**
	 * @Description Returns the range of the absolute pressure sensor in mbar
	 * This feature is only available on NIFS devices.
	 * @param sensorIndex Index of sensor or unique ID
	 * @out Pmin minimum absolute pressure in mbar
	 * @out Pmax maximum absolute pressure in mbar
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_get_absolutePressureRange(unsigned int sensorIndex, float* Pmin, float* Pmax);

	/**
	 * @Description Returns the current absolute pressure measurement in mbar
	 * This feature is only available on NIFS devices.
	 * @param sensorIndex Index of sensor or unique ID
	 * @out Pabs absolute pressure in mbar
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_get_absolutePressure(unsigned int sensorIndex, float* Pabs);

	/**
	 * @Description Returns the current state of the bypass valve.
	 * This feature is only available on NIFS devices.
	 * @param sensorIndex Index of sensor or unique ID
	 * @out state 1 if the valve is open, 0 if it is closed.
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_get_sensorBypassValve(unsigned int sensorIndex, unsigned char* state);

	/**
	 * @Description Sets the state of the sensor's bypass valve.
	 * This feature is only available on NIFS devices.
	 * @param sensorIndex Index of sensor or unique ID
	 * @param state 1 to open, 0 to close.
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_set_sensorBypassValve(unsigned int sensorIndex, unsigned char state);

	/*============================================================================*/
	/*--------------------------------  Logging  ---------------------------------*/
	/*============================================================================*/

	/**
	 * @Description Sets the verbosity of the logging feature, i.e., how much data is logged.
	 * @param verbosity The amount of data to log. Set to 0 to disable logging (default).
	 * Set to 5 to log the maximum amount of data.
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_set_log_verbosity(unsigned int verbosity);

	/**
	 * @Description Sets how the SDK outputs the log entries.
	 * @param output_to_file Output log entries to a file in the current directory. 1 to enable, 0 to disable. Default: enabled.
	 * @param output_to_stderr Output log entries to the stderr pipe (console). 1 to enable, 0 to disable. Default: disabled.
	 * @param output_to_queue Store log entries in memory. They can be retrieved via the fgt_get_next_log function. 1 to enable, 0 to disable. Default: disabled.
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_set_log_output_mode(unsigned char output_to_file, unsigned char output_to_stderr, unsigned char output_to_queue);

	/**
	 * @Description Returns the next log entry stored in memory, if any, and removes it from the queue.
	 * Will return an error if the queue is empty. Logs are only stored in memory if the corresponding option is set with the
	 * fgt_set_log_output_mode function. Call this function repeatedly until an error is returned to retrieve all log entries.
	 * @param log char array provided by the user, on which the log string will be copied.
	 *  Must have at least 2000 bytes of available space.
	 * @return fgt_ERROR_CODE
	 */
	unsigned char FGT_API fgt_get_next_log(char log[2000]);


#ifdef __cplusplus
}
#endif

#endif //_FGT_SDK_H

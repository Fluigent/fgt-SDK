/*============================================================================
*                   Fluigent Software Developement Kit                       
*----------------------------------------------------------------------------
*         Copyright (c) Fluigent 2019.  All Rights Reserved.                 
*----------------------------------------------------------------------------
*                                                                            
* Title:   fgt_SDK.h                                                         
* Purpose: Functions API for Fluigent instruments                            
* Version: 19.0.0.0                                                          
* Date:	06/2019															  
*============================================================================*/

#ifndef _FGT_SDK_H
#define _FGT_SDK_H

#ifdef __cplusplus
extern "C"
{
#endif

	/*============================================================================*/
	/*----------------------------  Types definition  ----------------------------*/
	/*============================================================================*/

	/** @Description Returned error codes from dll functions */
	enum class fgt_ERROR_CODE
	{							/** No error */
		OK,						/** USB communication error */
		USB_error,				/** Wrong command was sent */
		Wrong_command,			/** There is no module initialized at selected index */
		No_module_at_index,		/** Wrong module was selected, unavailable feature */
		Wrong_module,			/** Module is in sleep mode, orders are not taken into account */
		Module_is_sleep,		/** Controller error */
		Master_error,			/** Some instruments failed to initialize */
		Failed_init_all_instr,	/** Function parameter is not correct or out of the bounds*/
		Wrong_parameter,		/** Pressure module is in overpressure protection */
		Overpressure,			/** Pressure module is in underpressure protection */
		Underpressure,			/** No Fluigent instrument was found */
		No_instr_found,			/** No Fluigent pressure or sensor module was found */
		No_modules_found,		/** No Fluigent pressure controller was found */
		No_pressure_controller_found,		/** Pressure or sensor module is calibrating, read value may be incorrect */
		Calibrating,			/** Some dependencies are not found */
		Dll_dependency_error
	};

	/** @Description Instrument controller type */
	enum class fgt_INSTRUMENT_TYPE { None, MFCS, MFCS_EZ, FRP, LineUP };

	/** @Description Sensor type */
	enum class fgt_SENSOR_TYPE { None, Flow_XS_single, Flow_S_single, Flow_S_dual, Flow_M_single, Flow_M_dual, Flow_L_single, Flow_L_dual, Flow_XL_single };

	/** @Description Sensor calibration table */
	enum class fgt_SENSOR_CALIBRATION { None, H2O, IPA, HFE, FC40, OIL };

	/** @Description Power state */
	enum class fgt_POWER { POWER_OFF, POWER_ON, SLEEP };

	/** @Description TTL setting mode */
	enum class fgt_TTL_MODE { DETECT_RISING_EDGE, DETECT_FALLING_EDGE, OUTPUT_PULSE_LOW, OUTPUT_PULSE_HIGH };

	/** @Description Structure containing pressure or sensor identification and details */
	struct fgt_CHANNEL_INFO
	{
		/** Serial number of this channel's controller */
		unsigned short ControllerSN; 
		/** Firmware version of this channel (0 if not applicable) */
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
		fgt_INSTRUMENT_TYPE InstrType;
	};

	/** @Description Structure containing controller identification and details */
	struct fgt_CONTROLLER_INFO
	{
		/** Serial number */
		unsigned short SN;
		/** Firmware version */
		unsigned short Firmware;
		/** Index */
		unsigned int id;
		/** Instrument type */
		fgt_INSTRUMENT_TYPE InstrType;
	};

	/*============================================================================*/
	/*-------------------------------  Init/close  -------------------------------*/
	/*============================================================================*/

	/**
	 * @Description Initialize or reinitialize (if already opened) Fluigent SDK instance. All detected Fluigent instruments (MFCS, MFCS-EZ, FRP, LineUP) are initialized.
	 * This function is optional, directly calling a function will automatically creates the instance.
	 * Only one instance can be opened at once. If called again, session is reinitialized.
	 * @param void
	 * @return fgt_ERROR_CODE
	 * @see fgt_close
	 * @see fgt_initEx
	 */
	unsigned char __stdcall fgt_init(void);

	/**
	 * @Description Close communication with Fluigent instruments and free memory.
	 * This function is mandatory, if not called the dll will will generate an exception will generate an exceptiongenerate an exception when exiting your application.
	 * Using this function will remove session preferences such as units and limits. If any regulation is running it will stop pressure control.
	 */
	unsigned char __stdcall fgt_close(void);


	/**
	 * @Description Detects all connected Fluigent instrument(s), return their serial number and type
	 * @param [SN]: Array of controllers serial number. This is a 256 pre-allocated table tailed with 0's when no instrument
	 * @param [InstrType] : fgt_INSTRUMENT_TYPE. This is a 256 pre-allocated table tailed with 'None' value when no instrument
	 * @return total number of detected instruments
	 * @see fgt_initEx for specific initialization
	 */
	unsigned char __stdcall fgt_detect(unsigned short SN[256], int type[256]);

	/**
	 * @Description Initialize specific Fluigent instrument(s) from their unique serial number. This function can be used when multiple instruments are connected in order to select your device(s)
	 * @param [SN] Array of controllers serial number
	 * @return fgt_ERROR_CODE
	 */
	unsigned char __stdcall fgt_initEx(unsigned short SN[256]);


	/*============================================================================*/
	/*-----------------------------  Channels info  ------------------------------*/
	/*============================================================================*/

	/**
	 * @Description Retrieve information about session controllers. Controllers are MFCS, Flowboard, Link in an array.
	 * @out [info] Array of structure of fgt_CONTROLLER_INFO
	 * @return fgt_ERROR_CODE
	 */
	unsigned char __stdcall fgt_get_controllersInfo(fgt_CONTROLLER_INFO info[256]);

	/**
	 * @Description Get total number of initialized pressure channels. It is the sum of all MFCS, MFCS-EZ and FlowEZ pressure controllers
	 * @param *nbPChan Total number of initialized pressure channels
	 * @see fgt_get_pressureChannelsInfo array size is equal to nbPChan
	 * @return fgt_ERROR_CODE
	 */
	unsigned char __stdcall fgt_get_pressureChannelCount(unsigned char* nbPChan);

	/**
	 * @Description Get total number of initialized sensor channels. It is the sum of all connected flow-units on Flowboard and FlowEZ
	 * @param *nbQChan Total number of initialized sensor channels
	 * @return fgt_ERROR_CODE
	 * @see fgt_get_sensorChannelsInfo array size is equal to nbSChan
	 */
	unsigned char __stdcall fgt_get_sensorChannelCount(unsigned char* nbSChan);


	/**
	 * @Description Get total number of initialized TTL channels. It is the sum of all connected Link TTL ports
	 * @param *nbTtlChan Total number of initialized TTL channels
	 * @return fgt_ERROR_CODE
	 */
	unsigned char __stdcall fgt_get_TtlChannelCount(unsigned char* nbTtlChan);

	/**
	 * @Description: Retrieve information about each initialized pressure channel. This function is useful in order to get channels order, controller, unique ID and intrument type.
	 * By default this array is built with MFCS first, MFCS-EZ second and FlowEZ last. If only one instrument is used, index is the default channel indexing starting at 0.
	 * You can initialize instruments in specific order using fgt_initEx function
	 * @param info Array of structure of fgt_CHANNEL_INFO
	 * @return fgt_ERROR_CODE
	 */
	unsigned char __stdcall fgt_get_pressureChannelsInfo(fgt_CHANNEL_INFO info[256]);

	/**
	 * @Description: Retrieve information about each initialized sensor channel. This function is useful in order to get channels order, controller, unique ID and instrument type.
	 * By default this array is built with FRP first then FlowEZ and contains flow-units. If only one instrument is used, index is the default channel indexing starting at 0.
	 * You can initialize instruments in specific order using fgt_initEx function
	 * @param info Array of structure of fgt_CHANNEL_INFO 
	 * @param sensorType Array of fgt_SENSOR_TYPE
	 * @return fgt_ERROR_CODE
	 */
	unsigned char __stdcall fgt_get_sensorChannelsInfo(fgt_CHANNEL_INFO info[256], int sensorType[256]);

	/**
	 * @Description: Retrieve information about each initialized TTL channel. This function is useful in order to get channels order, controller, unique ID and instrument type.
	 * TTL channels are only available for LineUP Series, 2 ports for each connected Link
	 * @param info Array of structure of fgt_CHANNEL_INFO 
	 * @return fgt_ERROR_CODE
	 */
	unsigned char __stdcall fgt_get_TtlChannelsInfo(fgt_CHANNEL_INFO info[256]);


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
	unsigned char __stdcall fgt_set_pressure(unsigned int pressureIndex, float pressure);

	/**
	 * @Description Read pressure value of selected device
	 * @param pressureIndex Index of pressure channel or unique ID
	 * @out *pressure Read pressure measurement value in selected unit, default is "mbar"
	 * @return errorCode
	 * @see fgt_get_pressureEx
	 * @see fgt_get_pressureStatus
	 */
	unsigned char __stdcall fgt_get_pressure(unsigned int pressureIndex, float* pressure);

	/**
	 * @Description Read pressure value and time stamp of selected device. Time stamp is the device internal timer.
	 * @param pressureIndex Index of pressure channel or unique ID
	 * @out *pressure Read pressure measurement value in selected unit, default is "mbar"
	 * @out *timeStamp Hardware timer in ms
	 * @return fgt_ERROR_CODE
	 * @see fgt_get_pressure
	 * @see fgt_get_pressureStatus
	 */
	unsigned char __stdcall fgt_get_pressureEx(unsigned int pressureIndex, float* pressure, unsigned short* timeStamp);

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
	unsigned char __stdcall fgt_set_sensorRegulation(unsigned int sensorIndex, unsigned int pressureIndex, float setpoint);

	/**
	 * @Description Read sensor value of selected device
	 * @param sensorIndex Index of sensor channel or unique ID
	 * @out value Read sensor value in selected unit, default is "µl/min" for flowrate sensors
	 * @return fgt_ERROR_CODE
	 * @see fgt_get_sensorStatus
	 */
	unsigned char __stdcall fgt_get_sensorValue(unsigned int sensorIndex, float* value);

	/**
	 * @Description Read sensor value and timestamp of selected device. Time stamp is the device internal timer.
	 * @param sensorIndex Index of sensor channel or unique ID
	 * @out value Read sensor value in selected unit, default is "µl/min" for flowrate sensors
	 * @out timeStamp Hardware timer in ms
	 * @return fgt_ERROR_CODE
	 * @see fgt_get_sensorStatus
	 */
	unsigned char __stdcall fgt_get_sensorValueEx(unsigned int sensorIndex, float* value, unsigned short* timeStamp);


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
	unsigned char __stdcall fgt_set_sessionPressureUnit(char unit[140]);

	/**
	 * @Description Set pressure unit on selected pressure device, default value is "mbar". If type is invalid an error is returned.
	 * Every pressure read value and sent command will then use this unit.
	 * Example: "mbar", "millibar", "kPa" ...
	 * @param presureIndex Index of pressure channel or unique ID
	 * @param unit[] Array of char containing a unit string
	 * @return fgt_ERROR_CODE
	 * @see fgt_get_pressureStatus
	 */
	unsigned char __stdcall fgt_set_pressureUnit(unsigned int presureIndex, char unit[140]);

	/**
	 * @Description Get current unit on selected pressure device, default value is "mbar".
	 * Every pressure read value and sent command use this unit.
	 * @param pressureIndex Index of pressure channel or unique ID
	 * @out unit[] Array of char containing a unit string
	 * @return fgt_ERROR_CODE
	 */
	unsigned char __stdcall fgt_get_pressureUnit(unsigned int pressureIndex, char unit[140]);

	/**
	 * @Description Set sensor unit on selected sensor device, default value is "µl/min" for flowunits. If type is invalid an error is returned.
	 * Every sensor read value and regulation command will then use this unit.
	 * Example: "µl/h", "ulperDay", "microliter/hour" ...
	 * @param sensorIndex Index of sensor channel or unique ID
	 * @param unit[] Array of char containing a unit string
	 * @return fgt_ERROR_CODE
	 * @see fgt_set_sensorStatus
	 */
	unsigned char __stdcall fgt_set_sensorUnit(unsigned int sensorIndex, char unit[140]);

	/**
	 * @Description Get current unit on selected sensor device, default value is "µl/min" for flowunits.
	 * Every sensor read value and regulation command use this unit.
	 * @param sensorIndex Index of sensor channel or unique ID
	 * @out unit[] Array of char containing a unit string
	 * @return fgt_ERROR_CODE
	 */
	unsigned char __stdcall fgt_get_sensorUnit(unsigned int sensorIndex, char unit[140]);

	/**
	 * @Description Set used sensor internal calibration table. Function is only available for specific sensors (dual type) such as the flow-unit M accepting H2O and IPA
	 * @param sensorIndex Index of sensor channel or unique ID
	 * @param calibration fgt_SENSOR_CALIBRATION
	 * @return fgt_ERROR_CODE
	 */
	unsigned char __stdcall fgt_set_sensorCalibration(unsigned int sensorIndex, int calibration);

	/**
	 * @Description Get sensor's current calibration table.
	 * @param sensorIndex Index of sensor channel or unique ID
	 * @out *calibration fgt_SENSOR_CALIBRATION
	 * @return fgt_ERROR_CODE
	 */
	unsigned char __stdcall fgt_get_sensorCalibration(unsigned int sensorIndex, int* calibration);

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
	unsigned char __stdcall fgt_set_sensorCustomScale(unsigned int sensorIndex, float a, float b, float c);

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
	unsigned char __stdcall fgt_set_sensorCustomScaleEx(unsigned int sensorIndex, float a, float b, float c, float SMax);

	/**
	 * @Description Calibrate internal pressure sensor depending on atmospheric pressure. After calling this function 0 pressure value corresponds to atmospheric pressure.
	 * During calibration step no pressure order is accepted. Total duration vary from 3s to 8s.
	 * @param pressureIndex Index of pressure channel or unique ID
	 * @return fgt_ERROR_CODE
	 */
	unsigned char __stdcall fgt_calibratePressure(unsigned int pressureIndex);


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
	unsigned char __stdcall fgt_set_customSensorRegulation(float measure, float setpoint, float maxSensorRange, unsigned int pressureIndex);

	/**
	 * @Description Get pressure controller minimum and maximum range. Returned values takes into account set unit, default value is 'mbar'.
	 * @param pressureIndex Index of pressure channel or unique ID
	 * @out Pmin minim device pressure
	 * @out Pmax maximum device pressure
	 * @return fgt_ERROR_CODE
	 */
	unsigned char __stdcall fgt_get_pressureRange(unsigned int pressureIndex, float* Pmin, float* Pmax);

	/**
	 * @Description Get sensor minimum and maximum range. Returned values takes into account set unit, default value is 'µl/min' in case of flow-units.
	 * @param sensorIndex Index of sensor channel or unique ID
	 * @out Smin minimum measured sensor value
	 * @out Smax maximum measured sensor value
	 * @return fgt_ERROR_CODE
	 */
	unsigned char __stdcall fgt_get_sensorRange(unsigned int sensorIndex, float* Smin, float* Smax);

	/**
	 * @Description Set pressure working range and ensure that pressure will never exceed this limit. It takes into account current unit, default value is 'mbar'.
	 * This function is useful to protect your microfluidic system.
	 * @param pressureIndex Index of pressure channel or unique ID
	 * @param PlimMin minimum admissible device pressure
	 * @param PlimMax maximum admissible device pressure
	 * @return fgt_ERROR_CODE
	 */
	unsigned char __stdcall fgt_set_pressureLimit(unsigned int pressureIndex, float PlimMin, float PlimMax);

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
	unsigned char __stdcall fgt_set_sensorRegulationResponse(unsigned int sensorIndex, unsigned int responseTime);

	/**
	 * @Description Set pressure controller response. This function can be used to customise response time for your set-up.
	 * For FlowEZ available values are 0: use of fast switch valves or 1: do not use fast switch valves. Default value is 0.
	 * For MFCS available values are from 1 to 255. Higher the value, longer is the response time. Default value is 5.
	 * @param pressureIndex Index of pressure channel or unique ID
	 * @param value desired pressure controller response time, this depends on controller type
	 * @return fgt_ERROR_CODE
	 */
	unsigned char __stdcall fgt_set_pressureResponse(unsigned int pressureIndex, unsigned char value);

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
	unsigned char __stdcall fgt_get_pressureStatus(unsigned int pressureIndex, int* type, unsigned short* controllerSN, unsigned char* infoCode, char detail[140]);

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
	unsigned char __stdcall fgt_get_sensorStatus(unsigned int sensorIndex, int* type, unsigned short* controllerSN, unsigned char* infoCode, char detail[140]);

	/**
	 * @Description Set power ON or OFF on a controller (such as Link, MFCS, Flowboard). 
	 * Not all controllers support this functionality.
	 * @param controllerIndex Index of controller or unique ID
	 * @param powerState fgt_POWER
	 * @return fgt_ERROR_CODE
	 */
	unsigned char __stdcall fgt_set_power(unsigned int controllerIndex, unsigned char powerState);

	/**
	 * @Description Get power information about a controller (such as Link, MFCS, Flowboard). 
	 * Not all controllers support this functionality.
	 * @param controllerIndex Index of controller or unique ID
	 * @out powerState fgt_POWER
	 * @return fgt_ERROR_CODE
	 */
	unsigned char __stdcall fgt_get_power(unsigned int controllerIndex, unsigned char* powerState);


	/*============================================================================*/
	/*-----------------------------  TTL functions  ------------------------------*/
	/*============================================================================*/

	/**
	 * @Description Configure a specific TTL port (BNC ports) as input, output, rising or falling edge.
	 * @param TtlIndex Index of TTL port or unique ID
	 * @param mode fgt_TTL_MODE
	 * @return fgt_ERROR_CODE
	 */
	unsigned char __stdcall fgt_set_TtlMode(unsigned int TtlIndex, int mode);

	/**
	 * @Description Read TTL port (BNC port) if set as input.
	 * @param TtlIndex Index of TTL port or unique ID
	 * @out state 0: no edge was detected; 1: an edge is detected
	 * @return fgt_ERROR_CODE
	 * @see fgt_set_TtlMode
	 */
	unsigned char __stdcall fgt_read_Ttl(unsigned int TtlIndex, unsigned int* state);

	/**
	 * @Description Trigger a specific TTL port (BNC ports) if set as output.
	 * @param TtlIndex Index of TTL port or unique ID
	 * @return fgt_ERROR_CODE
	 * @see fgt_set_TtlMode
	 */
	unsigned char __stdcall fgt_trigger_Ttl(unsigned int TtlIndex);


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
	unsigned char __stdcall fgt_set_purge(unsigned int controllerIndex, unsigned char purge);

	/**
	 * @Description Manually activate internal electrovalve. This stops pressure regulation.
	 * This feature is only available on MFCS and MFCS-EZ devices.
	 * @param pressureIndex Index of pressure channel or unique ID
	 * @param value applied valve voltage from 0 to 100(%)
	 * @return fgt_ERROR_CODE
	 */
	unsigned char __stdcall fgt_set_manual(unsigned int pressureIndex, float value);


#ifdef __cplusplus
}
#endif

#endif //_FGT_SDK_H
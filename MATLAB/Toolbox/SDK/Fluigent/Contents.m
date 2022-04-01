% FLUIGENT
%
% Enumerations
%   fgt_INSTRUMENT_TYPE    - Fluigent product families
%   fgt_POWER              - Powered state of the instrument
%   fgt_SENSOR_CALIBRATION - Calibration table to be used by the sensor
%   fgt_SENSOR_TYPE        - Fluigent sensor available types and ranges
%   fgt_TTL_MODE           - TTL port direction and pulse type
%   fgt_VALVE_TYPE         - Fluigent valve types
% 
% Functions
%   fgt_calibratePressure            - Calibrate internal pressure sensor.
%   fgt_close                        - Close communication with Fluigent instruments and free memory.
%   fgt_detect                       - Detect all connected Fluigent instruments
%   fgt_get_controllersInfo          - Retrieve information about session controllers. 
%   fgt_get_power                    - Get power information about a controller.
%   fgt_get_pressure                 - Read pressure value of selected device.
%   fgt_get_pressureChannelCount     - Get total number of initialized pressure channels. 
%   fgt_get_pressureChannelsInfo     - Retrieve information about initialized pressure channels.
%   fgt_get_pressureRange            - Get pressure controller minimum and maximum range. 
%   fgt_get_pressureUnit             - Get current unit on selected pressure device.
%   fgt_get_sensorCalibration        - Get sensor's current calibration table.
%   fgt_get_sensorChannelCount       - Get total number of initialized sensor channels. 
%   fgt_get_sensorChannelsInfo       - Retrieve information about initialized sensor channels. 
%   fgt_get_sensorRange              - Description Get sensor minimum and maximum range. 
%   fgt_get_sensorUnit               - Description Get current unit on selected sensor device.
%   fgt_get_sensorValue              - Read sensor value of selected device
%   fgt_get_TtlChannelCount          - Get total number of initialized TTL channels. 
%   fgt_get_TtlChannelsInfo          - Retrieve information about each initialized TTL channel. 
%   fgt_init                         - Initialize or reinitialize the Fluigent SDK instance. 
%   fgt_read_Ttl                     - Description Read TTL port (BNC port) if set as input.
%   fgt_set_customSensorRegulation   - Start closed loop regulation with manual sensor update
%   fgt_set_manual                   - Manually set internal solenoid valve voltage. 
%   fgt_set_power                    - Set power ON or OFF on a controller.
%   fgt_set_pressure                 - Send pressure command to selected device.
%   fgt_set_pressureLimit            - Set pressure hard limits. 
%   fgt_set_pressureResponse         - Set pressure controller response. 
%   fgt_set_pressureUnit             - Set pressure unit on selected pressure device.
%   fgt_set_purge                    - Activate/deactivate purge function.
%   fgt_set_sensorCalibration        - Set used sensor internal calibration table. 
%   fgt_set_sensorCustomScale        - Apply a custom scale factor on sensor read value. 
%   fgt_set_sensorRegulation         - Start closed loop regulation 
%   fgt_set_sensorRegulationResponse - Set on a running regulation pressure response time.
%   fgt_set_sensorUnit               - Set sensor unit on selected sensor device.
%   fgt_set_sessionPressureUnit      - Set pressure unit for all initialized channels.
%   fgt_set_TtlMode                  - Configure a specific TTL port.
%   fgt_trigger_Ttl                  - Trigger a specific TTL port if it is in output mode.

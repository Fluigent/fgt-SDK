function [state, error_code] = fgt_get_sensorBypassValve( sensorIndex )
%FGT_GET_SENSORBYPASSVALVE Get the state of the sensor's bypass valve.
% 
% This feature is only available on NIFS devices.
%
% state = fgt_get_sensorBypassValve( sensorIndex ) returns 0 if the sensor's 
% bypass valve is closed and 1 if it is open.
%
% [state, error_code] = fgt_get_sensorBypassValve( sensorIndex ) also
% returns the error code returned by the library function

[error_code, state] = LowLevel.fgt_get_sensorBypassValve(sensorIndex);
manage_sensor_status('fgt_get_sensorBypassValve', sensorIndex);
error_code = fgt_ERROR_CODE(error_code);
end


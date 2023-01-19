function varargout = fgt_set_sensorBypassValve( sensorIndex, BypassValve )
%FGT_SET_SENSORBYPASSVALVE Open or close the sensor bypass valve.
% 
% This feature is only available on NIFS devices.
%
% fgt_set_sensorBypassValve(sensorIndex, state) sets the state of
% the bypass valve on the selected sensor, if it has one. Only the
% NIFS sensors have bypass valves. The state should be set to 1 to
% open the valve, and to 0 to close it.
%
% error_code = fgt_set_sensorBypassValve(sensorIndex, state) also
% returns the error code returned by the library function.
% 
% Examples
% % Open the bypass valve on the first sensor
% fgt_set_sensorBypassValve(0, 1)
% % Close the bypass valve on the first sensor
% fgt_set_sensorBypassValve(0, 0)

BypassValve = uint8(BypassValve);
error_code = LowLevel.fgt_set_sensorBypassValve( sensorIndex, BypassValve );
manage_sensor_status('fgt_set_sensorBypassValve', sensorIndex);
if nargout > 0
    varargout = {fgt_ERROR_CODE(error_code)};
end
end


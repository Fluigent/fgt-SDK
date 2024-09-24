function varargout = fgt_set_sensorRegulationInverted( sensorIndex, inverted )
%FGT_SET_SENSORREGULATIONINVERTED Specify whether the sensor is inverted in the physical setup
%
% I.e., if an increase in pressure causes the sensor value to decrease and vice-versa.
%
% fgt_set_sensorRegulationInverted(sensorIndex, true) sets the sensor to be inverted.
% fgt_set_sensorRegulationInverted(sensorIndex, false) sets the sensor to be non-inverted (default).
%
% error_code = fgt_set_sensorRegulationInverted(sensorIndex, inverted)
% also returns the error code returned by the library function.

error_code = LowLevel.fgt_set_sensorRegulationInverted( sensorIndex, inverted );
manage_sensor_status('fgt_set_sensorRegulationInverted', sensorIndex);
if nargout > 0
    varargout = {fgt_ERROR_CODE(error_code)};
end
end


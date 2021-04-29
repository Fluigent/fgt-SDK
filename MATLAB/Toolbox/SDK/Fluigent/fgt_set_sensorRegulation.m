function varargout = fgt_set_sensorRegulation( sensorIndex, pressureIndex, setpoint )
%FGT_SET_SENSORREGULATION Start closed loop regulation 
%
% fgt_set_sensorRegulation(sensorIndex, pressureIndex, setpoint) couples
% the selected sensor with the selected pressure channel and sets the
% sensor setpoint to be achieved.
%
% error_code = fgt_set_sensorRegulation(sensorIndex, pressureIndex, setpoint)
% also returns the error code returned by the library function.
%
% Pressure will be regulated in order to reach sensor setpoint.
% Call this function again in order to change the setpoint. 
%
% Calling fgt_set_pressure on the same pressure channel will stop
% regulation.
%
% Not supported by the IPS.
%
% See also:
%     fgt_set_pressure
%     fgt_set_customSensorRegulation
%     fgt_set_sensorRegulationResponse
    
error_code = LowLevel.fgt_set_sensorRegulation(sensorIndex, pressureIndex, setpoint);
manage_sensor_status('fgt_set_sensorRegulation', sensorIndex);
if nargout > 0
    varargout = {fgt_ERROR_CODE(error_code)};
end
end


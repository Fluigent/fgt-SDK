function [] = fgt_set_sensorRegulation( sensorIndex, pressureIndex, setpoint )
%FGT_SET_SENSORREGULATION Start closed loop regulation 
%
% fgt_set_sensorRegulation(sensorIndex, pressureIndex, setpoint) couples
% the selected sensor with the selected pressure channel and sets the
% sensor setpoint to be achieved.
%
% Pressure will be regulated in order to reach sensor setpoint.
% Call this function again in order to change the setpoint. 
%
% Calling fgt_set_pressure on the same pressure channel will stop
% regulation.
%
% See also:
%     fgt_set_pressure
%     fgt_set_customSensorRegulation
%     fgt_set_sensorRegulationResponse
    
LowLevel.fgt_set_sensorRegulation(sensorIndex, pressureIndex, setpoint);
manage_sensor_status('fgt_set_sensorRegulation', sensorIndex);
end


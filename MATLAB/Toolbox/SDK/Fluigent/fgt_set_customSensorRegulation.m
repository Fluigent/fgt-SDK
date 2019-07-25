function [ ] = fgt_set_customSensorRegulation(measure, setpoint, maxSensorRange, pressureIndex)
%FGT_SET_CUSTOMSENSORREGULATION Start closed loop regulation with manual sensor update
% 
% fgt_set_customSensorRegulation(measure, setpoint, maxSensorRange, pressureIndex)
% will update the algorithm with the current sensor measurement, desired
% setpoint, range and the index of the pressure channel that can drive it.
%
% The measurement, setpoint and range must be in the same unit.
% 
% Pressure will be regulated in order to reach sensor setpoint.
% Custom sensors, outside Fluigent ones, can be used such as different 
% Flow Units, pressure, level etc.
% However we do not guarantee full compatibility with all sensors. 
% Regulation quality is linked to sensor precision and your setup.
% In order to use this function, custom used sensor maximum range and 
% measured values have to be updated at least once per second.
% Directly setting pressure on same pressure_index will stop regulation.
% This function must be called at 1Hz minimum or the regulation will stop.

LowLevel.fgt_set_customSensorRegulation(measure, setpoint, ...
         maxSensorRange, pressureIndex);
manage_pressure_status('fgt_set_customSensorRegulation', pressureIndex);
end


function [] = fgt_set_pressureLimit( pressureIndex, PlimMin, PlimMax )
%FGT_SET_PRESSURELIMIT Set pressure hard limits. 
% 
% fgt_set_pressure(pressureIndex, PlimMin, PlimMax) sets the minimum and
% maximum pressure on the selected channel to the specified values, in the
% channel's current unit. Default unit is 'mbar'
% 
% Pressure setpoint will not exceed these limit during regulation.
% This function is useful to protect your microfluidic system.

LowLevel.fgt_set_pressureLimit( pressureIndex, PlimMin, PlimMax );
manage_pressure_status('fgt_set_pressureLimit', pressureIndex);
end


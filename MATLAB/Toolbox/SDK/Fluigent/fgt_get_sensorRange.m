function [SMin, SMax] = fgt_get_sensorRange( sensorIndex )
%FGT_GET_SENSORRANGE Description Get sensor minimum and maximum range. 
% 
% [SMin, SMax] = fgt_get_sensorRange( sensorIndex ) returns the sensor 
% minimum and maximum value in the selected unit. Default unit is
% 'µl/min' for Flow Units and 'mbar' for IPS modules.

[~, SMin, SMax] = LowLevel.fgt_get_sensorRange(sensorIndex);
manage_sensor_status('fgt_get_sensorRange', sensorIndex);
end


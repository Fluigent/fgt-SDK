function [unit] = fgt_get_sensorUnit( sensorIndex )
%FGT_GET_SENSORUNIT Description Get current unit on selected sensor device.
% 
% unit = fgt_get_sensorUnit( sensorIndex ) returns the current sensor 
% unit as a string. Default unit is 'µl/min' in case of Flow Units.

[~, unit] = LowLevel.fgt_get_sensorUnit(sensorIndex);
manage_sensor_status('fgt_get_sensorUnit', sensorIndex);
end


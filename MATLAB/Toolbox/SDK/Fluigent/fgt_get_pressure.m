function varargout = fgt_get_pressure( pressureIndex )
%FGT_GET_PRESSURE Read pressure value of selected device.
% 
% pressure = fgt_get_pressure( pressureIndex ) returns the pressure 
% measurement value in the selected unit, default is 'mbar'
%
% [pressure, timestamp] = fgt_get_pressure( pressureIndex ) returns the
% instrument's internal timestamp in addition to the pressure.

[~, pressure, timestamp] = LowLevel.fgt_get_pressureEx(pressureIndex);
manage_pressure_status('fgt_get_pressure', pressureIndex);
varargout = {pressure, timestamp};
end


function [error_code, pressure, timestamp] = fgt_get_pressureEx( controllerIndex )
%FGT_GET_PRESSURE Summary of this function goes here
%   Detailed explanation goes here
load_fgt
pressure = 0;
timestamp = uint16(0);
[error_code, pressure, timestamp] = calllib('fgt_sdk', 'fgt_get_pressureEx', controllerIndex, pressure, timestamp);
end


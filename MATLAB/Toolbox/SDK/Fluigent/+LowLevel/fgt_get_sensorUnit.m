function [error_code, unit] = fgt_get_sensorUnit( sensorIndex )
%FGT_GET_SENSORUNIT Summary of this function goes here
%   Detailed explanation goes here
unit = zeros(1, 140);
load_fgt
[error_code, unit] = calllib('fgt_sdk', 'fgt_get_sensorUnit', sensorIndex, unit);
unit = unit(unit ~=0);
unit = mod(int16(unit) + 256, 256);
unit = strtrim(char(unit));
end


function [error_code, unit] = fgt_get_pressureUnit( pressureIndex )
%FGT_GET_PRESSUREUNIT Summary of this function goes here
%   Detailed explanation goes here
load_fgt
unit = zeros(1, 140);
[error_code, unit] = calllib('fgt_sdk', 'fgt_get_pressureUnit', pressureIndex, unit);
unit = unit(unit ~=0);
unit = mod(int16(unit) + 256, 256);
unit = native2unicode(unit, 'UTF-8');
end


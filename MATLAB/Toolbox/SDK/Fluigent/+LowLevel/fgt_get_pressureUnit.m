function [error_code, unit] = fgt_get_pressureUnit( pressureIndex )
%FGT_GET_PRESSUREUNIT Summary of this function goes here
%   Detailed explanation goes here
load_fgt
unit = zeros(1, 140);
[error_code, unit] = calllib('fgt_sdk', 'fgt_get_pressureUnit', pressureIndex, unit);
unit = strtrim(char(unit(unit ~=0)));
end


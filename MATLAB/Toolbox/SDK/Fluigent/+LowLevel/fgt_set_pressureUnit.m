function [ error_code ] = fgt_set_pressureUnit( pressureIndex, unit )
%FGT_SET_PRESSUREUNIT Summary of this function goes here
%   Detailed explanation goes here
load_fgt
[error_code] = calllib('fgt_sdk', 'fgt_set_pressureUnit', pressureIndex, [uint8(unit),0]);

end


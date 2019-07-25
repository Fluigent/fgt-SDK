function [error_code, powerState] = fgt_get_power (controllerIndex)
%FGT_GET_POWER Summary of this function goes here
%   Detailed explanation goes here
load_fgt
powerState = uint8(0);
[error_code, powerState] = calllib('fgt_sdk', 'fgt_get_power', controllerIndex, powerState);

end


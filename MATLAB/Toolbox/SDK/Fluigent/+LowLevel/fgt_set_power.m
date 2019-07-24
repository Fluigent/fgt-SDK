function [error_code] = fgt_set_power(controllerIndex, powerState)
%FGT_SET_POWER Summary of this function goes here
%   Detailed explanation goes here
load_fgt
[error_code] = calllib('fgt_sdk', 'fgt_set_power', controllerIndex, powerState);

end


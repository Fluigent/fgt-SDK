function [error_code, pressure] = fgt_get_pressure( controllerIndex )
%FGT_GET_PRESSURE Summary of this function goes here
%   Detailed explanation goes here
load_fgt
pressure = 0;
[error_code, pressure] = calllib('fgt_sdk', 'fgt_get_pressure', controllerIndex, pressure);
end


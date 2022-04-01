function [error_code, pressure] = fgt_get_inletPressure( pressureIndex )
%FGT_GET_INLETPRESSURE Summary of this function goes here
%   Detailed explanation goes here
load_fgt
pressure = 0;
[error_code, pressure] = calllib('fgt_sdk', 'fgt_get_inletPressure', pressureIndex, pressure);
end


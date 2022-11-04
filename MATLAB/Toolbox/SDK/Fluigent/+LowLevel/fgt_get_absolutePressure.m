function [ error_code, PAbs ] = fgt_get_absolutePressure( sensorIndex )
%FGT_GET_ABSOLUTEPRESSURE Summary of this function goes here
%   Detailed explanation goes here
load_fgt
PAbs = 0;
[error_code, PAbs] = calllib('fgt_sdk', 'fgt_get_absolutePressure', sensorIndex, PAbs);

end


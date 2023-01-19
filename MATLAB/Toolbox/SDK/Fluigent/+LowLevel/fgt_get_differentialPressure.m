function [ error_code, PDiff ] = fgt_get_differentialPressure( sensorIndex )
%FGT_GET_DIFFERENTIALPRESSURE Summary of this function goes here
%   Detailed explanation goes here
load_fgt
PDiff = 0;
[error_code, PDiff] = calllib('fgt_sdk', 'fgt_get_differentialPressure', sensorIndex, PDiff);

end


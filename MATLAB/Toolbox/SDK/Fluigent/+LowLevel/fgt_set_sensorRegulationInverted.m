function [error_code] = fgt_set_sensorRegulationInverted( sensorIndex, inverted )
%FGT_SET_SENSORREGULATIONRESPONSE Summary of this function goes here
%   Detailed explanation goes here
load_fgt
[error_code] = calllib('fgt_sdk', 'fgt_set_sensorRegulationInverted', sensorIndex, inverted);

end


function [ error_code ] = fgt_set_sessionPressureUnit( unit )
%FGT_SET_SESSIONPRESSUREUNIT Summary of this function goes here
%   Detailed explanation goes here
load_fgt
unit = unicode2native(unit, 'UTF-8');
[error_code] = calllib('fgt_sdk', 'fgt_set_sessionPressureUnit', [uint8(unit),0]);
end


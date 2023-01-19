function [ error_code, PMin, PMax ] = fgt_get_differentialPressureRange( sensorIndex )
%FGT_GET_DIFFERENTIALPRESSURERANGE Summary of this function goes here
%   Detailed explanation goes here
load_fgt
PMin = 0;
PMax = 0;
[error_code, PMin, PMax] = calllib('fgt_sdk', 'fgt_get_differentialPressureRange', sensorIndex, PMin, PMax);

end


function [ error_code, PMin, PMax ] = fgt_get_absolutePressureRange( sensorIndex )
%FGT_GET_ABSOLUTEPRESSURERANGE Summary of this function goes here
%   Detailed explanation goes here
load_fgt
PMin = 0;
PMax = 0;
[error_code, PMin, PMax] = calllib('fgt_sdk', 'fgt_get_absolutePressureRange', sensorIndex, PMin, PMax);

end


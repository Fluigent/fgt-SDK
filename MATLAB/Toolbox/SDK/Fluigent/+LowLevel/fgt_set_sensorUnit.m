function [error_code] = fgt_set_sensorUnit( sensorIndex, unit )
%FGT_SET_FLOWRATEUNIT Summary of this function goes here
%   Detailed explanation goes here
load_fgt
unit = unicode2native(unit, 'UTF-8');
[error_code] = calllib('fgt_sdk', 'fgt_set_sensorUnit', sensorIndex, [uint8(unit), 0]);

end


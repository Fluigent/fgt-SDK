function [error_code] = fgt_set_valvePosition( valveIndex, position, direction, wait )
%FGT_SET_VALVEPOSITION Summary of this function goes here
%   Detailed explanation goes here
load_fgt
[error_code] = calllib('fgt_sdk', 'fgt_set_valvePosition', valveIndex, position, direction, wait);

end


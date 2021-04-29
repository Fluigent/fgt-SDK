function [error_code, position] = fgt_get_valvePosition( valveIndex )
%FGT_GET_VALVEPOSITION Get current valve position
%   Detailed explanation goes here
load_fgt
position = 0;
[error_code, position] = calllib('fgt_sdk', 'fgt_get_valvePosition', valveIndex, position);
manage_generic_status('fgt_get_valvePosition', error_code);
end


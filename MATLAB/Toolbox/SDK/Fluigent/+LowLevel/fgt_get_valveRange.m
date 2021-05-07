function [error_code, posMax] = fgt_get_valveRange( valveIndex )
%FGT_GET_VALVERANGE Summary of this function goes here
%   Detailed explanation goes here
load_fgt
posMax = 0;
[error_code, posMax] = calllib('fgt_sdk', 'fgt_get_valveRange', valveIndex, posMax);

end


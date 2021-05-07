function [error_code] = fgt_set_allValves( controllerIndex, moduleIndex, position )
%FGT_SET_ALLVALVES Summary of this function goes here
%   Detailed explanation goes here
load_fgt
[error_code] = calllib('fgt_sdk', 'fgt_set_allValves', controllerIndex, moduleIndex, position);
manage_generic_status('fgt_set_allValves', error_code);
end


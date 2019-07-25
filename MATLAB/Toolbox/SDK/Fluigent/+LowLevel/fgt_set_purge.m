function [ error_code ] = fgt_set_purge( controllerIndex, purge )
%FGT_SET_PURGE Summary of this function goes here
%   Detailed explanation goes here
load_fgt
[error_code] = calllib('fgt_sdk', 'fgt_set_purge', controllerIndex, purge);

end


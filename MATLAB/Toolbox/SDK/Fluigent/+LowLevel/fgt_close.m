function [ error_code ] = fgt_close( )
%FGT_CLOSE Summary of this function goes here
%   Detailed explanation goes here
load_fgt
error_code = calllib('fgt_sdk', 'fgt_close');

end


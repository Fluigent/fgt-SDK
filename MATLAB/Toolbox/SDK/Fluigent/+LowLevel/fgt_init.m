function [ error_code ] = fgt_init(  )
%FGT_INIT Summary of this function goes here
%   Detailed explanation goes here
load_fgt

error_code = calllib('fgt_sdk', 'fgt_init');

end


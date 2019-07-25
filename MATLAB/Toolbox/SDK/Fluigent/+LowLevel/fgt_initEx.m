function [ error_code ] = fgt_initEx( serial_numbers )
%FGT_INIT_EX Summary of this function goes here
%   Detailed explanation goes here
load_fgt
serial_numbers = [serial_numbers, 0];

error_code = calllib('fgt_sdk', 'fgt_initEx', serial_numbers);


end


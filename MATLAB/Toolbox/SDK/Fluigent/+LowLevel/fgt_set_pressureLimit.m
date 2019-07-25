function [ error_code ] = fgt_set_pressureLimit( pressureIndex, PlimMin, PlimMax )
%FGT_SET_PRESSURELIMIT Summary of this function goes here
%   Detailed explanation goes here
load_fgt
[error_code] = calllib('fgt_sdk', 'fgt_set_pressureLimit', pressureIndex, PlimMin, PlimMax);

end


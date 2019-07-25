function [ error_code ] = fgt_set_pressureResponse( pressureIndex, value )
%FGT_SET_PRESSURERESPONSE Summary of this function goes here
%   Detailed explanation goes here
load_fgt
[error_code] = calllib('fgt_sdk', 'fgt_set_pressureResponse', pressureIndex, value);

end


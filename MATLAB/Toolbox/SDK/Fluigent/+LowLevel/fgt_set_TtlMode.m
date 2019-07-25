function [ error_code ] = fgt_set_TtlMode( TtlIndex, mode )
%FGT_SET_TTLMODE Summary of this function goes here
%   Detailed explanation goes here
load_fgt
[error_code] = calllib('fgt_sdk', 'fgt_set_TtlMode', TtlIndex, mode);

end


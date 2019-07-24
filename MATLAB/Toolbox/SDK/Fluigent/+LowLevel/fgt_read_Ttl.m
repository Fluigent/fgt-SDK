function [ error_code, state ] = fgt_read_Ttl( TtlIndex )
%FGT_READ_TTL Summary of this function goes here
%   Detailed explanation goes here
load_fgt
state = uint8(0);
[error_code, state] = calllib('fgt_sdk', 'fgt_read_Ttl', TtlIndex, state);

end


function [error_code] = fgt_trigger_Ttl( TtlIndex )
%FGT_TRIGGER_TTL Summary of this function goes here
%   Detailed explanation goes here
load_fgt
[error_code] = calllib('fgt_sdk', 'fgt_trigger_Ttl', TtlIndex);

end


function [ state, error_code ] = fgt_read_Ttl( TtlIndex )
%FGT_READ_TTL Description Read TTL port (BNC port) if set as input.
% 
% state = fgt_read_Ttl( TtlIndex ) returns the current state of the
% selected TTL port: 1 if an edge was detected, 0 otherwise
%
% [ state, error_code ] = fgt_read_Ttl( TtlIndex ) also returns the error
% code returned by the library function.
%
% See also:
%     fgt_set_TtlMode

[error_code, state] = LowLevel.fgt_read_Ttl(TtlIndex);
manage_generic_status('fgt_read_Ttl', error_code);
error_code = fgt_ERROR_CODE(error_code);
end


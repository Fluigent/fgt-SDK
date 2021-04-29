function varargout = fgt_set_purge( pressureIndex, purge )
%FGT_SET_PURGE Activate/deactivate purge function.
% 
% fgt_set_purge(pressureIndex, purge) activates the purge function if
% purge is 1 and deactivate it if it is 0. 
%
% error_code = fgt_set_purge(pressureIndex, purge) also returns the error
% code returned by the library function.
%
% This feature is only available on MFCS devices equipped with a purge
% valve.

error_code = LowLevel.fgt_set_purge( pressureIndex, purge );
manage_pressure_status('fgt_set_purge', pressureIndex);
if nargout > 0
    varargout = {fgt_ERROR_CODE(error_code)};
end
end


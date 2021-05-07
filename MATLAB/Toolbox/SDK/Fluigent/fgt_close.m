function varargout = fgt_close( )
%FGT_CLOSE Close communication with Fluigent instruments and free memory.
% 
% Using this function will remove session preferences such as units 
% and limits. 
% If any regulation is running it will stop pressure control.

[error_code] = LowLevel.fgt_close();
manage_generic_status('fgt_close', error_code);
error_code = fgt_ERROR_CODE(error_code);
if nargout > 0
    varargout = {fgt_ERROR_CODE(error_code)};
end
end


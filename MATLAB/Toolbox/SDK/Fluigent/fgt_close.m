function [] = fgt_close( )
%FGT_CLOSE Close communication with Fluigent instruments and free memory.
% 
% Using this function will remove session preferences such as units 
% and limits. 
% If any regulation is running it will stop pressure control.

[error_code] = LowLevel.fgt_close();
manage_generic_status('fgt_close', error_code);
end


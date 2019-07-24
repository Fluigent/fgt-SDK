function parse_error( c_error )
%PARSE_ERROR Generate an error message based on the DLL error code

error_messages = {'No instrument detected', ...
                  'Channel not available'};
              
if c_error == 0
    return
elseif c_error > 0 && c_error <= numel(error_messages)
    errmsg = error_messages{c_error};
else
    errmsg = sprintf('Undefined error code %d', c_error);
end

err.message = errmsg;
err.identifier = 'FGT:Engine';
err.stack.file = '';
err.stack.name = 'Fluigent.Engine';
err.stack.line = 1;
error(err)


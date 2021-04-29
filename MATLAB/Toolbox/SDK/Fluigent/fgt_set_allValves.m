function varargout = fgt_set_allValves(controllerIndex, moduleIndex, position)
%FGT_SET_POWER the position of all two positional valves
% 
% fgt_set_allValves(controllerIndex, moduleIndex, position) will set all
% valves on the specified controller (Link or Switchboard) and module
% (P-Switch if the controller is a Link) to the specified position at the
% same time.
%
% error_code = fgt_set_allValves(controllerIndex, moduleIndex, position)
% also returns the error code returned by the library function.
% 
% See also:
%     fgt_set_valvePosition

[error_code] = LowLevel.fgt_set_allValves(controllerIndex, moduleIndex, position);
manage_generic_status('fgt_set_allValves', error_code);
if nargout > 0
    varargout = {fgt_ERROR_CODE(error_code)};
end
end


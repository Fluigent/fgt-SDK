function varargout = fgt_remove_simulated_instr( type, serial )
%FGT_REMOVE_SIMULATED_INSTR Remove a simulated instrument
%
% fgt_remove_simulated_instr(type, serial) removes a simulated instrument
% that had been previously created. If it had already been initialized by
% the SDK, the controller and channels will remain in the respective lists,
% but they will act as if the instrument is missing. This is equivalent to
% physically disconnecting a real instrument.
% Arguments
%  type    - Type of instrument to remove. Value of fgt_INSTRUMENT_TYPE
%  serial  - Serial number of the simulated instrument
%
% error_code = fgt_remove_simulated_instr(...) also returns the
% error code returned by the library function.
%
% See also:
%     fgt_create_simulated_instr

type = uint8(type);
[error_code] = LowLevel.fgt_remove_simulated_instr(type, serial);
manage_generic_status('fgt_remove_simulated_instr', error_code);
if nargout > 0
    varargout = {fgt_ERROR_CODE(error_code)};
end
end


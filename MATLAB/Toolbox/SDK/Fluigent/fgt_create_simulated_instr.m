function varargout = fgt_create_simulated_instr( type, serial, version, config )
%FGT_CREATE_SIMULATED_INSTR Create a simulated instrument
%
% fgt_create_simulated_instr(type, serial, version, config) creates a 
% simulated Fluigent instrument, which can be detected and initialized like
% a real one, for the purposes of testing and demonstrations.
% Arguments
%  type    - Type of instrument to simulate. Value of fgt_INSTRUMENT_TYPE
%  serial  - Serial number for the simulated instrument
%  version - Firmware version for the simulated instrument. Set to 0 to use
%            the default version
%  config  - Array describing the instrument's configuration. See the manual
%            for instructions on the format.
%
% error_code = fgt_create_simulated_instr(...) also returns the
% error code returned by the library function.
%
% See also:
%     fgt_remove_simulated_instr

type = uint8(type);
[error_code] = LowLevel.fgt_create_simulated_instr(type, serial, version, config);
manage_generic_status('fgt_create_simulated_instr', error_code);
if nargout > 0
    varargout = {fgt_ERROR_CODE(error_code)};
end
end


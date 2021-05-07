function varargout = fgt_set_sessionPressureUnit( unit )
%FGT_SET_SESSIONPRESSUREUNIT Set pressure unit for all initialized channels.
% 
% fgt_set_sessionPressureUnit(unit) sets the unit to be used on all
% pressure channels, which should be passed as a string.
%
% error_code = fgt_set_sessionPressureUnit(unit) also returns the error
% code returned by the library function.
% 
% Default value is 'mbar'. 
% If the unit is invalid the previous unit is kept and an error is logged.
% Every pressure read value and sent command will then use this unit.
%
% Examples: 
%     fgt_set_sessionPressureUnit('mbar')
%     fgt_set_sessionPressureUnit('psi')
% See also:
%     fgt_set_pressureUnit

error_code = LowLevel.fgt_set_sessionPressureUnit( unit );
manage_generic_status('fgt_set_sessionPressureUnit', error_code);
if nargout > 0
    varargout = {fgt_ERROR_CODE(error_code)};
end
end


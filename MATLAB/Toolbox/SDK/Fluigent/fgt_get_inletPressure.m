function varargout = fgt_get_inletPressure( pressureIndex )
%FGT_GET_INLETPRESSURE Read  the pressure measured at the device's inlet.
%
% This feature is only available on LineUP Flow EZ and FOEM Pressure
% Module instruments.
%
% pressure = fgt_get_inletPressure( pressureIndex ) returns the channel's
% inlet pressure in the selected unit, default is 'mbar'
%
% [pressure, error_code] = fgt_get_inletPressure( pressureIndex )
% also returns the error code returned by the library function

[error_code, pressure] = LowLevel.fgt_get_inletPressure(pressureIndex);
manage_pressure_status('fgt_get_inletPressure', pressureIndex);
error_code = fgt_ERROR_CODE(error_code);
varargout = {pressure, error_code};
end


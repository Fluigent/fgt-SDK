function varargout = fgt_set_sensorCustomScale(varargin)
%FGT_SET_SENSORCUSTOMSCALE Apply a custom scale factor on sensor read value. 
% 
% fgt_set_sensorCustomScale(sensor_index, a) applies a linear scale factor
% to the sensor reading, such that: 
%   scaledValue = a*sensorValue
%
% fgt_set_sensorCustomScale(sensor_index, a, b) applies a quadratic scale
% factor to the sensor reading, such that:
%   scaledValue = a*sensorValue + b*sensorValue^2
%
% fgt_set_sensorCustomScale(sensor_index, a, b, c) applies a cubic scale
% factor to the sensor reading, such that:
%   scaledValue = a*sensorValue + b*sensorValue^2 + c*sensorValue^3
%
% fgt_set_sensorCustomScale(sensor_index, a, b, c, SMax) applies a cubic
% scale factor and clips the value at SMax, such that if the result of
% applying the above formula is greater than SMax, the output will be SMax.
%
% error_code = fgt_set_sensorCustomScale(...) also returns the error code
% returned by the library function.
%
% This function is useful in order to adapt read sensor value to 
% physical measurement.
% For example if a Flow Unit is used with a special oil and its 
% calibration table is set to H2O, the flowrate reading will not be correct.
% Note that this scale is also used for the regulation.
% 
% Not supported by the IPS.

if nargin > 5
    error('Too many input arguments.')
elseif nargin < 2
    error('Not enough input arguments.')
elseif nargin == 5
    error_code = LowLevel.fgt_set_sensorCustomScaleEx(varargin{:});
else
    varargin(nargin+1:4) = {0};
    error_code = LowLevel.fgt_set_sensorCustomScale(varargin{:});
end
sensorIndex = varargin{1};
manage_sensor_status('fgt_set_sensorCustomScale', sensorIndex);
if nargout > 0
    varargout = {fgt_ERROR_CODE(error_code)};
end
end


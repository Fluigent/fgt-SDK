function varargout = fgt_set_valvePosition( varargin )
%FGT_SET_VALVEPOSITION Change the position of the selected valve
% 
% fgt_set_valvePosition( valveIndex, position ) sets the position on
% the selected valve, turning in the direction of the shortest path
% if it is a rotating valve. Blocks until the valve is done turning.
% 
% fgt_set_valvePosition( valveIndex, position, direction ) sets the 
% position on the selected valve, turning in the specified direction if
% it is a rotating valve. Blocks until the valve is done turning.
%
% fgt_set_valvePosition( valveIndex, position, direction, wait ) sets the 
% position on the selected valve, turning in the specified direction if
% it is a rotating valve. If wait is not 0, the function blocks until
% the valve arrives at the specified position.
%
% error_code = fgt_set_valvePosition(...) also returns the error code
% returned by the library function.
%
% See also:
%     fgt_set_allValves

if nargin > 4
    error('Too many input arguments.')
elseif nargin < 2
    error('Not enough input arguments.')
end

valveIndex = varargin{1};
position = varargin{2};
direction = 0;
wait = 1;

if nargin >= 3
    direction = int(varargin{3});
end

if nargin >= 4
    wait = int(varargin{4});
end

error_code = LowLevel.fgt_set_valvePosition( valveIndex, position, direction, wait );
manage_generic_status('fgt_set_valvePosition', error_code);
if nargout > 0
    varargout = {fgt_ERROR_CODE(error_code)};
end
end


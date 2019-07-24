function [] = fgt_set_purge( pressureIndex, purge )
%FGT_SET_PURGE Activate/deactivate purge function.
% 
% fgt_set_purge(pressureIndex, purge) activates the purge function if
% purge is 1 and deactivate it if it is 0. 
%
% This feature is only available on MFCS devices equipped with a purge
% valve.

LowLevel.fgt_set_purge( pressureIndex, purge );
manage_pressure_status('fgt_set_purge', pressureIndex);
end


function [methodinfo,structs,enuminfo,ThunkLibName]=fgt_SDK_32_prototype
%FGT_SDK_32_PROTOTYPE Create structures to define interfaces found in 'fgt_SDK'.

%This function was generated by loadlibrary.m parser version  on Fri Jul 29 13:29:21 2022
%perl options:'fgt_SDK.i -outfile=fgt_SDK_32_prototype.m'
ival={cell(1,0)}; % change 0 to the actual number of functions to preallocate the data.
structs=[];enuminfo=[];fcnNum=1;
fcns=struct('name',ival,'calltype',ival,'LHS',ival,'RHS',ival,'alias',ival);
ThunkLibName=[];
% unsigned char  _stdcall fgt_init ( void ); 
fcns.name{fcnNum}='fgt_init'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}=[];fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_close ( void ); 
fcns.name{fcnNum}='fgt_close'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}=[];fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_detect ( unsigned short SN [ 256 ], int type [ 256 ]); 
fcns.name{fcnNum}='fgt_detect'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint16Ptr', 'int32Ptr'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_initEx ( unsigned short SN [ 256 ]); 
fcns.name{fcnNum}='fgt_initEx'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint16Ptr'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_create_simulated_instr ( fgt_instrument_t type , unsigned short serial , unsigned short version , int * config , int length ); 
fcns.name{fcnNum}='fgt_create_simulated_instr'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'int32', 'uint16', 'uint16', 'int32Ptr', 'int32'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_remove_simulated_instr ( fgt_instrument_t type , unsigned short serial ); 
fcns.name{fcnNum}='fgt_remove_simulated_instr'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'int32', 'uint16'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_get_controllersInfo ( fgt_CONTROLLER_INFO info [ 256 ]); 
fcns.name{fcnNum}='fgt_get_controllersInfo'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'fgt_CONTROLLER_INFOPtr'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_get_pressureChannelCount ( unsigned char * nbPChan ); 
fcns.name{fcnNum}='fgt_get_pressureChannelCount'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint8Ptr'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_get_sensorChannelCount ( unsigned char * nbSChan ); 
fcns.name{fcnNum}='fgt_get_sensorChannelCount'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint8Ptr'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_get_TtlChannelCount ( unsigned char * nbTtlChan ); 
fcns.name{fcnNum}='fgt_get_TtlChannelCount'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint8Ptr'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_get_valveChannelCount ( unsigned char * nbValveChan ); 
fcns.name{fcnNum}='fgt_get_valveChannelCount'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint8Ptr'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_get_pressureChannelsInfo ( fgt_CHANNEL_INFO info [ 256 ]); 
fcns.name{fcnNum}='fgt_get_pressureChannelsInfo'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'fgt_CHANNEL_INFOPtr'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_get_sensorChannelsInfo ( fgt_CHANNEL_INFO info [ 256 ], fgt_sensor_t sensorType [ 256 ]); 
fcns.name{fcnNum}='fgt_get_sensorChannelsInfo'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'fgt_CHANNEL_INFOPtr', 'int32Ptr'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_get_TtlChannelsInfo ( fgt_CHANNEL_INFO info [ 256 ]); 
fcns.name{fcnNum}='fgt_get_TtlChannelsInfo'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'fgt_CHANNEL_INFOPtr'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_get_valveChannelsInfo ( fgt_CHANNEL_INFO info [ 256 ], fgt_valve_t valveType [ 256 ]); 
fcns.name{fcnNum}='fgt_get_valveChannelsInfo'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'fgt_CHANNEL_INFOPtr', 'int32Ptr'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_set_pressure ( unsigned int pressureIndex , float pressure ); 
fcns.name{fcnNum}='fgt_set_pressure'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint32', 'single'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_get_pressure ( unsigned int pressureIndex , float * pressure ); 
fcns.name{fcnNum}='fgt_get_pressure'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint32', 'singlePtr'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_get_pressureEx ( unsigned int pressureIndex , float * pressure , unsigned short * timeStamp ); 
fcns.name{fcnNum}='fgt_get_pressureEx'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint32', 'singlePtr', 'uint16Ptr'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_set_sensorRegulation ( unsigned int sensorIndex , unsigned int pressureIndex , float setpoint ); 
fcns.name{fcnNum}='fgt_set_sensorRegulation'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint32', 'uint32', 'single'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_get_sensorValue ( unsigned int sensorIndex , float * value ); 
fcns.name{fcnNum}='fgt_get_sensorValue'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint32', 'singlePtr'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_get_sensorValueEx ( unsigned int sensorIndex , float * value , unsigned short * timeStamp ); 
fcns.name{fcnNum}='fgt_get_sensorValueEx'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint32', 'singlePtr', 'uint16Ptr'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_get_sensorAirBubbleFlag ( unsigned int sensorIndex , unsigned char * detected ); 
fcns.name{fcnNum}='fgt_get_sensorAirBubbleFlag'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint32', 'uint8Ptr'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_get_valvePosition ( unsigned int valveIndex , int * position ); 
fcns.name{fcnNum}='fgt_get_valvePosition'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint32', 'int32Ptr'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_set_valvePosition ( unsigned int valveIndex , int position , fgt_switch_direction_t direction , int wait ); 
fcns.name{fcnNum}='fgt_set_valvePosition'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint32', 'int32', 'int32', 'int32'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_set_allValves ( unsigned int controllerIndex , unsigned int moduleIndex , int position ); 
fcns.name{fcnNum}='fgt_set_allValves'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint32', 'uint32', 'int32'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_set_sessionPressureUnit ( char unit [ 140 ]); 
fcns.name{fcnNum}='fgt_set_sessionPressureUnit'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'int8Ptr'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_set_pressureUnit ( unsigned int presureIndex , char unit [ 140 ]); 
fcns.name{fcnNum}='fgt_set_pressureUnit'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint32', 'int8Ptr'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_get_pressureUnit ( unsigned int pressureIndex , char unit [ 140 ]); 
fcns.name{fcnNum}='fgt_get_pressureUnit'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint32', 'int8Ptr'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_set_sensorUnit ( unsigned int sensorIndex , char unit [ 140 ]); 
fcns.name{fcnNum}='fgt_set_sensorUnit'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint32', 'int8Ptr'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_get_sensorUnit ( unsigned int sensorIndex , char unit [ 140 ]); 
fcns.name{fcnNum}='fgt_get_sensorUnit'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint32', 'int8Ptr'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_set_sensorCalibration ( unsigned int sensorIndex , fgt_calibration_t calibration ); 
fcns.name{fcnNum}='fgt_set_sensorCalibration'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint32', 'int32'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_get_sensorCalibration ( unsigned int sensorIndex , fgt_calibration_t * calibration ); 
fcns.name{fcnNum}='fgt_get_sensorCalibration'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint32', 'int32Ptr'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_set_sensorCustomScale ( unsigned int sensorIndex , float a , float b , float c ); 
fcns.name{fcnNum}='fgt_set_sensorCustomScale'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint32', 'single', 'single', 'single'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_set_sensorCustomScaleEx ( unsigned int sensorIndex , float a , float b , float c , float SMax ); 
fcns.name{fcnNum}='fgt_set_sensorCustomScaleEx'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint32', 'single', 'single', 'single', 'single'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_calibratePressure ( unsigned int pressureIndex ); 
fcns.name{fcnNum}='fgt_calibratePressure'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint32'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_set_customSensorRegulation ( float measure , float setpoint , float maxSensorRange , unsigned int pressureIndex ); 
fcns.name{fcnNum}='fgt_set_customSensorRegulation'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'single', 'single', 'single', 'uint32'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_get_pressureRange ( unsigned int pressureIndex , float * Pmin , float * Pmax ); 
fcns.name{fcnNum}='fgt_get_pressureRange'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint32', 'singlePtr', 'singlePtr'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_get_sensorRange ( unsigned int sensorIndex , float * Smin , float * Smax ); 
fcns.name{fcnNum}='fgt_get_sensorRange'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint32', 'singlePtr', 'singlePtr'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_get_valveRange ( unsigned int valveIndex , int * posMax ); 
fcns.name{fcnNum}='fgt_get_valveRange'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint32', 'int32Ptr'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_set_pressureLimit ( unsigned int pressureIndex , float PlimMin , float PlimMax ); 
fcns.name{fcnNum}='fgt_set_pressureLimit'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint32', 'single', 'single'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_set_sensorRegulationResponse ( unsigned int sensorIndex , unsigned int responseTime ); 
fcns.name{fcnNum}='fgt_set_sensorRegulationResponse'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint32', 'uint32'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_set_pressureResponse ( unsigned int pressureIndex , unsigned char value ); 
fcns.name{fcnNum}='fgt_set_pressureResponse'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint32', 'uint8'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_get_pressureStatus ( unsigned int pressureIndex , fgt_instrument_t * type , unsigned short * controllerSN , unsigned char * infoCode , char detail [ 140 ]); 
fcns.name{fcnNum}='fgt_get_pressureStatus'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint32', 'int32Ptr', 'uint16Ptr', 'uint8Ptr', 'int8Ptr'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_get_sensorStatus ( unsigned int sensorIndex , fgt_instrument_t * type , unsigned short * controllerSN , unsigned char * infoCode , char detail [ 140 ]); 
fcns.name{fcnNum}='fgt_get_sensorStatus'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint32', 'int32Ptr', 'uint16Ptr', 'uint8Ptr', 'int8Ptr'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_set_power ( unsigned int controllerIndex , unsigned char powerState ); 
fcns.name{fcnNum}='fgt_set_power'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint32', 'uint8'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_get_power ( unsigned int controllerIndex , unsigned char * powerState ); 
fcns.name{fcnNum}='fgt_get_power'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint32', 'uint8Ptr'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_set_TtlMode ( unsigned int TtlIndex , fgt_ttl_mode_t mode ); 
fcns.name{fcnNum}='fgt_set_TtlMode'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint32', 'int32'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_read_Ttl ( unsigned int TtlIndex , unsigned int * state ); 
fcns.name{fcnNum}='fgt_read_Ttl'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint32', 'uint32Ptr'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_trigger_Ttl ( unsigned int TtlIndex ); 
fcns.name{fcnNum}='fgt_trigger_Ttl'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint32'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_set_purge ( unsigned int controllerIndex , unsigned char purge ); 
fcns.name{fcnNum}='fgt_set_purge'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint32', 'uint8'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_set_manual ( unsigned int pressureIndex , float value ); 
fcns.name{fcnNum}='fgt_set_manual'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint32', 'single'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_set_digitalOutput ( unsigned int controllerIndex , unsigned char port , unsigned char state ); 
fcns.name{fcnNum}='fgt_set_digitalOutput'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint32', 'uint8', 'uint8'};fcnNum=fcnNum+1;
% unsigned char  _stdcall fgt_get_inletPressure ( unsigned int pressureIndex , float * pressure ); 
fcns.name{fcnNum}='fgt_get_inletPressure'; fcns.calltype{fcnNum}='stdcall'; fcns.LHS{fcnNum}='uint8'; fcns.RHS{fcnNum}={'uint32', 'singlePtr'};fcnNum=fcnNum+1;
structs.fgt_CHANNEL_INFO.members=struct('ControllerSN', 'uint16', 'firmware', 'uint16', 'DeviceSN', 'uint16', 'position', 'uint32', 'index', 'uint32', 'indexID', 'uint32', 'InstrType', 'int32');
structs.fgt_CONTROLLER_INFO.members=struct('SN', 'uint16', 'Firmware', 'uint16', 'id', 'uint32', 'InstrType', 'int32');
methodinfo=fcns;
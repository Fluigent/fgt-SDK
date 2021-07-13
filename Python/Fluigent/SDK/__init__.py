# -*- coding: utf-8 -*-
"""Module for communicating with Fluigent SDK"""
import os

from . import low_level
from . import exceptions

__version__ = "21.2.0"

# Enums
class fgt_ERROR(low_level.fgt_ERROR):
    """Returned error codes from dll functions"""
    
class fgt_POWER(low_level.fgt_POWER):
    """Power state"""
    
class fgt_TTL_MODE(low_level.fgt_TTL_MODE):
    """TTL setting mode"""
    
class fgt_SENSOR_TYPE(low_level.fgt_SENSOR_TYPE):
    """Sensor type"""

class fgt_INSTRUMENT_TYPE(low_level.fgt_INSTRUMENT_TYPE):
    """Instrument controller type"""
    
class fgt_SENSOR_CALIBRATION(low_level.fgt_SENSOR_CALIBRATION):
    """Sensor calibration table"""

class fgt_VALVE_TYPE(low_level.fgt_VALVE_TYPE):
    """Valve type"""
    
class fgt_SWITCH_DIRECTION(low_level.fgt_SWITCH_DIRECTION):
    """Switching direction for M-Switches"""
    
# Change enum instance types to the high level classes
def replace_enums():
    for enum_class in [fgt_ERROR, fgt_POWER, fgt_INSTRUMENT_TYPE,
                       fgt_SENSOR_CALIBRATION, fgt_SENSOR_TYPE, fgt_TTL_MODE]:
        values = enum_class.get_values()
        high_level_values = []
        for v in values:
            high_level_value = enum_class(int(v))
            high_level_values.append(high_level_value)
            setattr(enum_class, str(v), high_level_value)
        low_level.add_get_values(enum_class, high_level_values)
    
replace_enums()
del replace_enums

def format_firmware_version(bcd_version):
    return "{:x}.{:02x}".format(bcd_version >> 8, bcd_version & 0xFF)

# Instrument information structures
class fgt_CHANNEL_INFO(object):
    """Structure containing pressure or sensor identification and details"""
        
    def __init__(self, ll_fgt_CHANNEL_INFO):
        self.__controller_sn = ll_fgt_CHANNEL_INFO.ControllerSN
        self.__firmware = ll_fgt_CHANNEL_INFO.firmware
        self.__device_sn = ll_fgt_CHANNEL_INFO.DeviceSN
        self.__position = ll_fgt_CHANNEL_INFO.position
        self.__index = ll_fgt_CHANNEL_INFO.index
        self.__index_id = ll_fgt_CHANNEL_INFO.indexID
        self.__instr_type = fgt_INSTRUMENT_TYPE(ll_fgt_CHANNEL_INFO.type)
        
    @property
    def ControllerSN(self):
        """Serial number of this channel's controller"""
        return self.__controller_sn
    
    @property
    def firmware(self):
        """Firmware version of this channel (0 if not applicable)"""
        return self.__firmware
    
    @property
    def DeviceSN(self):
        """Serial number of this channel (0 if not applicable)"""
        return self.__device_sn
    
    @property
    def position(self):
        """Position on controller"""
        return self.__position
    
    @property
    def index(self):
        """Channel index within its physical quantities family"""
        return self.__index
    
    @property
    def indexID(self):
        """Unique channel identifier"""
        return self.__index_id
    
    @property
    def InstrType(self): 
        """Type of the instrument"""
        return self.__instr_type
    
    def formatattr(self, attr):
        if attr.lower() == "firmware":
            return "{}: {}".format(attr, format_firmware_version(getattr(self, attr)))
        else:
            return "{}: {}".format(attr, getattr(self, attr))
    
    def __repr__(self):
        fields = ["ControllerSN", "firmware", "DeviceSN", "position",
                  "index", "indexID", "InstrType"]
        return os.linesep.join([str(self.__class__)]
                       + [self.formatattr(attr) for attr in fields])
    
    def __int__(self):
        return self.__index_id

class fgt_CONTROLLER_INFO(object):
    """Structure containing controller identification and details"""
        
    def __init__(self, ll_fgt_CONTROLLER_INFO):
        self.__sn = ll_fgt_CONTROLLER_INFO.SN
        self.__firmware = ll_fgt_CONTROLLER_INFO.Firmware
        self.__id = ll_fgt_CONTROLLER_INFO.id
        self.__instr_type = fgt_INSTRUMENT_TYPE(ll_fgt_CONTROLLER_INFO.type)
        
    @property
    def SN(self):
        """Serial number"""
        return self.__sn
    
    @property
    def Firmware(self):
        """Firmware version"""
        return self.__firmware
    
    @property
    def index(self):
        """Index"""
        return self.__id
    
    @property
    def InstrType(self): 
        """Type of the instrument"""
        return self.__instr_type
    
    def formatattr(self, attr):
        if attr.lower() == "firmware":
            return "{}: {}".format(attr, format_firmware_version(getattr(self, attr)))
        else:
            return "{}: {}".format(attr, getattr(self, attr))
    
    def __repr__(self):
        fields = ["SN", "Firmware", "index", "InstrType"]
        return os.linesep.join([str(self.__class__)]
                       + [self.formatattr(attr) for attr in fields])
            
    def __int__(self):
        return self.__id
    
_get_error = False

def fgt_init(instruments = None):
    """Initialize or reinitialize the Fluigent SDK instance. 
    
    All detected Fluigent instruments (MFCS, MFCS-EZ, FRP, LineUP, IPS) are 
    initialized.
    This function is optional, directly calling a function will automatically
    create the instance.
    Only one instance can be opened at once. If called again, session is 
    reinitialized.
    
    If a list of serial numbers is passed to this function, only the 
    instruments whose serial numbers are in the list will be initialized.
    This can be used when multiple instruments are connected in order
    to select your device(s).
    
    Args:
        instruments: list containing the serial numbers of the instruments
                     default is None (initialize all instruments)
    
    See also:
        fgt_close
    """
    if instruments is None:
        c_error, = low_level.fgt_init()
    else:
        c_error, = low_level.fgt_initEx(instruments)
    exceptions.manage_generic_status("fgt_init", c_error)
    return fgt_ERROR(c_error)

def fgt_close():
    """Close communication with Fluigent instruments and free memory.
    
     Using this function will remove session preferences such as units 
     and limits. 
     If any regulation is running it will stop pressure control.
     """
    low_level_function = low_level.fgt_close
    c_error, = low_level_function()
    exceptions.manage_generic_status(low_level_function.__name__, c_error)
    return fgt_ERROR(c_error)
    
def fgt_get_controllersInfo(get_error = _get_error):
    """Retrieve information about session controllers. 
    
    Controllers are MFCS, Flowboard, Link and IPS.
     Returns:
         List of structure of fgt_CONTROLLER_INFO
     """
    low_level_function = low_level.fgt_get_controllersInfo
    c_error, channels = low_level_function()
    exceptions.manage_generic_status(low_level_function.__name__, c_error)
    c_error = fgt_ERROR(c_error)
    channels = [fgt_CONTROLLER_INFO(c) for c in channels]
    return (c_error, channels) if get_error else channels
    
def fgt_get_pressureChannelCount(get_error = _get_error):
    """Get total number of initialized pressure channels. 
    
    It is the sum of all MFCS, MFCS-EZ and Flow EZ pressure controllers.
    
    Returns:
        the total number of initialized pressure channels.
    See also:
        fgt_get_pressureChannelsInfo
     """
    low_level_function = low_level.fgt_get_pressureChannelCount
    c_error, count = low_level_function()
    exceptions.manage_generic_status(low_level_function.__name__, c_error)
    c_error = fgt_ERROR(c_error)
    return (c_error, count) if get_error else count
    
def fgt_get_sensorChannelCount(get_error = _get_error):
    """Get total number of initialized sensor channels. 
    
    It is the sum of all connected Flow Units on Flowboard and Flow EZ
    and IPS modules.
    
    Returns:
        the total number of initialized sensor channels.
    See also:
        fgt_get_sensorChannelsInfo
     """
    low_level_function = low_level.fgt_get_sensorChannelCount
    c_error, count = low_level_function()
    exceptions.manage_generic_status(low_level_function.__name__, c_error)
    c_error = fgt_ERROR(c_error)
    return (c_error, count) if get_error else count

def fgt_get_TtlChannelCount(get_error = _get_error):
    """Get total number of initialized TTL channels. 
    
    It is the sum of all connected Link TTL ports.
    
    Returns:
        the total number of initialized TTL channels.
     """
    low_level_function = low_level.fgt_get_TtlChannelCount
    c_error, count = low_level_function()
    exceptions.manage_generic_status(low_level_function.__name__, c_error)
    c_error = fgt_ERROR(c_error)
    return (c_error, count) if get_error else count
    
def fgt_get_valveChannelCount(get_error = _get_error):
    """Get total number of initialized valve channels. 
    
    It is the sum of all connected Two-Switch, L-Switch and M-Switch
    valves connected to Switchboard or Switch EZ devices, as well
    as individual P-Switch outputs (8 per device).
    
    Returns:
        the total number of initialized valve channels.
    See also:
        fgt_get_valveChannelsInfo
     """
    low_level_function = low_level.fgt_get_valveChannelCount
    c_error, count = low_level_function()
    exceptions.manage_generic_status(low_level_function.__name__, c_error)
    c_error = fgt_ERROR(c_error)
    return (c_error, count) if get_error else count

def fgt_get_pressureChannelsInfo(get_error = _get_error):
    """Retrieve information about initialized pressure channels.
    
    This function is useful in order to get channels order, controller, 
    unique ID and instrument type.
    By default this array is built with MFCS first, MFCS-EZ second and 
    Flow EZ last. 
    If only one instrument is used, index is the default channel indexing 
    starting at 0.
    You can initialize instruments in a specific order by passing the list of
    serial numbers to fgt_init.
    
    Returns:
        list of fgt_CHANNEL_INFO
    """
    low_level_function = low_level.fgt_get_pressureChannelsInfo
    c_error, channels = low_level_function()
    exceptions.manage_generic_status(low_level_function.__name__, c_error)
    c_error = fgt_ERROR(c_error)
    channels = [fgt_CHANNEL_INFO(c) for c in channels]
    return (c_error, channels) if get_error else channels
    
def fgt_get_sensorChannelsInfo(get_error = _get_error):
    """Retrieve information about initialized sensor channels. 
    
    This function is useful in order to get channels order, controller, 
    unique ID and instrument type.
    By default this array is built with FRP Flow Units first, then Flow EZ 
    Flow Units, then IPS modules. If only one instrument is used, index is the 
    default channel indexing starting at 0.
    You can initialize instruments in a specific order by passing the list of
    serial numbers to fgt_init.
    
    Returns:
        (channel_info, channel_type):
            channel_info: list of fgt_CHANNEL_INFO
            channel_type: list of fgt_SENSOR_TYPE
    """
    low_level_function = low_level.fgt_get_sensorChannelsInfo
    c_error, channels, types = low_level_function()
    exceptions.manage_generic_status(low_level_function.__name__, c_error)
    c_error = fgt_ERROR(c_error)
    channels = [fgt_CHANNEL_INFO(c) for c in channels]
    types = [fgt_SENSOR_TYPE(t) for t in types]
    return (c_error, channels, types) if get_error else (channels, types)
    
def fgt_get_TtlChannelsInfo(get_error = _get_error):
    """Retrieve information about each initialized TTL channel. 
    
    This function is useful in order to get channels order, controller, 
    unique ID and instrument type.
    TTL channels are only available for LineUP Series, 2 ports for each 
    connected Link.
    
    Returns: 
        list of fgt_CHANNEL_INFO
    """
    low_level_function = low_level.fgt_get_TtlChannelsInfo
    c_error, channels = low_level_function()
    exceptions.manage_generic_status(low_level_function.__name__, c_error)
    c_error = fgt_ERROR(c_error)
    channels = [fgt_CHANNEL_INFO(c) for c in channels]
    return (c_error, channels) if get_error else channels
    
def fgt_get_valveChannelsInfo(get_error = _get_error):
    """Retrieve information about initialized valve channels. 
    
    This function is useful in order to get channels order, controller, 
    unique ID and instrument type.
    You can initialize instruments in a specific order by passing the list of
    serial numbers to fgt_init.
    
    Returns:
        (channel_info, channel_type):
            channel_info: list of fgt_CHANNEL_INFO
            channel_type: list of fgt_VALVE_TYPE
    """
    low_level_function = low_level.fgt_get_valveChannelsInfo
    c_error, channels, types = low_level_function()
    exceptions.manage_generic_status(low_level_function.__name__, c_error)
    c_error = fgt_ERROR(c_error)
    channels = [fgt_CHANNEL_INFO(c) for c in channels]
    types = [fgt_VALVE_TYPE(t) for t in types]
    return (c_error, channels, types) if get_error else (channels, types)
    
def fgt_set_sessionPressureUnit(unit):
    """Set pressure unit for all initialized channels.
    
    Default value is "mbar". 
    If the unit is invalid the previous unit is kept and an error is logged.
    Every pressure read value and sent command will then use this unit.
    
    Args:
        unit: the desired unit as a string
    Examples: 
        fgt_set_sessionPressureUnit("mbar")
        fgt_set_sessionPressureUnit("psi")
    See also:
        fgt_get_pressureStatus
    """
    low_level_function = low_level.fgt_set_sessionPressureUnit
    c_error, = low_level_function(unit)
    exceptions.manage_generic_status(low_level_function.__name__, c_error)
    return fgt_ERROR(c_error)
    
def fgt_set_pressureUnit(pressure_index, unit):
    """Set pressure unit on selected pressure device.
    
    Default value is "mbar". 
    If the unit is invalid the previous unit is kept and an error is logged.
    Every pressure read value and sent command will then use this unit.

    Args:
        presureIndex: Index of pressure channel or unique ID
        unit: the desired unit as a string
    Examples: 
        fgt_set_pressureUnit(0, "mbar")
        fgt_set_pressureUnit(1, "psi")
    See also:
        fgt_get_pressureStatus
     """
    pressure_index = int(pressure_index)
    low_level_function = low_level.fgt_set_pressureUnit
    c_error, = low_level_function(pressure_index, unit)
    exceptions.manage_pressure_status(low_level_function.__name__, pressure_index)
    return fgt_ERROR(c_error)
    
def fgt_get_pressureUnit(pressure_index, get_error = _get_error):
    """Get current unit on selected pressure device.
    
    Args:
        pressure_index: Index of pressure channel or unique ID
    Returns:
        current unit as a string
    """
    pressure_index = int(pressure_index)
    low_level_function = low_level.fgt_get_pressureUnit
    c_error, unit = low_level_function(pressure_index)
    exceptions.manage_pressure_status(low_level_function.__name__, pressure_index)
    c_error = fgt_ERROR(c_error)
    return (c_error, unit) if get_error else unit
    
def fgt_set_sensorUnit(sensor_index, unit):
    """Set sensor unit on selected sensor device.
    Default value is "µl/min" for Flow Units. 
    If type is invalid an error is returned.
    Every sensor read value and regulation command will then use this unit.
    Example: "µl/h", "ulperDay", "microliter/hour" ...
    
    Not supported by the IPS.
    
    Args:
        sensor_index: Index of sensor channel or unique ID
        unit: desired unit as a string
    Examples: 
        fgt_set_sensorUnit(0, "µl/h")
        fgt_set_sensorUnit(1, "ulperDay")
     """
    sensor_index = int(sensor_index)
    low_level_function = low_level.fgt_set_sensorUnit
    c_error, = low_level_function(sensor_index, unit)
    exceptions.manage_sensor_status(low_level_function.__name__, sensor_index)
    return fgt_ERROR(c_error)

def fgt_get_sensorUnit(sensor_index, get_error = _get_error):
    """Get current unit on selected sensor device.
    
    Args:
        sensor_index: Index of sensor channel or unique ID
    Returns:
        current unit as a string. Default unit is 'µl/min' for Flow Units
        and 'mbar' for IPS modules.
    """
    sensor_index = int(sensor_index)
    low_level_function = low_level.fgt_get_sensorUnit
    c_error, unit = low_level_function(sensor_index)
    exceptions.manage_sensor_status(low_level_function.__name__, sensor_index)
    c_error = fgt_ERROR(c_error)
    return (c_error, unit) if get_error else unit
    
def fgt_set_sensorCalibration(sensor_index, calibration):
    """Set sensor calibration table or zero value. 
    
    For Flow Units supporting multiple calibration tables such as the Flow Unit
    M accepting H2O and IPA, calling this function sets the calibration table
    currently in use.
    
    For IPS modules, calling this function sets the current pressure
    measurement as the sensor's zero value.
    
    Args:
        sensor_index: Index of sensor channel or unique ID
        calibration: value from the fgt_SENSOR_CALIBRATION enum
                     If the sensor is not a Flow Unit, this argument is ignored
    """
    sensor_index = int(sensor_index)
    exceptions.check_enum_type("calibration", calibration, fgt_SENSOR_CALIBRATION)
    low_level_function = low_level.fgt_set_sensorCalibration
    c_error, = low_level_function(sensor_index, int(calibration))
    exceptions.manage_sensor_status(low_level_function.__name__, sensor_index)
    return fgt_ERROR(c_error)
    
def fgt_get_sensorCalibration(sensor_index, get_error = _get_error):
    """Get sensor's current calibration table, if applicable.
    
    Not supported by the IPS.
    
    Args:
        sensor_index: Index of sensor channel or unique ID
    Returns:
        Current calibration table as a value from the 
        fgt_SENSOR_CALIBRATION enum
        "None" if the sensor does not support calibration tables
    """
    sensor_index = int(sensor_index)
    low_level_function = low_level.fgt_get_sensorCalibration
    c_error, calibration = low_level_function(sensor_index)
    exceptions.manage_sensor_status(low_level_function.__name__, sensor_index)
    calibration = fgt_SENSOR_CALIBRATION(calibration)
    c_error = fgt_ERROR(c_error)
    return (c_error, calibration) if get_error else calibration
    
def fgt_set_sensorCustomScale(sensor_index, a, b = 0, c = 0, smax = None):
    """Apply a custom scale factor on sensor measurement.
    
    This function is useful in order to adapt read sensor value to 
    physical measurement.
    For example if a Flow Unit is used with a special oil and its 
    calibration table is set to H2O, read flowrate is not correct.
    Scale factor is applied using following formula:
        scaled_value = a*sensor_value + b*sensor_value^2 + c*sensor_value^3
    When applying a custom scale factor, sensor range may increase very 
    rapidly, SMax parameter is meant to limit this maximal value.
    This function purpose is to be used with the regulation in order to
    avoid too high maximum range on the sensor.
    
    Not supported by the IPS.
    
    Args:
        sensor_index: Index of sensor channel or unique ID
        a: proportional multiplier value
        b: square multiplier value, default is 0
        c: cubic multiplier value, default is 0
        smax: after scale maximal value (saturation), default is None (no limit)
    """
    sensor_index = int(sensor_index)
    if smax is None:
        c_error, = low_level.fgt_set_sensorCustomScale(sensor_index, a, b, c)
    else:
        c_error, = low_level.fgt_set_sensorCustomScaleEx(sensor_index, a, b, c, smax)
    exceptions.manage_sensor_status("fgt_set_sensorCustomScale", sensor_index)
    return fgt_ERROR(c_error)
    
def fgt_calibratePressure(pressure_index):
    """Calibrate internal pressure sensor.
    After calling this function 0 pressure value corresponds to 
    atmospheric pressure.
    During calibration step no pressure order is accepted. 
    Total duration varies from 3 to 8 seconds.
    
    Args:
        pressure_index: Index of pressure channel or unique ID
    """
    pressure_index = int(pressure_index)
    low_level_function = low_level.fgt_calibratePressure
    c_error, = low_level_function(pressure_index)
    exceptions.manage_pressure_status(low_level_function.__name__, pressure_index)
    return fgt_ERROR(c_error)
    
def fgt_set_pressure(pressure_index, pressure):
    """Send pressure command to selected device.
    
    Args:
        pressure_index: Index of pressure channel or unique ID
        pressure: Pressure order in selected unit, default is "mbar"
    See also:
        fgt_set_sensorRegulation
        fgt_get_pressureStatus
    """
    pressure_index = int(pressure_index)
    low_level_function = low_level.fgt_set_pressure
    c_error, = low_level_function(pressure_index, pressure)
    exceptions.manage_pressure_status(low_level_function.__name__, pressure_index)
    return fgt_ERROR(c_error)
    
def fgt_get_pressure(pressure_index, include_timestamp = False, get_error = _get_error):
    """Read pressure value of selected device. 
    
    Optionally, also returns a timestamp from the device's internal timer.
    
    Args:
        pressure_index: Index of pressure channel or unique ID
        include_timestamp: Include the timestamp in the return value.
                           Default is False
    Returns:
        if include_timestamp is False:
            pressure measurement value in the selected unit (default is "mbar")
        if include_timestamp is True:
            tuple containing:
             pressure measurement value in the selected unit
             timeStamp Hardware timer in ms
             
    Examples:
        pressure = fgt_get_pressure(0)
        pressure, timestamp = fgt_get_pressure(0, True)
        
    See also:
        fgt_get_pressureStatus
    """
    pressure_index = int(pressure_index)
    if include_timestamp:
        c_error, pressure, timestamp = low_level.fgt_get_pressureEx(pressure_index)
        exceptions.manage_pressure_status("fgt_get_pressure", pressure_index)
        c_error = fgt_ERROR(c_error)
        return (c_error, pressure, timestamp) if get_error else (pressure, timestamp)
    else:
        c_error, pressure = low_level.fgt_get_pressure(pressure_index)
        exceptions.manage_pressure_status("fgt_get_pressure", pressure_index)
        c_error = fgt_ERROR(c_error)
        return (c_error, pressure) if get_error else pressure

def fgt_set_sensorRegulation(sensor_index, pressure_index, setpoint):
    """Start closed loop regulation 
    
    Pressure will be regulated in order to reach sensor setpoint.
    Call this function again in order to change the setpoint. 
    Calling fgt_set_pressure on the same pressure_index will stop regulation.
    
    Not supported by the IPS.
    
    Args:
        sensor_index: Index of sensor channel or unique ID
        pressure_index: Index of pressure channel or unique ID
        setpoint: Regulation value to be reached in the selected unit.
                    Default is "µl/min" for flowrate sensors
    See also:
        fgt_set_pressure
        fgt_set_customSensorRegulation
        fgt_set_sensorRegulationResponse
    """
    sensor_index = int(sensor_index)
    pressure_index = int(pressure_index)
    low_level_function = low_level.fgt_set_sensorRegulation
    c_error, = low_level_function(sensor_index, pressure_index, setpoint)
    exceptions.manage_sensor_status(low_level_function.__name__, sensor_index)
    return fgt_ERROR(c_error)
    
def fgt_get_sensorValue(sensor_index, include_timestamp = False, get_error = _get_error):
    """Read sensor value of selected device
    
     Optionally, also returns a timestamp from the device's internal timer.
     Note: If the sensor is an IPS, the timestamp is always zero
    
    Args:
        sensor_index Index of sensor channel or unique ID
        include_timestamp: Include the timestamp in the return value.
                           Default is False
            
    Returns:
        if include_timestamp is False:
            value Read sensor value in selected unit
            Default is "µl/min" for flow rate sensors and "mbar" for the IPS
        if include_timestamp is True:
            tuple containing:
             value Read sensor value in selected unit
             timeStamp Hardware timer in ms
             
    Examples:
        sensor_value = fgt_get_sensorValue(0)
        sensor_value, timestamp = fgt_get_sensorValue(0, True)
        
    See also:
        fgt_set_sensorRegulation
    """
    sensor_index = int(sensor_index)
    if include_timestamp:
        c_error, sensorMeasurement, timestamp = low_level.fgt_get_sensorValueEx(sensor_index)
        exceptions.manage_sensor_status("fgt_get_sensorValue", sensor_index)
        c_error = fgt_ERROR(c_error)
        return (c_error, sensorMeasurement, timestamp) if get_error else (sensorMeasurement, timestamp)
    else:
        c_error, sensorMeasurement =  low_level.fgt_get_sensorValue(sensor_index)
        exceptions.manage_sensor_status("fgt_get_sensorValue", sensor_index)
        c_error = fgt_ERROR(c_error)
        return (c_error, sensorMeasurement) if get_error else sensorMeasurement
    
def fgt_set_customSensorRegulation(measure, command, max_sensor_range, pressure_index):
    """Start closed loop regulation with manual sensor update
    
    Pressure will be regulated in order to reach sensor setpoint.
    Custom sensors, outside Fluigent ones, can be used such as different 
    Flow Units, pressure, level etc.
    However we do not guarantee full compatibility with all sensors. 
    Regulation quality is linked to sensor precision and your setup.
    In order to use this function, custom used sensor maximum range and 
    measured values have to be updated at least once per second.
    Directly setting pressure on same pressure_index will stop regulation.
    This function must be called at 1Hz minimum or the regulation will stop.
    
    Args:
        measure: custom sensor measured value, no unit is required
        setpoint: custom sensor regulation goal value, no unit is required
        pressure_index: Index of pressure channel or unique ID
        maxSensorRange: custom sensor maximum range, no unit is required
    """
    pressure_index = int(pressure_index)
    low_level_function = low_level.fgt_set_customSensorRegulation
    c_error, = low_level_function(measure, command, max_sensor_range, pressure_index)
    exceptions.manage_generic_status(low_level_function.__name__, c_error)
    return fgt_ERROR(c_error)
    
def fgt_set_valvePosition(valve_index, position, direction = fgt_SWITCH_DIRECTION.Shortest, wait = True):
    """Change the position of the selected valve.
    
    Args:
        valve_index: Index of valve channel or unique ID
        position: Target position
        direction: direction to turn for M-Switches
        wait: if true, block until the valve arrives at the requested position
    """
    valve_index = int(valve_index)
    low_level_function = low_level.fgt_set_valvePosition
    c_error, = low_level_function(valve_index, position, direction, wait)
    exceptions.manage_generic_status(low_level_function.__name__, c_error)
    
def fgt_get_valvePosition(valve_index, get_error = _get_error):
    """Read the position of a specific valve channel.
    
    Args:
        valve_index: Index of valve channel or unique ID
    """
    valve_index = int(valve_index)
    low_level_function = low_level.fgt_get_valvePosition
    c_error, position = low_level_function(valve_index)
    exceptions.manage_generic_status(low_level_function.__name__, c_error)
    c_error = fgt_ERROR(c_error)
    return (c_error, position) if get_error else position

def fgt_set_allValves(controller_index, module_index, position):
    """Set the position of all two positional valves connected to
       specified controller / module
       
    Args:
        controller_index: Index of the controller (supported only by LineUp and ESS)
        module_index: Index of the module (supported only by P-Switch)
        position: Target position (0 or 1)
    """
    controller_index = int(controller_index)
    module_index = int(module_index)
    low_level_function = low_level.fgt_set_allValves
    c_error, = low_level_function(controller_index, module_index, position)
    exceptions.manage_generic_status(low_level_function.__name__, c_error)
    return fgt_ERROR(c_error)

def fgt_get_pressureRange(pressure_index, get_error = _get_error):
    """Get pressure controller minimum and maximum range. 
    
    Returned values takes into account set unit. Default value is 'mbar'.
    
    Args:
        pressure_index: Index of sensor channel or unique ID
    Returns:
        (pmin, pmax):
            minimum device pressure
            maximum device pressure
    """
    pressure_index = int(pressure_index)
    low_level_function = low_level.fgt_get_pressureRange
    c_error, pressure_min, pressure_max = low_level_function(pressure_index)
    exceptions.manage_pressure_status(low_level_function.__name__, pressure_index)
    c_error = fgt_ERROR(c_error)
    return (c_error, pressure_min, pressure_max) if get_error else (pressure_min, pressure_max)

def fgt_get_sensorRange(sensor_index, get_error = _get_error):
    """Get sensor minimum and maximum range. 
    
    Returned values takes into account set unit. Default value is 
    'µl/min' in case of Flow Units and 'mbar' for IPS modules.
    
    Args:
        sensor_index: Index of sensor channel or unique ID
    Returns:
        (smin, smax):
            minimum measured sensor value
            maximum measured sensor value
    """
    sensor_index = int(sensor_index)
    low_level_function = low_level.fgt_get_sensorRange
    c_error, sensor_min, sensor_max = low_level_function(sensor_index)
    exceptions.manage_sensor_status(low_level_function.__name__, sensor_index)
    c_error = fgt_ERROR(c_error)
    return (c_error, sensor_min, sensor_max) if get_error else (sensor_min, sensor_max)
    
def fgt_get_valveRange(valve_index, get_error = _get_error):
    """Get valve maximum position.
    
    Position indexing starts at 0. 
        
    Args:
        valve_index: Index of sensor channel or unique ID
    Returns:
        posMax: maximum valve position
    """
    valve_index = int(valve_index)
    low_level_function = low_level.fgt_get_valveRange
    c_error, pos_max = low_level_function(valve_index)
    exceptions.manage_generic_status(low_level_function.__name__, c_error)
    c_error = fgt_ERROR(c_error)
    return (c_error, pos_max) if get_error else pos_max

def fgt_set_pressureLimit(pressure_index, p_lim_min, p_lim_max):
    """Set pressure hard limits. 
    
    Pressure setpoint will not exceed these limit during regulation.
    It takes into account current unit, default value is 'mbar'.
    This function is useful to protect your microfluidic system.
    
    Args:
        pressure_index: Index of pressure channel or unique ID
        p_lim_min: minimum admissible device pressure
        p_lim_max: maximum admissible device pressure
    """
    pressure_index = int(pressure_index)
    low_level_function = low_level.fgt_set_pressureLimit
    c_error, = low_level_function(pressure_index, p_lim_min, p_lim_max)
    exceptions.manage_pressure_status(low_level_function.__name__, pressure_index)
    return fgt_ERROR(c_error)

def fgt_set_sensorRegulationResponse(sensor_index, response_time):
    """Set on a running regulation pressure response time. 
    
    Minimal value is 2 for Flow EZ, 6 for MFCS controllers.
    This function is useful if a more smooth response is wanted.
    
    Not supported by the IPS.
    
    Args:
        sensor_index: Index of sensor channel or unique ID
        responseTime: pressure response time in seconds
    """
    sensor_index = int(sensor_index)
    low_level_function = low_level.fgt_set_sensorRegulationResponse
    c_error, = low_level_function(sensor_index, response_time)
    exceptions.manage_sensor_status(low_level_function.__name__, sensor_index)
    return fgt_ERROR(c_error)

def fgt_set_pressureResponse(pressure_index, response_mode):
    """Set pressure controller response. 
    
    This function can be used to customise response time for your setup.
    For Flow EZ available values are 0 (use of fast switch valves) or 
    1 (do not use fast switch valves). Default value is 0.
    For MFCS available values are from 1 to 255. The higher the value, 
    the longer the response time. Default value is 5.
    
    Args:
        pressure_index: Index of pressure channel or unique ID
        value: desired pressure controller response time, this depends 
               on controller type
    """
    pressure_index = int(pressure_index)
    low_level_function = low_level.fgt_set_pressureResponse
    c_error, = low_level_function(pressure_index, response_mode)
    exceptions.manage_pressure_status(low_level_function.__name__, pressure_index)
    return fgt_ERROR(c_error)
    
def fgt_set_power(controller_index, power_state):
    """Set power ON or OFF on a controller.
    
    Not all controllers support this functionality.
    
    Args:
        controller_index: Index of controller or unique ID
        powerState: value in the fgt_POWER enum
    """
    controller_index = int(controller_index)
    exceptions.check_enum_type("power_state", power_state, fgt_POWER)
    low_level_function = low_level.fgt_set_power
    c_error, = low_level_function(controller_index, int(power_state))
    exceptions.manage_generic_status(low_level_function.__name__, c_error)
    return fgt_ERROR(c_error)
    
def fgt_get_power(controller_index, get_error = _get_error):
    """Get power information about a controller.
    
    Not all controllers support this functionality.
    Args:
        controller_index: Index of controller or unique ID
        
    Returns:
        value in the fgt_POWER enum
    """
    controller_index = int(controller_index)
    low_level_function = low_level.fgt_get_power
    c_error, power_state = low_level_function(controller_index)
    exceptions.manage_generic_status(low_level_function.__name__, c_error)
    power_state = fgt_POWER(power_state)
    c_error = fgt_ERROR(c_error)
    return (c_error, power_state) if get_error else power_state
    
def fgt_set_TtlMode(ttl_index, mode):
    """Configure a specific TTL port.
    
    Port can be configured as as input or output, rising or falling edge.
    
    Args:
        ttl_index: Index of TTL port or unique ID
        mode: value in the fgt_TTL_MODE enum
    """
    ttl_index = int(ttl_index)
    exceptions.check_enum_type("mode", mode, fgt_TTL_MODE)
    low_level_function = low_level.fgt_set_TtlMode
    c_error, = low_level_function(ttl_index, int(mode))
    exceptions.manage_generic_status(low_level_function.__name__, c_error)
    return fgt_ERROR(c_error)

def fgt_read_Ttl(ttl_index, get_error = _get_error):
    """Read TTL port (BNC port) if set as input.
    
    Args:
        ttl_index: Index of TTL port or unique ID
    
    Returns 
        0: no edge was detected 
        1: an edge was detected
    See also:
        fgt_set_TtlMode
    """
    ttl_index = int(ttl_index)
    low_level_function = low_level.fgt_read_Ttl
    c_error, ttl_state = low_level_function(ttl_index)
    exceptions.manage_generic_status(low_level_function.__name__, c_error)
    c_error = fgt_ERROR(c_error)
    return (c_error, ttl_state) if get_error else ttl_state
    
def fgt_trigger_Ttl(ttl_index):
    """Trigger a specific TTL port if it is in output mode.
    
    Args:
        ttl_index: Index of TTL port or unique ID
    See also:
        fgt_set_TtlMode
    """
    ttl_index = int(ttl_index)
    low_level_function = low_level.fgt_trigger_Ttl
    c_error, = low_level_function(ttl_index)
    exceptions.manage_generic_status(low_level_function.__name__, c_error)
    return fgt_ERROR(c_error)
    
def fgt_set_purge(controller_index, purge_state):
    """Activate/deactivate purge function.
    
    This feature is only available on MFCS devices equipped with special valve.
    
    Args:
        controller_index: Index of controller or unique ID
        purge_state 0: OFF, 1:ON
    """
    controller_index = int(controller_index)
    low_level_function = low_level.fgt_set_purge
    c_error, = low_level_function(controller_index, purge_state)
    exceptions.manage_generic_status(low_level_function.__name__, c_error)
    return fgt_ERROR(c_error)
    
def fgt_set_manual(pressure_index, voltage):
    """Manually set internal solenoid valve voltage. 
    
    This stops pressure regulation on the channel.
    
    This feature is only available on MFCS and MFCS-EZ devices.
    
    Args:
        pressure_index: Index of pressure channel or unique ID
        voltage: applied valve voltage from 0 to 100(%)
    """
    pressure_index = int(pressure_index)
    low_level_function = low_level.fgt_set_manual
    c_error, = low_level_function(pressure_index, voltage)
    exceptions.manage_pressure_status(low_level_function.__name__, pressure_index)
    return fgt_ERROR(c_error)
    
def fgt_detect():
    """Detect all connected Fluigent instruments.
    
    Returns: 
        (instr_sns, instr_types):
            instr_sns: list with the serial numbers from each instrument
            instr_types: list of values from the fgt_INSTRUMENT_TYPE enum
    See also:
        fgt_init
    """
    low_level_function = low_level.fgt_detect
    n_instruments, serial_numbers, instr_types = low_level_function()
    return serial_numbers, [fgt_INSTRUMENT_TYPE(i) for i in instr_types]
        
# -*- coding: utf-8 -*-
"""
Wrapper for the shared library. Functions that return more than one value will
return a tuple containing all of the outputs in order, starting from the
error code.
"""
import sys
import platform
import os
import pkg_resources
import ctypes
from ctypes import byref, c_ubyte, c_ushort, c_uint, c_char, c_int, c_float, POINTER, Structure

_is_64_bits = sys.maxsize > 2**32
_platform = sys.platform
_os_name = _platform.lower()
_machine = platform.machine()
_processor_arch = _machine.lower()
_is_windows = _os_name.startswith("win32")
_is_linux = _os_name.startswith("linux")
_is_osx = _os_name.startswith("darwin")
_is_x86 = _processor_arch.startswith("x86") or _processor_arch.startswith("amd")
_is_arm = _processor_arch.startswith('arm') or _processor_arch.startswith('aarch')
_libclass = ctypes.CDLL
_lib_relative_path = ["shared"]
_lib_name = "fgt_SDK"
def _raise_system_not_supported():
    raise NotImplementedError("SDK not supported on {} with architecture {} ({} bits)".
                              format(_platform, _machine, "64" if _is_64_bits else "32"))

# Determine OS
if _is_windows:
    _libclass = ctypes.WinDLL
    _lib_relative_path.append("windows")
    _lib_name = _lib_name + ".dll"
elif _is_linux:
    _lib_name = "lib" + _lib_name + ".so"
    _lib_relative_path.append("linux")
elif _is_osx:
    _lib_name = "lib" + _lib_name + ".dylib"
    _lib_relative_path.append("mac")

# Determine architecture    
if _is_x86 and _is_64_bits:
    _lib_relative_path.append("x64")
elif _is_x86 and not _is_64_bits:
    _lib_relative_path.append("x86")
if _is_arm and _is_64_bits:
    _lib_relative_path.append("arm64")
elif _is_arm and not _is_64_bits:
    _lib_relative_path.append("arm")

# Find shared library in package
resource_package = __name__
resource_path = '/'.join(_lib_relative_path)
_libdir = pkg_resources.resource_filename(resource_package, resource_path)
_libpath = os.path.join(_libdir, _lib_name)
if not(os.path.exists(_libpath)): _raise_system_not_supported()
lib = _libclass(_libpath) 

if sys.version_info.major >= 3:
    # Python 3 specific code
    c_char_converter = lambda c: ord(c)
    mu_converter = lambda unit: unit
elif sys.version_info.major == 2:
    # Python 2 specific code
    c_char_converter = lambda c: c
    has_mu_char = lambda unit: len(unit) > 0 and ord(unit[0]) > 128 and True or False
    mu_converter = lambda unit: has_mu_char(unit) and unit.replace(unit[0], "u") or unit 

# Enums
class fgt_ENUM(object):
    """"""
    def __init__(self, value):
        if value not in self.reverse_mapping.keys():
            raise ValueError("Invalid enum value {}".format(value))
        self.__value = value
        
    def __int__(self):
        return self.__value
    
    def __str__(self):
        return self.reverse_mapping[self.__value]
    
    def __repr__(self):
        return "{}: {} ({})".format(self.__class__.__name__, int(self), str(self))
    
    def __eq__(self, other):
        if type(other) is int:
            return self.__value == other
        return self.__class__ == other.__class__ and self.__value == other.__value

def add_get_values(enum_class, values):
    values_copy = [v for v in values]
    setattr(enum_class, "get_values", staticmethod(lambda:values_copy))

def make_enum(className, *sequential, **named):
    base_enums = dict(zip(sequential, range(len(sequential))), **named)
    enums = dict(zip(sequential, range(len(sequential))), **named)
    reverse = dict((value, key) for key, value in enums.items())
    enums["reverse_mapping"] = reverse
    newType = type(className, (fgt_ENUM,), enums)
    values = []
    # Assign an instance of the class to each enum value
    for key, value in base_enums.items():
        instance = newType(value)
        values.append(instance)
        setattr(newType, key, instance)
    # Add method to return the list of enum instances sorted by the integer value
    values.sort(key = lambda v : int(v))
    add_get_values(newType, values)
    return newType

fgt_ERROR = make_enum("fgt_ERROR", 
                 "OK", "USB_error", "Wrong_command", 
                 "No_module_at_index", "Wrong_module", "Module_is_sleep", 
                 "Master_error", "Failed_init_all_instr", "Wrong_parameter", 
                 "Overpressure", "Underpressure", "No_instr_found", 
                 "No_modules_found", "No_pressure_controller_found", 
                 "Calibrating", "Dll_dependency_error", "Processing")

fgt_POWER = make_enum("fgt_POWER", 
                 "POWER_OFF","POWER_ON", "SLEEP")

fgt_TTL_MODE = make_enum("fgt_TTL_MODE",
                    "DETECT_RISING_EDGE", "DETECT_FALLING_EDGE",
                    "OUTPUT_PULSE_LOW","OUTPUT_PULSE_HIGH")
   
fgt_SENSOR_TYPE = make_enum("fgt_SENSOR_TYPE",
                       "NONE", "Flow_XS_single", "Flow_S_single", 
                       "Flow_S_dual", "Flow_M_single", "Flow_M_dual", 
                       "Flow_L_single", "Flow_L_dual", "Flow_XL_single",
                       "Pressure_S", "Pressure_M", "Pressure_XL")
 
fgt_INSTRUMENT_TYPE = make_enum("fgt_INSTRUMENT_TYPE",
                           "NONE","MFCS","MFCS_EZ","FRP","LineUP", "IPS", "ESS")

fgt_SENSOR_CALIBRATION = make_enum("fgt_SENSOR_CALIBRATION",
                                      "NONE", "H2O", "IPA", "HFE", "FC40", 
                                      "OIL")
                                      
fgt_VALVE_TYPE = make_enum("fgt_VALVE_TYPE", "NONE", "MSwitch", "TwoSwitch", "LSwitch", "PSwitch")

fgt_SWITCH_DIRECTION = make_enum("fgt_SWITCH_DIRECTION", "Shortest", "Anticlockwise", "Clockwise")
    
# Structures
class fgt_STRUCT(Structure):
    def __repr__(self):
        return os.linesep.join([str(self.__class__)] 
                       + ["{}: {}".format(attr, getattr(self, attr))
                       for attr, data_type in self._fields_])
    
    def __getitem__(self, item):
        return getattr(self, item)
    
class fgt_CHANNEL_INFO(fgt_STRUCT):
    """Structure containing pressure or sensor identification and details
    
        ControllerSN: Serial number of this channel's controller
        firmware: Firmware version of this channel (0 if not applicable)
        DeviceSN: Serial number of this channel (0 if not applicable) 
        position: Position on controller 
        index: Channel index within its physical quantities family 
        indexID: Unique channel identifier 
        InstrType: Type of the instrument 
        """
    _fields_ = [("ControllerSN", c_ushort),
                ("firmware", c_ushort),
                ("DeviceSN", c_ushort), 
                ("position", c_uint), 
                ("index", c_uint),
                ("indexID", c_uint),
                ("type", c_uint)]

class fgt_CONTROLLER_INFO(fgt_STRUCT):
    """Structure containing controller identification and details
        
        SN Serial number
        Firmware: Firmware version
        id: Index
        InstrType: Instrument type
        """
    _fields_ = [("SN", c_ushort),
                ("Firmware", c_ushort),
                ("id", c_uint), 
                ("type", c_uint)]

# Function prototypes
lib.restype = c_ubyte
lib.fgt_init.argtypes = []
lib.fgt_initEx.argtypes = [POINTER(c_ushort)]
lib.fgt_close.argtypes = []
lib.fgt_get_controllersInfo.argtypes = [POINTER(fgt_CONTROLLER_INFO)] 
lib.fgt_get_pressureChannelCount.argtypes = [POINTER(c_ushort)]
lib.fgt_get_sensorChannelCount.argtypes = [POINTER(c_ushort)]
lib.fgt_get_TtlChannelCount.argtypes = [POINTER(c_ushort)]
lib.fgt_get_valveChannelCount.argtypes = [POINTER(c_ubyte)]
lib.fgt_get_pressureChannelsInfo.argtypes = [POINTER(fgt_CHANNEL_INFO)] 
lib.fgt_get_sensorChannelsInfo.argtypes = [POINTER(fgt_CHANNEL_INFO), POINTER(c_int)]
lib.fgt_get_TtlChannelsInfo.argtypes = [POINTER(fgt_CHANNEL_INFO)] 
lib.fgt_get_valveChannelsInfo.argtypes = [POINTER(fgt_CHANNEL_INFO), POINTER(c_int)]
lib.fgt_set_sessionPressureUnit.argtypes = [POINTER(c_char)]
lib.fgt_set_pressureUnit.argtypes = [c_uint, POINTER(c_char)]
lib.fgt_get_pressureUnit.argtypes = [c_uint, POINTER(c_char)]
lib.fgt_set_sensorUnit.argtypes = [c_uint, POINTER(c_char)]
lib.fgt_get_sensorUnit.argtypes = [c_uint, POINTER(c_char)]
lib.fgt_set_sensorCalibration.argtypes = [c_uint, c_int]
lib.fgt_get_sensorCalibration.argtypes = [c_uint, POINTER(c_int)]
lib.fgt_set_sensorCustomScale.argtypes = [c_uint, c_float, c_float, c_float]
lib.fgt_set_sensorCustomScaleEx.argtypes = [c_uint, c_float, c_float, c_float, c_float]
lib.fgt_calibratePressure.argtypes = [c_uint]
lib.fgt_set_pressure.argtypes = [c_uint, c_float]
lib.fgt_get_pressure.argtypes = [c_uint,  POINTER(c_float)]
lib.fgt_get_pressureEx.argtypes = [c_uint, POINTER(c_float), POINTER(c_ushort)]
lib.fgt_set_sensorRegulation.argtypes = [c_uint, c_uint, c_float]
lib.fgt_get_sensorValue.argtypes = [c_uint,  POINTER(c_float)]
lib.fgt_get_sensorValueEx.argtypes = [c_uint,  POINTER(c_float), POINTER(c_ushort)]
lib.fgt_set_customSensorRegulation.argtypes = [c_float, c_float, c_float, c_uint]
lib.fgt_get_pressureRange.argtypes = [c_uint, POINTER(c_float), POINTER(c_float)]
lib.fgt_get_sensorRange.argtypes = [c_uint, POINTER(c_float), POINTER(c_float)]
lib.fgt_get_valveRange.argtypes = [c_uint, POINTER(c_int)]
lib.fgt_set_pressureLimit.argtypes = [c_uint, c_float, c_float]
lib.fgt_set_sensorRegulationResponse.argtypes = [c_uint, c_uint]
lib.fgt_set_pressureResponse.argtypes = [c_uint, c_ubyte]
lib.fgt_get_pressureStatus.argtypes = [c_uint, POINTER(c_int), POINTER(c_ushort), POINTER(c_ubyte), POINTER(c_char)]
lib.fgt_get_sensorStatus.argtypes = [c_uint, POINTER(c_int), POINTER(c_ushort), POINTER(c_ubyte), POINTER(c_char)]
lib.fgt_set_power.argtypes = [c_uint, c_ubyte]
lib.fgt_get_power.argtypes = [c_uint, POINTER(c_ubyte)]
lib.fgt_set_TtlMode.argtypes = [c_uint, c_ubyte]
lib.fgt_read_Ttl.argtypes = [c_uint, POINTER(c_ubyte)]
lib.fgt_trigger_Ttl.argtypes = [c_uint]
lib.fgt_set_purge.argtypes = [c_uint, c_ubyte]
lib.fgt_set_manual.argtypes = [c_uint, c_float]
lib.fgt_detect.argtypes = [POINTER(c_ushort), POINTER(c_int)]
lib.fgt_get_valvePosition.argtypes = [c_uint, POINTER(c_int)]
lib.fgt_set_valvePosition.argtypes = [c_uint, c_int, c_int, c_int]
lib.fgt_set_allValves.argtypes = [c_uint, c_uint, c_int]


# Wrappers
def fgt_init():
    """Initializes the SDK engine and all connected instruments"""
    c_error = c_ubyte(lib.fgt_init())
    return c_error.value,

def fgt_initEx(instruments):
    """Initializes the SDK engine and only the specified instruments"""
    instrument_array = (c_ushort*len(instruments))(*instruments)
    c_error = c_ubyte(lib.fgt_initEx(instrument_array))
    return c_error.value,

def fgt_close():
    """Stops the engine and closes the connection with all instruments"""
    c_error = c_ubyte(lib.fgt_close())
    return c_error.value,

def fgt_get_controllersInfo():
    """Returns a list of structures containing information on the controller
    devices"""
    info_array = (fgt_CONTROLLER_INFO*256)()
    c_error = c_ubyte(lib.fgt_get_controllersInfo(info_array))
    channels = list(filter(lambda s : s.id != 0, info_array))
    return c_error.value, channels

def fgt_get_pressureChannelCount():
    """Returns the number of available pressure channels"""
    pressure_count = c_ushort(0)
    c_error = c_ubyte(lib.fgt_get_pressureChannelCount(byref(pressure_count)))
    return c_error.value, pressure_count.value

def fgt_get_sensorChannelCount():
    """Returns the number of available flow rate channels"""
    sensor_count = c_ushort(0)
    c_error = c_ubyte(lib.fgt_get_sensorChannelCount(byref(sensor_count)))
    return c_error.value, sensor_count.value

def fgt_get_TtlChannelCount():
    """Returns the number of available TTL ports"""
    ttl_count = c_ushort(0)
    c_error = c_ubyte(lib.fgt_get_TtlChannelCount(byref(ttl_count)))
    return c_error.value, ttl_count.value

def fgt_get_valveChannelCount():
    """Returns the number of available valve ports"""
    valve_count = c_ubyte(0)
    c_error = c_ubyte(lib.fgt_get_valveChannelCount(byref(valve_count)))
    return c_error.value, valve_count.value

def fgt_get_pressureChannelsInfo():
    """Returns a list of structures containing information on each pressure
    channel"""
    info_array = (fgt_CHANNEL_INFO*256)()
    c_error = c_ubyte(lib.fgt_get_pressureChannelsInfo(info_array))
    channels = list(filter(lambda s : s.indexID != 0, info_array))
    return c_error.value, channels
    
def fgt_get_sensorChannelsInfo():
    """Returns a list of structures containing information on each flow rate
    channel"""
    info_array = (fgt_CHANNEL_INFO*256)()
    type_array = (c_int * 256)()
    c_error = c_ubyte(lib.fgt_get_sensorChannelsInfo(info_array, type_array))
    channels = list(filter(lambda s : s.indexID != 0, info_array))
    sensor_types = list(filter(lambda t : t!= fgt_SENSOR_TYPE.NONE, type_array))
    return c_error.value, channels, sensor_types
    
def fgt_get_TtlChannelsInfo():
    """Returns a list of structures containing information on each TTL port"""
    info_array = (fgt_CHANNEL_INFO*256)()
    c_error = c_ubyte(lib.fgt_get_TtlChannelsInfo(info_array))
    channels = list(filter(lambda s : s.indexID != 0, info_array))
    return c_error.value, channels

def fgt_get_valveChannelsInfo():
    """Returns a list of structures containing information on each flow rate
    channel"""
    info_array = (fgt_CHANNEL_INFO*256)()
    type_array = (c_int * 256)()
    c_error = c_ubyte(lib.fgt_get_valveChannelsInfo(info_array, type_array))
    channels = list(filter(lambda s : s.indexID != 0, info_array))
    valve_types = list(filter(lambda t : t != fgt_VALVE_TYPE.NONE, type_array))
    return c_error.value, channels, valve_types
    
def fgt_set_sessionPressureUnit(unit):
    """Sets the default pressure unit (as a string) to be used by the engine"""
    unit_array = (c_char * (len(unit)+1))(*([c_char_converter(c) for c in unit]))
    c_error = c_ubyte(lib.fgt_set_sessionPressureUnit(unit_array))
    return c_error.value, 
    
def fgt_set_pressureUnit(pressure_index, unit):
    """Override the default pressure unit for a single pressure channel"""
    unit_array = (c_char * (len(unit)+1))(*([c_char_converter(c) for c in unit]))
    c_error = c_ubyte(lib.fgt_set_pressureUnit(c_uint(pressure_index), unit_array))
    return c_error.value,
    
def fgt_get_pressureUnit(pressure_index):
    """Returns the pressure unit being used for the specified channel"""
    unit_array = (c_char * 140)()
    c_error = c_ubyte(lib.fgt_get_pressureUnit(c_uint(pressure_index), unit_array))
    unit = unit_array.value.decode()
    return c_error.value, unit
    
def fgt_set_sensorUnit(sensor_index, unit):
    """Sets the unit to be used when reading and writing to the specified 
    sensor"""
    unit_array = (c_char * (len(unit)+1))(*([c_char_converter(c) for c in unit]))
    c_error = c_ubyte(lib.fgt_set_sensorUnit(c_uint(sensor_index), unit_array))
    return c_error.value,

def fgt_get_sensorUnit(sensor_index):
    """Returns the measurement unit being used for the specified channel"""
    unit_array = (c_char * 140)()
    c_error = c_ubyte(lib.fgt_get_sensorUnit(c_uint(sensor_index), unit_array))
    try:
        unit = unit_array.value.decode()
    except UnicodeDecodeError:
        unit = unit_array.value.decode("windows-1252")
    return c_error.value, mu_converter(unit)
    
def fgt_set_sensorCalibration(sensor_index, calibration):
    """Sets the calibration table for the specified sensor"""
    c_error = c_ubyte(lib.fgt_set_sensorCalibration(c_uint(sensor_index), c_int(calibration)))
    return c_error.value,
    
def fgt_get_sensorCalibration(sensor_index):
    """Returns the calibration table for the specified sensor"""
    calibration = c_int(0)
    c_error = c_ubyte(lib.fgt_get_sensorCalibration(c_uint(sensor_index), byref(calibration)))
    return c_error.value, calibration.value
    
def fgt_set_sensorCustomScale(sensor_index, a, b, c):
    """Sets a polynomial conversion function to scale the sensor measurement"""
    c_error = c_ubyte(lib.fgt_set_sensorCustomScale(sensor_index, 
                                        c_float(a), c_float(b), c_float(c)))
    return c_error.value,
    
def fgt_set_sensorCustomScaleEx(sensor_index, a, b, c, qmax):
    """"""
    c_error = c_ubyte(lib.fgt_set_sensorCustomScaleEx(c_uint(sensor_index), 
                            c_float(a), c_float(b), c_float(c), c_float(qmax)))
    return c_error.value,
    
def fgt_calibratePressure(pressure_index):
    """Calibrates the pressure on the specified channel (stops the channel for
    a few seconds)"""
    c_error = c_ubyte(lib.fgt_calibratePressure(c_uint(pressure_index)))
    return c_error.value,
    
def fgt_set_pressure(pressure_index, pressure):
    """Set the pressure on the specified pressure channel, in the unit 
    currently in use for that channel or in the default session unit"""
    c_error = c_ubyte(lib.fgt_set_pressure(c_uint(pressure_index), c_float(pressure)))
    return c_error.value,
    
def fgt_get_pressure(pressure_index):
    """Returns the pressure measured on the specified channel"""
    pressure = c_float(0)
    c_error = c_ubyte(lib.fgt_get_pressure(c_uint(pressure_index), byref(pressure)))
    return c_error.value, pressure.value

def fgt_get_pressureEx(pressure_index):
    """Returns the pressure measured on the specified channel, as well as the
    timestamp"""
    pressure = c_float(0)
    timestamp = c_ushort(0)
    c_error = c_ubyte(lib.fgt_get_pressureEx(c_uint(pressure_index), 
                                           byref(pressure), byref(timestamp)))
    return c_error.value, pressure.value, timestamp.value
    
def fgt_set_sensorRegulation(sensor_index, pressure_index, setpoint):
    """Sets the flow rate on the specified flow rate channel, using the
    specified pressure channel as an actuator"""
    c_error = c_ubyte(lib.fgt_set_sensorRegulation(c_uint(sensor_index), 
                            c_uint(pressure_index), c_float(setpoint)))
    return c_error.value,
    
def fgt_get_sensorValue(sensor_index):
    """Returns the measurement on the specified sensor"""
    sensorValue = c_float(0)
    c_error = c_ubyte(lib.fgt_get_sensorValue(c_uint(sensor_index),
                                           byref(sensorValue)))
    return c_error.value, sensorValue.value

def fgt_get_sensorValueEx(sensor_index):
    """Returns the measurement on the specified sensor, as well as the
    timestamp. The IPS always returns 0 for the timestamp."""
    sensorValue = c_float(0)
    timestamp = c_ushort(0)
    c_error = c_ubyte(lib.fgt_get_sensorValueEx(c_uint(sensor_index),
                                    byref(sensorValue), byref(timestamp)))
    return c_error.value, sensorValue.value, timestamp.value
    
def fgt_set_customSensorRegulation(measure, command, max_sensor_range, pressure_index):
    """Sends a sensor's data to use the control algorithm to regulate its value
    using a pressure channel. Must be called continuously"""
    c_error = c_ubyte(lib.fgt_set_customSensorRegulation(c_float(measure), 
                                c_float(command), c_float(max_sensor_range),
                                c_uint(pressure_index)))
    return c_error.value,
    
def fgt_get_pressureRange(pressure_index):
    """Returns the minimum and maximum pressure on the specified channel"""
    pressure_min = c_float(0)
    pressure_max = c_float(0)
    c_error = c_ubyte(lib.fgt_get_pressureRange(c_uint(pressure_index), 
                                    byref(pressure_min), byref(pressure_max)))
    return c_error.value, pressure_min.value, pressure_max.value
    
def fgt_get_sensorRange(sensor_index):
    """Returns the minimum and maximum value on the specified sensor"""
    sensor_min = c_float(0)
    sensor_max = c_float(0)
    c_error = c_ubyte(lib.fgt_get_sensorRange(c_uint(sensor_index), 
                                    byref(sensor_min), byref(sensor_max)))
    return c_error.value, sensor_min.value, sensor_max.value
        
def fgt_get_valveRange(valve_index):
    """Returns the maximum valve position. Position indexing starts at 0."""
    posMax = c_int(0)
    c_error = c_ubyte(lib.fgt_get_valveRange(c_uint(valve_index),
                                           byref(posMax)))
    return c_error.value, posMax.value

def fgt_set_pressureLimit(pressure_index, p_lim_min, p_lim_max):
    """Sets the maximum pressure that the specified channel can be set to
    during flow rate regulation"""
    c_error = c_ubyte(lib.fgt_set_pressureLimit(c_uint(pressure_index), 
                                    c_float(p_lim_min), c_float(p_lim_max)))
    return c_error.value,
    
def fgt_set_sensorRegulationResponse(sensor_index, response_time):
    """Set the response time of the regulation under normal conditions for
    the specified sensor"""
    c_error = c_ubyte(lib.fgt_set_sensorRegulationResponse(c_uint(sensor_index), 
                                    c_uint(response_time)))
    return c_error.value,
    
def fgt_set_pressureResponse(pressure_index, response_mode):
    """Set the pressure response mode"""
    c_error = c_ubyte(lib.fgt_set_pressureResponse(c_uint(pressure_index), 
                                    c_ubyte(response_mode)))
    return c_error.value,
    
def fgt_get_pressureStatus(pressure_index):
    """"""
    instr_type = c_int(0)
    instr_sn = c_ushort(0)
    information = c_ubyte(0)
    detail = (c_char * 200)()
    c_error = c_ubyte(lib.fgt_get_pressureStatus(c_uint(pressure_index), 
                         byref(instr_type), byref(instr_sn),
                         byref(information), detail))
    return c_error.value, instr_type.value, instr_sn.value, \
            information.value, detail.value.decode()
    
def fgt_get_sensorStatus(sensor_index):
    """"""
    instr_type = c_int(0)
    instr_sn = c_ushort(0)
    information = c_ubyte(0)
    detail = (c_char * 200)()
    c_error = c_ubyte(lib.fgt_get_sensorStatus(c_uint(sensor_index), 
                         byref(instr_type), byref(instr_sn), 
                         byref(information), detail))
    return c_error.value, instr_type.value, instr_sn.value, \
            information.value, detail.value.decode()
    
def fgt_set_power(controller_index, power_state):
    """Powers the specified controller on or off"""
    c_error = c_ubyte(lib.fgt_set_power(c_uint(controller_index), 
                                    c_ubyte(power_state)))
    return c_error.value,
    
def fgt_get_power(controller_index):
    """Returns a number indicating whether the specified controller is 
    powered on or off"""
    power_state = c_ubyte(0)
    c_error = c_ubyte(lib.fgt_get_power(c_uint(controller_index), 
                                    byref(power_state)))
    return c_error.value, power_state.value
    
def fgt_set_TtlMode(ttl_index, mode):
    """Sets the operation mode for the specified TTL port"""
    c_error = c_ubyte(lib.fgt_set_TtlMode(c_uint(ttl_index), c_ubyte(mode)))
    return c_error.value,
    
def fgt_read_Ttl(ttl_index):
    """Returns the current state of the specified TTL port. The port must be
    in input mode"""
    ttl_state = c_ubyte(0)
    c_error = c_ubyte(lib.fgt_read_Ttl(c_uint(ttl_index), byref(ttl_state)))
    return c_error.value, ttl_state.value
    
def fgt_trigger_Ttl(ttl_index):
    """Sends a pulse through the specified TTL port. The port must be in 
    output mode"""
    c_error = c_ubyte(lib.fgt_trigger_Ttl(c_uint(ttl_index)))
    return c_error.value,
    
def fgt_set_purge(controller_index, purge_state):
    """Turns the purge functionality on or off on the specified controller.
    Only available on MFCS and MFCS-EZ"""
    c_error = c_ubyte(lib.fgt_set_purge(c_uint(controller_index), c_ubyte(purge_state)))
    return c_error.value,
    
def fgt_set_manual(pressure_index, voltage):
    """Sets the voltage on the internal solenoid valve of the given pressure,
    channel, stopping the pressure regulation. Only available on MFCS series
    instruments"""
    c_error = c_ubyte(lib.fgt_set_manual(c_uint(pressure_index), c_float(voltage)))
    return c_error.value,
    
def fgt_detect():
    """Returns a list containing the serial numbers of all detected 
    instruments and another list containing their types"""
    serial_numbers = (c_ushort * 256)()
    instr_types = (c_int * 256)()
    n_instruments = c_ubyte(lib.fgt_detect(serial_numbers, instr_types))
    return n_instruments.value, list(filter(None, serial_numbers)), list(filter(None, instr_types)),

def fgt_get_valvePosition(valve_index):
    position = c_int(0)
    c_error = c_ubyte(lib.fgt_get_valvePosition(c_uint(valve_index), byref(position)))
    return(c_error.value, position.value)
    
def fgt_set_valvePosition(valve_index, position, direction, wait):
    wait_int = 1 if wait else 0
    c_error = c_ubyte(lib.fgt_set_valvePosition(c_uint(valve_index), c_int(position), c_int(direction), c_int(wait_int)))
    return c_error.value,

def fgt_set_allValves(controller_index, module_index, position):
    c_error = c_ubyte(lib.fgt_set_allValves(c_uint(controller_index),c_uint(module_index), c_int(position)))
    return c_error.value,

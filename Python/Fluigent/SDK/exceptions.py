"""This module contains the exceptions raised by the Fluigent SDK, to enable 
application control via try/except blocks"""

from __future__ import print_function
import logging

from . import low_level

error_report_mode = "print"

class FGT_ERROR(Exception):
    """Error in the Fluigent SDK"""
    
class FGT_WARNING(UserWarning):
    """Warning in the Fluigent SDK"""

def warn(e):
    if error_report_mode.lower() == "print":
        logging.warning(e)
    
def get_enum_name(EnumClass, key):
    return str(EnumClass(key))
    
def parse_error_data(function_name, channel_type, channel_index, c_error, 
                     instr_type, instr_sn, information, detail):
    if c_error == low_level.fgt_ERROR.OK:
        return 
    instr_type_str = get_enum_name(low_level.fgt_INSTRUMENT_TYPE, instr_type)
    if len(detail) < 4:
        detail = str(low_level.fgt_ERROR(c_error)).replace("_", " ")
    info = ""
    if information == 0:
        info = "info: remote control" 
    elif information == 1:
        info = "info: local control"
    error_origin = "{} {} {} of type {}".format(function_name, channel_type,
                    channel_index, instr_type_str)
    error_info = "error {} - {}".format(c_error, detail) 
    instr_info = ""
    if instr_sn != 0:
        instr_info = "Controller SN: {} {}".format(instr_sn, info)
    e = FGT_WARNING("{} {} {}".format(error_origin, error_info, instr_info))
    warn(e)
    
def manage_generic_status(function_name, c_error):
    """Handle errors not related to a specific channel
    
    This function produces an error message including the function 
    name and which explains the error code returned by the low level 
    function.
    
    This function is called automatically when a function from the toolbox
    unrelated to a specific sensor or pressure channel is called. By default,
    it sends a warning message if a non-zero error code was received.
    
    Modify this function if you want all or some of the error codes to
    generate errors (which will stop execution of the program if not
    handled).
    """
    if c_error == low_level.fgt_ERROR.OK:
        return
    c_error_str = get_enum_name(low_level.fgt_ERROR, c_error).replace("_", " ")
    e = FGT_WARNING("{} error {} - {}".format(function_name, c_error, 
                    c_error_str))
    warn(e)

def manage_pressure_status(function_name, pressure_index):
    """Handle pressure channel errors
    
    This function produces an error message including the function 
    name and which explains the error code returned by the low level 
    function.
    
    This function is called automatically when a function from the toolbox
    related to a specific pressure channel is called. By default, it sends a
    warning message if a non-zero error code is returned by the pressure
    status function.
    
    Modify this function if you want all or some of the error codes to
    generate errors (which will stop execution of the program if not
    handled).
    """
    c_error, instr_type, instr_sn, information, detail = \
        low_level.fgt_get_pressureStatus(pressure_index)
    parse_error_data(function_name, "pressure channel", pressure_index, 
                     c_error, instr_type, instr_sn, information, detail)
    
def manage_sensor_status(function_name, sensor_index):
    """Handle sensor errors
    
    This function produces an error message including the function 
    name and which explains the error code returned by the sensor 
    status function.
    
    This function is called automatically when a function from the toolbox
    related to a specific sensor is called. By default, it sends a warning
    message if a non-zero error code is returned by the sensor status
    function.
    
    Modify this function if you want all or some of the error codes to
    generate errors (which will stop execution of the program if not
    handled).
    """
    c_error, instr_type, instr_sn, information, detail = \
        low_level.fgt_get_sensorStatus(sensor_index)
    parse_error_data(function_name, "sensor channel", sensor_index, c_error, 
                     instr_type, instr_sn, information, detail)
    
def check_enum_type(arg_name, argument, expected_type):
    """Check that the function argument has the right enum type"""
    if type(argument) is int: 
        return
    if argument.__class__ is not expected_type:
        raise ValueError("{} should be of type int or {}".format(arg_name, expected_type))
        
        
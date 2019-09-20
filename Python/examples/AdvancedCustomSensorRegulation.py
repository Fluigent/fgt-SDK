#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""Advanced Custom Sensor Regulation example

This example shows how to use a custom sensor, different from
Fluigent ones and regulate pressure in order to reach the setpoint.
Different sensor types and ranges can be used (e.g. liquid pressure,
water level, l/min flow meter...), however, we do not guarantee 
full compatibility with all sensors.
For this demonstration, a Fluigent Flow Unit is used for more simplicity.

Requires at least one Fluigent pressure controller (MFCS, MFCS-EZ or Flow
EZ)

Copyright (c) Fluigent 2019.  All Rights Reserved.
"""

# Print function for Python 2 compatibility
from __future__ import print_function 
import time

from Fluigent.SDK import fgt_init, fgt_close
from Fluigent.SDK import fgt_get_sensorRange, fgt_get_sensorValue
from Fluigent.SDK import fgt_set_customSensorRegulation
from Fluigent.SDK import fgt_set_pressure

## Initialize the session
# This step is optional, if not called session will be automatically
# created
fgt_init()

## Get sensor range
# When using a custom sensor, its range has to be known.
# Replace this function with your custom sensor interface.
minSensor, maxSensor = fgt_get_sensorRange(0)

## Run regulation

# Read sensor value. Replace with your custom sensor's interface
sensorMeasurement = fgt_get_sensorValue(0)

# Loop for 10 seconds waiting 100ms between each sensor update
for i in range(100):
    # Replace this function with your custom sensor's interface
    sensorMeasurement = fgt_get_sensorValue(0)
    # Update regulation with sensor values. Here setpoint is set to 50# of
    # sensor range, first pressure channel of the list is used
    print('Running custom regulation, read: {}, setpoint: {}'.format(
            sensorMeasurement, maxSensor / 2 ))
    fgt_set_customSensorRegulation(sensorMeasurement, maxSensor/2 , maxSensor, 0)
    # Wait 100 milliseconds. Wait time between two successive updates
    # should be 1 seconds or less, otherwise pressure regulation is
    # stopped
    time.sleep(0.1)
    
fgt_set_pressure(0, 0)

## Close the session
fgt_close()

#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""Basic Sensor Regulation example

This example shows how to set a sensor regulation and generate a
sinusoidal profile on the first sensor and pressure module of the chain
			
Requires at least one Fluigent pressure controller (MFCS, MFCS-EZ or
Flow EZ) and at least one Fluigent sensor (Flow Unit connected to FRP or
Flow EZ)


Copyright (c) Fluigent 2019.  All Rights Reserved.
"""

# Print function for Python 2 compatibility
from __future__ import print_function 
import time
from math import sin, pi

from Fluigent.SDK import fgt_init, fgt_close
from Fluigent.SDK import fgt_get_sensorValue, fgt_get_sensorRange
from Fluigent.SDK import fgt_set_sensorRegulation, fgt_set_pressure

## Initialize the session
# This step is optional, if not called session will be automatically
# created
fgt_init()

## Get sensor range   
minSensor, maxSensor = fgt_get_sensorRange(0)

## Read sensor value
sensorMeasurement = fgt_get_sensorValue(0)
print('Current sensor value: {}'.format(sensorMeasurement))

# Set regulation setpoint to 10% of the maximum sensor value
# Use the first sensor and the first pressure channel detected
fgt_set_sensorRegulation(0, 0, maxSensor/10)

# Wait 5 seconds for the pressure to settle
print('Waiting 5 seconds...')
time.sleep(5)

# Read sensor value
sensorMeasurement = fgt_get_sensorValue(0)
print('Current sensor value: {:.2f}'.format(sensorMeasurement))

## Create a sinusoidal profile 
# The profile oscillates between the minimum and the maximum sensor value

# Create the sine wave setpoints
amplitude = (maxSensor-minSensor)
offset = minSensor
sinePoints = [(sin(angle*pi/180)+1)/2 for angle in range(0, 360, 10)]
setpoints = [value*amplitude + offset for value in sinePoints]

for sensorSetpoint in setpoints:
    # Set new setpoint
    print('Set sensor regulation to {:.2f}'.format(sensorSetpoint))
    fgt_set_sensorRegulation(0, 0, sensorSetpoint)
    # Wait 1 second
    time.sleep(1)
    # Read sensor value
    sensorMeasurement = fgt_get_sensorValue(0)
    print('Current sensor value: {:.2f}'.format(sensorMeasurement))

## Close the session
# Set pressure to 0 before closing. This also stops the regulation
fgt_set_pressure(0, 0)
fgt_close()

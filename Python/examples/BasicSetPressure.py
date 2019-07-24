#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""Basic Set Pressure example

This example shows how to set a pressure order and generate a ramp on the
first pressure module of the chain

Requires at least one Fluigent pressure controller (MFCS, MFCS-EZ or Flow
EZ)

Copyright (c) Fluigent 2019.  All Rights Reserved.
"""

# Print function for Python 2 compatibility
from __future__ import print_function 
import time

from Fluigent.SDK import fgt_init, fgt_close
from Fluigent.SDK import fgt_set_pressure, fgt_get_pressure, fgt_get_pressureRange

## Initialize the session
# This step is optional, if not called session will be automatically
# created
fgt_init()

## Set and read pressure

# Set pressure to 20 mbar on first pressure channel of the list
# mbar is the default unit at initialization
fgt_set_pressure(0, 20)

# Wait 5 seconds for the pressure to settle
print('Waiting 5 seconds...')
time.sleep(5)

# Read pressure value
pressureMeasurement = fgt_get_pressure(0)
print('Current pressure: {}'.format(pressureMeasurement))

## Create a pressure ramp profile 
# The ramp goes from device minimal to maximal pressure in 10 steps

# Create the pressure steps

def floatRange(start, stop, step):
    """Generate an arithmetic progression that can be iterated"""
    r = start
    while r < stop:
        yield r
        r += step
        
pMin, pMax = fgt_get_pressureRange(0)
stepSize = (pMax-pMin)/10
pressureSteps = floatRange(pMin, pMax, stepSize)

for pressureSetpoint in pressureSteps:
    # Set pressure
    print('Set pressure to {}'.format(pressureSetpoint))
    fgt_set_pressure(0, pressureSetpoint)
    # Wait 1 second
    time.sleep(5)
    # Read pressure
    pressureMeasurement = fgt_get_pressure(0)
    print('Current pressure: {}'.format(pressureMeasurement))

## Close the session
# Set pressure to 0 before closing
fgt_set_pressure(0, 0)
fgt_close()

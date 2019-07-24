#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""Advanced features example

This example shows advanced features such as limits, units and
calibration.
			
Requires at least one Fluigent pressure controller (MFCS, MFCS-EZ or Flow
EZ) and/or one Fluigent sensor (Flow Unit connected to FRP or Flow EZ)

Copyright (c) Fluigent 2019.  All Rights Reserved.
"""

# Print function for Python 2 compatibility
from __future__ import print_function 
import time

from Fluigent.SDK import fgt_close
from Fluigent.SDK import fgt_get_pressure, fgt_get_sensorValue
from Fluigent.SDK import fgt_get_pressureUnit, fgt_set_pressureUnit
from Fluigent.SDK import fgt_get_sensorUnit, fgt_set_sensorUnit
from Fluigent.SDK import fgt_calibratePressure, fgt_set_pressure
from Fluigent.SDK import fgt_get_pressureRange, fgt_set_pressureLimit
from Fluigent.SDK import fgt_get_sensorCalibration, fgt_set_sensorCalibration
from Fluigent.SDK import fgt_SENSOR_CALIBRATION

## Unit change

pressureIndex = 0
sensorIndex = 0

# Read pressure value
pressureValue = fgt_get_pressure(pressureIndex)
pressureUnit = fgt_get_pressureUnit(pressureIndex)
print('Read pressure: {} {}'.format(pressureValue, pressureUnit))

# Read sensor value
sensorValue = fgt_get_sensorValue(sensorIndex)
sensorUnit = fgt_get_sensorUnit(sensorIndex)
print('Read sensor: {} {}'.format(sensorValue, sensorUnit))

# Change pressure and sensor unit
# Note that if incorrect or invalid unit is used an error is returned.
# When unit is changed, all values are then in set unit
fgt_set_pressureUnit(pressureIndex, 'PSI')
fgt_set_sensorUnit(sensorIndex, 'ulperhour')
print('Changed pressure and sensor unit')

# Read pressure value again
pressureValue = fgt_get_pressure(pressureIndex)
pressureUnit = fgt_get_pressureUnit(pressureIndex)
print('Read pressure: {} {}'.format(pressureValue, pressureUnit))

# Read sensor value again
sensorValue = fgt_get_sensorValue(sensorIndex)
sensorUnit = fgt_get_sensorUnit(sensorIndex)
print('Read sensor: {} {}'.format(sensorValue, sensorUnit))

## Limit change

[minPressure, maxPressure] = fgt_get_pressureRange(pressureIndex)
fgt_set_pressureLimit(pressureIndex, minPressure / 2, maxPressure / 2)
print('Changed pressure limit to {} - {}'.format(minPressure / 2, maxPressure / 2))
print('Trying to set pressure to {}'.format(maxPressure))
fgt_set_pressure(pressureIndex, maxPressure)

## Calibration

# Pressure calibration
fgt_calibratePressure(pressureIndex)
print('Calibrating pressure channel... trying to send pressure order in same time')
fgt_set_pressure(pressureIndex, maxPressure/2)
# An error is thrown, set pressure orders are not accepted during calibration

# Sensor calibration
# Read sensor calibration table
sensorCalibration = fgt_get_sensorCalibration(sensorIndex)
print('Read sensor calibration: {}'.format(sensorCalibration))

# Change sensor calibration to water
# Note that if calibration is not supported, an error is thrown
fgt_set_sensorCalibration(sensorIndex, fgt_SENSOR_CALIBRATION.H2O)
print('Setting sensor calibration...')
# As for pressure calibration, this step needs a few moments before the
# read values are correct. The same error is thrown.
time.sleep(1)
# Read sensor calibration table again
sensorCalibration = fgt_get_sensorCalibration(sensorIndex)
print('Read sensor calibration: {}'.format(sensorCalibration))

## Close the session
fgt_close()

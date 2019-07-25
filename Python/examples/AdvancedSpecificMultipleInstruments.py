#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""Advanced Specific Multiple Instruments
This example shows how to use specific channels ID and multiple connected
instruments

Requires at least two Fluigent pressure channels

Copyright (c) Fluigent 2019.  All Rights Reserved.
"""

# Print function for Python 2 compatibility
from __future__ import print_function 

from Fluigent.SDK import fgt_detect, fgt_init, fgt_close
from Fluigent.SDK import fgt_get_controllersInfo
from Fluigent.SDK import fgt_get_pressureChannelCount, fgt_get_pressureChannelsInfo
from Fluigent.SDK import fgt_get_pressure

# Detect all controllers
SNs, types = fgt_detect()
controllerCount = len(SNs)
print('Number of controllers detected: {}'.format(controllerCount))

# List all found controllers' serial number and type
for i, sn in enumerate(SNs):
    print('Detected instrument at index: {}, ControllerSN: {}, type: {}'\
          .format(i, sn, str(types[i])))

## Initialize specific instruments
# Initialize only specific instrument controllers here If you do not want
# a controller in the list or if you want a specific order (e.g. LineUP
# before MFCS instruments), rearrange parsed SN table
fgt_init(SNs)

# Get total number of initialized pressure channels
print('Total number of pressure channels: {}'.format(fgt_get_pressureChannelCount()))

## Get detailed information about all controllers

controllerInfoArray = fgt_get_controllersInfo()
for i, controllerInfo in enumerate(controllerInfoArray):
    print('Controller info at index: {}'.format(i))
    print(controllerInfo)

## Get detailed information about all pressure channels

pressureInfoArray = fgt_get_pressureChannelsInfo()
for i, pressureInfo in enumerate(pressureInfoArray):
    print('Pressure channel info at index: {}'.format(i))
    print(pressureInfo)

## Read pressure using unique ID
# If you want to address a specific channel, unique ID can be used. However
# if hardware changed channel may not be found

try:
    pressure1 = fgt_get_pressure(pressureInfoArray[0].indexID)
    print('Read pressure from ID {} : {:.2f}\n'.format(pressureInfoArray[0].indexID, pressure1))
except IndexError as e:
    print('WARNING: Cannot read pressure on channel 0')

try:
    pressure2 = fgt_get_pressure(pressureInfoArray[1].indexID)
    print('Read pressure from ID {} : {:.2f}\n'.format(pressureInfoArray[1].indexID, pressure2))
except IndexError as e:
    print('WARNING: Cannot read pressure on channel 1')

## Close the session
fgt_close()

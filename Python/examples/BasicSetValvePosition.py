#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""Basic Set Valve Position example

This example shows how to change the position of a valve

Requires at least one Fluigent valve controller (M-Switch, L-Switch,
2-Switch or P-Switch)

Copyright (c) Fluigent 2021.  All Rights Reserved.
"""

# Print function for Python 2 compatibility
from __future__ import print_function 

from Fluigent.SDK import fgt_init, fgt_close
from Fluigent.SDK import fgt_get_valveChannelCount
from Fluigent.SDK import fgt_get_valveRange, fgt_get_valvePosition, fgt_set_valvePosition

## Initialize the session
# This step is optional, if not called session will be automatically
# created
fgt_init()

## Get valve indices
valve_indices = range(fgt_get_valveChannelCount())

if not valve_indices:
    raise Exception("No valve channels found")

for valve_index in valve_indices:
    print("valve {} is in position {}".format(valve_index, fgt_get_valvePosition(valve_index)))
    # Get all available positions for this valve
    positions = range(fgt_get_valveRange(valve_index)+1)
    # Set valve to each of the available positions, waiting for it to switch each time
    for position in positions:
        fgt_set_valvePosition(valve_index, position)
        print("valve {} is in position {}".format(valve_index, fgt_get_valvePosition(valve_index)))
    
    # Return valve to default position
    fgt_set_valvePosition(valve_index, 0)

## Close the session
fgt_close()

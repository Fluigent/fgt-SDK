#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""Advanced Parallel Pressure Control example

This example shows how to send concurrent pressure orders using threads.
The Dll handles parallel calls, functions can be called simultaneously.
This demonstrates thread handling, same result is obtained using 
successive calls as all function calls are executed instantly (within a few µs)

Hardware setup: At least two Fluigent pressure controllers (MFCS, MFCS-EZ or Flow EZ)

Copyright (c) Fluigent 2019.  All Rights Reserved.
"""

# Print function for Python 2 compatibility
from __future__ import print_function 
import time
import random
from threading import Thread

from Fluigent.SDK import fgt_init, fgt_close
from Fluigent.SDK import fgt_set_pressure, fgt_get_pressureRange
from Fluigent.SDK import fgt_get_pressureChannelCount

cancellationToken = False

def pressureTask(pressureIndex, period):
    """Set the selected pressure channel to a random value every [period] seconds"""
    minPressure, maxPressure = fgt_get_pressureRange(pressureIndex)
    while not cancellationToken:
        pressureOrder = random.random()*maxPressure
        fgt_set_pressure(pressureIndex, pressureOrder);
        print("task {}: New pressure order: {:.2f} mbar".format(pressureIndex, pressureOrder))
        time.sleep(period)

## Initialize the session
# This step is mandatory before starting threads at the same time
fgt_init()

## Create the threads
# Thread 1: drives the first pressure channel (index 0) every 2 seconds
thread1 = Thread(target = pressureTask, args = (0, 2))
# Thread 2: drives the second pressure channel (index 1) every 5 seconds
thread2 = Thread(target = pressureTask, args = (1, 5))

try:
    # Start the threads
    thread1.start()
    thread2.start()
    # Wait 10 seconds
    time.sleep(10);
finally:
    # Stop the threads
    cancellationToken = True;
    thread1.join();
    thread2.join();
    # Reset pressure on all channels
    for pressure_index in range(fgt_get_pressureChannelCount()):
        fgt_set_pressure(pressure_index, 0)
    ## Close the session
    fgt_close()

/*============================================================================
*               Fluigent Software Developement Kit for C++
*----------------------------------------------------------------------------
*         Copyright (c) Fluigent 2021.  All Rights Reserved.
*----------------------------------------------------------------------------
*
* Title:   Advanced Parallel Pressure Control.cpp
* Purpose: This example shows how to send concurrent pressure orders using threads.
*			The Dll handles parallel calls, functions can be called simultaneously.
*			This demonstrates thread handling, same result is obtained using 
*			successive calls as all function calls are executed instantly (within a few �s)
*
* Software: fgt_SDK is the library managing all Fluigent instruments
*			"fgt_SDK_Cpp.h" is the wrapper to fgt_SDK dll
* Hardware setup: At least two Fluigent pressure controllers (MFCS, MFCS-EZ or Flow EZ)
* Version: 21.0.0.0
* Date:	04/2021
*============================================================================*/


#include <iostream>
#include <thread>					// Include threading library
#include <time.h>					// Include time library for random number generation
#include "fgt_SDK_Cpp.h"			// include wrapper to fgt_SDK dll, functions can also be accessed by loading the dll


bool CancellationToken = false;		// Thread stop flag

// Task driving pressure, every 2 seconds randomly
void task1(int pressureIndex)
{
	// Variables declaration
	float pressureOrder;
	float maxPressure;				// min/max pressure controller range
	float minPressure;

	// Get pressure controller range
	Fgt_get_pressureRange(pressureIndex, &minPressure, &maxPressure);

	while (!CancellationToken)
	{
		srand(time(NULL));				// Random initialization 
		pressureOrder = (rand() % 100) * maxPressure / 100.0;
		Fgt_set_pressure(pressureIndex, pressureOrder);
		std::cout << "task1: New pressure order: " << pressureOrder << " mbar " << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	}
}

// Task driving pressure, every 5 seconds randomly
void task2(int pressureIndex)
{
	// Variables declaration
	float pressureOrder;
	float maxPressure;				// min/max pressure controller range
	float minPressure;

	// Get pressure controller range
	Fgt_get_pressureRange(pressureIndex, &minPressure, &maxPressure);

	while (!CancellationToken)
	{
		srand(time(NULL));				// Random initialization 
		pressureOrder = (rand() % 100) * maxPressure / 100.0;
		Fgt_set_pressure(pressureIndex, pressureOrder);
		std::cout << "task2: New pressure order: " << pressureOrder << " mbar " << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	}
}


int main()
{

	Fgt_init();						// Initialize session with all detected Fluigent instrument(s)
									// This step is mandatory before starting threads at the same time

	// Construct two threads and run. Does not block execution.
	std::thread thread1(task1, 0);		// Start thread on pressure channel index 0
	std::thread thread2(task2, 1);			// Start thread on pressure channel index 1

	// Wait 10 seconds
	std::this_thread::sleep_for(std::chrono::milliseconds(10000));

	// Stop threads
	CancellationToken = true;
	thread1.join();
	thread2.join();

	Fgt_set_pressure(0, 0);	// Set pressure to 0 before close
	Fgt_set_pressure(1, 0);	// Set pressure to 0 before close

	Fgt_close();								// Close session

}

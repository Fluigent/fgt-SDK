/*============================================================================
*               Fluigent Software Developement Kit for C++
*----------------------------------------------------------------------------
*         Copyright (c) Fluigent 2021.  All Rights Reserved.
*----------------------------------------------------------------------------
*
* Title:   Basic Set Pressure.cpp
* Purpose: This example shows how to set a pressure order and generate a ramp
*			on the first pressure module of the chain
*
* Software: fgt_SDK is the library managing all Fluigent instruments
*			"fgt_SDK_Cpp.h" is the wrapper to fgt_SDK dll
* Hardware setup: At least one Fluigent valve (M-Switch, L-Switch, 2-Switch
*                 or P-Switch)
* Version: 21.0.0.0
* Date:	04/2021
*============================================================================*/


#include <iostream>
#include "fgt_SDK_Cpp.h"			// include wrapper to fgt_SDK dll, functions can also be accessed by loading the dll

int main()
{
	Fgt_init();						// Initialize session with all detected Fluigent instrument(s)
									// This step is optional, if not called session will be automatically created

	unsigned char n_valves{};
	Fgt_get_valveChannelCount(&n_valves);

	if (n_valves == 0)
	{
		std::cout << "No valve channels found" << std::endl;
	}

	for (auto valve_index = 0U; valve_index < n_valves; valve_index++)
	{
		int position{};
		Fgt_get_valvePosition(valve_index, &position);
		std::cout << "Valve " << valve_index << " is in position " << position << std::endl;
		int pos_max{};
		Fgt_get_valveRange(valve_index, &pos_max);
		for (auto target_position = 0U; target_position <= pos_max; target_position++)
		{
			Fgt_set_valvePosition(valve_index, target_position);
			Fgt_get_valvePosition(valve_index, &position);
			std::cout << "Valve " << valve_index << " is in position " << position << std::endl;
		}
		Fgt_set_valvePosition(valve_index, 0);
	}

	// Close session
	Fgt_close();
}

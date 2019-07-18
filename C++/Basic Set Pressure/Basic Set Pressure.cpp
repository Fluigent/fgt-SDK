// Basic Set Pressure.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "../fgt_SDK_Cpp.h"

int main()
{
	std::string unit = "";
	Fgt_set_pressure(0, 10000);

	Fgt_get_pressureUnit(0, &unit);
	std::cout << "pressure unit: " << unit << std::endl;

	Fgt_set_pressureUnit(0, "PSI");
	Fgt_get_pressureUnit(0, &unit);
	std::cout << "pressure unit: " << unit << std::endl;

	Fgt_close();
}

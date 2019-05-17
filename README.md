# Fluigent Software Developement Kit - Beta version 19.0.0

# Overview
Fluigent Software Development Kit (SDK) allows you to fully integrate Fluigent devices in your application; it has been declined in several languages, among the most popular ones in the instrumentation field (e.g. LabVIEW, C++, C# .NET, Python…).

This SDK regroups all Fluigent pressure and sensor instruments as well as an advanced regulation loop. 

You can still use independent SDK (MFCS, FRP, LineUP) for basic hardware set-ups or for specific software requirements. 

Main advantages of using this SDK:
* all Fluigent instruments (pressure and sensor) are managed by one instance (instead of one instance per intrument type)
* if hardware is changed in many cases software code does not need to be adapted
* embedded regulation allow powerful and custom loop feedback between any pressure and sensor
* custom sensors (other than Fluigent ones) can also be pressure regulated
* features such as limits, units, calibration and detailed errors allow advanced functionalities

# Supported hardware
By using Fluigent SDK, you have direct access to following Fluigent devices:
* MFCS Series: MFCS, MFCS-EZ, MFCS-EX and PX pressure controllers
* LineUP Series: Link, Flow EZ pressure controller, flow-units XS, S, M, L and XL connected to Flow EZ
* Flowboard: XS, S, M, L and XL flow-units

# Software layers

## Fluigent dll

Fluigent SDK, is based upon the following files:
* fgt_SDK_32.dll
* fgt_SDK_64.dll
* fgt_SDK.h

Additionally, as Fluigent SDK interacts with Fluigent devices following dependencies are required:
* mfcs_c_32.dll
* mfcs_c_64.dll
* frp_c_32.dll
* frp_c_64.dll
* LineUP_c_32.dll
* LineUP_c_64.dll

## Dll wrappers

The SDK’s wrapper layer is an abstraction layer allowing the developer to manipulate high level concepts rather than low level function exposed by the provided dll.

Middleware layer main aim is to :
* call the fgt_SDK_*.dll file
* adapt variable type for a more friendly use
* display pretty error if occurs

Each programming language has it's own specificities however SDK Wrapper tries at best to be the same for each environment. 

Supported packages:

| Language | Package |
| --- | --- |
| C++ | fgt_SDK_Cpp.cpp middleware file.  fgt_SDK_Cpp.sln Visual Studio complete solution containing middleware and examples |

# Documentation
Refer to Fluigent SDK.pdf file for detailed documentation.

fgt_SDK_*.dll functions are documented in fgt_SDK.h header file.

Wrappers and examples are also documented, depending on the environement.

# Support
You can use this GitHub repository to find the source code, report issues, and contribute.

# Folders content
* **Fluigent SDK.pdf** file - Detailed documentation explaining global philosophy, functions and examples.
* **Shared** folder - Contains dll file and dependencies for 32 and 64 windows operating systems.
* **C++** folder - Contains C++ console application examples.
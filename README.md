# Fluigent Software Developement Kit

## Overview
Fluigent Software Development Kit (SDK) allows you to fully integrate Fluigent devices in your application; it has been declined in several languages, among the most popular ones in the instrumentation field (e.g. LabVIEW, C++, C\char`# .NET, Python…).

This SDK regroups all Fluigent pressure and sensor instruments as well as an advanced regulation loop. 

You can still use independent SDK (MFCS, FRP, LineUP) for basic hardware set-ups or for specific software requirements. 

Main advantages of using this SDK:
* all Fluigent instruments (pressure and sensor) are managed by one instance (instead of one instance per intrument type)
* if hardware is changed in many cases software code does not need to be adapted
* embedded regulation allow powerful and custom loop feedback between any pressure and sensor
* custom sensors (other than Fluigent ones) can also be pressure regulated
* features such as limits, units, calibration and detailed errors allow advanced functionalities

## Supported hardware
By using Fluigent SDK, you have direct access to following Fluigent devices:
* MFCS™ Series: MFCS™, MFCS™-EZ, MFCS™-EX and PX pressure controllers
* LineUP Series: Link, Flow EZ™ pressure controller, flow-units XS, S, M, L and XL connected to Flow EZ™
* Flowboard: XS, S, M, L and XL flow-units

## Software layers

# Fluigent dll

Fluigent SDK, is based upon the following files:
* fgt\_SDK\_32.dll
* fgt\_SDK\_64.dll
* fgt\_SDK.h


Additionally, as Fluigent SDK interacts with Fluigent devices following dependencies are required:
* mfcs\_c\_32.dll
* mfcs\_c\_64.dll
* frp\_c\_32.dll
* frp\_c\_64.dll
* LineUP\_c\_32.dll
* LineUP\_c\_64.dll

# Dll wrappers

The SDK’s wrapper layer is an abstraction layer allowing the developer to manipulate high level concepts rather than low level function exposed by the provided dll.


Installation Instructions
1. From LabVIEW, launch **Tools»VI Package Manager**, search for "NIPM API", and install it.
![alt text](images/nipm-api-on-vipm.png)
2. In LabVIEW, access the NIPM API by going to the **Functions Palette»Addons»NIPM API**.
3. (Optional) Install the [NIPM Feed Manager (Beta)](https://github.com/allenh-ni/nipm-feed-manager-gui-labview), and use it to manage NIPM feeds and packages. 

Note: If necessary, you can find historical versions in the [Exports](https://github.com/allenh-ni/nipm-api-labview/tree/master/Exports) folder.

## Documentation
Refer to the Context Help and examples that ship with the installed API.

## Support
This API is not officially supported by National Instruments. You can use this GitHub repository to find the source code, report issues, and contribute.

## Source Code
* **Source** folder - Contains the source code for this API.  At a low-level, this API calls the nipkg command-line interface (CLI).
* **Build Spec** folder - Contains the VIPM build spec (.vipb) used to create the .vip file.
* **Export** folder - Contains versions of the VIPM package (.vip), which you can use to install this API.
# Fluigent Software Developement Kit - version 21.0.0

# Overview
The Fluigent Software Development Kit (SDK) allows you to fully integrate Fluigent devices in your application;
it has been ported to the most popular programming language within the instrumentation field
(LabVIEW, C++, C# .NET, Python and MATLAB).

This SDK merge all Fluigent pressure controllers and sensor instruments and provide an advanced regulation loop.
You can still use independent SDK (MFCS, FRP, LineUP, ESS) for simple hardware setups or for specific software requirements.

Main advantages this newest version of our SDK, helps you to:
* Code faster by providing a single API for all instruments
* Save memory footprint using a single instance for all devices
* Ensure the interchangeability between Fluigent instruments
* Get the best performances with the embedded regulation allows powerful and custom
feedback loop between any pressure controller and sensor
* Use third party sensors that can be regulated by our pressure controllers
* Save time including features such as limits, units, calibration and detailed errors allow advanced functionalities

# Usage
The fastest way to use the SDK with your favorite language is to download the latest release from the 
[dedicated page](https://github.com/Fluigent/fgt-SDK/releases).
Then, follow the instructions from the manual to install each package.

If you want to compile from source, you can clone or download this repository and follow the instructions, when provided, 
in the language sub-folder you are interested in.

# Supported OS

| Operating system | 32 bits | 64 bits |
| ---------------- | ------- | ------- |
| Windows 7/8/10   | X       | X       |
| Linux            |         | X       |
| macOS            |         | X       |

# Supported hardware
By using Fluigent SDK, you have direct access to following Fluigent devices:
* MFCS Series: MFCS, MFCS-EZ, MFCS-EX and PX pressure controllers
* LineUP Series: Link, Flow EZ pressure controller, Flow Unit connected to Flow EZ,
Switch EZ and compatible switches, and P-Switch
* Flowboard and compatible Flow Units
* Inline Pressure Sensor (IPS)
* ESS Series Switchboard and compatible switches

# Software layers

## Native libraries

The Fluigent SDK, is based on a set of native shared libraries for each supported platform.
The libraries are sorted into folders by the operating system and processor architecture they target:

- windows/x86/fgt_SDK.dll
- windows/x64/fgt_SDK.dll
- linux/x64/libfgt_SDK.so
- mac/x64/libfgt_SDK.dylib
- fgt_SDK.h

Legacy files fgt_SDK_32.dll and fgt_SDK_64.dll are also included for convenience, in case.
They correspond to the Windows x86 and Windows x64 libraries, respectively.

## Middleware

The SDK middleware is a set of packages that make it easier to use the SDK with various programming languages.

The middleware packages provide the following functionalities for your convenience:
- Identify, locate and load the appropriate SDK native library according to the platform
- Convert data types to the native types used by each language to keep the user code clean
- Handle errors and display formatted error messages in program output

The middleware matches the conventions of each programming language while keeping the interface as similar as possible across all supported languages.

Supported packages:

| Language | Package                                                                                              |
| -------- | ---------------------------------------------------------------------------------------------------- |
| C++      | Cross-platform CMake project containing middleware and examples                                      |
| C#       | Cross-platform .NET Core NuGet package. .NET solution containing package source and examples         |
| LabVIEW  | Windows Toolkit with examples. LabVIEW project containing toolkit source                             |
| Python   | Cross-platform package and Windows installers. Project folder containing package source and examples |
| MATLAB   | Windows Toolbox containing middleware and examples. Project folder containing toolbox source         |

#### Linux permissions
On Linux-based operating systems, the system usually does not allow access to peripheral devices without superuser rights.
It is possible to make an exception for Fluigent instruments, so the SDK can detect and communicate with them when run by a normal user.
You can run the script **linux-udev.sh** that we provide, which automatically makes the necessary changes to the system.
The script must be run with superuser rights.

#### macOS signature problems
When opening a compiled library on macOS operating systems you may encounter an error **"libfgt_SDK.dylib" cannot be opened because the developer cannot be verified.** 
We are working to resolve this issue, but as a temporary workaround you can head to **System Preferences -> Security & Privacy** and click the **Allow Anyway** button 
next to the notification about the library being blocked due to an unidentified developer signature. We are sorry for the inconvenience!

# Documentation
Refer to the user manual **Fluigent SDK.pdf** for detailed documentation.

The public API of the native libraries is documented in the header file **fgt_SDK.h**.

Wrappers and examples are also documented, depending on the environement.

# Support
You can use this GitHub repository to find the source code, report issues, and contribute.

# Folders content
* **Fluigent SDK.pdf** file - Detailed documentation explaining global philosophy, functions and examples.
* **Shared** folder - Header file and the native shared libraries for all supported systems.
* **C++** folder - C++ CMake project with console application examples.
* **C#** folder - C# NuGet source and console application examples.
* **LabVIEW** folder - LabVIEW toolkit source and examples.
* **Python** folder - Python package source and  examples.
* **MATLAB** folder - MATLAB toolbox source and examples.

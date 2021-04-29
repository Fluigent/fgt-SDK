## C# Fluigent Software Development Kit

C# Fluigent SDK wrapper is a multi-platform middleware built with .NET Core 3.1 for the fgt_SDK library, compatible with Windows (x86 and x64), Linux (x64) and macOS (x64). 
* [Repository content](#repository-content)
* [Quick start](#quick-start)
	* [Install nuget using Visual Studio](#install-nuget-using-visual-studio)
	* [Install nuget using terminal](#install-nuget-using-terminal)
* [Building instructions](#building-instructions)
	* [Build using Visual Studio](#build-using-visual-studio)
    * [Build using dotnet command-line interface](#build-using-dotnet-command-line-interface)
* [FAQ](#faq)

## Repository content

This repository consists of the following directories:
                 
+ **fgt_sdk_csharp** with the middleware source code
+ **StaticFiles** with compiled fgt_SDK libraries for each supported platform and architecture
+ **UnitTests** project with a couple of low level test cases
+ **Examples** of how to use the wrapper:
    + **Basic Get Instruments Info** - retrieve information example about Fluigent instruments: type, controller, serial number and unique ID
	+  **Basic Read Sensor Data** - a basic example to show how to retrieve the data from the sensor channel
	+ **Basic Sensor Regulation** - simple example to set a flowrate and sinusoidal profile
	+ **Basic Set Pressure** - simple example to set a pressure and ramp profile
	+ **Basic Set Valve Position** - simple example to set the positions of valves
	+ **Advanced Custom Sensor Regulation** - use a custom sensor example different from Fluigent ones and regulate pressure
	+ **Advanced Features** - advanced features example such as limits, units and calibration
	+ **Advanced Parallel Pressure Control** - advanced example using threads in order to apply pressure asynchronously
	+ **Advanced Specific Multiple Instruments** - example use of specific channels ID and multiple connected instruments
	
## Quick start
The fastest and easiest way to start working with the C# wrapper for Fluigent SDK is to use the NuGeT dependency. However, you can also build the wrapper source with examples by yourself (for that check the [Building instructions](#building-instructions) section).

### Install nuget using Visual Studio
In order to install **fgt_sdk** package you have right-click your project in the solution explorer and choose **Manage NuGeT packages...**. In the search input type **fgt_sdk**, set **nuget.org** as a package source and click install. If you cannot find the package, you can alternatively download the latest **release** from GitHub that contains the NuGeT. Then you can install the package locally by adding a new **package source** that points to a folder containing **fgt_sdk.X.X.X.nupkg** archive.

Useful links:

 - [Create a .NET console application using Visual Studio](https://docs.microsoft.com/en-us/dotnet/core/tutorials/with-visual-studio)
 - [Manage NuGet packages in Visual Studio for Windows](https://docs.microsoft.com/en-us/nuget/consume-packages/install-use-packages-visual-studio)
 - [Manage NuGet packages in Visual Studio for Mac](https://docs.microsoft.com/en-us/visualstudio/mac/nuget-walkthrough?toc=/nuget/toc.json&view=vsmac-2019)

### Install nuget using terminal
Alternatively, you can use the terminal in order to install the **fgt_sdk** package. Here are the links to the tutorials on how to manage packages using:

 - [dotnet command-line interface](https://docs.microsoft.com/en-us/nuget/consume-packages/install-use-packages-dotnet-cli)
 - [nuget command-line interface](https://docs.microsoft.com/en-us/nuget/consume-packages/install-use-packages-nuget-cli)

## Building instructions

In order to build the project make sure you have **.NET Core 3.1 SDK and .NET Core Runtime** installed. You can download the missing platform [here](https://dotnet.microsoft.com/download).
 
### Build using Visual Studio

Open the `fgt_sdk_csharp.sln` file in Visual Studio. From the `Build` menu choose `Build Solution` option. In order to run an example change the startup item in the toolbar menu to the chosen project and from the `Debug` menu choose `Start Debugging`.
You can find compiled package under a following path:
`\fgt_sdk_csharp\bin\{build type}\fgt_sdk.X.X.X.nupkg`

### Build using dotnet command-line interface
Open the terminal in the root directory (where the file `fgt-sdk-csharp.sln` is located). Build the project using a command below
```sh
dotnet build
```
This command will build the middleware project, produce a nuget package and compile all the examples.
In order to run the example execute the `dotnet run` command with the `project` parameter:
```sh
dotnet run --project ./Examples/{example folder}/{example name}.csproj
```

## FAQ
Are you stuck with an error in your code? Find a couple of useful tips below! If it does not help to solve your problem and you think that you found a bug, consider adding a new issue on our [GitHub repository](https://github.com/Fluigent/fgt-SDK "GitHub repository").
                 
+ *Why Fluigent class `fgtSdk` is undefined?*

Make sure that you include the namespace with the `using` directive
```csharp
using fgt_sdk;
```

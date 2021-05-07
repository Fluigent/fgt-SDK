## C++ Fluigent Software Development Kit

C++ Fluigent SDK wrapper is a multi-platform C++ middleware for the fgt_SDK library, compatible with Windows (x86 and x64), Linux (x64) and macOS (x64). 
* [Repository content](#repository-content)
* [Building instructions](#building-instructions)
    * [Prerequisites](#prerequisites)
    * [Build with CMake command-line interface](#build-with-cmake-command-line-interface)
    * [Build with Visual Studio or VS Code](#build-with-visual-studio-or-vs-code)
    * [Start new project](#start-new-project)
* [FAQ](#faq)

## Repository content

This repository consists of following directories:
                 
+ **fgt_SDK_Cpp** with the middleware source code and compiled fgt_SDK libraries for each supported platform and architecture
+ Examples of how to use the wrapper:
    + **Basic Get Instruments Info** - retrieve information example about Fluigent instruments: type, controller, serial number and unique ID
	+  **Basic Read Sensor Data** - basic example to show how to retrieve the data from the sensor channel
	+ **Basic Sensor Regulation** - simple example to set a flowrate and sinusoidal profile
	+ **Basic Set Pressure** - simple example to set a pressure and ramp profile
	+ **Basic Set Valve Position** - simple example to set the positions of valves
	+ **Advanced Custom Sensor Regulation** - use a custom sensor example different from Fluigent ones and regulate pressure
	+ **Advanced Features** - advanced features example such as limits, units and calibration
	+ **Advanced Parallel Pressure Control** - advanced example using threads in order to apply pressure asynchronously
	+ **Advanced Specific Multiple Instruments** - example use of specific channels ID and multiple connected instruments

## Building instructions
### Prerequisites
In order to build the project make sure you have installed following components:
                 
+ **C++ compiler** - following compilers have been used during tests:
	+ MSVC (on Windows)
	+ GCC (on Linux)
	+ Clang (on macOS)
+ [**CMake**](https://cmake.org/) with a version 3.17 or higher
 
### Build with CMake command-line interface
Open the terminal in the folder where this Readme file is located, create and enter the `build` folder.
```sh
mkdir build
cd build
```
Then generate and configure the build files. CMake will automatically detect installed C++ compiler.
```sh
cmake ..
```
Start the build process using generated files. This will compile all the examples and copy the appropriate library version to the output folder (`/build/Examples/{Example Folder name}/`). Depending on the user CMake settings the output executable can be located in additional `Debug` or `Release` folder. You can read more about passing the build type parameter to the cmake command in the [documentation](https://cmake.org/cmake/help/latest/variable/CMAKE_BUILD_TYPE.html).
```sh
cmake --build .
```
Run the chosen example in console. 
```sh
./Examples/{Example Folder Name}/{ExampleName}
```

### Build with Visual Studio or VS Code
Before you proceed make sure you have the `CMake tools` available in your IDE. This extension is installed together with `Desktop development with C++` by default in **Visual Studio for Windows**. You can verify the component installation in Visual Studio Installer. 

For **macOS and Linux** you can install this tool in the extension view of **VS Code**. Note that the it is possible to build and run the project in other IDEs that supports C++, however the environment setups mentioned above were tested and used by us.

                 
+ Run the Visual Studio or VS Code and open the project root folder by clicking **File->Open Folder..**
+ Find the `CMakeLists.txt` in the **project root folder** inside the solution explorer. Right click on the file and choose **Generate Cache for fgt_SDK_Cpp** in Visual Studio or **Configure All Projects** in VS Code. If you do not find this option verify your CMake and CMake tools extension installation.
+ Build the projects by choosing **Build->Build All** in the Visual Studio top panel or right clicking `CMakeLists.txt` and choosing **Build All Projects** in VS Code.
+ Change the startup item in the toolbar menu and hit **F** button to run / debug the chosen example in Visual Studio or execute the output in the console (`/build/Examples/{Example Folder Name}/{ExampleName}`). In VS Code you can also prepare the launch configuration to automate that process.

### Start new project
The easiest way to start a new project is to copy and modify the files from this repository. You can remove the `Examples` directory and create your own project. Then you have to modify the **last line** of the `CMakeLists.exe` in the root project folder by adding a new directory name. 
```cmake
add_subdirectory(Examples) # Change to add_subdirectory(NewProjectName)
```
Next step is to initialize the empty directory of the new project with a `CMakeLists.txt` file with the following content:
```cmake
set(program_name "NewProgram") # Set your program name
add_executable(${program_name} "NewProgramMain.cpp") # Add source code here
target_link_libraries(${program_name} PRIVATE fgt_SDK_cpp)
COPY_SDK_LIB(${program_name})
```
Happy coding!

## FAQ
Are you stuck with an error in your code? Find couple of useful tips below! If it does not help to solve your problem and you think that you found a bug, consider adding new issue on our [GitHub repository](https://github.com/Fluigent/fgt-SDK "GitHub repository").
                 
+ *Why Fluigent function `Fgt_xxx_xxxxx` is undefined?*

Make sure that you include the header with the declarations in your source code 
```cpp
#include "fgt_SDK_Cpp.h"
```
+ *Can I use the fgt_SDK library directly?*

The answer is yes. You can link the appropriate version of the library statically during compilation or dynamically inside your source code.
# nipm-api-labview
NI Package Manager API (Beta) for LabVIEW 2014 or later.

## Overview
My goal is to provide users with a beta API for NI Package Manager tasks.  Please feel free to use this API, give feedback, and contribute.  NI will use this feedback to create an official NIPM API in the future.

You can use this API to:
* Install/uninstall/upgrade packages
* Get package attributes
* Create feeds, add packages to feeds, remove packages from feeds, list packages in feeds
* Register/unregister feeds
* ...

![alt text](images/nipm-beta-api-screenshot.png)

You can find content, tutorials, and additional tools for NI package management at [bit.ly/nipkg](http://bit.ly/nipkg)

## How to Install
Prerequisites:
* LabVIEW 2014 or later
* [NI Package Manager](http://www.ni.com/downloads/ni-package-manager) 17.5 or later
* Operating System: Refer to the OS requirements for NI Package Manager

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
Before going through any of these steps, first you need to get the project set up. 

1. Create a directory structure that suites you on your hard drive. 
2. In visual studio, create a project, and select it to load out of the folder of your choice. Use /Build
3. When you want to add a new folder to the project, right click on the solution, and select "Add new Filter", then map the filter to the folder that you want on your hard drive. 

Suggested Directory Structure: 
Assets
Build
Docs
Bin
ExLib [External Libraries that are to be included and are not part of the system]
Headers
Source
 [other folders for various files]
Temp


By doing this, you can have the solution and project files not clutter up everything. 

Note: The $(PlatformName) is for any project that is going to be supported by more than one system. If you are going to support only one Platform, IE, only windows, or only linux, then this can be excluded. 

Configutation Properties -> General

-> Output Directory: $(ProjectDir)..\..\..\Bin\$(PlatformName)$(Configuration)\ 

-> Intermediate Directory: $(ProjectDir)..\..\..\Temp\$(ProjectName)$(Configuration)\

-> Target Name: $(ProjectName)$(PlatformName)$(Configuration)

*Some of the following values may be set by default. 

-> Debugging -> Debugging Command : $(TargetPath) *usually set by default

-> Debugging-> Working Directory : $(ProjectDir)..\..\..\Bin\

C/C++ -> Precompiled Headers -> Precompiled Header File : $(IntDir)$(TargetName).pch *usually set by default


-> General -> Additional Include Directories : $(ProjectDir)..\..\Headers\

-> Output Files : $(IntDir) for Asm List Location, Object Filename and Program Database File, this is usually set by default.

Linker -> Debug Settings -> Generate Program Database File : $(TargetDir)$(TargetName).pdb

-> Debugging -> Map File : $(TargetDir)$(TargetName).map [May have to enable the file to even be made]

xcopy "$(TargetDir)$(TargetName).lib" "C:\Projects\KIller1_UnitTests\ExLib\" /s /i /y





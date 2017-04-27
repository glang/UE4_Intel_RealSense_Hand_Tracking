# Unreal Engine 4 + Intel RealSense Hand Tracking
A Unreal Engine 4 project that integrates Intel Realsense (librealsense) for basic hand tracking

![](http://i.imgur.com/1TvzITs.gif)

If you are also trying to get librealsense to work with UE4, then of particular importance is what I added to this project's build.cs file here: https://github.com/glang/UE4_Intel_RealSense_Hand_Tracking/blob/master/Source/R200_Hand_Tracking/R200_Hand_Tracking.Build.cs You want to change those paths to ones pointing to where you put those files. Without this, visual studio will not be able to compile correctly with librealsense functions.

This tutorial helped me immensely: 
https://wiki.unrealengine.com/Linking_Static_Libraries_Using_The_Build_System
But for the build.cs file, use what I have instead. The code in the guide is outdated.

If you have any questions about this, email me at grangerzero (at) gmail

Happy hacking!

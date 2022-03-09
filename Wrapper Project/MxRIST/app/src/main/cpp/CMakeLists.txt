## For more information about using CMake with Android Studio, read the
## documentation: https://d.android.com/studio/projects/add-native-code.html
#
## Sets the minimum version of CMake required to build the native library.
#
#cmake_minimum_required(VERSION 3.10.2)
#
## Declares and names the project.
#
#project("mxrist")
#
## Creates and names a library, sets it as either STATIC
## or SHARED, and provides the relative paths to its source code.
## You can define multiple libraries, and CMake builds them for you.
## Gradle automatically packages shared libraries with your APK.
#
#add_library( # Sets the name of the library.
#        ../../../../jni/rist/
#
#        # Sets the library as a shared library.
#        SHARED
#
#        # Provides a relative path to your source file(s).
#        ../../../../jni/RISTNet.cpp)
#
##set_target_properties( # Specifies the target library.
##        imported-lib
##
##        # Specifies the parameter you want to define.
##        PROPERTIES IMPORTED_LOCATION
##
##        # Provides the path to the library you want to import.
##        imported-lib/src/${ANDROID_ABI}/libimported-lib.so )
#
#include_directories(../../../../jni/rist/include/)
#
#
#find_library( # Defines the name of the path variable that stores the
#        # location of the NDK library.
#        log-lib
#
#        # Specifies the name of the NDK library that
#        # CMake needs to locate.
#        log )
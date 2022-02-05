![librist logo](librist_logo.png)

# librist

A library that can be used to easily add the RIST protocol to your application.

This code was written to comply with the Video Services Forum (VSF) Technical Recommendations TR-06-1 and TR-06-2. The protocol goes by the codename "RIST"

The canonical repository URL for this repo is https://code.videolan.org/rist/librist

This project is partially funded by the SipRadius LLC.

### Reached
1. Complete C implementation of the rist protocol,
2. Provide a usable API.

### On-going
1. Currently I am compiling the Library for Android and IOS platform.

## Goal and Features

The goal of this project is to provide a rist library for **most platforms**.

It supports all features from the TR-06-1 and most of the features of TR-06-2.

## Library sweet spot (optimal use cases with current defaults)

- Buffer sizes from 50 ms to 30 seconds
- Networks with round trip times from 0ms to 5000ms
- Bitrates from 0 to 1 Gbps
- Packet size should be kept under the path's MTU (typically 1500). The library does not support packet fragmentation.
- Bi-directional communication available (not one-way systems like satellite)

If you have an application that needs to operate outside the sweet spot described above, you will need to modify some constants in the rist-private.h header and/or use some of the more obscure API calls to fine tune the library for your use case. The library can overcome all the limitations above by fine-tuning with the exception of packet fragmentation which will be addressed as a feature enhancement in the future.

## Dependencies

None. This library has no external runtime dependencies on any OS other than normal core OS libraries.

# Compile using meson/ninja (linux, osx and windows-mingw)

1. Install [Meson](https://mesonbuild.com/) (0.47 or higher), [Ninja](https://ninja-build.org/)
2. Alternatively, use "pip3 install meson" and "pip3 install ninja" to install them
3. Run `mkdir build && cd build` to create a build directory and enter it
4. Run `meson ..` to configure meson, add `--default-library=static` if static linking is desired
5. Run `ninja` to compile

# Compile using meson/ninja (windows - Visual Studio 2019)

1. Open a cmd window and type "pip3 install meson" to install meson through Python Package Index
2. Run x64 Native Tools Command Prompt for VS 2019.exe
3. cd to the folder where you downloaded or cloned the librist source code
4. Run the command "meson setup build --backend vs2019"
5. Run the command "meson compile -C build"
6. The compiled library and the tools will be in the build and build/tools folders respectively
7. Alternatively, open librist.sln and build the applications manually if you prefer to use the VS IDE


## License

**librist** is released under a very liberal license, a contrario from the other VideoLAN projects, so that it can be embedded anywhere, including non-open-source software; or even drivers, to allow the creation of hybrid decoders.

The reasoning behind this decision is the same as for libvorbis, see [RMS on vorbis](https://lwn.net/2001/0301/a/rms-ov-license.php3).

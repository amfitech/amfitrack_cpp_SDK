# AMFITRACK C++ SDK

## Overview
The **AMFITRACK C++ SDK** is a C++ library that enables developers to interface with AMFITRACK devices. This SDK provides a streamlined API for integrating AMFITRACK motion tracking hardware into your projects.

This document explains how to set up and use the SDK in a C++ project using CMake.

## Features
- Simple API for accessing AMFITRACK devices.
- C++17/20 compatibility.
- Cross-platform support (Windows, Linux, macOS).
- Example project for quick integration.

## Prerequisites
Before using the SDK, ensure you have the following installed:

- **C++ Compiler:**
  - MSVC (Visual Studio 2019 or later)
  - GCC 8+ (Linux)
  - Clang (macOS/Linux)
- **CMake** (version 3.15 or later)
- **Git** (for cloning the repository and submodules)

## Installation
### Cloning the SDK
To use the SDK in your project, clone the repository and initialize submodules:
```sh
# Clone the repository
git clone --recurse-submodules https://github.com/amfitech/amfitrack_cpp_SDK.git
```

Alternatively, if you already cloned it without submodules:
```sh
git submodule update --init --recursive
```

## Integrating the SDK into a C++ Project
### Using CMake
Below is an example `CMakeLists.txt` file demonstrating how to integrate the SDK into your project:

```cmake
cmake_minimum_required(VERSION 3.15)

project("Amfitrack_TestProject")

# Add the AMFITRACK SDK as a subdirectory
add_subdirectory("Library/amfitrack_cpp_SDK")

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Source files
set(SOURCES
    Amfitrack_TestProject.cpp
)

# Header files
set(HEADERS
    Amfitrack_TestProject.hpp
)

# Define the executable
add_executable(Amfitrack_TestProject ${SOURCES} ${HEADERS})

# Link the AMFITRACK API library
target_link_libraries(Amfitrack_TestProject PUBLIC Amfitrack_API)

# Set C++ standard
if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET Amfitrack_TestProject PROPERTY CXX_STANDARD 20)
endif()
```

## Usage
### Initializing the SDK
To use the Amfitrack SDK in your code:

```cpp
#include "AmfitrackCppSDK.hpp"

int main() {
    /* Create instance of amfitrack */ 
    AMFITRACK& AMFITRACK = AMFITRACK::getInstance(); 
    /* Initializes the USB and connects to the devices */
    AMFITRACK.initialize_amfitrack();
    /* Starts the main thread, that read the data */
    AMFITRACK.start_amfitrack_task();

    while (1)
    {
        /* See if AMFITRACK Sensor device ID 2 is active */
        if (AMFITRACK.getDeviceActive(2))
        {
            lib_AmfiProt_Amfitrack_Pose_t PoseTester;
            /* Get the pose from AMFITRACK Sensor device ID 2 */
            AMFITRACK.getDevicePose(2, &PoseTester);
            printf("Pose X: %f | Y: %f | Z: %f \n", PoseTester.position_x_in_m, 
                                                    PoseTester.position_y_in_m, 
                                                    PoseTester.position_z_in_m
                                                    );
        }
    }
}
```

## Contributions

Contributions are welcome! Please submit issues and pull requests on GitHub.

## Contact

For discussions, questions, and support, visit the [GitHub Discussions](https://github.com/amfitech/amfitrack_cpp_SDK/discussions) page.
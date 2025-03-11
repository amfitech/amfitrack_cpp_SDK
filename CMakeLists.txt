# CMakeList.txt : CMake project for Amfitrack_Cpp_SDK, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.16)

# Set the project name
set(APP_NAME Amfitrack_API)

project (${APP_NAME})

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/amfiprotapi)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/lib_crc)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/lib_generic_parameter)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/lib_macro)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/lib_queue)


# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_PATH})

# Source files
set(SOURCES
    Amfitrack.cpp
    src/AmfitrackNode.cpp
    src/usb_connection.cpp
    lib/amfiprotapi/lib_AmfiProt.cpp
    lib/amfiprotapi/lib_AmfiProt_Amfitrack.cpp
    lib/amfiprotapi/lib_AmfiProt_API.cpp
    lib/lib_crc/lib_CRC.c
    lib/lib_generic_parameter/lib_Generic_Parameter.c
    lib/lib_queue/lib_Queue.c
)

# Header files
set(HEADERS
    Amfitrack.hpp
    src/AmfitrackNode.h
    src/usb_connection.h
    src/project_conf.h
    lib/amfiprotapi/lib_AmfiProt.hpp
    lib/amfiprotapi/lib_AmfiProt_Amfitrack.hpp
    lib/amfiprotapi/lib_AmfiProt_API.hpp
    lib/lib_crc/lib_CRC.h
    lib/lib_generic_parameter/lib_Generic_Parameter.h
    lib/lib_macro/lib_MACRO.h
    lib/lib_queue/lib_Queue.h
)

# Add library
add_library(${APP_NAME} ${SOURCES} ${HEADERS})

# ===== HIDAPI Cross-Platform Integration =====
set(HIDAPI_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib/hidapi")
set(BUILD_SHARED_LIBS OFF)  # Force static library
add_subdirectory(${HIDAPI_PATH})

# Include HIDAPI headers
include_directories(${HIDAPI_PATH}/hidapi)

# Select the correct HIDAPI backend for each OS
target_link_libraries(${APP_NAME} PRIVATE hidapi::hidapi)
#if(WIN32)
#    target_link_libraries(${APP_NAME} PRIVATE hidapi::winapi)
#elseif(APPLE)
#    target_link_libraries(${APP_NAME} PRIVATE hidapi::darwin)
#elseif(UNIX)
#    target_link_libraries(${APP_NAME} PRIVATE hidapi::libusb)
#endif()

# Ensure HIDAPI is included in build
target_include_directories(${APP_NAME} PRIVATE ${HIDAPI_PATH}/hidapi)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${APP_NAME} PROPERTY CXX_STANDARD 20)
endif()

# Compiler-specific options
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # Add MSVC-specific options here
  target_compile_options(${APP_NAME} PRIVATE /W4 /permissive-)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # Add G++-specific options here
  target_compile_options(${APP_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

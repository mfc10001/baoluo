# Install script for directory: /home/ll/baoluo/ise/ise/ext/utils/json

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/ll/baoluo/ise/build/linux/debug-install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/ll/baoluo/ise/build/linux/debug/lib/libise_utils_json.a")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ise/ext/utils/json" TYPE FILE FILES
    "/home/ll/baoluo/ise/build/linux/../../ise/ext/utils/json/autolink.h"
    "/home/ll/baoluo/ise/build/linux/../../ise/ext/utils/json/config.h"
    "/home/ll/baoluo/ise/build/linux/../../ise/ext/utils/json/json_batchallocator.h"
    "/home/ll/baoluo/ise/build/linux/../../ise/ext/utils/json/value.h"
    "/home/ll/baoluo/ise/build/linux/../../ise/ext/utils/json/json.h"
    "/home/ll/baoluo/ise/build/linux/../../ise/ext/utils/json/writer.h"
    "/home/ll/baoluo/ise/build/linux/../../ise/ext/utils/json/reader.h"
    "/home/ll/baoluo/ise/build/linux/../../ise/ext/utils/json/forwards.h"
    "/home/ll/baoluo/ise/build/linux/../../ise/ext/utils/json/features.h"
    )
endif()

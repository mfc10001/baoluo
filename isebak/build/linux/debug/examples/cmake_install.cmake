# Install script for directory: /home/ll/baoluo/ise/examples

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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/ll/baoluo/ise/build/linux/debug/examples/hello_world/cmake_install.cmake")
  include("/home/ll/baoluo/ise/build/linux/debug/examples/chargen_client/cmake_install.cmake")
  include("/home/ll/baoluo/ise/build/linux/debug/examples/chargen_server/cmake_install.cmake")
  include("/home/ll/baoluo/ise/build/linux/debug/examples/daytime_server/cmake_install.cmake")
  include("/home/ll/baoluo/ise/build/linux/debug/examples/discard_server/cmake_install.cmake")
  include("/home/ll/baoluo/ise/build/linux/debug/examples/echo_server/cmake_install.cmake")
  include("/home/ll/baoluo/ise/build/linux/debug/examples/server_modules/cmake_install.cmake")
  include("/home/ll/baoluo/ise/build/linux/debug/examples/server_module_msgs/cmake_install.cmake")
  include("/home/ll/baoluo/ise/build/linux/debug/examples/http_server/cmake_install.cmake")
  include("/home/ll/baoluo/ise/build/linux/debug/examples/server_inspector/cmake_install.cmake")
  include("/home/ll/baoluo/ise/build/linux/debug/examples/thread_pool/cmake_install.cmake")
  include("/home/ll/baoluo/ise/build/linux/debug/examples/udp_server/cmake_install.cmake")
  include("/home/ll/baoluo/ise/build/linux/debug/examples/udp_client/cmake_install.cmake")
  include("/home/ll/baoluo/ise/build/linux/debug/examples/timer/cmake_install.cmake")

endif()

# Install script for directory: /home/ll/baoluo/ise/build/linux

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/ll/baoluo/ise/build/linux/debug/lib/libise.a")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ise/main" TYPE FILE FILES
    "/home/ll/baoluo/ise/build/linux/../../ise/main/ise_iocp.h"
    "/home/ll/baoluo/ise/build/linux/../../ise/main/ise_inspector.h"
    "/home/ll/baoluo/ise/build/linux/../../ise/main/ise_options.h"
    "/home/ll/baoluo/ise/build/linux/../../ise/main/ise_thread.h"
    "/home/ll/baoluo/ise/build/linux/../../ise/main/ise_template.h"
    "/home/ll/baoluo/ise/build/linux/../../ise/main/ise_server_tcp.h"
    "/home/ll/baoluo/ise/build/linux/../../ise/main/ise_stldefs.h"
    "/home/ll/baoluo/ise/build/linux/../../ise/main/ise_application.h"
    "/home/ll/baoluo/ise/build/linux/../../ise/main/ise_exceptions.h"
    "/home/ll/baoluo/ise/build/linux/../../ise/main/ise_classes.h"
    "/home/ll/baoluo/ise/build/linux/../../ise/main/ise.h"
    "/home/ll/baoluo/ise/build/linux/../../ise/main/ise_socket.h"
    "/home/ll/baoluo/ise/build/linux/../../ise/main/ise_epoll.h"
    "/home/ll/baoluo/ise/build/linux/../../ise/main/ise_timer.h"
    "/home/ll/baoluo/ise/build/linux/../../ise/main/ise_assert.h"
    "/home/ll/baoluo/ise/build/linux/../../ise/main/ise_svr_mod.h"
    "/home/ll/baoluo/ise/build/linux/../../ise/main/ise_svr_mod_msgs.h"
    "/home/ll/baoluo/ise/build/linux/../../ise/main/ise_http.h"
    "/home/ll/baoluo/ise/build/linux/../../ise/main/ise_server_assistor.h"
    "/home/ll/baoluo/ise/build/linux/../../ise/main/ise_err_msgs.h"
    "/home/ll/baoluo/ise/build/linux/../../ise/main/ise_event_loop.h"
    "/home/ll/baoluo/ise/build/linux/../../ise/main/ise_global_defs.h"
    "/home/ll/baoluo/ise/build/linux/../../ise/main/ise_sys_threads.h"
    "/home/ll/baoluo/ise/build/linux/../../ise/main/ise_sys_utils.h"
    "/home/ll/baoluo/ise/build/linux/../../ise/main/ise_server_udp.h"
    "/home/ll/baoluo/ise/build/linux/../../ise/main/ise_database.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/ll/baoluo/ise/build/linux/debug/ext/utils/cmake_install.cmake")
  include("/home/ll/baoluo/ise/build/linux/debug/ext/dbi/mysql/cmake_install.cmake")
  include("/home/ll/baoluo/ise/build/linux/debug/ext/utils/cipher/cmake_install.cmake")
  include("/home/ll/baoluo/ise/build/linux/debug/ext/utils/xml/cmake_install.cmake")
  include("/home/ll/baoluo/ise/build/linux/debug/examples/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

file(WRITE "/home/ll/baoluo/ise/build/linux/debug/${CMAKE_INSTALL_MANIFEST}" "")
foreach(file ${CMAKE_INSTALL_MANIFEST_FILES})
  file(APPEND "/home/ll/baoluo/ise/build/linux/debug/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
endforeach()

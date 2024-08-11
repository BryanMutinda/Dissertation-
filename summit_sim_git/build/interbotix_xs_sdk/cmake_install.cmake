# Install script for directory: /home/bryan/dissertation/Dissertation-/summit_sim_git/src/trossen/interbotix_ros_core/interbotix_ros_xseries/interbotix_xs_sdk

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/bryan/dissertation/Dissertation-/summit_sim_git/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  
      if (NOT EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}")
        file(MAKE_DIRECTORY "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}")
      endif()
      if (NOT EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/.catkin")
        file(WRITE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/.catkin" "")
      endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/bryan/dissertation/Dissertation-/summit_sim_git/install/_setup_util.py")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/bryan/dissertation/Dissertation-/summit_sim_git/install" TYPE PROGRAM FILES "/home/bryan/dissertation/Dissertation-/summit_sim_git/build/interbotix_xs_sdk/catkin_generated/installspace/_setup_util.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/bryan/dissertation/Dissertation-/summit_sim_git/install/env.sh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/bryan/dissertation/Dissertation-/summit_sim_git/install" TYPE PROGRAM FILES "/home/bryan/dissertation/Dissertation-/summit_sim_git/build/interbotix_xs_sdk/catkin_generated/installspace/env.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/bryan/dissertation/Dissertation-/summit_sim_git/install/setup.bash;/home/bryan/dissertation/Dissertation-/summit_sim_git/install/local_setup.bash")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/bryan/dissertation/Dissertation-/summit_sim_git/install" TYPE FILE FILES
    "/home/bryan/dissertation/Dissertation-/summit_sim_git/build/interbotix_xs_sdk/catkin_generated/installspace/setup.bash"
    "/home/bryan/dissertation/Dissertation-/summit_sim_git/build/interbotix_xs_sdk/catkin_generated/installspace/local_setup.bash"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/bryan/dissertation/Dissertation-/summit_sim_git/install/setup.sh;/home/bryan/dissertation/Dissertation-/summit_sim_git/install/local_setup.sh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/bryan/dissertation/Dissertation-/summit_sim_git/install" TYPE FILE FILES
    "/home/bryan/dissertation/Dissertation-/summit_sim_git/build/interbotix_xs_sdk/catkin_generated/installspace/setup.sh"
    "/home/bryan/dissertation/Dissertation-/summit_sim_git/build/interbotix_xs_sdk/catkin_generated/installspace/local_setup.sh"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/bryan/dissertation/Dissertation-/summit_sim_git/install/setup.zsh;/home/bryan/dissertation/Dissertation-/summit_sim_git/install/local_setup.zsh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/bryan/dissertation/Dissertation-/summit_sim_git/install" TYPE FILE FILES
    "/home/bryan/dissertation/Dissertation-/summit_sim_git/build/interbotix_xs_sdk/catkin_generated/installspace/setup.zsh"
    "/home/bryan/dissertation/Dissertation-/summit_sim_git/build/interbotix_xs_sdk/catkin_generated/installspace/local_setup.zsh"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/bryan/dissertation/Dissertation-/summit_sim_git/install/.rosinstall")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/bryan/dissertation/Dissertation-/summit_sim_git/install" TYPE FILE FILES "/home/bryan/dissertation/Dissertation-/summit_sim_git/build/interbotix_xs_sdk/catkin_generated/installspace/.rosinstall")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/interbotix_xs_sdk/msg" TYPE FILE FILES
    "/home/bryan/dissertation/Dissertation-/summit_sim_git/src/trossen/interbotix_ros_core/interbotix_ros_xseries/interbotix_xs_sdk/msg/JointGroupCommand.msg"
    "/home/bryan/dissertation/Dissertation-/summit_sim_git/src/trossen/interbotix_ros_core/interbotix_ros_xseries/interbotix_xs_sdk/msg/JointSingleCommand.msg"
    "/home/bryan/dissertation/Dissertation-/summit_sim_git/src/trossen/interbotix_ros_core/interbotix_ros_xseries/interbotix_xs_sdk/msg/JointTrajectoryCommand.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/interbotix_xs_sdk/srv" TYPE FILE FILES
    "/home/bryan/dissertation/Dissertation-/summit_sim_git/src/trossen/interbotix_ros_core/interbotix_ros_xseries/interbotix_xs_sdk/srv/Reboot.srv"
    "/home/bryan/dissertation/Dissertation-/summit_sim_git/src/trossen/interbotix_ros_core/interbotix_ros_xseries/interbotix_xs_sdk/srv/RobotInfo.srv"
    "/home/bryan/dissertation/Dissertation-/summit_sim_git/src/trossen/interbotix_ros_core/interbotix_ros_xseries/interbotix_xs_sdk/srv/MotorGains.srv"
    "/home/bryan/dissertation/Dissertation-/summit_sim_git/src/trossen/interbotix_ros_core/interbotix_ros_xseries/interbotix_xs_sdk/srv/TorqueEnable.srv"
    "/home/bryan/dissertation/Dissertation-/summit_sim_git/src/trossen/interbotix_ros_core/interbotix_ros_xseries/interbotix_xs_sdk/srv/OperatingModes.srv"
    "/home/bryan/dissertation/Dissertation-/summit_sim_git/src/trossen/interbotix_ros_core/interbotix_ros_xseries/interbotix_xs_sdk/srv/RegisterValues.srv"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/interbotix_xs_sdk/cmake" TYPE FILE FILES "/home/bryan/dissertation/Dissertation-/summit_sim_git/build/interbotix_xs_sdk/catkin_generated/installspace/interbotix_xs_sdk-msg-paths.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/bryan/dissertation/Dissertation-/summit_sim_git/devel/.private/interbotix_xs_sdk/include/interbotix_xs_sdk")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/bryan/dissertation/Dissertation-/summit_sim_git/devel/.private/interbotix_xs_sdk/share/roseus/ros/interbotix_xs_sdk")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/bryan/dissertation/Dissertation-/summit_sim_git/devel/.private/interbotix_xs_sdk/share/common-lisp/ros/interbotix_xs_sdk")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/bryan/dissertation/Dissertation-/summit_sim_git/devel/.private/interbotix_xs_sdk/share/gennodejs/ros/interbotix_xs_sdk")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND "/usr/bin/python3" -m compileall "/home/bryan/dissertation/Dissertation-/summit_sim_git/devel/.private/interbotix_xs_sdk/lib/python3/dist-packages/interbotix_xs_sdk")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages" TYPE DIRECTORY FILES "/home/bryan/dissertation/Dissertation-/summit_sim_git/devel/.private/interbotix_xs_sdk/lib/python3/dist-packages/interbotix_xs_sdk")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/bryan/dissertation/Dissertation-/summit_sim_git/build/interbotix_xs_sdk/catkin_generated/installspace/interbotix_xs_sdk.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/interbotix_xs_sdk/cmake" TYPE FILE FILES "/home/bryan/dissertation/Dissertation-/summit_sim_git/build/interbotix_xs_sdk/catkin_generated/installspace/interbotix_xs_sdk-msg-extras.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/interbotix_xs_sdk/cmake" TYPE FILE FILES
    "/home/bryan/dissertation/Dissertation-/summit_sim_git/build/interbotix_xs_sdk/catkin_generated/installspace/interbotix_xs_sdkConfig.cmake"
    "/home/bryan/dissertation/Dissertation-/summit_sim_git/build/interbotix_xs_sdk/catkin_generated/installspace/interbotix_xs_sdkConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/interbotix_xs_sdk" TYPE FILE FILES "/home/bryan/dissertation/Dissertation-/summit_sim_git/src/trossen/interbotix_ros_core/interbotix_ros_xseries/interbotix_xs_sdk/package.xml")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/interbotix_xs_sdk" TYPE PROGRAM FILES "/home/bryan/dissertation/Dissertation-/summit_sim_git/build/interbotix_xs_sdk/catkin_generated/installspace/xs_sdk_sim")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/bryan/dissertation/Dissertation-/summit_sim_git/build/interbotix_xs_sdk/gtest/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/bryan/dissertation/Dissertation-/summit_sim_git/build/interbotix_xs_sdk/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")

execute_process(COMMAND "/home/bryan/dissertation/Dissertation-/summit_sim_git/build/interbotix_ux_modules/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/bryan/dissertation/Dissertation-/summit_sim_git/build/interbotix_ux_modules/catkin_generated/python_distutils_install.sh) returned error code ")
endif()

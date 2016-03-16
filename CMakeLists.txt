cmake_minimum_required(VERSION 2.8.8)

#project(FeederLocator)
set(LIB_DIR "${CMAKE_BINARY_DIR}/lib")
set(BIN_DIR "${CMAKE_BINARY_DIR}/bin")
file(MAKE_DIRECTORY "${LIB_DIR}")
file(MAKE_DIRECTORY "${BIN_DIR}")



##########################
#install setting
#########################
if(WIN32)
  message(STATUS "WIN32")
  set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/install"
    CACHE PATH "Install Path")
else()
  message(STATUS "UNIX")
  set(CMAKE_INSTALL_PREFIX "/usr/local/"
    CACHE PATH "Install Path")
endif()

##########################
# add modules
#########################

add_subdirectory(Camera)

add_subdirectory(GUI)


#####################################################################
set_property(TARGET camera PROPERTY LIBRARY_OUTPUT_DIRECTORY "${LIB_DIR}")
set_property(TARGET FeederLocator    PROPERTY RUNTIME_OUTPUT_DIRECTORY "${BIN_DIR}")
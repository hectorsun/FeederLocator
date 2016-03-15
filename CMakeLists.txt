cmake_minimum_required(VERSION 2.8.8)

project(FeederLocator)



##########################
#install setting
#########################
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/install")


##########################
# add modules
#########################
add_subdirectory(Camera)

add_subdirectory(GUI)
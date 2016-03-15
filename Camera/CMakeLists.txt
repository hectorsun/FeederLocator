message("camera mode")

project(camera)

add_library(camera SHARED CCamera.cpp)

install(TARGETS camera DESTINATION "${CMAKE_INSTALL_PREFIX}")
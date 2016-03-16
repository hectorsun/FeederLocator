message("camera mode")

project(camera)

add_definitions(-DCAMAPI_EXPORTS)

add_library(camera SHARED CCamera.cpp)

install(TARGETS camera DESTINATION "${CMAKE_INSTALL_PREFIX}")
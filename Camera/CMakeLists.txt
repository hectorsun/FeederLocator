message("camera mode")

project(camera)

set(CameraSimulate CACHE BOOL "Read image from disk")

add_definitions(-DCAMAPI_EXPORTS)

if(CameraSimulate)
	message("CameraSimulate")
	set(PicPath "${CMAKE_CURRENT_SOURCE_DIR}/figure/1.bmp")
	#message("PicPath: ${PicPath}")
	find_package(OpenCV REQUIRED)
	add_definitions(-DPicPath)
	include_directories(${OpenCV_INCLUDE_DIRS})
	#message("Opencv_inc : ${OpenCV_INCLUDE_DIRS}")
	add_library(camera SHARED CCameraSimu.cpp)
	target_link_libraries(camera ${OpenCV_LIBS})
	
	install(PROGRAMS "${CMAKE_CURRENT_SOURCE_DIR}/figure/1.bmp" DESTINATION "${CMAKE_INSTALL_PREFIX}")
	install(PROGRAMS "${CMAKE_CURRENT_SOURCE_DIR}/figure/1.bmp" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

else(not CameraSimulate)
	add_library(camera SHARED CCamera.cpp)
endif()


install(TARGETS camera DESTINATION "${CMAKE_INSTALL_PREFIX}")

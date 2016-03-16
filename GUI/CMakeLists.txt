find_package(Qt5Widgets)


set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(CAMERA_PATH "${CMAKE_SOURCE_DIR}/Camera" )
include_directories("${CAMERA_PATH}")

qt5_add_resources(RESOURCE_ADDED "${CMAKE_CURRENT_SOURCE_DIR}/GUI.qrc")

add_executable(FeederLocator CMainWindow.cpp CPaintWidget.cpp main.cpp ${RESOURCE_ADDED})

target_link_libraries(FeederLocator Qt5::Widgets camera)

if(WIN32)
  install(TARGETS FeederLocator DESTINATION "${CMAKE_INSTALL_PREFIX}")
else()
  install(TARGETS FeederLocator DESTINATION "bin")
endif()

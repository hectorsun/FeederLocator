find_package(Qt5Widgets)


set(CMAke_AUTOMOC ON)

set(CAMERA_PATH "${CMAKE_SOURCE_DIR}/Camera" )
include_directories("${CAMERA_PATH}")

add_executable(FeederLocator main.cpp)

target_link_libraries(FeederLocator Qt5::Widgets camera)


install(TARGETS FeederLocator DESTINATION "${CMAKE_INSTALL_PREFIX}")
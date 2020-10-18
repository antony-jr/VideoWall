CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
set(videowall_SOURCES
    main.cpp
)

set(MIN_QT_VERSION "5.6.0")

find_package(Qt5Core ${MIN_QT_VERSION})
find_package(Qt5Network ${MIN_QT_VERSION})

add_executable(VideoWall ${videowall_SOURCES})
target_link_libraries(VideoWall PUBLIC Qt5::Core Qt5::Network)
install(TARGETS VideoWall ${INSTALL_TARGETS_DEFAULT_ARGS})

CMAKE_MINIMUM_REQUIRED(VERSION 3.18)
set(videowall_SOURCES
    main.cpp
)

set(MIN_QT_VERSION "6.0.0")

find_package(Qt6Core ${MIN_QT_VERSION})
find_package(Qt6Network ${MIN_QT_VERSION})

add_executable(VideoWall ${videowall_SOURCES})
target_link_libraries(VideoWall PUBLIC Qt6::Core Qt6::Network)
install(TARGETS VideoWall ${INSTALL_TARGETS_DEFAULT_ARGS})

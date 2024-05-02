set(videowallplugin_SOURCES
    videowallplugin.cpp
    videowallengine.cpp
)

add_library(plasma_videowall_plugin ${videowallplugin_SOURCES})

target_link_libraries(plasma_videowall_plugin
    Qt5::Concurrent
    Qt5::Core
    Qt5::Gui
    Qt5::Qml
    Qt5::Quick

    KF5::ConfigCore
    KF5::Package
)

install(TARGETS plasma_videowall_plugin DESTINATION ${KDE_INSTALL_QMLDIR}/com/github/antonyjr/plasma/wallpapers/VideoWall)
install(FILES qmldir DESTINATION ${KDE_INSTALL_QMLDIR}/com/github/antonyjr/plasma/wallpapers/VideoWall)

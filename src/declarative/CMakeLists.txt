set(videowallplugin_SOURCES
    videowallplugin.cpp
    videowallengine.cpp
)

add_library(plasma_videowall_plugin SHARED ${videowallplugin_SOURCES})

target_link_libraries(plasma_videowall_plugin PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Plasma
)

install(TARGETS plasma_videowall_plugin DESTINATION ${KDE_INSTALL_QMLDIR}/com/github/antonyjr/plasma/wallpapers/VideoWall)
install(FILES qmldir DESTINATION ${KDE_INSTALL_QMLDIR}/com/github/antonyjr/plasma/wallpapers/VideoWall)

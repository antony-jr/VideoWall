#include <QQmlEngine>

#include "videowallplugin.h"
#include "videowallengine.h"


void VideoWallPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<VideoWallEngine>(uri, 1, 0, "VideoWallEngine");
}

void VideoWallPlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    Q_UNUSED(uri)
    ///engine->addImageProvider(QLatin1String("dynamic"), new DynamicWallpaperImageProvider);
}

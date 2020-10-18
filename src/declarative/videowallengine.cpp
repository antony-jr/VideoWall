#include "videowallengine.h"

VideoWallEngine::VideoWallEngine(QObject *parent)
    : QObject(parent)
{
}

VideoWallEngine::~VideoWallEngine()
{
}

void VideoWallEngine::setDefaultWallpaperUrl(const QUrl &url) {
	m_defaultWallpaperUrl = url;
	auto localFile = m_defaultWallpaperUrl.toLocalFile();
	auto split = localFile.split(".");
	if(split.isEmpty()) {
		emit defaultWallpaperChanged(false);
		return;
	}
	auto extension = split.takeLast();
	if(extension == "png" ||
           extension == "jpg" ||
	   extension == "jpeg") {
		emit defaultWallpaperChanged(/*is video wallpaper=*/false);
		return;
	}
	emit defaultWallpaperChanged(true); 
}

QUrl VideoWallEngine::defaultWallpaperUrl() const {
	return m_defaultWallpaperUrl;
}



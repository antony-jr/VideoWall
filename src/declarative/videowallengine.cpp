#include "videowallengine.h"

VideoWallEngine::VideoWallEngine(QObject *parent)
    : QObject(parent)
{
	n_fillMode = 0;
	n_volume = n_rate = 1.0;
	b_VideoWallpaper = false;
	
	///// We need to remove any sockets if the previous program crashed.
	m_localServer.removeServer(QString::fromUtf8("com.github.antony-jr.VideoWall"));
	
	if(!m_localServer.listen(QString::fromUtf8("com.github.antony-jr.VideoWall"))) {
		return;
	}
	connect(&m_localServer, &QLocalServer::newConnection,
		 this, &VideoWallEngine::handleNewConnection);
}

VideoWallEngine::~VideoWallEngine()
{
	m_localServer.removeServer(QString::fromUtf8("com.github.antony-jr.VideoWall"));
}

void VideoWallEngine::setDefaultWallpaperUrl(const QUrl &url) {
	m_defaultWallpaperUrl = url;
	auto localFile = m_defaultWallpaperUrl.toLocalFile();
	auto split = localFile.split(".");
	if(split.isEmpty()) {
		b_VideoWallpaper = false;
		emit update(false);
		return;
	}
	auto extension = split.takeLast();
	if(extension == "png" ||
           extension == "jpg" ||
	   extension == "jpeg") {
		b_VideoWallpaper = false;
		emit update(/*is video wallpaper=*/false);
		return;
	}
	b_VideoWallpaper = true;
	emit update(true); 
}

QUrl VideoWallEngine::defaultWallpaperUrl() const {
	return m_defaultWallpaperUrl;
}

void VideoWallEngine::setFillMode(int mode) {
	n_fillMode = mode;
	emit update(b_VideoWallpaper);
}

int VideoWallEngine::fillMode() const {
	return n_fillMode;
}

void VideoWallEngine::setPlaybackRate(double rate) {
	n_rate = rate;
	emit update(b_VideoWallpaper);
}

double VideoWallEngine::playbackRate() const {
	return n_rate;
}
    
void VideoWallEngine::setVolume(double vol) {
	n_volume = vol;
	emit update(b_VideoWallpaper);
}

double VideoWallEngine::volume() const {
	return n_volume;
}


//// Public Invokes 
void VideoWallEngine::requestUpdate() {
	emit update(b_VideoWallpaper);
}


//// Private Slots.
void VideoWallEngine::handleNewConnection() {
	auto socket = m_localServer.nextPendingConnection();
	if(!socket || !socket->isValid()) {
		return;
	}
	connect(socket, &QLocalSocket::readyRead, 
		 this, &VideoWallEngine::handleReadyRead,
		 Qt::QueuedConnection);
}

void VideoWallEngine::handleReadyRead() {
	auto socket = qobject_cast<QLocalSocket*>(QObject::sender());
	if(!socket) {
		return;
	}

	auto dataSent = QString::fromUtf8(socket->readAll());
	socket->disconnectFromServer();
	
	//// Parse Commands
	//// The first 10 characters are reserved for command.
	//// The next data after 10 characters can be used anyway.
	QString command = dataSent.left(10);
	if(command.contains("play")) {
		QString localFile = dataSent.right(dataSent.size() - 10);
		emit play(QUrl::fromLocalFile(localFile));
	}else if(command.contains("stopall")) {
		emit stop();
	}	
	socket->deleteLater();
}

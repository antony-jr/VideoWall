#include "videowallengine.h"

#include <QFile>

VideoWallEngine::VideoWallEngine(QObject *parent)
    : QObject(parent)
{
	///// We need to remove any sockets if the previous program crashed.
	m_localServer.removeServer(QString::fromUtf8("com.github.antony-jr.VideoWall"));

	if(!m_localServer.listen(QString::fromUtf8("com.github.antony-jr.VideoWall"))) {
		qDebug() << "ERROR:: Cannot start local server";
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
	
	//// Parse Commands
	//// The first 10 characters are reserved for command.
	//// The next data after 10 characters can be used anyway.
	QString command = dataSent.left(10);
	if(command.contains("play")) {
		QString localFile = dataSent.right(dataSent.size() - 10);
		qDebug() << "Playing:: " << localFile;
		emit play(QUrl::fromLocalFile(localFile));
	}else if(command.contains("stopall")) {
		qDebug() << "Not Implemented";
	}
	socket->deleteLater();
}

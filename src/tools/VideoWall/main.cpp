#include <QCoreApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QDebug>
#include <QFileInfo>
#include <QLocalSocket>
#include <QString>
#include <QTimer>
#include <QFileInfo>

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("VideoWall");
    QCoreApplication::setApplicationVersion("1.0");

    QString videoFile = QString::fromUtf8(argv[1]);
    QFileInfo info(videoFile);
    QString absPath = info.absoluteFilePath();

    QString serverName = QString::fromUtf8("com.github.antony-jr.VideoWall");
    QLocalSocket socket;

    QObject::connect(&socket, &QLocalSocket::connected,
    [&]() {
    	QByteArray msg;
	msg.fill(' ', 10); // First 10 chars are reserved for command.
	msg[0] = 'p';
	msg[1] = 'l';
	msg[2] = 'a';
	msg[3] = 'y';
	msg.append(absPath.toUtf8());
    	socket.write(msg);
    });

    QObject::connect(&socket, &QLocalSocket::errorOccurred,
    [&](QLocalSocket::LocalSocketError socketError) {
    	if(socketError != QLocalSocket::PeerClosedError) {		
    		qDebug() << "ERROR:: " << socketError;
	}
	QTimer::singleShot(200, &app, &QCoreApplication::quit);
    });
    socket.connectToServer(serverName); 
    return app.exec();
}

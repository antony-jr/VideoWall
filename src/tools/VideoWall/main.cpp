#include <QCoreApplication>
#include <QFileInfo>
#include <QLocalSocket>
#include <QString>
#include <QTimer>
#include <iostream>

static void print_header() {
    std::cout << "VideoWall v1.0, Play a Video as Wallpaper.\n"
	      << "Copyright (C) " 
	      << __DATE__ + 7 
	      << ", Antony Jr.\n";
}


static void print_usage(const std::string &prog) {
    std::cout 
    << "Usage: " << prog << " [OPTIONS] [VIDEO FILE(S)]\n\n"
    << "OPTIONS:\n"
    << "    -k,--kill                  Kill current playing media.\n"
    << "    -v,--version               Show version.\n"
    << "    -h,--help                  Show this help.\n\n";
}

int main(int ac, char **av)
{
    if(ac == 1) {
	    print_header();
	    print_usage(std::string(*av));
	    return 0;
    }
    QCoreApplication app(ac, av);
    QCoreApplication::setApplicationName("VideoWall");
    QCoreApplication::setApplicationVersion("1.0");

    int r = 0;
    std::string progName(*av);
    bool bMute = false,
	 bVideoGiven = false;
    QStringList mVideoPaths;
    
    QLocalSocket mSocket;
    QObject::connect(&mSocket, &QLocalSocket::errorOccurred,
    [&app, &mVideoPaths](QLocalSocket::LocalSocketError socketError) {
    	if(socketError != QLocalSocket::PeerClosedError) {
    		qDebug() << "ERROR:: " << socketError;
	}
	/*
	else {
		if(!mVideoPaths.isEmpty()){
			//// TODO: Implement this somehow.	
			return;
		}
	}
	*/
	QTimer::singleShot(200, &app, &QCoreApplication::quit);
    });
    

    //// The socket where the server listens to.
    const QString mServerName = QString::fromUtf8("com.github.antony-jr.VideoWall");

    auto fKillMediaPlay = [&mSocket]() {
    	QByteArray msg;
	msg.fill(' ', 10); // First 10 chars are reserved for command.
	msg[0] = 's';
	msg[1] = 't';
	msg[2] = 'o';
	msg[3] = 'p';
	msg[4] = 'a';
	msg[5] = 'l';
	msg[6] = 'l';
    	mSocket.write(msg);
    };
    
    auto fMediaPlay = [&mSocket, &mVideoPaths]() {
    	auto first = mVideoPaths.takeFirst();
	QFileInfo info(first);
	auto fileAbsPath = info.absoluteFilePath();

	QByteArray msg;
	msg.fill(' ', 10); // First 10 chars are reserved for command.
	msg[0] = 'p';
	msg[1] = 'l';
	msg[2] = 'a';
	msg[3] = 'y';
	msg.append(fileAbsPath.toUtf8());
    	mSocket.write(msg);
    };

    ++av; // Go past program name.
    while(*av){
	if(!qstrcmp(*av, "-m") ||
	   !qstrcmp(*av, "--mute")){
		bMute = true;	
	}else if(!qstrcmp(*av, "-k") ||
		 !qstrcmp(*av, "--kill")){
		QObject::connect(&mSocket, &QLocalSocket::connected, fKillMediaPlay);
		mSocket.connectToServer(mServerName);
		return app.exec();
	}else if(!qstrcmp(*av, "-v") ||
		 !qstrcmp(*av, "--version")){
		print_header();	
		return r;
	}else if(!qstrcmp(*av, "-h") ||
		 !qstrcmp(*av, "--help")){
		print_header();
		print_usage(progName);
		return r;
	}else{
		// Append this to our list of
		// Video file paths.
		mVideoPaths << QString::fromUtf8(*av);
		bVideoGiven = true;
	}
	++av;	
    }

    if(!bVideoGiven) {
	    print_header();
	    print_usage(progName);
	    return r;
    }

    QObject::connect(&mSocket, &QLocalSocket::connected, fMediaPlay); 
    mSocket.connectToServer(mServerName); 
    return app.exec();
}

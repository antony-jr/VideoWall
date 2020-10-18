#ifndef VIDEO_WALL_ENGINE_H_INCLUDED
#define VIDEO_WALL_ENGINE_H_INCLUDED 
#include <QObject>
#include <QUrl>
#include <QLocalSocket>
#include <QLocalServer>
#include <QStandardPaths>

class VideoWallEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl defaultWallpaperUrl READ defaultWallpaperUrl WRITE setDefaultWallpaperUrl NOTIFY defaultWallpaperChanged)
    Q_PROPERTY(NOTIFY play
	       NOTIFY stop
	       NOTIFY defaultWallpaperChanged)
public:
    explicit VideoWallEngine(QObject *parent = nullptr);
    ~VideoWallEngine() override;

    //// This will act as some sort of init.
    void setDefaultWallpaperUrl(const QUrl&);
    QUrl defaultWallpaperUrl() const;

private slots:
    void handleNewConnection();
    void handleReadyRead();

signals:
    void play(QUrl videoFile);
    void stop();
    void defaultWallpaperChanged(/*is video wallpaper=*/bool isVideoWallPaper);
private:
    QUrl m_defaultWallpaperUrl;
    QLocalServer m_localServer;
};
#endif /// VIDEO_WALL_ENGINE_H_INCLUDED

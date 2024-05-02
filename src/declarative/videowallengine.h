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
    Q_PROPERTY(QUrl defaultWallpaperUrl READ defaultWallpaperUrl WRITE setDefaultWallpaperUrl NOTIFY update)
    Q_PROPERTY(int fillMode READ fillMode WRITE setFillMode NOTIFY update)
    Q_PROPERTY(double playbackRate READ playbackRate WRITE setPlaybackRate NOTIFY update)
    Q_PROPERTY(double volume READ volume WRITE setVolume NOTIFY update)

    Q_PROPERTY(NOTIFY play
	       NOTIFY stop)
public:
    explicit VideoWallEngine(QObject *parent = nullptr);
    ~VideoWallEngine() override;
    	
    void setDefaultWallpaperUrl(const QUrl&);
    QUrl defaultWallpaperUrl() const;

    void setFillMode(int);
    int fillMode() const;

    void setPlaybackRate(double);
    double playbackRate() const;

    void setVolume(double);
    double volume() const;

    Q_INVOKABLE void requestUpdate(); 

private slots:
    void handleNewConnection();
    void handleReadyRead();

signals:
    void play(QUrl videoFile);
    void stop();
    void update(bool isVideoWallPaper);
private:
    int n_fillMode;
    double n_rate, n_volume;
    bool b_VideoWallpaper;
    QUrl m_defaultWallpaperUrl;
    QLocalServer m_localServer;
};
#endif /// VIDEO_WALL_ENGINE_H_INCLUDED

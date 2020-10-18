#pragma once
#include <QObject>
#include <QUrl>


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

signals:
    void play(QUrl videoFile);
    void stop();
    void defaultWallpaperChanged(/*is video wallpaper=*/bool isVideoWallPaper);
private:
    QUrl m_defaultWallpaperUrl;
};

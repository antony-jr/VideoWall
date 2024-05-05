import QtMultimedia
import QtQuick
import com.github.antonyjr.plasma.wallpapers.VideoWall
import org.kde.plasma.plasmoid

WallpaperItem {
    id: root

    function resetAll() {
        mediaplayer.loops = 0;
        default_image_output.visible = false;
        mediaplayer.visible = false;
        mediaplayer.volume = 1;
        mediaplayer.muted = false;
        mediaplayer.playbackRate = 1;
    }

    Video {
        id: mediaplayer

        visible: false
        autoPlay: false
        loops: 0
        fillMode: {
            if (wallpaper.configuration.Fill == 0)
                return VideoOutput.Stretch;
            else if (wallpaper.configuration.Fill == 1)
                return VideoOutput.PreserveAspectFit;
            else if (wallpaper.configuration.Fill == 2)
                return VideoOutput.PreserveAspectCrop;
            return VideoOutput.PreserveAspectCrop;
        }
        anchors.fill: parent
        muted: false
        volume: 1
    }

    Timer {
        id: playtimer

        interval: 500
        running: false
        repeat: true
        onTriggered: function() {
            if (mediaplayer.source != wallpaper.configuration.VideoOrImage) {
                if (mediaplayer.playbackState == MediaPlayer.PlayingState) {
                    const diff = mediaplayer.duration - mediaplayer.position;
                    if (diff < 700 || diff == 0) {
                        playtimer.stop();
                        mediaplayer.stop();
                        videowall_engine.requestUpdate();
                    }
                }
            }
        }
    }

    Image {
        id: default_image_output

        visible: false
        anchors.fill: parent
        fillMode: {
            if (wallpaper.configuration.Fill == 0)
                return VideoOutput.Stretch;
            else if (wallpaper.configuration.Fill == 1)
                return VideoOutput.PreserveAspectFit;
            else if (wallpaper.configuration.Fill == 2)
                return VideoOutput.PreserveAspectCrop;
            return VideoOutput.PreserveAspectCrop;
        }
    }

    VideoWallEngine {
        id: videowall_engine

        defaultWallpaperUrl: wallpaper.configuration.VideoOrImage
        fillMode: wallpaper.configuration.Fill
        playbackRate: wallpaper.configuration.Rate
        volume: wallpaper.configuration.Volume
        onUpdate: function(isVideoWallPaper) {
            resetAll();
            if (isVideoWallPaper) {
                mediaplayer.visible = true;
                mediaplayer.loops = MediaPlayer.Infinite;
                mediaplayer.source = wallpaper.configuration.VideoOrImage;
                mediaplayer.volume = wallpaper.configuration.Volume;
                mediaplayer.muted = wallpaper.configuration.Volume == 0;
                mediaplayer.playbackRate = wallpaper.configuration.Rate;
                mediaplayer.source = wallpaper.configuration.VideoOrImage;
                mediaplayer.play();
                mediaplayer.visible = true;
            } else {
                default_image_output.source = wallpaper.configuration.VideoOrImage;
                default_image_output.visible = true;
            }
        }
        onPlay: function(videoFile) {
            resetAll();
            mediaplayer.source = videoFile;
            mediaplayer.play();
            mediaplayer.visible = true;
            playtimer.start();
        }
        onStop: function() {
            playtimer.stop();
            mediaplayer.stop();
            videowall_engine.requestUpdate();
        }
    }

}

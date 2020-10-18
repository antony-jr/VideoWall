import QtQuick 2.5
import QtMultimedia 5.6
import org.kde.plasma.core 2.0 as Plasmacore

import com.github.antonyjr.plasma.wallpapers.VideoWall 1.0

Item {
	MediaPlayer {
		id: mediaplayer
		autoPlay: false
		volume: 1 
		muted: false
		onStopped: {
		
		}
	}

	VideoOutput {
		id: default_video_output
		visible: false
		anchors.fill: parent
		fillMode: {
			if(wallpaper.configuration.Fill == 0) {
				return VideoOutput.Stretch
			} else if(wallpaper.configuration.Fill == 1) {
				return VideoOutput.PreserveAspectFit
			} else if(wallpaper.configuration.Fill == 2) {
				return VideoOutput.PreserveAspectCrop
			}
			return VideoOutput.PreserveAspectCrop
		}
		source: mediaplayer
	}

	Image {
               id: default_image_output
	       visible: false
	       anchors.fill: parent
	       fillMode: {
		if(wallpaper.configuration.Fill == 0) {
			return VideoOutput.Stretch
		} else if(wallpaper.configuration.Fill == 1) {
			return VideoOutput.PreserveAspectFit
		} else if(wallpaper.configuration.Fill == 2) {
			return VideoOutput.PreserveAspectCrop
		}
			return VideoOutput.PreserveAspectCrop
	       }
	} 

	VideoWallEngine {
		id: videowall_engine
		defaultWallpaperUrl: wallpaper.configuration.VideoOrImage
		onDefaultWallpaperChanged: {
			if(isVideoWallPaper) {
				default_image_output.visible = true; 	
				mediaplayer.loops = MediaPlayer.Infinite;
				mediaplayer.source = wallpaper.configuration.VideoOrImage;
				default_video_output.visible = true;	

				mediaplayer.volume = wallpaper.configuration.Volume;
				mediaplayer.muted = wallpaper.configuration.Volume == 0;
				mediaplayer.playbackRate = wallpaper.configuration.Rate;

				mediaplayer.play();
			} else {
				default_video_output.visible = false;				
				mediaplayer.stop();
				mediaplayer.source = "";
				default_image_output.source = wallpaper.configuration.VideoOrImage;
				default_image_output.visible = true; 
			}
		}
		
		onPlay: {
			mediaplayer.loops = 0;
			mediaplayer.source = "";
			default_image_output.visible = false; 	
			default_video_output.visible = false;	
			
			mediaplayer.volume = 1;
			mediaplayer.muted = false;
			mediaplayer.playbackRate = 1;

			mediaplayer.source = videoFile;
			mediaplayer.play();
			default_video_output.visible = true;
		}	
	}
}

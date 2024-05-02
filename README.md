# Videowall [![GitHub issues](https://img.shields.io/github/issues/antony-jr/VideoWall.svg?style=for-the-badge)](https://github.com/antony-jr/VideoWall/issues) [![GitHub forks](https://img.shields.io/github/forks/antony-jr/VideoWall.svg?style=for-the-badge)](https://github.com/antony-jr/VideoWall/network) [![GitHub stars](https://img.shields.io/github/stars/antony-jr/VideoWall.svg?style=for-the-badge)](https://github.com/antony-jr/VideoWall/stargazers) [![GitHub license](https://img.shields.io/github/license/antony-jr/VideoWall.svg?style=social)](https://github.com/antony-jr/VideoWall/blob/master/LICENSE)

Videowall is a KDE Plasma 6 Wallpaper which can make you play videos on the wallpaper.
In addition to this it can also play whatever Video file you wanna play using a simple
CLI tool. 

**Depends on:** **Linux** , **KDE Plasma 6**.

# Installation

```
 $ git clone https://github.com/antony-jr/VideoWall
 $ cd VideoWall
 $ cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr .
 $ make -j$(nproc)
 $ sudo make install
 $ VideoWall # Installed.
```

# Usage

You need to first select the VideoWall from the Wallpaper Configuation in KDE Plasma, then set a 
default Video Loop or Image. This default Image/Video will be displayed when a Video is not played.

And to play any Video with Audio on the fly.

**Usage is simple, you give a directory of videos or a single video file**

```
 $ VideoWall SomeVideo.mp4
```

# Support

If you think this project is cool then just give me a :star: and a :fork_and_knife: if you want to improve it. Thank You! 


# License

The MIT License. 

Copyright (c) 2017 [@antony-jr](https://github.com/antony-jr).

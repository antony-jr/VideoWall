# Videowall [![GitHub issues](https://img.shields.io/github/issues/antony-jr/VideoWall.svg?style=for-the-badge)](https://github.com/antony-jr/VideoWall/issues) [![GitHub forks](https://img.shields.io/github/forks/antony-jr/VideoWall.svg?style=for-the-badge)](https://github.com/antony-jr/VideoWall/network) [![GitHub stars](https://img.shields.io/github/stars/antony-jr/VideoWall.svg?style=for-the-badge)](https://github.com/antony-jr/VideoWall/stargazers) [![GitHub license](https://img.shields.io/github/license/antony-jr/VideoWall.svg?style=social)](https://github.com/antony-jr/VideoWall/blob/master/LICENSE)

**IMPORTANT: VideoWall for Plasma 6 is available at [plasma6-wallpaper](https://github.com/antony-jr/VideoWall/tree/plasma6-wallpaper) branch** (Use this if you are on Plasma 6)

Videowall a KDE Plasma 5 Wallpaper which can make you play videos on the wallpaper.

**Depends on:** **Linux** , **KDE Plasma 5**.

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

You will need to select VideoWall from the Desktop Wallpaper Configuration in your KDE Plasma.

**Usage is simple, you give a directory of videos or a single video file**

```
 $ VideoWall SomeVideo.mp4
```

# Support

If you think this project is cool then just give me a :star: and a :fork_and_knife: if you want to improve it. Thank You! 


# License

The MIT License. 

Copyright (c) 2017 [@antony-jr](https://github.com/antony-jr).

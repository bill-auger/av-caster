### AvCaster - *A simple GUI for live screencasting*

| build | status |
| ----  | ------ |
| linux | [![Build Status](https://travis-ci.org/bill-auger/av-caster.svg?branch=master)](https://travis-ci.org/bill-auger/av-caster) |
| dev   | [![Build Status](https://travis-ci.org/bill-auger/av-caster.svg)](https://travis-ci.org/bill-auger/av-caster) |

AvCaster is a native linux appliction built with the [JUCE](http://juce.com/) framework and using [gStreamer](http://gstreamer.freedesktop.org/) as the media backend.  It is currently capable of recording to file and streaming to an RTMP server with screen capture, webcam, and stereo audio.  This initial implementation is specialized for full-screen screencast with webcam overlay and is hard-coded to stream only to [livecoding.tv](https://www.livecoding.tv/) but other servers may be added in the future  If one is handy with bits it could be easily customized for webcam-only, screencap-only, audio-only, or for any RTMP server as it is now.  All of these and more indeed may be upcoming standard features.


#### Motivation
The motivation behind this project is that streaming with a feature-rich, bleeding-edge client such as OBS and FMLE is very CPU intensive even on reasonably modern machines.  In situations such as live code streaming where the broadcast is essentially a background task there is far more utility in reserving those extra cycles for development tasks.

A command-line solution is the obvious choice for such scenarios but obviously lacks a real-time preview.  This project was initially a simple GUI ffmpeg command-line launcher; but in the process of implementing the real-time preview feature, it has since become a gStreamer native library implementation.


#### Get AvCaster
###### AvCaster for Penguins
```
  # subscribe to the repository
  $ curl -s https://packagecloud.io/install/repositories/ninjam/av-caster/script.deb.sh | sudo bash

  # install the package
  $ sudo apt-get install av-caster
```


#### Community Support
Feel free to to post any questions or comments to the [AvCaster issue tracker](https://github.com/bill-auger/av-caster/issues) and you can visit the home page of the [AvCaster wiki](https://github.com/bill-auger/av-caster/wiki) for updates  Also, this project is open-source and pull requests are quite welcomed.


#### building from source
##### AvCaster build dependencies  
debian/ubuntu:
```
  sudo apt-get install libfreetype6-dev libx11-dev libxinerama-dev
                       libxcursor-dev mesa-common-dev libasound2-dev
                       freeglut3-dev libxcomposite-dev libxrender-dev
                       libjack-jackd2-dev libgstreamer-plugins-base1.0-dev
```


#### Similar Projects
There were several similar projects considered for expansion before this project was launched fresh.  They all can capture and mux in audio but they capture screen only (no webcam/text/logo) and only two of them feature a real-time preview.  They are ordered roughly by feature-set from most to least capable in terms of the AvCaster project's feature requirements.
  * [SimpleScreenRecorder](https://github.com/MaartenBaert/ssr) - features a real-time preview
  * [gtk-recordmydesktop](http://recordmydesktop.sourceforge.net/) - features a real-time preview
  * [vokoscreen](http://www.kohaupt-online.de/hp/) - very nice looking and intutive GUI
  * [kazam](https://launchpad.net/kazam) - similar features as vokoscreen
  * [ffmpeg-gui](http://sourceforge.net/projects/ffmpegfrontend/) - cross-platform QT basic ffmpeg launcher
  * [ffmpeggui](http://sourceforge.net/projects/ffmpeg-gui/) - Win32 basic ffmpeg launcher


Also, the original ffmpeg bash script with all of the features that this project has since re-implemented is in [this gist](https://gist.github.com/bill-auger/9480205a38d9d00d2fa3) if anyone is interested in a command-line broadcasting tool.

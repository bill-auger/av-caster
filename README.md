### AvCaster - *a simple GUI for live screencasting*

AvCaster is currently a native linux appliction built with the [JUCE](http://juce.com/) framework and using [gStreamer](http://gstreamer.freedesktop.org/) as the media backend - it is currently capable of recording to file and streaming to an RTMP server with screen capture, webcam, and stereo audio - this initial implementation is specialized for full-screen screencast with webcam overlay and is hard-coded to stream only to [livecoding.tv](https://www.livecoding.tv/) but other servers may be added in the future - if one is handy with bits it could be easily customized for webcam-only, screencap-only, audio-only, or for any RTMP server as it is now - all of these and more indeed may be upcoming standard features - a debian package should be coming soon and perhaps binaries for other OS's


#### motivation
the motivation behind this project is that streaming with a feature-rich, bleeding-edge client such as OBS and FMLE is very CPU intensive even on reasonably modern machines - in situations such as live code streaming where the broadcast is essentially a background task there is far more utility in reserving those extra cycles for development tasks

a command-line solution is the obvious choice for such scenarios but o/c lacks a real-time preview - this project was initially a simple GUI ffmpeg command-line launcher but has since become a gStreamer native library implementation


#### community support
feel free to to post any questions or comments to the [AvCaster issue tracker](https://github.com/bill-auger/av-caster/issues) and you can visit the home page of the [AvCaster wiki](https://github.com/bill-auger/av-caster/wiki) for updates - also this project is open-source and pull requests are quite welcomed


#### similar projects
there were several similar projects considered for expansion before this project was launched fresh - they all can capture and mux in audio but they capture screen only (no webcam/text/logo) and only two of them feature a real-time preview - they are ordered roughly by feature-set from most to least capable in terms of the AvCaster project's feature requirements
  * [SimpleScreenRecorder](https://github.com/MaartenBaert/ssr) - features a real-time preview
  * [gtk-recordmydesktop](http://recordmydesktop.sourceforge.net/) - features a real-time preview
  * [vokoscreen](http://www.kohaupt-online.de/hp/) - very nice looking and intutive GUI
  * [kazam](https://launchpad.net/kazam) - similar features as vokoscreen
  * [ffmpeg-gui](http://sourceforge.net/projects/ffmpegfrontend/) - cross-platform QT basic ffmpeg launcher
  * [ffmpeggui](http://sourceforge.net/projects/ffmpeg-gui/) - Win32 basic ffmpeg launcher


also the original ffmpeg bash script with all of the features that this project has since re-implemented is in [this gist](https://gist.github.com/bill-auger/9480205a38d9d00d2fa3) if anyone is interested in a command-line broadcasting tool

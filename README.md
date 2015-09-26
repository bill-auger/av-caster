### AvCaster - *a simple GUI for live screencasting*

the motivation behind this project is that streaming with a feature-rich, bleeding-edge client such as OBS and FMLE is very CPU intensive even on reasonably modern machines - in situations such as live code streaming where the screencast is not the primary application there is far more utility in reserving those extra cycles for more useful tasks

a command-line solution is the obvious choice for such applications but o/c lacks a real-time preview - this project was initially a simple native JUCE GUI ffmpeg command-line launcher but it seems to be moving toward a native library implementation using libav and/or gstreamer

the reference bash script that this GUI app will wrap (or re-implemet) is in [this gist](https://gist.github.com/bill-auger/9480205a38d9d00d2fa3)

some similar projects - they all can capture and mux in audio but they capture screen only (no webcam/text/logo) and only two of them feature a real-time preview:
  * [SimpleScreenRecorder](https://github.com/MaartenBaert/ssr) - features a real-time preview
  * [gtk-recordmydesktop](http://recordmydesktop.sourceforge.net/) - features a real-time preview
  * [vokoscreen](http://www.kohaupt-online.de/hp/) - very nice looking and intutive GUI
  * [kazam](https://launchpad.net/kazam) - similar features as vokoscreen
  * [ffmpeg-gui](http://sourceforge.net/projects/ffmpegfrontend/) - cross-platform QT basic ffmpeg launcher
  * [ffmpeggui](http://sourceforge.net/projects/ffmpeg-gui/) - Win32 basic ffmpeg launcher

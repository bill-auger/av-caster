## AvCaster - *A simple native gStreamer GUI for screencast, webcam, and audio streaming*

| build       | status                                         |
| ----------- | ---------------------------------------------- |
| Release     | [![release build status][master-img]][travis]  |
| Development | [![development build status][dev-img]][travis] |
[master-img]: https://travis-ci.org/bill-auger/av-caster.svg?branch=master
[dev-img]:    https://travis-ci.org/bill-auger/av-caster.svg
[travis]:     https://travis-ci.org/bill-auger/av-caster
[pkgbuild]:   https://raw.githubusercontent.com/bill-auger/av-caster/master/Builds/Packaging/PKGBUILD
[deb]:        https://packagecloud.io/ninjam/av-caster

AvCaster is a native GNU/linux appliction built with the [JUCE](http://juce.com/) framework and using [gStreamer](http://gstreamer.freedesktop.org/) as the media backend.  It is currently capable of recording to file and streaming to an RTMP server with screen capture, webcam, and stereo audio.  This initial implementation is specialized for full-screen screencast with webcam overlay and is hard-coded to stream only to [livecoding.tv](https://www.livecoding.tv/) but other servers may be added in the future.  If one is handy with bits it could be easily customized for webcam-only, screencap-only, audio-only, or for any RTMP server as it is now.  All of these and more indeed may be upcoming standard features.


### Motivation
The motivation behind this project is that streaming with a feature-rich, bleeding-edge client such as OBS and FMLE is very CPU intensive even on reasonably capable machines.  In situations such as live code streaming where the broadcast is an auxiliary concern, there is more utility in reserving those extra cycles for primary development tasks.

A command-line solution is the obvious choice for such scenarios but obviously lacks real-time control and preview.  This project was created to mark a reasonable balance between headless performance and a graphical feature set.  Initially a simple ffmpeg command-line launcher GUI; it has since become a gStreamer native library implementation.


### Get AvCaster
#### AvCaster for Penguins
\* Debian/Jessie, Ubuntu/Utopic, Ubuntu/Vivid, Ubuntu/Wily:
```
# NOTE: The debian package will not install on Ubuntu/Trusty because it's gStreamer is outdated.

  # subscribe to the repository
  $ curl -s https://packagecloud.io/install/repositories/ninjam/av-caster/script.deb.sh | sudo bash
  $ sudo apt-get update

  # install the package
  $ sudo apt-get install av-caster
```
\* Other debian-based distros can download the [latest .deb package][deb] directly or manually add the AvCaster repo to your apt sources:
```
# Debian users install debian-archive-keyring first (Ubuntu users can skip this step)
$ sudo apt-get install debian-archive-keyring

# Install secure transport and the repo GPG key
$ sudo apt-get install apt-transport-https
$ curl https://packagecloud.io/gpg.key | sudo apt-key add -

# Subscribe to the AvCaster repo and install
$ AVCASTER_APT_SOURCE="deb https://packagecloud.io/ninjam/av-caster/debian/ jessie main"
$ sudo echo $AVCASTER_APT_SOURCE > /etc/apt/sources.list.d/ninjam_av-caster.list
$ sudo apt-get update
$ sudo apt-get install av-caster
```
\* Other GNU/Linux: Refer to "Building from source" below


### Community Support
AvCaster is still very much in beta so testers comments and suggestions are appreciated. Also, this project is open-source and pull requests are quite welcomed.

If AvCaster refuses to launch after changing some parameters in the GUI you can try deleting the persistent configuration file in your AppData dir (e.g. ~/.av-caster/AvCaster.bin).

Feel free to to post any questions or comments to the [AvCaster issue tracker](https://github.com/bill-auger/av-caster/issues) and you can visit the home page of the [AvCaster wiki](https://github.com/bill-auger/av-caster/wiki) for updates.


### Building from source
\* ArchLinux:
a [PKGBUILD file][pkgbuild] is included in Builds/Packaging
#### build dependencies
\* Debian/Ubuntu:
```
# NOTE: AvCaster builds against gStreamer1.0 base libraries
#           and requires gStreamer version 1.4 or greater to run.

  sudo apt-get install libfreetype6-dev libgstreamer-plugins-base1.0-dev libx11-dev \
                       libxcursor-dev libxinerama-dev
```
\* Other GNU/Linux: install the corresponding libraries as above for your system
#### compile
```
  cd Builds/GnuMakefile
  make CONFIG=Release
  ./build/av-caster
```
#### runtime dependencies
\* Debian/Ubuntu:
```
  sudo apt-get install freeglut3 gstreamer1.0-plugins-bad gstreamer1.0-plugins-good    \
                       gstreamer1.0-plugins-ugly libfreetype6 libgl1-mesa-glx libx11-6 \
                       libxcomposite1 libxcursor1 libxext6 libxinerama1 libxrender1
```
\* Other GNU/Linux: install the corresponding libraries as above for your system


### Similar Projects
There were several similar projects considered for expansion before this project was launched fresh.  They all can capture and mux in audio but they capture screen only (no webcam/text/logo) and only two of them feature a real-time preview.  They are ordered roughly by feature-set from most to least capable in terms of the AvCaster project's feature requirements.
  * [SimpleScreenRecorder](https://github.com/MaartenBaert/ssr) - features a real-time preview
  * [gtk-recordmydesktop](http://recordmydesktop.sourceforge.net/) - features a real-time preview
  * [vokoscreen](http://www.kohaupt-online.de/hp/) - very nice looking and intutive GUI
  * [kazam](https://launchpad.net/kazam) - similar features as vokoscreen
  * [ffmpeg-gui](http://sourceforge.net/projects/ffmpegfrontend/) - cross-platform QT basic ffmpeg launcher
  * [ffmpeggui](http://sourceforge.net/projects/ffmpeg-gui/) - Win32 basic ffmpeg launcher


Also, the original ffmpeg bash script with all of the features that this project has since re-implemented is in [this gist](https://gist.github.com/bill-auger/9480205a38d9d00d2fa3) if anyone is interested in a command-line webcasting tool.

<table><tr valign="top">
  <td align="center">
    <h2>AvCaster<br /><a href="https://gitter.im/bill-auger/av-caster">
      <img alt="Gitter" src="https://badges.gitter.im/Join%20Chat.svg" /></a></h2>
    <table>
      <tr><th colspan="2">Build Status</th></tr>
      <tr>
        <td align="left">Release</td>
        <td><a href="https://travis-ci.org/bill-auger/av-caster">
          <img src="https://travis-ci.org/bill-auger/av-caster.svg?branch=master" width="100" height="18"
               alt="release build status" /></a></td></tr>
      <tr>
        <td align="left">Development</td>
        <td><a href="https://travis-ci.org/bill-auger/av-caster">
          <img src="https://travis-ci.org/bill-auger/av-caster.svg" width="100" height="18"
               alt="development build status" /></a></td></tr>
      <tr>
        <td align="left">Lint</td>
        <td><a href="https://scan.coverity.com/projects/bill-auger-av-caster">
          <img src="https://scan.coverity.com/projects/bill-auger-av-caster/badge.svg" width="100" height="18"
               alt="static analysis status" /></a></td></tr></table>
  </td>
  <td><h2>*A simple native gStreamer GUI for screencast, webcam, and audio streaming*</h2></td></tr></table>


AvCaster is a native GNU/linux appliction built with the [JUCE][juce] framework and using [gStreamer][gstreamer] as the media backend.  It is currently capable of recording to file or streaming to an RTMP server with screen capture, webcam, and stereo audio.  This initial implementation is specialized for full-screen screencast with webcam overlay.  It is moderately configurable, with a preset configuration for streaming via [livecoding.tv][lctv], and allows custom user-defined configurations to be stored as additional presets.  If one is handy with bits it could be easily customized for webcam-only, screencap-only, audio-only, or for any streaming server.  Also, it has been designed for portability, anticipating Windows and Mac ports.  These and more are planned to become standard features along with presets for other hosts.


### Motivation
The motivation behind this project is that streaming with a feature-rich, bleeding-edge client such as OBS and FMLE is very CPU intensive even on reasonably capable machines.  In situations such as live code streaming, where the broadcast is an auxiliary concern, there is more utility in reserving those extra cycles for primary development tasks.

A command-line solution is the obvious choice for such scenarios but obviously lacks real-time control and preview.  This project was created to mark a reasonable balance between headless performance and a graphical feature set.  Initially a simple ffmpeg command-line launcher GUI; it has since become a gStreamer native library implementation.


### Get AvCaster
*NOTE: AvCaster requires gStreamer >= v1.6.0 and the non-free 'ugly' plugins which may not be available in your standard main/free repository (see "runtime dependencies" for your distro below)*
#### AvCaster Package Repositories
The [OpenSUSE Build Service][obs] hosts AvCaster x86 and x86-64 binary package repositories for the following distributions:
  * Debian 8 , Ubuntu 15.10
  * Suse Tumbleweed , SUSE 12
  * CentOS 7 , Fedora 23 , RedHat 7 , ScientificLinux 7

Follow the [instructions][obs] there to subscribe your package manager or download the latest package for your distribution directly.  Let us know if you would like packaging for another architecture.
#### Other GNU/Linux:
Refer to "Building from Source" below.


### Community Support
AvCaster is a free and open-source community project and is still very much in its infancy; so testers, comments, and suggestions are appreciated.  Pull requests are quite welcomed and any submissions that advance the project toward is proposed milestones will be accepted.  If there is significant community support for this project, it could be transfered to a github organization, an IRC and/or gitter chat could be established, a website could be created, an so on.  Let us hear your ideas.  If you would like to help to improve AvCaster, we could especially use your help in the following areas:
  * developers/consultants (especially with gStreamer expertise)
  * designers (logo , website , GUI graphics/layout)
  * beta testers (anyone who streams regularly)
  * HOWTO documentation and screencasts

In any case you can "Star" this repo above if you like this project or "Watch" the repo or visit the home page of the [AvCaster Wiki][wiki] for updates.


### Getting Help / Bug Reporting
If AvCaster refuses to launch after changing some parameters in the GUI you can try deleting the persistent configuration file in your AppData dir (e.g. ~/.av-caster/av-caster.bin).

Please report any problems on the [AvCaster Issue Tracker][tracker].

Feel free join the [gitter chat][gitter] to post any questions or comments or, well ... just chat.


### Building from Source
*NOTE: AvCaster requires gStreamer >= v1.6.0*
#### ArchLinux:
```
### build and install via makepkg ###
$ wget https://raw.githubusercontent.com/bill-auger/av-caster/master/Builds/Packaging/PKGBUILD
$ makepkg --install ./PKGCONFIG
```
#### Debian/Ubuntu:
```
### build dependencies ###
$ sudo apt-get install build-essential libfreetype6-dev libgstreamer-plugins-base1.0-dev \
                       libircclient-dev libx11-dev libxcursor-dev libxinerama-dev
### runtime dependencies (Debian 'unstable' , Ubuntu 'wily universe') ###
$ sudo apt-get install freeglut3 gstreamer1.0-plugins-bad gstreamer1.0-plugins-good \
                       gstreamer1.0-plugins-ugly libfreetype6 libgl1-mesa-glx       \
                       libircclient1 libx11-6 libxcomposite1 libxcursor1 libxext6   \
                       libxinerama1 libxrender1
### compile ###
$ cd Builds/Makefile
$ make CONFIG=Release
$ ./build/av-caster
```
#### Suse:
```
### build dependencies ###
$ sudo zypper install gcc-c++ libX11-devel freetype2-devel libXinerama-devel           \
                      libXcursor-devel gstreamer-plugins-base-devel libircclient-devel
### runtime dependencies ###
$ sudo zypper install gstreamer-plugins-good gstreamer-plugins-bad-free \
                      gstreamer-plugins-ugly libircclient1
### compile ###
$ cd Builds/Makefile
$ make CONFIG=Release
$ ./build/av-caster
```
#### Fedora:
```
### build dependencies ###
$ sudo dnf install gcc-c++ libX11-devel freetype-devel libXinerama-devel             \
                   libXcursor-devel gstreamer1-plugins-base-devel libircclient-devel
### runtime dependencies (rpmfusion repositories) ###
$ RPMFUSION_URL=http://download1.rpmfusion.org
$ FEDORA_VERSION=$(rpm -E %fedora)
$ REPO1=$RPMFUSION_URL/free/fedora/rpmfusion-free-release-$FEDORA_VERSION.noarch.rpm
$ REPO2=$RPMFUSION_URL/nonfree/fedora/rpmfusion-nonfree-release-$FEDORA_VERSION.noarch.rpm
$ sudo dnf install $REPO1 $REPO2
$ sudo dnf install gstreamer1-plugins-good gstreamer1-plugins-bad-free \
                   gstreamer1-plugins-ugly libircclient1
### compile ###
$ cd Builds/Makefile
$ make CONFIG=Release
$ ./build/av-caster
```
#### Other GNU/Linux:
Install the corresponding libraries as above for your system.


#### Developers and Designers
You will find in the Builds/Scripts directory some helper scripts to aid in building and debugging this application. Note that we are currently locked at JUCE v3.1.1 until [an issue affecting scaled monitor resolutions](http://www.juce.com/forum/topic/juce-v320-and-v401-apps-window-not-visible-scaled-monitor-resolutions) is resolved. This is not relevant to most development tasks, but if you must use the Introjucer GUI builder for design or project maintenance, please compile it from [this branch](https://github.com/bill-auger/JUCE/tree/v3-1-1).

Note that branches other than 'master' tend to be rebased often so you may need to force pull those.
```
### Build the Introjucer GUI builder and project manager ###
$ git clone --depth 1 https://github.com/bill-auger/JUCE.git
$ git checkout v3-1-1
$ cd JUCE/extras/Introjucer/Builds/Linux/
$ make
$ ./build/Introjucer

### Then select "Open" from the Introjucer "File" menu and browse to the AvCaster.jucer file in this project root directory. ###
```


### Similar Projects
There were several similar projects considered for expansion before this project was launched fresh.  They all can capture and mux in audio but they capture screen only (no webcam/text/logo) and only two of them feature a real-time preview.  They are ordered roughly by feature-set from most to least capable in terms of the AvCaster project's feature requirements.
  * [SimpleScreenRecorder](https://github.com/MaartenBaert/ssr) - feature-rich with real-time preview
  * [gtk-recordmydesktop](http://recordmydesktop.sourceforge.net/) - feature-rich with real-time preview
  * [kazam](https://launchpad.net/kazam) - feature-rich but no preview
  * [vokoscreen](http://www.kohaupt-online.de/hp/) - similar features as kazam with pretty and intutive GUI
  * [ffmpeg-gui](http://sourceforge.net/projects/ffmpegfrontend/) - cross-platform QT basic ffmpeg launcher
  * [ffmpeggui](http://sourceforge.net/projects/ffmpeg-gui/) - Win32 basic ffmpeg launcher

Also, the original ffmpeg bash script with all of the features that this project has since re-implemented is in [this gist](https://gist.github.com/bill-auger/9480205a38d9d00d2fa3) if an ultra-lightweight command-line webcasting tool is more suitable.  It requires some manual configuration o/c, but is approximately twice as nice.


[juce]:       http://juce.com/
[gstreamer]:  http://gstreamer.freedesktop.org/
[lctv]:       https://www.livecoding.tv/
[deb]:        https://packagecloud.io/ninjam/av-caster
[wiki]:       https://github.com/bill-auger/av-caster/wiki
[tracker]:    https://github.com/bill-auger/av-caster/issues
[gitter-img]: https://badges.gitter.im/Join%20Chat.svg
[gitter]:     https://gitter.im/bill-auger/av-caster
[obs]:        http://software.opensuse.org/download/package?project=home:bill-auger&package=av-caster

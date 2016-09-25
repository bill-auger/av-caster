<table>
  <tr valign="top">
    <td width="250" align="center">
      <h2>AvCaster</h2>
      <table>
        <tr>
          <td align="left">Chat:</td>
          <td><a href="https://gitter.im/bill-auger/av-caster">
            <img src="https://badges.gitter.im/Join%20Chat.svg"
                 alt="Gitter" width="100" height="18" /></a></td></tr>
        <tr>
          <td align="left">Issues:</td>
          <td><a href="https://github.com/bill-auger/av-caster/issues">
            <img src="https://img.shields.io/github/issues/bill-auger/av-caster.svg"
                 alt="Issues" width="100" height="18" /></a></td></tr></table></td>
    <td rowspan="2"><h2><i>A light-weight native gStreamer GUI for screencast, webcam, and audio recording and streaming</i></h2>
    AvCaster is built upon the <a href="https://www.juce.com/">JUCE</a> framework, utilizing <a href="https://gstreamer.freedesktop.org/">gStreamer</a> as the media backend and <a href="http://www.ulduzsoft.com/libircclient/">libircclient</a> as the chat backend.  It is currently capable of recording to file or streaming to an RTMP server with screen capture (full-screen), webcam (full-screen or overlay), and audio (mono or stereo).  It is moderately configurable, with preset configurations for streaming via popular servers such as <a href="https://www.livecoding.tv/">livecoding.tv</a>, and allows custom user-defined configurations to be stored as additional presets.  This initial target is GNU/Linux, but it has been designed for portability and includes starter projects for AndroidStudio, CodeBlocks, VisualStudio, and xCode IDEs.  Let us know if it would interest you to see AvCaster ported to another platform (e.g. Windows, Mac, mobile) by leaving a note on the relevant <a href="https://github.com/bill-auger/av-caster/issues?q=is%3Aopen+milestone%3A%22cross-platform+version%22+label%3Aepic">Cross-platform Milestone</a> issue.  Feel free to open issues for other platforms if they are not yet listed.</td></tr>
  <tr><td>
    <table>
      <tr><th colspan="2">Build Status</th></tr>
      <tr>
        <td align="left">Release:</td>
        <td><a href="https://travis-ci.org/bill-auger/av-caster">
          <img src="https://travis-ci.org/bill-auger/av-caster.svg?branch=master"
               alt="release build status" width="100" height="18" /></a></td></tr>
      <tr>
        <td align="left">Development:</td>
        <td><a href="https://travis-ci.org/bill-auger/av-caster">
          <img src="https://travis-ci.org/bill-auger/av-caster.svg"
               alt="development build status" width="100" height="18" /></a></td></tr>
      <tr>
        <td align="left">Lint:</td>
        <td><a href="https://scan.coverity.com/projects/bill-auger-av-caster">
          <img src="https://scan.coverity.com/projects/bill-auger-av-caster/badge.svg"
               alt="static analysis status" width="100" height="18" /></a></td></tr>
    </table>
  </td></tr></table>


### Motivation
The motivation behind this project is that streaming with a feature-rich, bleeding-edge client such as the [OBS Open Broadcster Software](https://obsproject.com/) and the classic [FMLE Flash Media Live Encoder](https://www.adobe.com/products/flash-media-encoder.html) is a very CPU-demanding task even for reasonably capable computers.  Those programs are well suited as a substitute for dedicated capture hardware in high-performance scenarios such as game-casting; but in the most common use-cases such as live performance, design-casting, and code-casting, there is more utility in reserving your CPU cycles for primary tasks such as audio processing, graphics rendering, and source code compiling.  Another strong motivation is that most computers can not use either of those popular programs on GNU/Linux; which is the primary target platform for AvCaster.

A command-line solution is the obvious choice for such scenarios but is obviously not as user-friendly and lacking real-time control and preview.  The primary design goal for AvCaster is to strike a reasonable balance between headless performance and full-featured graphical convenience.  Ideally, AvCaster should be usable on the standard hardware of an Arm device or x86-32bit-era PC with libre drivers and well suited for lesser CPU-intesive tasks such as tutorial screencast recording and vlogging  on a wide range of devices.


### Get AvCaster
_NOTE: AvCaster requires gStreamer >= v1.6.0 and the 'ugly' plugins set which may not be available in your standard main/free repository (see "runtime dependencies" for your distro below)._
#### AvCaster Package Repositories
The [OpenSuse Build Service][obs] hosts AvCaster x86 and x86-64 binary package repositories for the following distributions:
  * Arch
  * Debian 9
  * Fedora 23, Fedora 24
  * OpenSuse Leap 42.2, OpenSuse Tumbleweed
  * Ubuntu 16.04

Follow the [instructions][obs] there to download the latest package for your distribution or subscribe your package manager for future updates.  Let us know if you would like packaging for another distribution or architecture.
#### Arch:
There is also an [AUR repo for AvCaster][aur] maintained by [GitHub user fa7ad][fa7ad].  Feel free to [vote for AvCaster on AUR][aur] if you are an AUR user and would like to see AvCaster promoted to the 'community' binary repo.

The Arch PKGBUILD file is also included in the Builds/Packaging/ directory of this repo. Refer to the "Building from Source" section below.
#### Other GNU/Linux:
Refer to the "Building from Source" section below.


### Getting Help / Bug Reporting
If AvCaster refuses to launch after changing some parameters in the GUI you can (as a last resort) try deleting the persistent configuration file in your user AppData dir (e.g. ~/.config/av-caster/av-caster.bin).  Note that this will reset/clear all settings back to the initial state.

Please report any problems on the [AvCaster Issue Tracker][tracker].

Feel free join the [Gitter Chat][gitter] to post any questions or comments, or ... erm ... just chat.


### Building from Source

#### Arch:
```
### build and install via makepkg ###
$ wget https://raw.githubusercontent.com/bill-auger/av-caster/master/Builds/Packaging/PKGBUILD
# makepkg -sri ./PKGBUILD
```

#### Debian >= 9, Ubuntu >= 15.10:
```
### build dependencies ###
$ sudo apt-get install build-essential libfreetype6-dev libgstreamer-plugins-base1.0-dev \
                       libircclient-dev libx11-dev libxcursor-dev libxinerama-dev        \
                       libxrandr-dev

### runtime dependencies ###
$ sudo apt-get install freeglut3 gstreamer1.0-alsa gstreamer1.0-plugins-bad       \
                       gstreamer1.0-plugins-good gstreamer1.0-plugins-ugly        \
                       gstreamer1.0-pulseaudio libfreetype6 libgl1-mesa-glx       \
                       libircclient1 libx11-6 libxcomposite1 libxcursor1 libxext6 \
                       libxinerama1 libxrender1

### compile ###
$ cd Builds/Makefile
$ make
$ sudo make install

### run ###
$ av-caster
```

#### Fedora >= 23 (plus rpmfusion repositories):
```
### build dependencies ###
$ su -c "dnf install freetype-devel gcc-c++ gstreamer1-plugins-base-devel               \
                     libircclient-devel libX11-devel libXcursor-devel libXinerama-devel \
                     libXrandr-devel"

### runtime dependencies ###
$ RPMFUSION_URL=http://download1.rpmfusion.org/free/fedora
$ FEDORA_VERSION=$(rpm -E %fedora)
$ REPO_PKG=$RPMFUSION_URL/rpmfusion-free-release-$FEDORA_VERSION.noarch.rpm
$ su -c "dnf install $REPO_PKG"
$ su -c "dnf install gstreamer1-plugins-bad-free gstreamer1-plugins-bad-freeworld \
                     gstreamer1-plugins-good     gstreamer1-plugins-good-extras   \
                     gstreamer1-plugins-ugly     libircclient"

### compile ###
$ cd Builds/Makefile
$ make
$ su -c "make install"

### run ###
$ av-caster
```

#### OpenSuse Leap >= 42, OpenSuse Tumbleweed, Suse SLE >= 12:
```
### build dependencies ###
$ sudo zypper install freetype2-devel gcc-c++ gstreamer-plugins-base-devel               \
                      libircclient-devel libX11-devel libXinerama-devel libXcursor-devel \
                      libXrandr-devel

### runtime dependencies ###
$ sudo zypper install gstreamer-plugins-bad gstreamer-plugins-good \
                      gstreamer-plugins-ugly libircclient1

### compile ###
$ cd Builds/Makefile
$ make
$ sudo make install

### run ###
$ av-caster
```

#### Other GNU/Linux:
Install the corresponding libraries as above for your system and compile similarly.


### Community
AvCaster is a free and open-source community project; so testers, comments, and suggestions are appreciated.  Pull requests are quite welcomed and any submissions that advance the project toward is proposed milestones will be accepted.  Let us hear your ideas.  If you would like to help to improve AvCaster, we could especially use your help in the following areas:
  * developers/consultants (especially with gStreamer expertise)
  * designers (logo, website, GUI graphics/layout)
  * beta testers (anyone who streams regularly)
  * HOWTO documentation and screencasts

In any case, you can ["Star" the upstream repo][upstream] to show your support for this project and you can "Watch" the repo or visit the home page of the [AvCaster Wiki][wiki] for updates.

Feel free join the [Gitter Chat][gitter] to post any questions or comments, or ... erm ... just chat.


### Developers and Designers
Please read the contribution guidelines in [CONTRIBUTING.md](https://github.com/bill-auger/av-caster/blob/master/CONTRIBUTING.md).


### Similar Projects
There were several similar projects considered for expansion before this project was launched fresh.  They all can capture and mux in audio but they capture screen only (no webcam/text/logo) and only two of them feature a real-time preview.  They are ordered roughly by feature-set from most to least capable in terms of the AvCaster project's feature requirements.
  * [SimpleScreenRecorder](https://github.com/MaartenBaert/ssr) - feature-rich with real-time preview
  * [gtk-recordmydesktop](http://recordmydesktop.sourceforge.net/) - feature-rich with real-time preview
  * [kazam](https://launchpad.net/kazam) - feature-rich but no preview
  * [vokoscreen](http://www.kohaupt-online.de/hp/) - similar features as kazam with pretty and intutive GUI
  * [ffmpeg-gui](http://sourceforge.net/projects/ffmpegfrontend/) - cross-platform QT basic ffmpeg launcher
  * [ffmpeggui](http://sourceforge.net/projects/ffmpeg-gui/) - Win32 basic ffmpeg launcher

Also, the ffmpeg bash script that AvCaster was originally conceived to wrap is in [this gist](https://gist.github.com/bill-auger/9480205a38d9d00d2fa3) if an ultra-lightweight command-line webcasting tool is more suitable.  It is capable of recording to file or streaming to an RTMP server with screen capture, webcam, text overlay, and stereo audio.  It requires some manual configuration o/c, but is approximately twice as nice.


[upstream]: https://github.com/bill-auger/av-caster
[wiki]:     https://github.com/bill-auger/av-caster/wiki/
[tracker]:  https://github.com/bill-auger/av-caster/issues
[gitter]:   https://gitter.im/bill-auger/av-caster
[obs]:      http://software.opensuse.org/download/package?project=home:bill-auger&package=av-caster
[aur]:      https://aur.archlinux.org/packages/av-caster/
[fa7ad]:    https://github.com/fa7ad/av-caster-aur/

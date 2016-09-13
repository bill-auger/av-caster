#
# spec file for package av-caster
#
# Copyright (c) 2015-2106 bill-auger bill-auger@programmer.net
#
# All modifications and additions to the file contributed by third parties
# remain the property of their copyright owners, unless otherwise agreed
# upon. The license for this file, and modifications and additions to the
# file, is the same license as for the pristine package itself (unless the
# license for the pristine package is not an Open Source License, in which
# case the license is the MIT License). An "Open Source License" is a
# license that conforms to the Open Source Definition (Version 1.9)
# published by the Open Source Initiative.

# Please submit bugfixes or comments via http://bugs.opensuse.org/
#

Name:          av-caster
Version:       0.16.004
Release:       1%{?dist}
Summary:       A light-weight native gStreamer GUI for screencast, webcam, and audio streaming
License:       GPL-3.0
URL:           https://github.com/bill-auger/%{name}/
Source0:       https://github.com/bill-auger/%{name}/archive/v%{version}.tar.gz
BuildRequires: gcc-c++ libircclient-devel libX11-devel libXcursor-devel libXinerama-devel libXrandr-devel
%if 0%{?sles_version} || 0%{?suse_version}
BuildRequires: freetype2-devel gstreamer-plugins-base-devel update-desktop-files
Requires:      gstreamer-plugins-good gstreamer-plugins-bad gstreamer-plugins-ugly libircclient1
%endif
%if 0%{?centos_version} || 0%{?fedora_version} || 0%{?rhel_version}
BuildRequires: freetype-devel gstreamer1-plugins-base-devel
Requires:      gstreamer1-plugins-good gstreamer1-plugins-bad-free gstreamer1-plugins-ugly libircclient
%endif


%define package_bin_dir   %{buildroot}%{_bindir}
%define package_apps_dir  %{buildroot}%_datadir/applications/
%define package_icons_dir %{buildroot}%_datadir/icons/hicolor/48x48/apps/
%define binary_artefact   Builds/Makefile/build/%{name}
%define desktop_file      Assets/%{name}.desktop
%define icon_file         Assets/avcaster-logo-48.png


%description
  AvCaster is a native GNU/Linux application built with the JUCE framework
  and using gStreamer as the media backend. The current version capable of
  recording to file or streaming to an RTMP server with screen capture,
  webcam overlay, and stereo audio. It is moderately configurable,
  with a preset configuration for streaming via livecoding.tv, and allows
  custom user-defined configurations to be stored as additional presets.

%prep
%autosetup

%build
cd Builds/Makefile/
make %{?_smp_mflags} CONFIG=Release

%install
mkdir -p %{buildroot}%{_bindir}
# mkdir -p %package_apps_dir
# mkdir -p %package_icons_dir
mv       %binary_artefact %package_bin_dir/
# mv       %desktop_file    %package_apps_dir/
# mv       %icon_file       %package_icons_dir/

%files
%doc
%{_bindir}/%{name}

%post
%if ! 0%{?suse_version}
  xdg-desktop-menu forceupdate
%endif

%postun
%if ! 0%{?suse_version}
  xdg-desktop-menu forceupdate
%endif

%changelog
* Wed Sep 14 2016 bill-auger
- v0.16.004

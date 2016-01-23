#
# spec file for package av-caster
#
# Copyright (c) 2015 bill-auger bill-auger@programmer.net
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
Version:       0.15.201
Release:       1%{?dist}
Summary:       A simple native gStreamer GUI for screencast, webcam, and audio streaming
License:       LGPL-3.0
URL:           https://github.com/bill-auger/%{name}/
Source0:       https://github.com/bill-auger/%{name}/archive/v%{version}.tar.gz
BuildRequires: freetype2-devel gcc-c++ libX11-devel libXinerama-devel libXcursor-devel
%if 0%{?sles_version} || 0%{?suse_version}
BuildRequires: gstreamer-plugins-base-devel
Requires:      gstreamer-plugins-good gstreamer-plugins-bad gstreamer-plugins-ugly
%endif
%if 0%{?centos_version} || 0%{?fedora_version} || 0%{?rhel_version}
BuildRequires: gstreamer1-plugins-base-devel
Requires:      gstreamer1-plugins-good gstreamer1-plugins-bad-free gstreamer1-plugins-ugly
%endif

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
mv Builds/Makefile/build/%{name} %{buildroot}%{_bindir}/

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
* Sat Dec 19 2015 bill-auger
- v0.15.201

# Maintainer: bill-auger <bill-auger@programmer.net>


pkgname=av-caster
pkgver=0.16.005
pkgrel=1
pkgdesc="A light-weight native gStreamer GUI for screencast, webcam, and audio recording and streaming"
arch=('i686' 'x86_64')
url=https://github.com/bill-auger/av-caster
license=('GPL3')

depends=('gst-plugins-bad' 'gst-plugins-base' 'gst-plugins-good' 'gst-plugins-ugly' 'gstreamer')
makedepends=('libircclient' 'libxinerama' 'libxrandr')

_builddir=${pkgname}-${pkgver}/Builds/Makefile
source=(https://github.com/bill-auger/av-caster/archive/v${pkgver}.tar.gz)
sha256sums=('6f5f8a24c9ae9d8a43672f56586b8a8bca94282680860970f8f7dacfc970b0e2')


build()
{
  cd ${_builddir}

  make CONFIG=Release
}

package()
{
  install -Dm 755 ${_builddir}/build/av-caster ${pkgdir}/usr/bin/av-caster
}

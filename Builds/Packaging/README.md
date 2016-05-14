
the files contained in this directory are used by the OpenSUSE Build Service to build/package binary artifacts and are otherwise not interesting

when merging into master, the current manual procedure is as follows:
* update version number in jucer
* create a tag/tarball named as "vMAJOR.MINOR.REV"
* download tarball and calclulate md5sum
* in Builds/Packaging/PKGBUILD
  => update 'pkgver', 'md5sums'
  => update 'makedepends' and/or 'depends'
* in Builds/Packaging/_service
  => update 'path'
* in Builds/Packaging/av-caster.spec
  => update 'Version'
  => update 'BuildRequires' and/or 'Requires'
  => update '%build' recipe, package '%files', and/or '%post' install hooks
  => update '%changelog' date and version
* in Builds/Packaging/av-caster.dsc
  => update 'Version'
  => update 'Build-Depends'
  => update 'Files' filename (checksum and size are arbitrary)
* in Builds/Packaging/debian.changelog
  => add new entry with list of significant commits
* in Builds/Packaging/debian.rules
  => update 'build-stamp:' recipe and 'install:' package files
* in Builds/Packaging/debian.control
  => update 'Build-Depends' and/or 'Depends'
* copy the entire Builds/Packaging/ directory to the local osc directory
* move the tarball to the local osc directory as vMAJOR.MINOR.REV.tar.gz
* osc local build e.g.
  $ osc build openSUSE_Tumbleweed x86_64 ./av-caster.spec
  $ osc build Debian_8.0          x86_64 ./av-caster.dsc
* tweak any of the above steps as necessary until everything rocks sweetly
* osc commit to the OBS build server for final build
* update main README.md as necessary, git commit everything, then merge into master

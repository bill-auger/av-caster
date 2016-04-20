
the files contained in this directory are used by the OpenSUSE Build Service to build/package binary artifacts and are otherwise not interesting

when merging into master, the current manual procedure is as follows:
* create a tag/tarball of the development branch named as "vMAJOR.MINOR.REV"
* calclulate md5sum of tarball
* Builds/Packaging/PKGBUILD
  => update 'pkgver', 'md5sums'
  => add any new 'makedepends' and/or 'depends'
* Builds/Packaging/av-caster.spec
  => update 'Version'
  => add any new 'BuildRequires' and/or 'Requires'
  => add any new build steps, package '%files', and/or install hooks
  => update '%changelog' date and version
* Builds/Packaging/av-caster.dsc
  => update 'Version'
  => add any new 'Build-Depends'
  => ('Files' checksum and size are arbitrary)
* Builds/Packaging/_service
  => update 'path'
* Builds/Packaging/debian.changelog
  => * add terse changes
* Builds/Packaging/debian.rules
  => add any new package files, and/or build steps
* Builds/Packaging/debian.control
  => add any new 'Build-Depends' and/or 'Depends'
* commit any of the above changed files to the build server
* repeat any of the above steps as necessary until everything rocks
* update main README.md as necessary, commit everything, then merge into master

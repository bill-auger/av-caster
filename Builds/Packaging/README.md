
the files contained in this directory are used by the openSUSE Build Service to package binary artifacts and are otherwise not interesting

when merging into master, the current manual routine is as follows (perhaps we can automate some of these):
* create a tag/tarball of the development branch named as "vMAJOR.MINOR.REV"
* calclulate md5sum of tarball
* update 'pkgver', 'md5sums' in Builds/Packaging/PKGBUILD
* update 'Version' and 'Files' in Builds/Packaging/av-caster.dsc (checksum and size are arbitrary)
* update 'Version' in Builds/Packaging/av-caster.spec
* update 'path' in Builds/Packaging/_service
* add to Builds/Packaging/debian.changelog
* update '%changelog' date and version in Builds/Packaging/av-caster.spec
* add any new dependencies to 'depends' and/or 'makedepends' in Builds/Packaging/PKGBUILD
* add any new dependencies to 'Build-Depends' in Builds/Packaging/av-caster.dsc
* add any new 'BuildRequires' or 'Requires' , package '%files' , or steps/hooks to Builds/Packaging/av-caster.spec
* add any new package files , or build steps to Builds/Packaging/debian.rules
* commit any of the above changed files to the build server
* repeat any of the above steps as necessary until everything rocks
* update main README.md as necessary, commit everything, and merge development into master



the files contained in this directory are used by the openSUSE Build Service to package binary artifacts and are otherwise not interesting

when merging into master, the current manual routine is as follows (perhaps we can automate some of these):
* update 'VERSION' in .travis.yml
* update 'Version' in Builds/Packaging/av-caster.dsc
* update 'Version' in Builds/Packaging/av-caster.spec
* update Builds/Packaging/debian.changelog
* update %changelog version in Builds/Packaging/av-caster.spec
* add any new dependencies to Builds/Packaging/av-caster.dsc (checksum is arbitrary)
* add any new dependencies , package files , or build steps to Builds/Packaging/av-caster.spec
* add any new dependencies , package files , or build steps to Builds/Packaging/debian.rules
* tag/create a tarball and md5sum for arch package
* update 'pkgver', 'url', and 'md5sums' in Builds/Packaging/PKGBUILD
* commit any of the above changed files to the build server

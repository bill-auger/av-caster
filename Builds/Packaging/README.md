the arch PKGBUILD file contained in this directory is somewhat brittle in that the md5sum property refers to a tarball that is yet to be acquired - which in the case of a git repo is created automatically based on the last commit - so it is not possible to include this checksum in the git repo itself because doing so would necessarily cause the checksum to change - therefore arch users must first download the tarball then run md5sum on it - then modify the value of md5sums in the PKGBUILD file to match (at least until we ask the arch peeps if there is a better way of handling this)

the remaining files contained in this directory are used by travis to package binary artifacts and are otherwise not interesting

when merging into master, the current manualy routine is as follows (perhaps we can automate some of these):
* update 'VERSION' in .travis.yml
* update Builds/Packaging/changelog
* tag/create a tarball and md5sum for arch package
* update 'pkgver', 'url', and 'md5sums' in Builds/Packaging/PKGBUILD

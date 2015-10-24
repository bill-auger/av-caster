#!/bin/bash

REPO=$1
PACKAGE=$2

DISTROS="debian/jessie
         ubuntu/utopic
         ubuntu/vivid
         ubuntu/wily"


for distro in $DISTROS
do package_cloud yank $REPO/$distro $PACKAGE
   package_cloud push $REPO/$distro $PACKAGE
done

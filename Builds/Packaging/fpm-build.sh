#!/bin/bash

VERSION=$1
ARCH=$2

SOURCE_REPO_NAME='bill-auger'
PROJECT_NAME='av-caster'
DEB_DESC="A simple native gStreamer GUI for screencast, webcam, and audio streaming"


  fpm -s dir -t deb --name $PROJECT_NAME --version $VERSION              \
    -C              .                                                    \
    --package       ./"$PROJECT_NAME"_"$VERSION"_"$ARCH".deb             \
    --architecture  "$ARCH"                                              \
    --license       'LGPLv3'                                             \
    --maintainer    'bill-auger@programmer.net'                          \
    --vendor        "https://github.com/$SOURCE_REPO_NAME/$PROJECT_NAME" \
    --url           "https://github.com/$SOURCE_REPO_NAME/$PROJECT_NAME" \
    --depends       'freeglut3'                                          \
    --depends       'libfreetype6'                                       \
    --depends       'libgl1-mesa-glx | libgl1'                           \
    --depends       'libx11-6'                                           \
    --depends       'libxcomposite1'                                     \
    --depends       'libxcursor1'                                        \
    --depends       'libxext6'                                           \
    --depends       'libxinerama1'                                       \
    --depends       'libxrender1'                                        \
    --depends       'gstreamer1.0-plugins-good'                          \
    --depends       'gstreamer1.0-plugins-bad >= 1.4'                    \
    --depends       'gstreamer1.0-plugins-ugly'                          \
    --description   "$DEB_DESC"                                          \
    --deb-changelog ./changelog                                          \
    --deb-priority  'optional'                                           \
    --category      'network'                                            \
    usr/

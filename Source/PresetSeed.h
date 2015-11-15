/*\
|*|  Copyright 2015 bill-auger <https://github.com/bill-auger/av-caster/issues>
|*|
|*|  This file is part of the AvCaster program.
|*|
|*|  AvCaster is free software: you can redistribute it and/or modify
|*|  it under the terms of the GNU Lesser General Public License version 3
|*|  as published by the Free Software Foundation.
|*|
|*|  AvCaster is distributed in the hope that it will be useful,
|*|  but WITHOUT ANY WARRANTY; without even the implied warranty of
|*|  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|*|  GNU Lesser General Public License for more details.
|*|
|*|  You should have received a copy of the GNU Lesser General Public License
|*|  along with AvCaster.  If not, see <http://www.gnu.org/licenses/>.
\*/


#ifndef PRESETSEED_H_INCLUDED
#define PRESETSEED_H_INCLUDED

#include "Constants.h"


class PresetSeed
{
protected:

  PresetSeed() ;

  void createPreset() ;


  // node ID
  Identifier presetId ;

  // control params
  String     presetName ;
  bool       isOutputOn ;
  bool       isInterstitialOn ;
  bool       isScreencapOn ;
  bool       isCameraOn ;
  bool       isTextOn ;
  bool       isPreviewOn ;

  // screencap params
  int        displayN ;
  int        screenN ;
  int        screencapW ;
  int        screencapH ;
  int        offsetX ;
  int        offsetY ;

  // camera params
  int        cameraResolutionIdx ;
  int        cameraDeviceIdx ;

  // audio params
  int        audioApiIdx ;
  int        audioDeviceIdx ;
  int        audioCodecIdx ;
  int        nChannels ;
  int        samplerate ;
  int        audioBitrate ;

  // text params
  String     motdText ;
  int        textStyleIdx ;
  int        textPosIdx ;

  // interstitial params
  String     interstitialLoc ;

  // output params
  int        sinkIdx ;
  int        muxerIdx ;
  int        outputW ;
  int        outputH ;
  int        framerate ;
  int        videoBitrate ;
  String     outputDest ;


public:

  // AvCasterStore->configPresets child node
  ValueTree preset ;
} ;


class FilePresetSeed : public PresetSeed { public: FilePresetSeed() ; } ;


class RtmpPresetSeed : public PresetSeed { public: RtmpPresetSeed() ; } ;


class LctvPresetSeed : public PresetSeed { public: LctvPresetSeed() ; } ;

#endif // PRESETSEED_H_INCLUDED

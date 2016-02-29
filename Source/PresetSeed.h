/*\
|*|  Copyright 2015-2016 bill-auger <https://github.com/bill-auger/av-caster/issues>
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


#ifndef _PRESETSEED_H_
#define _PRESETSEED_H_

#include "Constants.h"


class PresetSeed
{
public:

  static ValueTree DefaultStore() ;
  static ValueTree PresetSeeds () ;


protected:

  PresetSeed() ;

  void createPreset() ;

  // node ID
  Identifier presetId ;
  // Controls params
  String     presetName ;
  // ConfigOutput params
  int        sinkIdx ;
  String     outputDest ;


private:

  void setValue(ValueTree a_node , Identifier a_key , var a_value) ;


  // AvCasterStore->presets child node
  ValueTree presetStore ;
  // AvCasterStore->network node
  ValueTree networkStore ;

  // Controls params
  bool   isScreencapActive ;
  bool   isCameraActive ;
  bool   isTextActive ;
  bool   isImageActive ;
  bool   isPreviewActive ;
  bool   isAudioActive ;
  // ConfigScreen params
  int    displayN ;
  int    screenN ;
  int    screencapW ;
  int    screencapH ;
  int    offsetX ;
  int    offsetY ;
  // ConfigCamera params
  int    cameraResolutionIdx ;
  int    cameraDeviceIdx ;
  // ConfigAudio params
  int    audioApiIdx ;
  int    audioDeviceIdx ;
  int    audioCodecIdx ;
  int    nChannels ;
  int    samplerate ;
  int    audioBitrate ;
  // ConfigText params
  String motdText ;
  int    textStyleIdx ;
  int    textPosIdx ;
  // ConfigImage params
  String imageLocation ;
  // ConfigOutput params
  int    muxerIdx ;
  int    outputW ;
  int    outputH ;
  int    framerate ;
  int    videoBitrate ;
  // ConfigChat params
  String network ;
  int    port ;
  String nick ;
  String pass ;
  String channel ;
  bool   showTimestamps ;
  bool   showJoinParts ;
  String greeting ;
} ;


class FilePresetSeed : private PresetSeed { friend class PresetSeed ; private: FilePresetSeed() ; } ;


class RtmpPresetSeed : private PresetSeed { friend class PresetSeed ; private: RtmpPresetSeed() ; } ;


class LctvPresetSeed : private PresetSeed { friend class PresetSeed ; private: LctvPresetSeed() ; } ;

#endif // _PRESETSEED_H_

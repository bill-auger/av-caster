/*\
|*|  AvCaster - light-weight native gStreamer GUI for screencast, webcam, and audio streaming
|*|  Copyright 2015-2018 bill-auger <https://github.com/bill-auger/av-caster/issues>
|*|
|*|  This file is part of the AvCaster program.
|*|
|*|  AvCaster is free software: you can redistribute it and/or modify
|*|  it under the terms of the GNU General Public License version 3
|*|  as published by the Free Software Foundation.
|*|
|*|  AvCaster is distributed in the hope that it will be useful,
|*|  but WITHOUT ANY WARRANTY; without even the implied warranty of
|*|  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|*|  GNU General Public License for more details.
|*|
|*|  You should have received a copy of the GNU General Public License
|*|  along with AvCaster.  If not, see <http://www.gnu.org/licenses/>.
\*/


#ifndef _SEEDS_H_
#define _SEEDS_H_

#include "../Constants/Constants.h"


class Seeds
{
public:

  static ValueTree DefaultStore() ;
  static ValueTree PresetSeeds () ;


protected:

  Seeds() ;

  void createPreset() ;

  // node ID
  Identifier presetId ;
  // Presets params
  String     presetName ;
  // ConfigOutput params
  int        outputSinkIdx ;
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
  // Presets params
  String configPane ;
  // ConfigScreen params
  int    displayN ;
  int    screenN ;
  int    screencapW ;
  int    screencapH ;
  int    offsetX ;
  int    offsetY ;
  // ConfigCamera params
  int    cameraDeviceIdx ;
  int    cameraResolutionIdx ;
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


class FileSeed : private Seeds { friend class Seeds ; private: FileSeed() ; } ;


class RtmpSeed : private Seeds { friend class Seeds ; private: RtmpSeed() ; } ;


class LctvSeed : private Seeds { friend class Seeds ; private: LctvSeed() ; } ;

#endif // _SEEDS_H_

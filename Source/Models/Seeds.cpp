/*\
|*|  AvCaster - light-weight native gStreamer GUI for screencast, webcam, and audio streaming
|*|  Copyright 2015-2018, 2020 bill-auger <https://github.com/bill-auger/av-caster/issues>
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


#include "Seeds.h"


/* Seeds public class methods */

ValueTree Seeds::DefaultStore()
{
  ValueTree default_store = ValueTree(CONFIG::STORAGE_ID) ;
  default_store.setProperty(CONFIG::CONFIG_VERSION_ID , CONFIG::CONFIG_VERSION     , nullptr) ;
  default_store.setProperty(CONFIG::PRESET_ID         , CONFIG::DEFAULT_PRESET_IDX , nullptr) ;
  default_store.addChild   (ValueTree(CONFIG::PRESETS_ID) , -1 , nullptr) ;

  return default_store ;
}

ValueTree Seeds::PresetSeeds()
{
  FileSeed file_preset_seed ;
  RtmpSeed rtmp_preset_seed ;
  LctvSeed lctv_preset_seed ;

  ValueTree preset_seeds = ValueTree(CONFIG::PRESETS_ID) ;
  preset_seeds.addChild(file_preset_seed.presetStore , CONFIG::FILE_PRESET_IDX , nullptr) ;
  preset_seeds.addChild(rtmp_preset_seed.presetStore , CONFIG::RTMP_PRESET_IDX , nullptr) ;
  preset_seeds.addChild(lctv_preset_seed.presetStore , CONFIG::LCTV_PRESET_IDX , nullptr) ;

  return preset_seeds ;
}


/* Seeds protected constructor */

Seeds::Seeds()
{
  this->isScreencapActive   = CONFIG::DEFAULT_IS_SCREEN_ACTIVE ;
  this->isCameraActive      = CONFIG::DEFAULT_IS_CAMERA_ACTIVE ;
  this->isTextActive        = CONFIG::DEFAULT_IS_TEXT_ACTIVE ;
  this->isImageActive       = CONFIG::DEFAULT_IS_IMAGE_ACTIVE ;
  this->isPreviewActive     = CONFIG::DEFAULT_IS_PREVIEW_ACTIVE ;
  this->isAudioActive       = CONFIG::DEFAULT_IS_AUDIO_ACTIVE ;
  this->configPane          = CONFIG::DEFAULT_CONFIG_PANE ;
  this->displayN            = CONFIG::DEFAULT_DISPLAY_N ;
  this->screenN             = CONFIG::DEFAULT_SCREEN_N ;
  this->screencapW          = CONFIG::DEFAULT_SCREENCAP_W ;
  this->screencapH          = CONFIG::DEFAULT_SCREENCAP_H ;
  this->offsetX             = CONFIG::DEFAULT_OFFSET_X ;
  this->offsetY             = CONFIG::DEFAULT_OFFSET_Y ;
  this->cameraDeviceIdx     = CONFIG::DEFAULT_CAMERA_DEVICE_IDX ;
  this->cameraResolutionIdx = CONFIG::DEFAULT_CAMERA_RES_IDX ;
  this->audioApiIdx         = CONFIG::DEFAULT_AUDIO_API_IDX ;
  this->audioDeviceIdx      = CONFIG::DEFAULT_AUDIO_DEVICE_IDX ;
  this->audioCodecIdx       = CONFIG::DEFAULT_AUDIO_CODEC_IDX ;
  this->nChannels           = CONFIG::DEFAULT_N_CHANNELS ;
  this->samplerate          = CONFIG::DEFAULT_SAMPLERATE_IDX ;
  this->audioBitrate        = CONFIG::DEFAULT_AUDIO_BITRATE_IDX ;
  this->motdText            = CONFIG::DEFAULT_MOTD_TEXT ;
  this->textStyleIdx        = CONFIG::DEFAULT_TEXT_STYLE_IDX ;
  this->textPosIdx          = CONFIG::DEFAULT_TEXT_POSITION_IDX ;
  this->imageLocation       = CONFIG::DEFAULT_IMAGE_LOCATION ;
  this->muxerIdx            = CONFIG::DEFAULT_OUTPUT_MUXER_IDX ;
  this->outputW             = CONFIG::DEFAULT_OUTPUT_W ;
  this->outputH             = CONFIG::DEFAULT_OUTPUT_H ;
  this->framerate           = CONFIG::DEFAULT_FRAMERATE_IDX ;
  this->videoBitrate        = CONFIG::DEFAULT_VIDEO_BITRATE_IDX ;
  this->networkStore        = ValueTree(CONFIG::NETWORK_ID) ;
  this->network             = CONFIG::DEFAULT_NETWORK ;
  this->port                = CONFIG::DEFAULT_PORT ;
  this->nick                = CONFIG::DEFAULT_NICK ;
  this->pass                = CONFIG::DEFAULT_PASS ;
  this->channel             = CONFIG::DEFAULT_CHANNEL ;
  this->showTimestamps      = CONFIG::DEFAULT_SHOW_TIMESTAMPS ;
  this->showJoinParts       = CONFIG::DEFAULT_SHOW_JOINPARTS ;
  this->greeting            = CONFIG::DEFAULT_GREETING ;

  // subclass responsibility
  this->presetStore   = ValueTree() ;
  this->presetId      = Identifier::null ;
  this->presetName    = String() ;
  this->outputSinkIdx = -1 ;
  this->outputDest    = String() ;
}

void Seeds::createPreset()
{
  this->presetStore = ValueTree(presetId) ;

  setValue(this->presetStore , CONFIG::SCREEN_ID        , var(this->isScreencapActive  )) ;
  setValue(this->presetStore , CONFIG::CAMERA_ID        , var(this->isCameraActive     )) ;
  setValue(this->presetStore , CONFIG::TEXT_ID          , var(this->isTextActive       )) ;
  setValue(this->presetStore , CONFIG::IMAGE_ID         , var(this->isImageActive      )) ;
  setValue(this->presetStore , CONFIG::PREVIEW_ID       , var(this->isPreviewActive    )) ;
  setValue(this->presetStore , CONFIG::AUDIO_ID         , var(this->isAudioActive      )) ;
  setValue(this->presetStore , CONFIG::PRESET_NAME_ID   , var(this->presetName         )) ;
  setValue(this->presetStore , CONFIG::CONFIG_PANE_ID   , var(this->configPane         )) ;
  setValue(this->presetStore , CONFIG::DISPLAY_N_ID     , var(this->displayN           )) ;
  setValue(this->presetStore , CONFIG::SCREEN_N_ID      , var(this->screenN            )) ;
  setValue(this->presetStore , CONFIG::SCREENCAP_W_ID   , var(this->screencapW         )) ;
  setValue(this->presetStore , CONFIG::SCREENCAP_H_ID   , var(this->screencapH         )) ;
  setValue(this->presetStore , CONFIG::OFFSET_X_ID      , var(this->offsetX            )) ;
  setValue(this->presetStore , CONFIG::OFFSET_Y_ID      , var(this->offsetY            )) ;
  setValue(this->presetStore , CONFIG::CAMERA_DEVICE_ID , var(this->cameraDeviceIdx    )) ;
  setValue(this->presetStore , CONFIG::CAMERA_RES_ID    , var(this->cameraResolutionIdx)) ;
  setValue(this->presetStore , CONFIG::AUDIO_API_ID     , var(this->audioApiIdx        )) ;
  setValue(this->presetStore , CONFIG::AUDIO_DEVICE_ID  , var(this->audioDeviceIdx     )) ;
  setValue(this->presetStore , CONFIG::AUDIO_CODEC_ID   , var(this->audioCodecIdx      )) ;
  setValue(this->presetStore , CONFIG::N_CHANNELS_ID    , var(this->nChannels          )) ;
  setValue(this->presetStore , CONFIG::SAMPLERATE_ID    , var(this->samplerate         )) ;
  setValue(this->presetStore , CONFIG::AUDIO_BITRATE_ID , var(this->audioBitrate       )) ;
  setValue(this->presetStore , CONFIG::MOTD_TEXT_ID     , var(this->motdText           )) ;
  setValue(this->presetStore , CONFIG::TEXT_STYLE_ID    , var(this->textStyleIdx       )) ;
  setValue(this->presetStore , CONFIG::TEXT_POSITION_ID , var(this->textPosIdx         )) ;
  setValue(this->presetStore , CONFIG::IMAGE_LOC_ID     , var(this->imageLocation      )) ;
  setValue(this->presetStore , CONFIG::OUTPUT_SINK_ID   , var(this->outputSinkIdx      )) ;
  setValue(this->presetStore , CONFIG::OUTPUT_MUXER_ID  , var(this->muxerIdx           )) ;
  setValue(this->presetStore , CONFIG::OUTPUT_W_ID      , var(this->outputW            )) ;
  setValue(this->presetStore , CONFIG::OUTPUT_H_ID      , var(this->outputH            )) ;
  setValue(this->presetStore , CONFIG::FRAMERATE_ID     , var(this->framerate          )) ;
  setValue(this->presetStore , CONFIG::VIDEO_BITRATE_ID , var(this->videoBitrate       )) ;
  setValue(this->presetStore , CONFIG::OUTPUT_DEST_ID   , var(this->outputDest         )) ;

  this->presetStore.addChild(this->networkStore , -1 , nullptr) ;
  setValue(this->networkStore , CONFIG::NETWORK_ID    , var(this->network       )) ;
  setValue(this->networkStore , CONFIG::PORT_ID       , var(this->port          )) ;
  setValue(this->networkStore , CONFIG::NICK_ID       , var(this->nick          )) ;
  setValue(this->networkStore , CONFIG::PASS_ID       , var(this->pass          )) ;
  setValue(this->networkStore , CONFIG::CHANNEL_ID    , var(this->channel       )) ;
  setValue(this->networkStore , CONFIG::TIMESTAMPS_ID , var(this->showTimestamps)) ;
  setValue(this->networkStore , CONFIG::JOINPARTS_ID  , var(this->showJoinParts )) ;
  setValue(this->networkStore , CONFIG::GREETING_ID   , var(this->greeting      )) ;
}


/* Seeds private methods */

void Seeds::setValue(ValueTree a_node , Identifier a_key , var a_value)
{
  a_node.setProperty(a_key , a_value , nullptr) ;
}


/* Seeds subclass public constructors */

FileSeed::FileSeed()
{
  presetId      = CONFIG::FILE_PRESET_ID ;
  presetName    = CONFIG::FILE_PRESET_NAME ;
  outputSinkIdx = CONFIG::FILE_OUTPUT_IDX ;
  outputDest    = CONFIG::DEFAULT_OUTPUT_DEST ;
  createPreset() ;
}

RtmpSeed::RtmpSeed()
{
  presetId      = CONFIG::RTMP_PRESET_ID ;
  presetName    = CONFIG::RTMP_PRESET_NAME ;
  outputSinkIdx = CONFIG::RTMP_OUTPUT_IDX ;
  outputDest    = String() ;
  createPreset() ;
}

LctvSeed::LctvSeed()
{
  presetId      = CONFIG::LCTV_PRESET_ID ;
  presetName    = CONFIG::LCTV_PRESET_NAME ;
  outputSinkIdx = CONFIG::RTMP_OUTPUT_IDX ;
  outputDest    = String() ;
  createPreset() ;
}

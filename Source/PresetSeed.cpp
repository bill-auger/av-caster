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


#include "PresetSeed.h"


PresetSeed::PresetSeed()
{
  isScreencapActive    = CONFIG::DEFAULT_IS_SCREENCAP_ACTIVE ;
  isCameraActive       = CONFIG::DEFAULT_IS_CAMERA_ACTIVE ;
  isTextActive         = CONFIG::DEFAULT_IS_TEXT_ACTIVE ;
  isImageActive        = CONFIG::DEFAULT_IS_IMAGE_ACTIVE ;
  isPreviewActive      = CONFIG::DEFAULT_IS_PREVIEW_ACTIVE ;
  isAudioActive        = CONFIG::DEFAULT_IS_AUDIO_ACTIVE ;
  isOutputActive       = CONFIG::DEFAULT_IS_OUTPUT_ACTIVE ;
  displayN             = CONFIG::DEFAULT_DISPLAY_N ;
  screenN              = CONFIG::DEFAULT_SCREEN_N ;
  screencapW           = CONFIG::DEFAULT_SCREENCAP_W ;
  screencapH           = CONFIG::DEFAULT_SCREENCAP_H ;
  offsetX              = CONFIG::DEFAULT_OFFSET_X ;
  offsetY              = CONFIG::DEFAULT_OFFSET_Y ;
  cameraDeviceIdx      = CONFIG::DEFAULT_CAMERA_DEVICE_IDX ;
  cameraResolutionIdx  = CONFIG::DEFAULT_CAMERA_RES_IDX ;
  audioApiIdx          = CONFIG::DEFAULT_AUDIO_API_IDX ;
  audioDeviceIdx       = CONFIG::DEFAULT_AUDIO_DEVICE_IDX ;
  audioCodecIdx        = CONFIG::DEFAULT_AUDIO_CODEC_IDX ;
  nChannels            = CONFIG::DEFAULT_N_CHANNELS ;
  samplerate           = CONFIG::DEFAULT_SAMPLERATE_IDX ;
  audioBitrate         = CONFIG::DEFAULT_AUDIO_BITRATE_IDX ;
  motdText             = CONFIG::DEFAULT_MOTD_TEXT ;
  textStyleIdx         = CONFIG::DEFAULT_TEXT_STYLE_IDX ;
  textPosIdx           = CONFIG::DEFAULT_TEXT_POSITION_IDX ;
  imageLocation        = CONFIG::DEFAULT_IMAGE_LOCATION ;
  muxerIdx             = CONFIG::DEFAULT_OUTPUT_MUXER_IDX ;
  outputW              = CONFIG::DEFAULT_OUTPUT_W ;
  outputH              = CONFIG::DEFAULT_OUTPUT_H ;
  framerate            = CONFIG::DEFAULT_FRAMERATE_IDX ;
  videoBitrate         = CONFIG::DEFAULT_VIDEO_BITRATE_IDX ;

  // subclass responsibility
  preset     = ValueTree::invalid ;
  presetId   = Identifier::null ;
  presetName = String::empty ;
  sinkIdx    = -1 ;
  outputDest = String::empty ;
}

void PresetSeed::createPreset()
{
  preset = ValueTree(presetId) ;
  preset.setProperty(CONFIG::PRESET_NAME_ID         , var(presetName          ) , nullptr) ;
  preset.setProperty(CONFIG::IS_SCREENCAP_ACTIVE_ID , var(isScreencapActive   ) , nullptr) ;
  preset.setProperty(CONFIG::IS_CAMERA_ACTIVE_ID    , var(isCameraActive      ) , nullptr) ;
  preset.setProperty(CONFIG::IS_TEXT_ACTIVE_ID      , var(isTextActive        ) , nullptr) ;
  preset.setProperty(CONFIG::IS_IMAGE_ACTIVE_ID     , var(isImageActive       ) , nullptr) ;
  preset.setProperty(CONFIG::IS_PREVIEW_ACTIVE_ID   , var(isPreviewActive     ) , nullptr) ;
  preset.setProperty(CONFIG::IS_AUDIO_ACTIVE_ID     , var(isAudioActive       ) , nullptr) ;
  preset.setProperty(CONFIG::IS_OUTPUT_ACTIVE_ID    , var(isOutputActive      ) , nullptr) ;
  preset.setProperty(CONFIG::DISPLAY_N_ID           , var(displayN            ) , nullptr) ;
  preset.setProperty(CONFIG::SCREEN_N_ID            , var(screenN             ) , nullptr) ;
  preset.setProperty(CONFIG::SCREENCAP_W_ID         , var(screencapW          ) , nullptr) ;
  preset.setProperty(CONFIG::SCREENCAP_H_ID         , var(screencapH          ) , nullptr) ;
  preset.setProperty(CONFIG::OFFSET_X_ID            , var(offsetX             ) , nullptr) ;
  preset.setProperty(CONFIG::OFFSET_Y_ID            , var(offsetY             ) , nullptr) ;
  preset.setProperty(CONFIG::CAMERA_DEVICE_ID       , var(cameraDeviceIdx     ) , nullptr) ;
  preset.setProperty(CONFIG::CAMERA_RES_ID          , var(cameraResolutionIdx ) , nullptr) ;
  preset.setProperty(CONFIG::AUDIO_API_ID           , var(audioApiIdx         ) , nullptr) ;
  preset.setProperty(CONFIG::AUDIO_DEVICE_ID        , var(audioDeviceIdx      ) , nullptr) ;
  preset.setProperty(CONFIG::AUDIO_CODEC_ID         , var(audioCodecIdx       ) , nullptr) ;
  preset.setProperty(CONFIG::N_CHANNELS_ID          , var(nChannels           ) , nullptr) ;
  preset.setProperty(CONFIG::SAMPLERATE_ID          , var(samplerate          ) , nullptr) ;
  preset.setProperty(CONFIG::AUDIO_BITRATE_ID       , var(audioBitrate        ) , nullptr) ;
  preset.setProperty(CONFIG::MOTD_TEXT_ID           , var(motdText            ) , nullptr) ;
  preset.setProperty(CONFIG::TEXT_STYLE_ID          , var(textStyleIdx        ) , nullptr) ;
  preset.setProperty(CONFIG::TEXT_POSITION_ID       , var(textPosIdx          ) , nullptr) ;
  preset.setProperty(CONFIG::IMAGE_ID               , var(imageLocation       ) , nullptr) ;
  preset.setProperty(CONFIG::OUTPUT_SINK_ID         , var(sinkIdx             ) , nullptr) ;
  preset.setProperty(CONFIG::OUTPUT_MUXER_ID        , var(muxerIdx            ) , nullptr) ;
  preset.setProperty(CONFIG::OUTPUT_W_ID            , var(outputW             ) , nullptr) ;
  preset.setProperty(CONFIG::OUTPUT_H_ID            , var(outputH             ) , nullptr) ;
  preset.setProperty(CONFIG::FRAMERATE_ID           , var(framerate           ) , nullptr) ;
  preset.setProperty(CONFIG::VIDEO_BITRATE_ID       , var(videoBitrate        ) , nullptr) ;
  preset.setProperty(CONFIG::OUTPUT_DEST_ID         , var(outputDest          ) , nullptr) ;
}

FilePresetSeed::FilePresetSeed()
{
  presetId   = CONFIG::FilterId(CONFIG::FILE_PRESET_NAME , APP::VALID_ID_CHARS) ;
  presetName = CONFIG::FILE_PRESET_NAME ;
  sinkIdx    = CONFIG::FILE_OUTPUT_IDX ;
  outputDest = CONFIG::DEFAULT_OUTPUT_DEST ;
  createPreset() ;
}

RtmpPresetSeed::RtmpPresetSeed()
{
  presetId   = CONFIG::FilterId(CONFIG::RTMP_PRESET_NAME , APP::VALID_ID_CHARS) ;
  presetName = CONFIG::RTMP_PRESET_NAME ;
  sinkIdx    = CONFIG::RTMP_OUTPUT_IDX ;
  outputDest = String::empty ;
  createPreset() ;
}

LctvPresetSeed::LctvPresetSeed()
{
  presetId   = CONFIG::FilterId(CONFIG::LCTV_PRESET_NAME , APP::VALID_ID_CHARS) ;
  presetName = CONFIG::LCTV_PRESET_NAME ;
  sinkIdx    = CONFIG::RTMP_OUTPUT_IDX ;
  outputDest = String::empty ;
  createPreset() ;
}

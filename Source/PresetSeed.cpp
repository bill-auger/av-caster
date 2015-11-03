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
  isOutputOn          = CONFIG::DEFAULT_IS_OUTPUT_ON ;
  isInterstitialOn    = CONFIG::DEFAULT_IS_INTERSTITIAL_ON ;
  isScreencapOn       = CONFIG::DEFAULT_IS_SCREENCAP_ON ;
  isCameraOn          = CONFIG::DEFAULT_IS_CAMERA_ON ;
  isTextOn            = CONFIG::DEFAULT_IS_TEXT_ON ;
  isPreviewOn         = CONFIG::DEFAULT_IS_PREVIEW_ON ;
  displayN            = CONFIG::DEFAULT_DISPLAY_N ;
  screenN             = CONFIG::DEFAULT_SCREEN_N ;
  screencapW          = CONFIG::DEFAULT_SCREENCAP_W ;
  screencapH          = CONFIG::DEFAULT_SCREENCAP_H ;
  offsetX             = CONFIG::DEFAULT_OFFSET_X ;
  offsetY             = CONFIG::DEFAULT_OFFSET_Y ;
  cameraDeviceIdx     = CONFIG::DEFAULT_CAMERA_DEV_IDX ;
  cameraResolutionIdx = CONFIG::DEFAULT_CAMERA_RES_IDX ;
  audioApiIdx         = CONFIG::DEFAULT_AUDIO_API_IDX ;
  audioDeviceIdx      = CONFIG::DEFAULT_AUDIO_DEVICE_IDX ;
  audioCodecIdx       = CONFIG::DEFAULT_AUDIO_CODEC_IDX ;
  nChannels           = CONFIG::DEFAULT_N_CHANNELS ;
  samplerate          = CONFIG::DEFAULT_SAMPLERATE_IDX ;
  audioBitrate        = CONFIG::DEFAULT_AUDIO_BITRATE_IDX ;
  motdText            = CONFIG::DEFAULT_MOTD_TEXT ;
  textStyleIdx        = CONFIG::DEFAULT_TEXT_STYLE_IDX ;
  textPosIdx          = CONFIG::DEFAULT_TEXT_POSITION_IDX ;
  interstitialLoc     = CONFIG::DEFAULT_INTERSTITIAL_LOC ;
  containerIdx        = CONFIG::DEFAULT_OUTPUT_CONTAINER_IDX ;
  outputW             = CONFIG::DEFAULT_OUTPUT_W ;
  outputH             = CONFIG::DEFAULT_OUTPUT_H ;
  framerate           = CONFIG::DEFAULT_FRAMERATE_IDX ;
  videoBitrate        = CONFIG::DEFAULT_VIDEO_BITRATE_IDX ;
}

void PresetSeed::createPreset()
{
  preset = ValueTree(presetId) ;
  preset.setProperty(CONFIG::PRESET_NAME_ID        , var(presetName         ) , nullptr) ;
  preset.setProperty(CONFIG::IS_OUTPUT_ON_ID       , var(isOutputOn         ) , nullptr) ;
  preset.setProperty(CONFIG::IS_INTERSTITIAL_ON_ID , var(isInterstitialOn   ) , nullptr) ;
  preset.setProperty(CONFIG::IS_SCREENCAP_ON_ID    , var(isScreencapOn      ) , nullptr) ;
  preset.setProperty(CONFIG::IS_CAMERA_ON_ID       , var(isCameraOn         ) , nullptr) ;
  preset.setProperty(CONFIG::IS_TEXT_ON_ID         , var(isTextOn           ) , nullptr) ;
  preset.setProperty(CONFIG::IS_PREVIEW_ON_ID      , var(isPreviewOn        ) , nullptr) ;
  preset.setProperty(CONFIG::DISPLAY_N_ID          , var(displayN           ) , nullptr) ;
  preset.setProperty(CONFIG::SCREEN_N_ID           , var(screenN            ) , nullptr) ;
  preset.setProperty(CONFIG::SCREENCAP_W_ID        , var(screencapW         ) , nullptr) ;
  preset.setProperty(CONFIG::SCREENCAP_H_ID        , var(screencapH         ) , nullptr) ;
  preset.setProperty(CONFIG::OFFSET_X_ID           , var(offsetX            ) , nullptr) ;
  preset.setProperty(CONFIG::OFFSET_Y_ID           , var(offsetY            ) , nullptr) ;
  preset.setProperty(CONFIG::CAMERA_DEV_ID         , var(cameraDeviceIdx    ) , nullptr) ;
  preset.setProperty(CONFIG::CAMERA_RES_ID         , var(cameraResolutionIdx) , nullptr) ;
  preset.setProperty(CONFIG::AUDIO_API_ID          , var(audioApiIdx        ) , nullptr) ;
  preset.setProperty(CONFIG::AUDIO_DEVICE_ID       , var(audioDeviceIdx     ) , nullptr) ;
  preset.setProperty(CONFIG::AUDIO_CODEC_ID        , var(audioCodecIdx      ) , nullptr) ;
  preset.setProperty(CONFIG::N_CHANNELS_ID         , var(nChannels          ) , nullptr) ;
  preset.setProperty(CONFIG::SAMPLERATE_ID         , var(samplerate         ) , nullptr) ;
  preset.setProperty(CONFIG::AUDIO_BITRATE_ID      , var(audioBitrate       ) , nullptr) ;
  preset.setProperty(CONFIG::MOTD_TEXT_ID          , var(motdText           ) , nullptr) ;
  preset.setProperty(CONFIG::TEXT_STYLE_ID         , var(textStyleIdx       ) , nullptr) ;
  preset.setProperty(CONFIG::TEXT_POSITION_ID      , var(textPosIdx         ) , nullptr) ;
  preset.setProperty(CONFIG::INTERSTITIAL_LOC_ID   , var(interstitialLoc    ) , nullptr) ;
  preset.setProperty(CONFIG::OUTPUT_STREAM_ID      , var(streamIdx          ) , nullptr) ;
  preset.setProperty(CONFIG::OUTPUT_CONTAINER_ID   , var(containerIdx       ) , nullptr) ;
  preset.setProperty(CONFIG::OUTPUT_W_ID           , var(outputW            ) , nullptr) ;
  preset.setProperty(CONFIG::OUTPUT_H_ID           , var(outputH            ) , nullptr) ;
  preset.setProperty(CONFIG::FRAMERATE_ID          , var(framerate          ) , nullptr) ;
  preset.setProperty(CONFIG::VIDEO_BITRATE_ID      , var(videoBitrate       ) , nullptr) ;
  preset.setProperty(CONFIG::OUTPUT_DEST_ID        , var(outputDest         ) , nullptr) ;
}

FilePresetSeed::FilePresetSeed()
{
  presetName = CONFIG::FILE_PRESET_NAME ;
  presetId   = CONFIG::FilterId(presetName) ;
  streamIdx  = CONFIG::FILE_STREAM_IDX ;
  outputDest = CONFIG::DEFAULT_OUTPUT_DEST ;
  createPreset() ;
}

RtmpPresetSeed::RtmpPresetSeed()
{
  presetName = CONFIG::RTMP_PRESET_NAME ;
  presetId   = CONFIG::FilterId(presetName) ;
  streamIdx  = CONFIG::RTMP_STREAM_IDX ;
  outputDest = String::empty ;
  createPreset() ;
}

LctvPresetSeed::LctvPresetSeed()
{
  presetName = CONFIG::LCTV_PRESET_NAME ;
  presetId   = CONFIG::FilterId(presetName) ;
  streamIdx  = CONFIG::RTMP_STREAM_IDX ;
  outputDest = String::empty ;
  createPreset() ;
}

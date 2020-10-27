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


#include "Constants.h"


const uint8 GST::MIN_MAJOR_VERSION = 1 ;
const uint8 GST::MIN_MINOR_VERSION = 6 ;

// NOTE: compositor inputs are either mutually exclusive (compositor disabled)
//           or must all be enabled (compositor enabled)
//       N_COMPOSITOR_INPUTS is coupled to the state of AvCaster::DisabledFeatures
const int GST::N_COMPOSITOR_INPUTS = 2 + !TEXT_BIN_NYI + !IMAGE_BIN_NYI ;

// element IDs
const String GST::PIPELINE_ID         = "pipeline" ;
const String GST::SCREENCAP_BIN_ID    = "screencap-bin" ;
const String GST::CAMERA_BIN_ID       = "camera-bin" ;
const String GST::TEXT_BIN_ID         = "text-bin" ;
const String GST::IMAGE_BIN_ID        = "interstitial-bin" ;
const String GST::COMPOSITOR_BIN_ID   = "compositor-bin" ;
const String GST::PREVIEW_BIN_ID      = "preview-bin" ;
const String GST::PREVIEW_SINK_ID     = "preview-real-sink" ;
const String GST::PREVIEW_FAUXSINK_ID = "preview-faux-sink" ;
const String GST::PREVIEW_SINKPAD_ID  = "preview-sinkpad" ;
const String GST::AUDIO_BIN_ID        = "audio-bin" ;
const String GST::MUXER_BIN_ID        = "muxer-bin" ;
const String GST::OUTPUT_BIN_ID       = "output-bin" ;
// plugin IDs
#if JUCE_LINUX
const String GST::SCREEN_PLUGIN_ID    = "ximagesrc" ;
const String GST::CAMERA_PLUGIN_ID    = "v4l2src" ;
const String GST::ALSA_PLUGIN_ID      = "alsasrc" ;
const String GST::PULSE_PLUGIN_ID     = "pulsesrc" ;
const String GST::JACK_PLUGIN_ID      = "jackaudiosrc" ;
const String GST::PREVIEW_PLUGIN_ID   = "xvimagesink" ;
#endif //JUCE_LINUX
const String GST::FAUXSRC_PLUGIN_ID   = "fakesrc" ;
const String GST::FAUXSINK_PLUGIN_ID  = "fakesink" ;
const String GST::TESTVIDEO_PLUGIN_ID = "videotestsrc" ;
const String GST::TESTAUDIO_PLUGIN_ID = "audiotestsrc" ;
const String GST::FILESINK_PLUGIN_ID  = "filesink" ;
const String GST::RTMPSINK_PLUGIN_ID  = "rtmpsink" ;

const String GST::LCTV_RTMP_URL = "rtmp://usmedia3.livecoding.tv:1935/livecodingtv/" ;

// library error messages
const String GST::ALSA_INIT_ERROR  = "Could not open audio device for recording. Device is being used by another application." ;
const String GST::PULSE_INIT_ERROR = "Failed to connect: Connection refused" ;
const String GST::JACK_INIT_ERROR  = "Jack server not found" ;
const String GST::XV_INIT_ERROR    = "Could not initialise Xv output" ;
const String GST::FILE_SINK_ERROR  = "No file name specified for writing." ;

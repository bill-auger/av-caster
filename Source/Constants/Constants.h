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


#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

// enable standard features
// #define DISABLE_MEDIA
// #define SCREEN_ONLY
// #define CAMERA_ONLY
// #define TEXT_ONLY
// #define IMAGE_ONLY
#define TRAY_ICON_NYI // TODO: requires juce_gui_extras package
#define TEXT_BIN_NYI  1
#define IMAGE_BIN_NYI 0 // faux src
#define DISABLE_GUI_CONFIG_NYI
#define DISABLE_AUDIO   (! JUCE_LINUX) // replace audio-real-source with fakesrc
#define DISABLE_PREVIEW (! JUCE_LINUX) // replace preview-sink with fakesink
//#define DISABLE_OUTPUT               // replace filesink or rtmpsink with fakesink
#define GST_COMPOSITOR_BUG
// #define NO_DYNAMIC_MEDIA_Z_ORDER
#define DISABLE_CHAT
#define SEED_IRC_NETWORKS ((!defined(DISABLE_CHAT)) && 0)
#define SUPRESS_GREETING_MESSAGES
#ifdef DEBUG
#  define SUPRESS_ALERTS
#endif // DEBUG
// #define CHATLIST_KICK_BTN_NYI

// debugging tweaks and kludges
#define INJECT_DEFAULT_CAMERA_DEVICE_INFO
#define FIX_OUTPUT_RESOLUTION_TO_LARGEST_INPUT
#define NATIVE_CAMERA_RESOLUTION_ONLY
// #define FAKE_MUX_ENCODER_SRC_AND_SINK // isolate compositor from encoder and muxer from output
// #define MOCK_CHAT_NICKS

// enable debug/tracing features
#ifdef DEBUG
#  define DEBUG_TRACE 1
#else // DEBUG
#  define DEBUG_TRACE 1
#endif // DEBUG
#define DEBUG_ANSI_COLORS           (DEBUG_TRACE && 1)
#define DEBUG_DUMP_CONFIG_VERBOSITY (DEBUG_TRACE &  0) /* 0 => none , 1 => nodes only , 2 => all */
#define DEBUG_DUMP_CONFIG_XML       (DEBUG_TRACE && 1)
#define DEBUG_QUIT_BEFORE_MAIN_LOOP 0
#define DEBUG_QUIT_AFTER_MAIN_LOOP  0


// configuration and runtime constants
#include "JuceHeader.h"
#include "AppConstants.h"
#include "GstConstants.h"
#include "IrcConstants.h"
#include "GuiConstants.h"
#include "ConfigConstants.h"

#endif // _CONSTANTS_H_

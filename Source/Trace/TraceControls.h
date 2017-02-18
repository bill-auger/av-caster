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


#ifndef _TRACECONTROLS_H_
#define _TRACECONTROLS_H_

#ifdef DEBUG_TRACE

#  include "Trace.h"


#  define DEBUG_TRACE_CONTROLS_LOAD_CONFIG                                                           \
  Trace::TraceGui("loading preset '" + STRING(this->configStore[CONFIG::PRESET_NAME_ID]) + "'") ;    \
  Trace::TraceGui(String("setting controls: ")                                                     + \
                 ((is_screen_active ) ? "screen, "  : "") + ((is_camera_active) ? "camera, " : "") + \
                 ((is_text_active   ) ? "text, "    : "") + ((is_image_active ) ? "image, "  : "") + \
                 ((is_preview_active) ? "preview, " : "") + ((is_audio_active ) ? "audio, "  : "") + \
                 ((is_output_active ) ? "output, "  : "") + "sink (" + String(sink_idx) + ")"    ) ; \
  DEBUG_TRACE_DUMP_CONFIG(this->configStore , "volatile")                                            ;

#else // DEBUG_TRACE

#  define DEBUG_TRACE_CONTROLS_LOAD_CONFIG ;

#endif // DEBUG_TRACE
#endif // _TRACECONTROLS_H_

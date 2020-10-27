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


#ifndef _TRACE_H_
#define _TRACE_H_

#include "JuceHeader.h"
#include "../Constants/Constants.h"


#define DEBUG_TRACE_EVENTS    (DEBUG_TRACE && 1)
#define DEBUG_TRACE_GUI       (DEBUG_TRACE && 1)
#define DEBUG_TRACE_GUI_VB    (DEBUG_TRACE && 0)
#define DEBUG_TRACE_MEDIA     (DEBUG_TRACE && 1)
#define DEBUG_TRACE_MEDIA_VB  (DEBUG_TRACE && 0)
#define DEBUG_TRACE_CONFIG    (DEBUG_TRACE && 1)
#define DEBUG_TRACE_CONFIG_VB (DEBUG_TRACE && 0)
#define DEBUG_TRACE_CHAT      (DEBUG_TRACE && 1)
#define DEBUG_TRACE_CHAT_VB   (DEBUG_TRACE && 0)
#define DEBUG_TRACE_STATE     (DEBUG_TRACE && 1)
#define DEBUG_TRACE_WARNINGS  (DEBUG_TRACE && 0)
#define DEBUG_TRACE_ERRORS    (DEBUG_TRACE && 1)

#if DEBUG_ANSI_COLORS
#  define CGREEN  String("\033[1;32m")
#  define CYELLOW String("\033[1;33m")
#  define CRED    String("\033[0;31m")
#  define CBLUE   String("\033[1;34m")
#  define CEND    String("\033[0m"   )
#else // DEBUG_ANSI_COLORS
#  define CGREEN  String()
#  define CYELLOW String()
#  define CRED    String()
#  define CBLUE   String()
#  define CEND    String()
#endif // DEBUG_ANSI_COLORS

#define LOG(msg) Logger::outputDebugString(msg)

#ifdef DEBUG_TRACE

#  undef DBG
#  define DBG(msg) Trace::TraceDebug(msg)

#  define DEBUG_TRACE_DUMP_CONFIG(config_store , node_desc)                                      \
  Trace::TraceConfigVb("dumping "     + String((DEBUG_DUMP_CONFIG_VERBOSITY > 0) ? "verbose" :   \
                                                                                   "terse"   ) + \
                       " config per " + String(__FUNCTION__) + "()") ;                           \
  Trace::DumpConfig(config_store , node_desc)                                                    ;

#  define DEBUG_TRACE_DUMP_CONFIG_XML(config_node , node_desc) \
  Trace::WriteConfigXml(config_node , node_desc)               ;


class Trace
{
public:

  static void EnableTracing(bool should_enable) ;

  static void TraceEvent   (String msg) ;
  static void TraceGui     (String msg) ;
  static void TraceGuiVb   (String msg) ;
  static void TraceMedia   (String msg) ;
  static void TraceMediaVb (String msg) ;
  static void TraceConfig  (String msg) ;
  static void TraceConfigVb(String msg) ;
  static void TraceChat    (String msg) ;
  static void TraceChatVb  (String msg) ;
  static void TraceState   (String msg) ;
  static void TraceWarning (String msg) ;
  static void TraceError   (String msg) ;
  static void TraceDebug   (String msg) ;

  static void TraceMissingNode    (ValueTree config_store , Identifier a_node_id) ;
  static void TraceMissingProperty(ValueTree config_store    , Identifier a_property_id ,
                                   var       a_default_value                            ) ;
  static void DumpConfig          (ValueTree config_store , String node_desc) ;
  static void WriteConfigXml      (ValueTree config_node , String node_desc) ;

  static String VarType          (var a_var) ;
  static void   TraceTreeChanged (ValueTree& a_node , const Identifier& a_key) ;
  static void   TraceValueChanged(Value& a_value , String name) ;
  static String TraceSetValue    (ValueTree a_node , const Identifier& a_key , var a_value) ;


  static bool EventEnabled ;
  static bool GuiEnabled ;
  static bool GuiVbEnabled ;
  static bool MediaEnabled ;
  static bool MediaVbEnabled  ;
  static bool ConfigEnabled ;
  static bool ConfigVbEnabled ;
  static bool ChatEnabled ;
  static bool ChatVbEnabled ;
  static bool StateEnabled ;
  static bool WarningsEnabled ;
  static bool ErrorsEnabled ;
} ;

#else // DEBUG_TRACE

#  define DEBUG_TRACE_DUMP_CONFIG(config_store , node_desc)    ;
#  define DEBUG_TRACE_DUMP_CONFIG_XML(config_node , node_desc) ;

#endif // DEBUG_TRACE

#endif // _TRACE_H_

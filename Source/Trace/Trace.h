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


#ifndef _TRACE_H_
#define _TRACE_H_

#include "JuceHeader.h"
#include "../Constants/Constants.h"


#ifdef DEBUG_TRACE

#  define LOG(msg) Logger::outputDebugString(msg)

#  define DEBUG_TRACE_DUMP_CONFIG(config_store , node_desc)                                       \
  Trace::TraceConfigVb("dumping "     + String((!!DUMP_CONFIG_VERBOSITY) ? "verbose" : "terse") + \
                       " config per " + String(__FUNCTION__) + "()") ;                            \
  Trace::DumpConfig(config_store , node_desc)                                                    ;

#  define DEBUG_TRACE_DUMP_CONFIG_XML(config_node , node_desc)                                     \
  Trace::TraceConfig("writing config XML to file 'config-dump.xml' per " + String(__FUNCTION__)) ; \
  XmlElement* xml = root_clone.createXml() ;                                                       \
  xml->writeToFile(File("config-dump.xml") , StringRef()) ; delete xml                                    ;


class Trace
{
public:

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

  static void TraceMissingNode    (ValueTree config_store , Identifier a_node_id) ;
  static void TraceMissingProperty(ValueTree config_store    , Identifier a_property_id ,
                                   var       a_default_value                            ) ;
  static void DumpConfig          (ValueTree config_store , String node_desc) ;

  static String VarType          (var a_var) ;
  static void   TraceTreeChanged (ValueTree& a_node , const Identifier& a_key) ;
  static void   TraceValueChanged(Value& a_value , String name) ;
  static String TraceSetValue    (ValueTree a_node , const Identifier& a_key , var a_value) ;
} ;

#endif // DEBUG_TRACE

#endif // _TRACE_H_

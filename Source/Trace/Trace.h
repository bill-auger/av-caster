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
#include "../Constants.h"


#ifdef DEBUG_TRACE

#define LOG(msg) Logger::outputDebugString(msg)


class Trace
{
public:

  static void TraceEvent          (String msg) ;
  static void TraceGui            (String msg) ;
  static void TraceMedia          (String msg) ;
  static void TraceConfig         (String msg) ;
  static void TraceChat           (String msg) ;
  static void TraceVerbose        (String msg) ;
  static void TraceState          (String msg) ;
  static void TraceWarning        (String msg) ;
  static void TraceError          (String msg) ;
  static void TraceMissingNode    (ValueTree config_store , Identifier a_node_id) ;
  static void TraceMissingProperty(ValueTree config_store    , Identifier a_property_id ,
                                   var       a_default_value                            ) ;
  static void DumpConfig          (ValueTree config_store , String node_desc) ;
} ;

#endif // DEBUG_TRACE

#endif // _TRACE_H_

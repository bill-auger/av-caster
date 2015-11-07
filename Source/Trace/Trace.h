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


#ifndef TRACE_H_INCLUDED
#define TRACE_H_INCLUDED

#include "JuceHeader.h"
#include "../Constants.h"


#ifdef DEBUG

class Trace
{
public:

  static bool TraceEvent          (String msg) ;
  static bool TraceGui            (String msg) ;
  static bool TraceMedia          (String msg) ;
  static bool TraceConfig         (String msg) ;
  static bool TraceVerbose        (String msg) ;
  static bool TraceState          (String msg) ;
  static bool TraceWarning        (String msg) ;
  static bool TraceError          (String msg) ;
  static void TraceMissingNode    (ValueTree config_store , Identifier a_node_id) ;
  static void TraceMissingProperty(ValueTree config_store    , Identifier a_property_id ,
                                   var       a_default_value                            ) ;
  static void DumpConfig          (ValueTree config_store , String node_desc) ;
} ;

#endif // DEBUG

#endif // TRACE_H_INCLUDED

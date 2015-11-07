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


#include "Trace.h"
#include "../AvCaster.h"

#ifdef DEBUG

/* Trace class public class methods */

bool Trace::TraceEvent  (String msg) { if (DEBUG_TRACE_EVENTS) DBG(          "[EVENT]:   " + msg) ; return true ; }
bool Trace::TraceGui    (String msg) { if (DEBUG_TRACE_GUI   ) DBG(          "[GUI]:     " + msg) ; return true ; }
bool Trace::TraceMedia  (String msg) { if (DEBUG_TRACE_MEDIA ) DBG(          "[MEDIA]:   " + msg) ; return true ; }
bool Trace::TraceConfig (String msg) { if (DEBUG_TRACE_CONFIG) DBG(          "[CONFIG]:  " + msg) ; return true ; }
bool Trace::TraceVerbose(String msg) { if (DEBUG_TRACE_VB    ) DBG(          "[DEBUG]:   " + msg) ; return true ; }
#  if ! DEBUG_ANSI_COLORS
bool Trace::TraceState  (String msg) { if (DEBUG_TRACE_STATE)  DBG(          "[STATE]:   " + msg) ; return true ; }
bool Trace::TraceWarning(String msg) { if (DEBUG_TRACE_STATE)  DBG(          "[WARNING]: " + msg) ; return true ; }
bool Trace::TraceError  (String msg) { if (DEBUG_TRACE_STATE)  DBG(          "[ERROR]:   " + msg) ; return true ; }
#  else // DEBUG_ANSI_COLORS
bool Trace::TraceState  (String msg) { if (DEBUG_TRACE_STATE)  DBG("\033[1;32m[STATE]:   " + msg + "\033[0m") ; return true ; }
bool Trace::TraceWarning(String msg) { if (DEBUG_TRACE_STATE)  DBG("\033[1;33m[WARNING]: " + msg + "\033[0m") ; return true ; }
bool Trace::TraceError  (String msg) { if (DEBUG_TRACE_STATE)  DBG("\033[0;31m[ERROR]:   " + msg + "\033[0m") ; return true ; }
#  endif // DEBUG_ANSI_COLORS

void Trace::TraceMissingNode(ValueTree config_store , Identifier a_node_id)
{
  if (!config_store.getChildWithName(a_node_id).isValid())
    Trace::TraceConfig("missing node - adding '" + String(a_node_id) + "'") ;
}

void Trace::TraceMissingProperty(ValueTree config_store    , Identifier a_property_id ,
                                 var       a_default_value                            )
{
  // supress transient nodes
  if (a_property_id == CONFIG::IS_CONFIG_PENDING_ID) return ;

  if (!config_store.hasProperty(a_property_id))
    Trace::TraceConfig("missing property of '"       + String(config_store.getType())     +
                       "' - restoring default for '" + String(a_property_id)   + "' => '" +
                                                       STRING(a_default_value) + "'"      ) ;
}

void Trace::DumpConfig(ValueTree config_store , String node_desc)
{
  if (config_store.isValid())
  {
    Identifier node_name    = config_store.getType() ;
    int        n_properties = config_store.getNumProperties() ;

    String pad = "  " ;
    String dbg = String("config dump " + node_desc + " =>\n") + pad  +
                 "node => "            + String(node_name)           +
                 " (properties: "      + String(n_properties) + ")"  ;

    for (int property_n = 0 ; property_n < n_properties ; ++property_n)
    {
      Identifier key          = config_store.getPropertyName(property_n) ;
      var        stored_value = config_store.getProperty(key , "n/a") ;
      dbg += "\n" + pad + "  key => "             + String(key)             +
             "\n" + pad + "    stored_value  => " + stored_value.toString() ;
    }

    Trace::TraceConfig(dbg) ;
  }
  else Trace::TraceError("stored config invalid - will not store") ;
}

#endif // DEBUG

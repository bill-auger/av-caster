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


#include "Trace.h"
#include "../AvCaster.h"

#ifdef DEBUG_TRACE


/* Trace class public class methods */

void Trace::TraceEvent  (String msg) { if (DEBUG_TRACE_EVENTS) LOG(          "[EVENT]:   " + msg) ;               }
void Trace::TraceGui    (String msg) { if (DEBUG_TRACE_GUI   ) LOG(          "[GUI]:     " + msg) ;               }
void Trace::TraceMedia  (String msg) { if (DEBUG_TRACE_MEDIA ) LOG(          "[MEDIA]:   " + msg) ;               }
void Trace::TraceConfig (String msg) { if (DEBUG_TRACE_CONFIG) LOG(          "[CONFIG]:  " + msg) ;               }
void Trace::TraceChat   (String msg) { if (DEBUG_TRACE_CHAT  ) LOG(          "[CHAT]:    " + msg) ;               }
void Trace::TraceVerbose(String msg) { if (DEBUG_TRACE_VB    ) LOG(          "[DEBUG]:   " + msg) ;               }
#  if ! DEBUG_ANSI_COLORS
void Trace::TraceState  (String msg) { if (DEBUG_TRACE_STATE)  LOG(          "[STATE]:   " + msg) ;               }
void Trace::TraceWarning(String msg) { if (DEBUG_TRACE_STATE)  LOG(          "[WARNING]: " + msg) ;               }
void Trace::TraceError  (String msg) { if (DEBUG_TRACE_STATE)  LOG(          "[ERROR]:   " + msg) ;               }
#  else // DEBUG_ANSI_COLORS
void Trace::TraceState  (String msg) { if (DEBUG_TRACE_STATE)  LOG("\033[1;32m[STATE]:   " + msg + "\033[0m") ;   }
void Trace::TraceWarning(String msg) { if (DEBUG_TRACE_STATE)  LOG("\033[1;33m[WARNING]: " + msg + "\033[0m") ;   }
void Trace::TraceError  (String msg) { if (DEBUG_TRACE_STATE)  LOG("\033[0;31m[ERROR]:   " + msg + "\033[0m") ;   }
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
  if (a_property_id == CONFIG::IS_PENDING_ID ||
      a_property_id == CONFIG::OUTPUT_ID      ) return ;

  if (!config_store.hasProperty(a_property_id))
  {
    Trace::TraceConfig("missing property of '"       + String(config_store.getType())     +
                       "' - restoring default for '" + String(a_property_id)   + "' => '" +
                                                       STRING(a_default_value) + "'"      ) ;
    DumpConfig(config_store , "missing property ") ;
  }
}

void Trace::DumpConfig(ValueTree config_store , String node_desc)
{
  if (!DEBUG_TRACE_VB) return ;

  if (!config_store.isValid())
  { Trace::TraceError("Trace::DumpConfig() - invalid node") ; return ; }

  String node_name    = String(config_store.getType()) ;
  int    n_properties =        config_store.getNumProperties() ;
  int    n_children   =        config_store.getNumChildren() ;

  String pad = "  " ;
  String dbg = String("dump node '" + node_desc            + "' =>\n") + pad +
               "node => "           + node_name                              +
               " (properties: "     + String(n_properties) + ")"             +
               " (children: "       + String(n_children)   + ")"             ;

  for (int property_n = 0 ; property_n < n_properties ; ++property_n)
  {
    Identifier key          = config_store.getPropertyName(property_n) ;
    var        stored_value = config_store.getProperty(key , "n/a") ;
    dbg += "\n" + pad + "  key => "             + String(key)             +
            "\n" + pad + "    stored_value  => " + stored_value.toString() ;
  }

  Trace::TraceConfig(dbg) ;

  for (int child_n = 0 ; child_n < n_children ; ++child_n)
  {
    ValueTree child_node      = config_store.getChild(child_n) ;
    String    child_node_desc = node_name + "[" + String(child_n) + "] ('" +
                                String(child_node.getType()) + "')"        ;
    DumpConfig(child_node , child_node_desc) ;
  }
}

#endif // DEBUG_TRACE

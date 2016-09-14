/*\
|*|  Copyright 2015-2016 bill-auger <https://github.com/bill-auger/av-caster/issues>
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


#include "Trace.h"
#include "../Controllers/AvCaster.h"

#ifdef DEBUG_TRACE


/* Trace class public class methods */

void Trace::TraceEvent   (String msg) { if (DEBUG_TRACE_EVENTS   ) LOG(          "[EVENT]:   " + msg) ;               }
void Trace::TraceGui     (String msg) { if (DEBUG_TRACE_GUI      ) LOG(          "[GUI]:     " + msg) ;               }
void Trace::TraceGuiVb   (String msg) { if (DEBUG_TRACE_GUI_VB   ) LOG(          "[GUI]:     " + msg) ;               }
void Trace::TraceMedia   (String msg) { if (DEBUG_TRACE_MEDIA    ) LOG(          "[MEDIA]:   " + msg) ;               }
void Trace::TraceMediaVb (String msg) { if (DEBUG_TRACE_MEDIA_VB ) LOG(          "[MEDIA]:   " + msg) ;               }
void Trace::TraceConfig  (String msg) { if (DEBUG_TRACE_CONFIG   ) LOG(          "[CONFIG]:  " + msg) ;               }
void Trace::TraceConfigVb(String msg) { if (DEBUG_TRACE_CONFIG_VB) LOG(          "[CONFIG]:  " + msg) ;               }
void Trace::TraceChat    (String msg) { if (DEBUG_TRACE_CHAT     ) LOG(          "[CHAT]:    " + msg) ;               }
void Trace::TraceChatVb  (String msg) { if (DEBUG_TRACE_CHAT_VB  ) LOG(          "[CHAT]:    " + msg) ;               }
#  if ! DEBUG_ANSI_COLORS
void Trace::TraceState   (String msg) { if (DEBUG_TRACE_STATE    ) LOG(          "[STATE]:   " + msg) ;               }
void Trace::TraceWarning (String msg) { if (DEBUG_TRACE_STATE    ) LOG(          "[WARNING]: " + msg) ;               }
void Trace::TraceError   (String msg) { if (DEBUG_TRACE_STATE    ) LOG(          "[ERROR]:   " + msg) ;               }
#  else // DEBUG_ANSI_COLORS
void Trace::TraceState   (String msg) { if (DEBUG_TRACE_STATE    ) LOG("\033[1;32m[STATE]:   " + msg + "\033[0m") ;   }
void Trace::TraceWarning (String msg) { if (DEBUG_TRACE_STATE    ) LOG("\033[1;33m[WARNING]: " + msg + "\033[0m") ;   }
void Trace::TraceError   (String msg) { if (DEBUG_TRACE_STATE    ) LOG("\033[0;31m[ERROR]:   " + msg + "\033[0m") ;   }
void Trace::TraceDebug   (String msg) {                            LOG("\033[1;33m[DEBUG]:   " + msg + "\033[0m") ;   }
#  endif // DEBUG_ANSI_COLORS

void Trace::TraceMissingNode(ValueTree config_store , Identifier a_node_id)
{
  if (!config_store.getChildWithName(a_node_id).isValid())
    Trace::TraceConfig("missing node of '" + STRING(config_store.getType())      +
                       "' - adding '"      + STRING(a_node_id             ) + "'") ;
}

void Trace::TraceMissingProperty(ValueTree config_store    , Identifier a_property_id ,
                                 var       a_default_value                            )
{
  if (!config_store.hasProperty(a_property_id))
  {
    Trace::TraceConfig("missing property of '"       + STRING(config_store.getType())     +
                       "' - restoring default for '" + STRING(a_property_id)   + "' => '" +
                                                       STRING(a_default_value) + "'"      ) ;
    DEBUG_TRACE_DUMP_CONFIG(config_store , "missing property ") ;
  }
}

void Trace::DumpConfig(ValueTree config_store , String node_desc)
{
#if (DUMP_CONFIG_VERBOSITY < 1)
  return ;
#endif // DUMP_CONFIG_VERBOSITY

  if (!config_store.isValid())
  { Trace::TraceError("Trace::DumpConfig() - invalid node: " + node_desc) ; return ; }

  String node_name    = STRING(config_store.getType()) ;
  int    n_properties =        config_store.getNumProperties() ;
  int    n_children   =        config_store.getNumChildren() ;

  String pad = "  " ;
  String dbg = String("dumping node: " + node_desc            + " =>\n") + pad +
               "node => "              + node_name                             +
               " (properties: "        + String(n_properties) + ")"            +
               " (children: "          + String(n_children)   + ")"            ;

#if (DUMP_CONFIG_VERBOSITY >= 2)
  for (int property_n = 0 ; property_n < n_properties ; ++property_n)
  {
    Identifier key          = config_store.getPropertyName(property_n) ;
    var        stored_value = config_store.getProperty(key , "n/a") ;
    dbg += "\n" + pad + "  key => "             + STRING(key)             +
           "\n" + pad + "    stored_value  => " + stored_value.toString() ;
  }
#endif // DUMP_CONFIG_VERBOSITY

  Trace::TraceConfig(dbg) ;

  for (int child_n = 0 ; child_n < n_children ; ++child_n)
  {
    ValueTree child_node      = config_store.getChild(child_n) ;
    String    child_id        = STRING(child_node.getType()) ;
    String    child_node_desc = String("'") + node_name + "[" + String(child_n) +
                                "]] ('"     + child_id  + "')"                  ;
    DumpConfig(child_node , child_node_desc) ;
  }
}

void Trace::WriteConfigXml(ValueTree config_node , String node_desc)
{
#ifdef DUMP_CONFIG_XML
  return ;
#endif // DUMP_CONFIG_XML

  String      file_name = "config-dump-" + node_desc + ".xml" ;
  XmlElement* xml       = config_node.createXml() ;

  xml->writeToFile(File(file_name) , StringRef()) ; delete xml ;
  Trace::TraceConfig("wrote config XML to file '" + file_name           +
                     "' per "                     + String(__FUNCTION__)) ;
}

String Trace::VarType(var a_var) // juce var dynamic datatypes
{
  return (a_var.isVoid()      ) ? "void"      :
         (a_var.isUndefined() ) ? "undefined" :
         (a_var.isInt()       ) ? "int"       :
         (a_var.isInt64()     ) ? "int64"     :
         (a_var.isBool()      ) ? "bool"      :
         (a_var.isDouble()    ) ? "double"    :
         (a_var.isString()    ) ? "string"    :
         (a_var.isObject()    ) ? "object"    :
         (a_var.isArray()     ) ? "array"     :
         (a_var.isBinaryData()) ? "binary"    :
         (a_var.isMethod()    ) ? "method"    :
                                  "unknown"   ;
}

void Trace::TraceTreeChanged(ValueTree& a_node , const Identifier& a_key)
{
  String parent_id = STRING(a_node.getParent().getType()) ;
  String node_id   = parent_id + ((parent_id.isEmpty()) ? "" : "::") + STRING(a_node.getType()) ;
  String var_type  = VarType(a_node[a_key]) ;
  String a_value   = STRING(a_node[a_key]).upToFirstOccurrenceOf("?" , true  , true) ;
  if (a_key == CONFIG::OUTPUT_DEST_ID && a_value.containsChar('?')) a_value += "...'" ;

  Trace::TraceEvent("value changed for tree " + node_id  + "['" + STRING(a_key) +
                    "'] => ("                 + var_type + ")'" + a_value       + "'" ) ;
}

void Trace::TraceValueChanged(Value& a_value , String name)
{
  Trace::TraceEvent("value changed for '"   + name            + "' => (" +
                    VarType(a_value) + ")'" + STRING(a_value) + "'"      ) ;
}

String Trace::TraceSetValue(ValueTree a_node , const Identifier& a_key , var a_value)
{
  String prev_type  = Trace::VarType(a_node[a_key]) ;
  String next_type  = Trace::VarType(a_value      ) ;
  String node_id    = (a_node.isValid()) ? STRING(a_node.getType()) : String("NULL") ;
  String prev_val   = (a_node.isValid()) ? STRING(a_node[a_key]   ) : String("NULL") ;
  String next_val   = STRING(a_value) ;
  String key        = (a_key .isValid()) ? STRING(a_key           ) : String("NULL") ;
  String change_msg = "key "               + node_id   + "['"  + key      +
                      "'] changing from (" + prev_type + ")'"  + prev_val +
                      "' to ("             + next_type + ")'"  + next_val + "'" ;

  return (next_type != prev_type || next_val != prev_val) ? change_msg : String::empty ;
}

#endif // DEBUG_TRACE

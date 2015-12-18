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


#ifndef _TRACEAVCASTERSTORE_H_
#define _TRACEAVCASTERSTORE_H_

#ifdef DEBUG

#  include "Trace.h"


/* persistence */

#  define DEBUG_TRACE_VERIFY_CONFIG                                                             \
  String success_msg   = "stored config parsed successfully v" + String(stored_version) ;    \
  String not_found_msg = "stored config not found - restoring defaults" ;                    \
  String invalid_msg   = "stored config invalid - restoring defaults" ;                      \
  String upgraded_msg  = "upgrading config version to v" + String(CONFIG::CONFIG_VERSION) ;  \
  String outdated_msg  = "stored config backed up - schema changed - restoring defaults" ;   \
  Trace::TraceConfig("looking for stored config at " + this->configFile.getFullPathName()) ; \
  Trace::TraceConfig(((!stored_config.isValid()            ) ? not_found_msg :               \
                     ((!stored_config.hasType(root_node_id)) ? invalid_msg   :               \
                     ((!do_versions_match                  ) ? outdated_msg  :               \
                                                               success_msg))))               ;

#  define DEBUG_TRACE_VERIFY_PRESETS_NODE                  \
  Trace::TraceMissingNode(this->root , CONFIG::PRESETS_ID) ;

#  define DEBUG_TRACE_VERIFY_SERVERS_NODE                  \
  Trace::TraceMissingNode(this->root , CONFIG::SERVERS_ID) ;

#  define DEBUG_TRACE_VERIFY_CONFIG_ROOT                                   \
  if (!this->root.isValid()) Trace::TraceError("invalid config root node") ;

#  define DEBUG_TRACE_VERIFY_CONFIG_PRESETS                                      \
  if (!this->presets.isValid()) Trace::TraceError("invalid config presets node") ;

#  define DEBUG_TRACE_VERIFY_CONFIG_PRESET                              \
  if (!this->config.isValid()) Trace::TraceError("invalid preset node") ;

#  define DEBUG_TRACE_VERIFY_SERVERS                                      \
  if (!this->servers.isValid()) Trace::TraceError("invalid servers node") ;

#  define DEBUG_TRACE_VERIFY_SERVER_IN                                   \
  if (!a_server_node.isValid()) Trace::TraceError("invalid server node") ;

#  define DEBUG_TRACE_VERIFY_SERVER_OUT                               \
  String node_id = String(a_server_node.getType()) ;                  \
  if (!a_server_node.getParent().isValid())                           \
    Trace::TraceError("pruned corrupt server node '" + node_id + "'") ;

#  define DEBUG_TRACE_VERIFY_CONFIG_PROPERTY                          \
  Trace::TraceMissingProperty(config_store , a_key , a_default_value) ;

#  define DEBUG_TRACE_SANITIZE_CONFIG_INT_PROPERTY                                       \
  String node_id = String(config_store.getType()) ; String property_id = String(a_key) ; \
  if (a_value < min_value || a_value > max_value)                                        \
    Trace::TraceConfig("value out of range for property of '" + node_id          +       \
                       "' - removing '"                       + property_id + "'")       ;

#  define DEBUG_TRACE_DUMP_CONFIG_ROOT     Trace::DumpConfig(this->root    , "root"    ) ;
#  define DEBUG_TRACE_DUMP_CONFIG_PRESETS  Trace::DumpConfig(this->presets , "presets" ) ;
#  define DEBUG_TRACE_DUMP_CONFIG_SERVERS  Trace::DumpConfig(this->servers , "servers" ) ;
#  define DEBUG_TRACE_DUMP_CONFIG_VOLATILE Trace::DumpConfig(this->config  , "volatile") ;
#  define DEBUG_TRACE_DUMP_CONFIG_CAMERAS  Trace::DumpConfig(this->cameras , "cameras" ) ;
#  define DEBUG_TRACE_DUMP_CONFIG_AUDIOS   Trace::DumpConfig(this->audios  , "audios"  ) ;

# define DEBUG_TRACE_DUMP_CONFIG(method_name)                    \
  Trace::TraceVerbose(String(method_name) + " dumping config") ; \
  DEBUG_TRACE_DUMP_CONFIG_ROOT                                   \
  DEBUG_TRACE_DUMP_CONFIG_PRESETS                                \
  DEBUG_TRACE_DUMP_CONFIG_SERVERS                                \
  DEBUG_TRACE_DUMP_CONFIG_VOLATILE                               \
  DEBUG_TRACE_DUMP_CONFIG_CAMERAS                                \
  DEBUG_TRACE_DUMP_CONFIG_AUDIOS

#  define DEBUG_TRACE_STORE_CONFIG                                                      \
  String file_path = this->configFile.getFullPathName() ;                               \
  if (!this->root.isValid()) Trace::TraceError("stored config invalid - not storing") ; \
  else                       Trace::TraceConfig("storing config to " + file_path)       ;

#  define DEBUG_TRACE_STORE_SERVER                                              \
  Trace::TraceConfig("creating storage for IRC server '" +                      \
                     host + ":" + String(port) + "' channel '" + channel + "'") ;


/* maintenance */

#  define DEBUG_TRACE_CONFIG_TREE_CHANGED                                                \
  String parent_id = String(a_node.getParent().getType()) ;                              \
  String node_id   = String(a_node.getType()) ;                                          \
  String key       = String(a_key) ;                                                     \
  String val       = STRING(a_node[a_key]) ;                                             \
  Trace::TraceEvent("value changed for " + node_id + "['" + key + "'] => '" + val + "'") ;

#  define DEBUG_TRACE_DETECT_CAPTURE_DEVICES                                     \
  bool is_bogus_cam = cameras.getChild(0).getType() == Identifier("bogus-cam") ; \
  String n_devices = String((is_bogus_cam) ? 0                       :           \
                                             cameras.getNumChildren()) ;         \
  Trace::TraceState("detected (" + n_devices + ") capture devices")              ;

#  define DEBUG_TRACE_STORE_PRESET                                 \
  Trace::TraceConfig("storing preset[" + String(preset_idx) +      \
                     "] '"             + preset_name        + "'") ;

#  define DEBUG_TRACE_RENAME_PRESET                                        \
  Trace::TraceConfig("renaming preset[" + String(preset_idx)        +      \
                     "] from '"         + AvCaster::GetPresetName() +      \
                     "' to '"           + preset_name               + "'") ;

#  define DEBUG_TRACE_DELETE_PRESET                                        \
  Trace::TraceConfig("deleting preset[" + String(preset_idx)             + \
                     "] '"              + AvCaster::GetPresetName() + "'") ;

#  define DEBUG_TRACE_TOGGLE_CONTROL                                          \
  Trace::TraceConfig("error re-configuring media - reverting control toggle") ;

#  define DEBUG_TRACE_SET_CONFIG                                              \
  String    key        = (a_key.isValid()) ? String(a_key) : String("NULL") ; \
  ValueTree node       = getKeyNode(a_key) ;                                  \
  String    change_msg = "key '"             + key                 +          \
                         "' changing from '" + STRING(node[a_key]) +          \
                         "' to '"            + STRING(a_value    ) + "'" ;    \
  Trace::TraceVerbose("config " + change_msg) ;

#  define DEBUG_TRACE_UPDATE_IRC_HOST                                                     \
  if (server_store.isValid())                                                             \
    Trace::TraceConfig("updating " + alias_uris[alias_n] + " host '" + actual_host + "'") ;

#  define DEBUG_TRACE_UPDATE_CHAT_NICKS                                                          \
  String dbg = " invalid updating chatters" ;                                                    \
  if      (!server_store  .isValid())   Trace::TraceError("server_store " + dbg) ;               \
  else if (!chatters_store.isValid()) { Trace::TraceError("chatters_store" + dbg) ;              \
                                        Trace::DumpConfig(server_store , "chatters invalid") ; } \
  else DEBUG_TRACE_DUMP_CHAT_NICKS(chatters_store)

#  define DEBUG_TRACE_ADD_CHAT_NICK                                                   \
  Identifier server_id = server_store.getType() ;                                     \
    Trace::TraceConfig("adding chatter '" + String(user_id)   + "' (" + *nick + ")" + \
                       " from '"          + String(server_id) + "' (" + host  + ")" ) ;

#  define DEBUG_TRACE_REMOVE_CHAT_NICK                                     \
  String userid = String(chatter_store.getType()) ;                        \
  if (!nicks.contains(nick))                                               \
    Trace::TraceConfig("removing chatter '" + userid + "' (" + nick + ")") ;

#  define DEBUG_TRACE_DUMP_CHAT_NICKS(chatters_store) if (DEBUG_TRACE_VB)           \
  {                                                                                 \
    Identifier server_id = chatters_store.getParent().getType() ;                   \
    Trace::TraceConfig(String("dumping (") + String(nicks.size()) + ") '"       +   \
                       String(server_id)                          + "' nicks=[" +   \
                       nicks.joinIntoString(",")                  + "]"         ) ; \
  }

#else // DEBUG

#  define DEBUG_TRACE_VERIFY_CONFIG                     ;
#  define DEBUG_TRACE_VERIFY_PRESETS_NODE               ;
#  define DEBUG_TRACE_VERIFY_SERVERS_NODE               ;
#  define DEBUG_TRACE_VERIFY_CONFIG_ROOT                ;
#  define DEBUG_TRACE_VERIFY_CONFIG_PRESETS             ;
#  define DEBUG_TRACE_VERIFY_CONFIG_PRESET              ;
#  define DEBUG_TRACE_VERIFY_SERVERS                    ;
#  define DEBUG_TRACE_VERIFY_SERVER_IN                  ;
#  define DEBUG_TRACE_VERIFY_SERVER_OUT                 ;
#  define DEBUG_TRACE_VERIFY_CONFIG_PROPERTY            ;
#  define DEBUG_TRACE_SANITIZE_CONFIG_INT_PROPERTY      ;
#  define DEBUG_TRACE_DUMP_CONFIG_ROOT                  ;
#  define DEBUG_TRACE_DUMP_CONFIG_PRESETS               ;
#  define DEBUG_TRACE_DUMP_CONFIG_SERVERS               ;
#  define DEBUG_TRACE_DUMP_CONFIG_VOLATILE              ;
#  define DEBUG_TRACE_DUMP_CONFIG_CAMERAS               ;
#  define DEBUG_TRACE_DUMP_CONFIG_AUDIOS                ;
#  define DEBUG_TRACE_DUMP_CONFIG(method_name)          ;
#  define DEBUG_TRACE_STORE_CONFIG                      ;
#  define DEBUG_TRACE_STORE_SERVER                      ;
#  define DEBUG_TRACE_CONFIG_TREE_CHANGED               ;
#  define DEBUG_TRACE_DETECT_CAPTURE_DEVICES            ;
#  define DEBUG_TRACE_STORE_PRESET                      ;
#  define DEBUG_TRACE_RENAME_PRESET                     ;
#  define DEBUG_TRACE_DELETE_PRESET                     ;
#  define DEBUG_TRACE_TOGGLE_CONTROL                    ;
#  define DEBUG_TRACE_SET_CONFIG                        ;
#  define DEBUG_TRACE_UPDATE_IRC_HOST                   ;
#  define DEBUG_TRACE_UPDATE_CHAT_NICKS                 ;
#  define DEBUG_TRACE_ADD_CHAT_NICK                     ;
#  define DEBUG_TRACE_REMOVE_CHAT_NICK                  ;
#  define DEBUG_TRACE_DUMP_CHAT_NICKS(chatters_store)   ;

#endif // DEBUG
#endif // _TRACEAVCASTERSTORE_H_

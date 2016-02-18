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


#ifndef _TRACEAVCASTERSTORE_H_
#define _TRACEAVCASTERSTORE_H_

#ifdef DEBUG_TRACE

#  include "Trace.h"


/* persistence */

#  define DEBUG_TRACE_VERIFY_CONFIG                                                          \
  String success_msg   = "stored config parsed successfully v" + String(stored_version) ;    \
  String not_found_msg = "stored config not found - restoring defaults" ;                    \
  String invalid_msg   = "stored config invalid - restoring defaults" ;                      \
  String upgraded_msg  = "upgrading config version to v" + String(CONFIG::CONFIG_VERSION) ;  \
  String outdated_msg  = "stored config backed up - schema changed - restoring defaults" ;   \
  Trace::TraceConfig("looking for stored config at " + this->configFile.getFullPathName()) ; \
  Trace::TraceConfig(((!stored_config.isValid()                  ) ? not_found_msg :         \
                     ((!stored_config.hasType(CONFIG::STORAGE_ID)) ? invalid_msg   :         \
                     ((!do_versions_match                        ) ? outdated_msg  :         \
                                                                     success_msg))))         ;

#  define DEBUG_TRACE_VERIFY_PRESETS_NODE                  \
  Trace::TraceMissingNode(this->root , CONFIG::PRESETS_ID) ;

#  define DEBUG_TRACE_VERIFY_NETWORKS_NODE                  \
  Trace::TraceMissingNode(this->root , CONFIG::NETWORKS_ID) ;

#  define DEBUG_TRACE_VERIFY_CONFIG_ROOT                                   \
  if (!this->root.isValid()) Trace::TraceError("invalid config root node") ;

#  define DEBUG_TRACE_VERIFY_CONFIG_PRESETS                                      \
  if (!this->presets.isValid()) Trace::TraceError("invalid config presets node") ;

#  define DEBUG_TRACE_VERIFY_CONFIG_PRESET                              \
  if (!this->config.isValid()) Trace::TraceError("invalid preset node") ;

#  define DEBUG_TRACE_VERIFY_NETWORKS                                       \
  if (!this->networks.isValid()) Trace::TraceError("invalid networks node") ;

#  define DEBUG_TRACE_VERIFY_NETWORK_IN                                    \
  if (!a_network_node.isValid()) Trace::TraceError("invalid network node") ;

#  define DEBUG_TRACE_VERIFY_NETWORK_OUT                               \
  String node_id = String(a_network_node.getType()) ;                  \
  if (!a_network_node.getParent().isValid())                           \
    Trace::TraceError("pruned corrupt network node '" + node_id + "'") ;

#  define DEBUG_TRACE_VERIFY_CONFIG_PROPERTY                          \
  Trace::TraceMissingProperty(config_store , a_key , a_default_value) ;

#  define DEBUG_TRACE_SANITIZE_CONFIG_INT_PROPERTY                                       \
  String node_id = String(config_store.getType()) ; String property_id = String(a_key) ; \
  if (a_value < min_value || a_value > max_value)                                        \
    Trace::TraceConfig("value out of range for property of '" + node_id          +       \
                       "' - removing '"                       + property_id + "'")       ;

#  define DEBUG_TRACE_DUMP_CONFIG_ROOT     Trace::DumpConfig(this->root     , "root"    ) ;
#  define DEBUG_TRACE_DUMP_CONFIG_PRESETS  Trace::DumpConfig(this->presets  , "presets" ) ;
#  define DEBUG_TRACE_DUMP_CONFIG_NETWORKS Trace::DumpConfig(this->networks , "networks") ;
#  define DEBUG_TRACE_DUMP_CONFIG_VOLATILE Trace::DumpConfig(this->config   , "volatile") ;
#  define DEBUG_TRACE_DUMP_CONFIG_CAMERAS  Trace::DumpConfig(this->cameras  , "cameras" ) ;
#  define DEBUG_TRACE_DUMP_CONFIG_AUDIOS   Trace::DumpConfig(this->audios   , "audios"  ) ;

# define DEBUG_TRACE_DUMP_CONFIG(method_name)                    \
  Trace::TraceVerbose(String(method_name) + " dumping config") ; \
  DEBUG_TRACE_DUMP_CONFIG_ROOT                                   \
  DEBUG_TRACE_DUMP_CONFIG_PRESETS                                \
  DEBUG_TRACE_DUMP_CONFIG_NETWORKS                               \
  DEBUG_TRACE_DUMP_CONFIG_VOLATILE                               \
  DEBUG_TRACE_DUMP_CONFIG_CAMERAS                                \
  DEBUG_TRACE_DUMP_CONFIG_AUDIOS

#  define DEBUG_TRACE_STORE_CONFIG                                                      \
  String file_path = this->configFile.getFullPathName() ;                               \
  if (!this->root.isValid()) Trace::TraceError("stored config invalid - not storing") ; \
  else                       Trace::TraceConfig("storing config to " + file_path)       ;

#  define DEBUG_TRACE_STORE_NETWORK                                                \
  Trace::TraceConfig("creating storage for IRC network '" +                        \
                     network + ":" + String(port) + "' channel '" + channel + "'") ;


/* maintenance */

#  define DEBUG_TRACE_LISTEN                                 \
  String state = (should_listen) ? "started" : "stopped" ;   \
  Trace::TraceConfig(state + " listening for model changes") ;

#  define DEBUG_TRACE_CONFIG_TREE_CHANGED Trace::TraceTreeChanged(a_node , a_key) ;

#  define DEBUG_TRACE_DETECT_CAPTURE_DEVICES                                     \
  bool is_bogus_cam = cameras.getChild(0).getType() == Identifier("bogus-cam") ; \
  String n_devices = String((is_bogus_cam) ? 0                       :           \
                                             cameras.getNumChildren()) ;         \
  Trace::TraceState("detected (" + n_devices + ") capture devices")              ;

#  define DEBUG_TRACE_STORE_PRESET                                  \
  bool is_new = this->config.hasProperty(CONFIG::PRESET_NAME_ID) ;  \
  String state = (is_new) ? "storing" : "updating" ;                \
  Trace::TraceConfig(state + " preset[" + String(preset_idx) +      \
                     "] '"              + preset_name        + "'") ;

#  define DEBUG_TRACE_RENAME_PRESET                                        \
  Trace::TraceConfig("renaming preset[" + String(preset_idx)        +      \
                     "] from '"         + AvCaster::GetPresetName() +      \
                     "' to '"           + preset_name               + "'") ;

#  define DEBUG_TRACE_DELETE_PRESET                                        \
  Trace::TraceConfig("deleting preset[" + String(preset_idx)             + \
                     "] '"              + AvCaster::GetPresetName() + "'") ;

#  define DEBUG_TRACE_DEACTIVATE_CONTROL                                      \
  Trace::TraceConfig("error configuring media - deactivating control toggle") ;

#  define DEBUG_TRACE_SET_CONFIG                                                 \
  String key        = (a_key.isValid()) ? String(a_key) : String("NULL") ;       \
  String node_id    = String(storage_node.getType()) ;                           \
  String change_msg = "key '"             + key                 +                \
                      "' changing from '" + STRING(storage_node[a_key]) +        \
                      "' to '"            + STRING(a_value    ) + "'" ;          \
  if (!storage_node.isValid()) Trace::TraceError("invalid node " + change_msg) ; \
  else                         Trace::TraceVerbose("config node '" + node_id +   \
                                                   "' " + change_msg)            ;

#  define DEBUG_TRACE_UPDATE_IRC_HOST                                                      \
  if (network_store.isValid())                                                             \
    Trace::TraceConfig("updating '" + String(network_id) + "' host (" + actual_host + ")") ;

#  define DEBUG_TRACE_UPDATE_CHAT_NICKS                                                           \
  String network = STRING(network_store[CONFIG::NETWORK_ID]) ;                                    \
  String dbg     = "'" + String(network_id) + "' invalid - not updating chatters" ;               \
  if      (!network_store .isValid())   Trace::TraceError("network_store "  + dbg) ;              \
  else if (!chatters_store.isValid()) { Trace::TraceError("chatters_store " + dbg) ;              \
                                        Trace::DumpConfig(network_store , "chatters invalid") ; } \
  else { DEBUG_TRACE_DUMP_CHAT_NICKS(network_id , active_nicks                 , "active_nicks")  \
         DEBUG_TRACE_DUMP_CHAT_NICKS(network_id , getChatNicks(chatters_store) , "stored_nicks")  }

#  define DEBUG_TRACE_ADD_CHAT_NICK                                                \
  String     nickidx   = String(stored_nicks.indexOf(*nick)) ;                     \
  String     nnicks    = String(stored_nicks.size()) ;                             \
  Trace::TraceConfig("adding chatter ("         + nickidx + "/" + nnicks + ") '" + \
                     String(user_id   ) + "' (" + *nick   + ")" + " to   '"      + \
                     String(network_id) + "' (" + network + ")"                  ) ;

#  define DEBUG_TRACE_REMOVE_CHAT_NICK                                                     \
  String nnicks    = String(chatters_store.getNumChildren()) ;                             \
  String nickidx   = String(chatter_n) ;                                                   \
  String userid    = String(chatter_store.getType()) ;                                     \
  if (!active_nicks.contains(stored_nick))                                                 \
    Trace::TraceConfig(String("removing chatter (") + nickidx     + "/" + nnicks + ") '" + \
                       userid  + "' (" + stored_nick + ")" + " from '" + network + "'"   ) ;

#  define DEBUG_TRACE_DUMP_CHAT_NICKS(networkid , nicks , label) nicks.sort(true) ;       \
  Trace::TraceConfigVb("\tdumping (" + String(nicks.size())                     + ") '" + \
                                       String(networkid)         + "' " + label + "=["  + \
                                       nicks.joinIntoString(",")                + "]"   ) ;

#else // DEBUG_TRACE

#  define DEBUG_TRACE_VERIFY_CONFIG                   ;
#  define DEBUG_TRACE_VERIFY_PRESETS_NODE             ;
#  define DEBUG_TRACE_VERIFY_NETWORKS_NODE            ;
#  define DEBUG_TRACE_VERIFY_CONFIG_ROOT              ;
#  define DEBUG_TRACE_VERIFY_CONFIG_PRESETS           ;
#  define DEBUG_TRACE_VERIFY_CONFIG_PRESET            ;
#  define DEBUG_TRACE_VERIFY_NETWORKS                 ;
#  define DEBUG_TRACE_VERIFY_NETWORK_IN               ;
#  define DEBUG_TRACE_VERIFY_NETWORK_OUT              ;
#  define DEBUG_TRACE_VERIFY_CONFIG_PROPERTY          ;
#  define DEBUG_TRACE_SANITIZE_CONFIG_INT_PROPERTY    ;
#  define DEBUG_TRACE_DUMP_CONFIG_ROOT                ;
#  define DEBUG_TRACE_DUMP_CONFIG_PRESETS             ;
#  define DEBUG_TRACE_DUMP_CONFIG_NETWORKS            ;
#  define DEBUG_TRACE_DUMP_CONFIG_VOLATILE            ;
#  define DEBUG_TRACE_DUMP_CONFIG_CAMERAS             ;
#  define DEBUG_TRACE_DUMP_CONFIG_AUDIOS              ;
#  define DEBUG_TRACE_DUMP_CONFIG(method_name)        ;
#  define DEBUG_TRACE_STORE_CONFIG                    ;
#  define DEBUG_TRACE_STORE_NETWORK                   ;
#  define DEBUG_TRACE_LISTEN                          ;
#  define DEBUG_TRACE_CONFIG_TREE_CHANGED             ;
#  define DEBUG_TRACE_DETECT_CAPTURE_DEVICES          ;
#  define DEBUG_TRACE_STORE_PRESET                    ;
#  define DEBUG_TRACE_RENAME_PRESET                   ;
#  define DEBUG_TRACE_DELETE_PRESET                   ;
#  define DEBUG_TRACE_DEACTIVATE_CONTROL              ;
#  define DEBUG_TRACE_SET_CONFIG                      ;
#  define DEBUG_TRACE_UPDATE_IRC_HOST                 ;
#  define DEBUG_TRACE_UPDATE_CHAT_NICKS               ;
#  define DEBUG_TRACE_ADD_CHAT_NICK                   ;
#  define DEBUG_TRACE_REMOVE_CHAT_NICK                ;
#  define DEBUG_TRACE_DUMP_CHAT_NICKS(chatters_store) ;

#endif // DEBUG_TRACE
#endif // _TRACEAVCASTERSTORE_H_

/*\
|*|  AvCaster - light-weight native gStreamer GUI for screencast, webcam, and audio streaming
|*|  Copyright 2015-2018, 2020 bill-auger <https://github.com/bill-auger/av-caster/issues>
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


#ifndef _TRACEAVCASTERSTORE_H_
#define _TRACEAVCASTERSTORE_H_

#ifdef DEBUG_TRACE

#  include "Trace.h"


/* persistence */

#  define DEBUG_TRACE_VERIFY_STORED_CONFIG                                                    \
  String not_found_msg = "stored config not found - restoring defaults" ;                     \
  String invalid_msg   = "stored config invalid - restoring defaults" ;                       \
  String corrupt_msg   = "stored config corrupt - pruning duplicated nodes" ;                 \
  String upgraded_msg  = "upgrading config version from v" + String(stored_version) +         \
                         " to v"                           + String(CONFIG::CONFIG_VERSION) ; \
  String success_msg   = "stored config parsed successfully v" + String(stored_version) ;     \
  Trace::TraceConfig("looking for stored config at " + this->storageFile.getFullPathName()) ; \
  Trace::TraceConfig((!was_storage_found  ) ? not_found_msg :                                 \
                     (!is_root_valid      ) ? invalid_msg   :                                 \
                     (!has_canonical_nodes) ? corrupt_msg   :                                 \
                     (!do_versions_match  ) ? upgraded_msg  : success_msg)                    ;

#  define DEBUG_TRACE_VERIFY_PRESET                                                       \
  if (!this->config.isValid()) Trace::TraceError("invalid preset node") ;                 \
  else                         Trace::TraceMissingNode(this->config , CONFIG::NETWORK_ID) ;

#  define DEBUG_TRACE_SANITIZE_PRESETS                                                  \
  String npresets = String(this->presets.getNumChildren() - CONFIG::N_STATIC_PRESETS) ; \
  Trace::TraceConfig("found (" + npresets + ") user-defined presets")                   ;

#  define DEBUG_TRACE_VERIFY_MISSING_NODE           \
  Trace::TraceMissingNode(config_store , a_node_id) ;

#  define DEBUG_TRACE_VERIFY_MISSING_PROPERTY                         \
  Trace::TraceMissingProperty(config_store , a_key , a_default_value) ;

#  define DEBUG_TRACE_SANITIZE_INT_PROPERTY                                                     \
  String relation = String(min_value) + " <= " + String(a_value) + " <= " + String(max_value) ; \
  String node_id = STRING(config_store.getType()) ; String property_id = STRING(a_key) ;        \
  if (a_value < min_value || a_value > max_value)                                               \
    Trace::TraceConfig("value (" + relation + ") out of range for '"  +                         \
                       node_id + "['" + property_id + "'] - removing" )                         ;

#  define DEBUG_TRACE_FILTER_ROGUE_KEY                                                    \
  if (!persistent_keys.contains(property_id))                                             \
    Trace::TraceConfig("removing rogue property '" + String(property_id)                + \
                       "' from '"                  + STRING(parent_node.getType()) + "'") ;

#  define DEBUG_TRACE_FILTER_ROGUE_NODE                                               \
  if (!persistent_node_ids.contains(node_id))                                         \
    Trace::TraceConfig("removing rogue node '" + String(node_id)                    + \
                       "' from '"              + STRING(parent_node.getType()) + "'") ;

#  define DEBUG_TRACE_DUMP_CONFIG_ROOT               \
  DEBUG_TRACE_DUMP_CONFIG(this->root     , "root"    )
#  define DEBUG_TRACE_DUMP_CONFIG_PRESETS            \
  DEBUG_TRACE_DUMP_CONFIG(this->presets  , "presets" )
#  define DEBUG_TRACE_DUMP_CONFIG_VOLATILE           \
  DEBUG_TRACE_DUMP_CONFIG(this->config   , "volatile")
#  define DEBUG_TRACE_DUMP_CONFIG_NETWORK            \
  DEBUG_TRACE_DUMP_CONFIG(this->network  , "network" )
#  define DEBUG_TRACE_DUMP_CONFIG_CHATTERS           \
  DEBUG_TRACE_DUMP_CONFIG(this->chatters , "chatters")
#  define DEBUG_TRACE_DUMP_CONFIG_CAMERAS            \
  DEBUG_TRACE_DUMP_CONFIG(this->cameras  , "cameras" )
#  define DEBUG_TRACE_DUMP_CONFIG_AUDIOS             \
  DEBUG_TRACE_DUMP_CONFIG(this->audios   , "audios"  )

#  define DEBUG_TRACE_DUMP_CONFIG_ALL \
  DEBUG_TRACE_DUMP_CONFIG_ROOT        \
  DEBUG_TRACE_DUMP_CONFIG_PRESETS     \
  DEBUG_TRACE_DUMP_CONFIG_VOLATILE    \
  DEBUG_TRACE_DUMP_CONFIG_NETWORK     \
  DEBUG_TRACE_DUMP_CONFIG_CHATTERS    \
  DEBUG_TRACE_DUMP_CONFIG_CAMERAS     \
  DEBUG_TRACE_DUMP_CONFIG_AUDIOS

#  define DEBUG_TRACE_STORE_CONFIG                                                      \
  String file_path = this->storageFile.getFullPathName() ;                              \
  if (!this->root.isValid()) Trace::TraceError("stored config invalid - not storing") ; \
  else                       Trace::TraceConfig("storing config to " + file_path)       ;


/* maintenance */

#  define DEBUG_TRACE_LISTEN                                 \
  String state = (should_listen) ? "resumed" : "suspended" ; \
  Trace::TraceConfig(state + " listening for model changes") ;

#  define DEBUG_TRACE_CONFIG_TREE_CHANGED Trace::TraceTreeChanged(a_node , a_key) ;

#  define DEBUG_TRACE_DETECT_CAPTURE_DEVICES                                     \
  bool is_bogus_cam = cameras.getChild(0).getType() == Identifier("bogus-cam") ; \
  String n_devices = String((is_bogus_cam) ? 0                       :           \
                                             cameras.getNumChildren()) ;         \
  Trace::TraceState("detected (" + n_devices + ") capture devices")              ;

#  define DEBUG_TRACE_STORE_PRESET                                              \
  bool   is_new = ! preset_store.hasProperty(CONFIG::PRESET_NAME_ID) ;          \
  String state  = String((is_new) ? "creating" : "updating") + " storage for" ; \
  Trace::TraceConfig(state + " preset[" + String(preset_idx) +                  \
                     "] '"              + preset_name        + "'")             ;

#  define DEBUG_TRACE_RENAME_PRESET                                        \
  Trace::TraceConfig("renaming preset[" + String(preset_idx)        +      \
                     "] from '"         + AvCaster::GetPresetName() +      \
                     "' to '"           + preset_name               + "'") ;

#  define DEBUG_TRACE_DELETE_PRESET                                        \
  Trace::TraceConfig("deleting preset[" + String(preset_idx)             + \
                     "] '"              + AvCaster::GetPresetName() + "'") ;

#  define DEBUG_TRACE_LOAD_PRESET                                        \
  Trace::TraceConfig("loading preset[" + String(preset_idx) + "] '" +    \
                     STRING(preset_store[CONFIG::PRESET_NAME_ID]) + "'") ;

#  define DEBUG_TRACE_DEACTIVATE_CONTROL                                          \
  String err = (AvCaster::IsInitialized) ? "error configuring media - " : "" ;    \
  Trace::TraceConfig(err + "deactivating control toggle '" + STRING(a_key) + "'") ;

#  define DEBUG_TRACE_SET_PROPERTY                                           \
  if (AvCaster::IsInitialized && AvCaster::DisabledFeatures.contains(a_key)) \
    Trace::TraceError("attempting to set disabled media key - ignoring") ;

#  define DEBUG_TRACE_SET_VALUE(a_node , a_key , a_value , postfix)                      \
  ValueTree a_parent_node   = a_node.getParent() ;                                       \
  String    node_id         = STRING(a_node.getType()) ;                                 \
  String    key             = STRING(a_key           ) ;                                 \
  bool      is_unknown      = !isKnownProperty(a_node , a_key) ;                         \
  bool      is_unknown_node = a_node        != this->root     &&                         \
                              a_node        != this->config   &&                         \
                              a_node        != this->network  &&                         \
                              a_parent_node != this->presets  &&                         \
                              a_parent_node != this->chatters &&                         \
                              a_parent_node != this->cameras  &&                         \
                              a_parent_node != this->audios    ;                         \
  String    change_msg      = ((!is_unknown    ) ? ""                                :   \
                               (is_unknown_node) ? "unknown node '" + node_id + "' " :   \
                                                   "unknown key '"  + key     + "' " ) + \
                              Trace::TraceSetValue(a_node , a_key , a_value) ;           \
  if (AvCaster::IsInitialized && change_msg.isNotEmpty())                                \
    if (!is_unknown) Trace::TraceConfigVb(change_msg + postfix) ;                        \
    else             Trace::TraceError   (change_msg + postfix)                          ;

#  define DEBUG_TRACE_STORE_SET_VALUE                \
  DEBUG_TRACE_SET_VALUE(a_node , a_key , a_value , "")

#  define DEBUG_TRACE_GUI_SET_VALUE                          \
  DEBUG_TRACE_SET_VALUE(a_node , a_key , a_value , " via GUI")

#  define DEBUG_TRACE_UPDATE_CHAT_NICKS_IN                                      \
  String network_id = STRING(this->network[CONFIG::NETWORK_ID]) ;               \
  Trace::TraceConfig("updating '" + network_id + "' n_nicks from (" +           \
                     String(getChatNicks().size()) + ") to ("       +           \
                     String(active_nicks  .size()) + ")"            ) ;         \
  DEBUG_TRACE_DUMP_CHAT_NICKS(network_id , active_nicks   , "active_nicks  IN") \
  DEBUG_TRACE_DUMP_CHAT_NICKS(network_id , getChatNicks() , "stored_nicks  IN")

#  define DEBUG_TRACE_UPDATE_CHAT_NICKS_OUT                                     \
  DEBUG_TRACE_DUMP_CHAT_NICKS(network_id , active_nicks   , "active_nicks OUT") \
  DEBUG_TRACE_DUMP_CHAT_NICKS(network_id , getChatNicks() , "stored_nicks OUT")

#  define DEBUG_TRACE_ADD_CHAT_NICK                                                    \
  String nickidx = String(stored_nicks.indexOf(active_nick)) ;                         \
  String nnicks  = String(stored_nicks.size()        ) ;                               \
  Trace::TraceConfig("adding chatter ("         + nickidx     + "/" + nnicks + ") '" + \
                     STRING(chatter_id) + "' (" + active_nick + ")" + " to '"        + \
                     String(network_id) + "' (" + network_id  + ")"                  ) ;

#  define DEBUG_TRACE_REMOVE_CHAT_NICK                                                      \
  String nnicks  = String(this->chatters.getNumChildren()) ;                                \
  String nickidx = String(chatter_idx                    ) ;                                \
  String userid  = STRING(chatter_store.getType()        ) ;                                \
  if (!active_nicks.contains(stored_nick))                                                  \
    Trace::TraceConfig(String("removing chatter (") + nickidx + "/" + nnicks + ") '"      + \
                       userid  + "' (" + stored_nick + ")" + " from '" + network_id + "'" ) ;

#  define DEBUG_TRACE_DUMP_CHAT_NICKS(networkid , nicks , label) nicks.sort(true) ;       \
  Trace::TraceConfigVb("\tdumping (" + String(nicks.size())                     + ") '" + \
                                       String(networkid)         + "' " + label + "=["  + \
                                       nicks.joinIntoString(",")                + "]"   ) ;

#else // DEBUG_TRACE

#  define DEBUG_TRACE_VERIFY_STORED_CONFIG                  ;
#  define DEBUG_TRACE_VERIFY_PRESET                         ;
#  define DEBUG_TRACE_SANITIZE_PRESETS                      ;
#  define DEBUG_TRACE_VERIFY_MISSING_NODE                   ;
#  define DEBUG_TRACE_VERIFY_MISSING_PROPERTY               ;
#  define DEBUG_TRACE_SANITIZE_INT_PROPERTY                 ;
#  define DEBUG_TRACE_FILTER_ROGUE_KEY                      ;
#  define DEBUG_TRACE_FILTER_ROGUE_NODE                     ;
#  define DEBUG_TRACE_DUMP_CONFIG_ROOT                      ;
#  define DEBUG_TRACE_DUMP_CONFIG_PRESETS                   ;
#  define DEBUG_TRACE_DUMP_CONFIG_VOLATILE                  ;
#  define DEBUG_TRACE_DUMP_CONFIG_NETWORK                   ;
#  define DEBUG_TRACE_DUMP_CONFIG_CHATTERS                  ;
#  define DEBUG_TRACE_DUMP_CONFIG_CAMERAS                   ;
#  define DEBUG_TRACE_DUMP_CONFIG_AUDIOS                    ;
#  define DEBUG_TRACE_DUMP_CONFIG_ALL                       ;
#  define DEBUG_TRACE_STORE_CONFIG                          ;
#  define DEBUG_TRACE_LISTEN                                ;
#  define DEBUG_TRACE_CONFIG_TREE_CHANGED                   ;
#  define DEBUG_TRACE_DETECT_CAPTURE_DEVICES                ;
#  define DEBUG_TRACE_STORE_PRESET                          ;
#  define DEBUG_TRACE_RENAME_PRESET                         ;
#  define DEBUG_TRACE_DELETE_PRESET                         ;
#  define DEBUG_TRACE_LOAD_PRESET                           ;
#  define DEBUG_TRACE_DEACTIVATE_CONTROL                    ;
#  define DEBUG_TRACE_STORE_SET_VALUE                       ;
#  define DEBUG_TRACE_GUI_SET_VALUE                         ;
#  define DEBUG_TRACE_UPDATE_CHAT_NICKS_IN                  ;
#  define DEBUG_TRACE_UPDATE_CHAT_NICKS_OUT                 ;
#  define DEBUG_TRACE_ADD_CHAT_NICK                         ;
#  define DEBUG_TRACE_REMOVE_CHAT_NICK                      ;
#  define DEBUG_TRACE_DUMP_CHAT_NICKS(chatters_store)       ;

#endif // DEBUG_TRACE
#endif // _TRACEAVCASTERSTORE_H_

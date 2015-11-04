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


#ifndef TRACEAVCASTERSTORE_H_INCLUDED
#define TRACEAVCASTERSTORE_H_INCLUDED

#ifdef DEBUG

#  include "Trace.h"


/* persistence */

#  define DEBUG_TRACE_VERIFY_CONFIG                                                         \
  String success_msg   = "stored config parsed successfully v" + String(stored_version) ;   \
  String not_found_msg = "stored config not found - restoring defaults" ;                   \
  String invalid_msg   = "stored config invalid - restoring defaults" ;                     \
  String upgraded_msg  = "upgrading config version to v" + String(CONFIG::CONFIG_VERSION) ; \
  String outdated_msg  = "stored config backed up - schema changed - restoring defaults" ;  \
  Trace::TraceConfig(((!stored_config.isValid()            ) ? not_found_msg :              \
                     ((!stored_config.hasType(root_node_id)) ? invalid_msg   :              \
                     ((!do_versions_match                  ) ? outdated_msg  :              \
                                                               success_msg))))              ;

#  define DEBUG_TRACE_VALIDATE_CONFIG_ROOT                                  \
  if (!this->configRoot.isValid()) Trace::TraceError("invalid config root") ;

#  define DEBUG_TRACE_VALIDATE_CONFIG_PRESET                            \
  if (!this->configStore.isValid()) Trace::TraceError("invalid preset") ;

#  define DEBUG_TRACE_VALIDATE_CONFIG_PROPERTY                        \
  Trace::TraceMissingProperty(config_store , a_key , a_default_value) ;

#  define DEBUG_TRACE_DUMP_STORE_CONFIG                                          \
  if (!this->configRoot.isValid()) Trace::TraceError("error storing config") ;   \
  else {                           Trace::TraceConfig("storing config") ;        \
         DEBUG_TRACE_DUMP_CONFIG_ROOT                                            \
         DEBUG_TRACE_DUMP_CONFIG_PRESETS                                         \
         DEBUG_TRACE_DUMP_CONFIG_VOLATILE                                        \
         DEBUG_TRACE_DUMP_CONFIG_CAMERAS                                         \
         DEBUG_TRACE_DUMP_CONFIG_AUDIO                                           }

#  define DEBUG_TRACE_DUMP_CONFIG_ROOT     if (DEBUG_TRACE_VB) Trace::DumpConfig(this->configRoot    , "root"    ) ;
#  define DEBUG_TRACE_DUMP_CONFIG_VOLATILE if (DEBUG_TRACE_VB) Trace::DumpConfig(this->configStore   , "volatile") ;
#  define DEBUG_TRACE_DUMP_CONFIG_CAMERAS  if (DEBUG_TRACE_VB) Trace::DumpConfig(this->cameraDevices , "cameras" ) ;
#  define DEBUG_TRACE_DUMP_CONFIG_AUDIO    if (DEBUG_TRACE_VB) Trace::DumpConfig(this->audioDevices  , "audio"   ) ;
#  define DEBUG_TRACE_DUMP_CONFIG_PRESETS  if (DEBUG_TRACE_VB)               \
  { int preset_n = this->configPresets.getNumChildren() ; while (preset_n--) \
    Trace::DumpConfig(this->configPresets.getChild(preset_n) , "presets") ;  }


/* state */

#  define DEBUG_TRACE_CONFIG_TREE_CHANGED                     \
  String key = String(a_key) ;                                \
  String val = a_node[a_key].toString() ;                     \
  Trace::TraceEvent("value changed => " + key + " => " + val) ;

#define DEBUG_TRACE_DETECT_CAPTURE_DEVICES                                                             \
  bool is_bogus_cam = cameraDevices.getChild(0).getType() == Identifier("bogus-cam") ; \
  String n_devices = String((is_bogus_cam) ? 0                             :           \
                                             cameraDevices.getNumChildren()) ;         \
  Trace::TraceState("detected (" + n_devices + ") capture devices") ;

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

#else // DEBUG

#  define DEBUG_TRACE_VERIFY_CONFIG            ;
#  define DEBUG_TRACE_VALIDATE_CONFIG_ROOT     ;
#  define DEBUG_TRACE_VALIDATE_CONFIG_PRESET   ;
#  define DEBUG_TRACE_VALIDATE_CONFIG_PROPERTY ;
#  define DEBUG_TRACE_DUMP_STORE_CONFIG        ;
#  define DEBUG_TRACE_DUMP_CONFIG_ROOT         ;
#  define DEBUG_TRACE_DUMP_CONFIG_VOLATILE     ;
#  define DEBUG_TRACE_DUMP_CONFIG_CAMERAS      ;
#  define DEBUG_TRACE_DUMP_CONFIG_AUDIO        ;
#  define DEBUG_TRACE_DUMP_CONFIG_PRESETS      ;
#  define DEBUG_TRACE_CONFIG_TREE_CHANGED      ;
#  define DEBUG_TRACE_DETECT_CAPTURE_DEVICES   ;
#  define DEBUG_TRACE_STORE_PRESET             ;
#  define DEBUG_TRACE_RENAME_PRESET            ;
#  define DEBUG_TRACE_DELETE_PRESET            ;

#endif // DEBUG
#endif  // TRACEAVCASTERSTORE_H_INCLUDED

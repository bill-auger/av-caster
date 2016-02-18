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


#ifndef _TRACECONFIG_H_
#define _TRACECONFIG_H_

#ifdef DEBUG_TRACE

#  include "Trace.h"


#  define DEBUG_TRACE_CONFIG_LOAD_CONFIG                                                        \
  Trace::TraceConfig("loading preset '" + STRING(config_store[CONFIG::PRESET_NAME_ID]) + "'") ; \
  Trace::DumpConfig(config_store , "volatile")                                                  ;

#  define DEBUG_TRACE_SET_CREATE_PRESET_MODE                                               \
  bool has_mode_changed = is_pending_new_preset_name != isCreatePresetMode() ;             \
  if (has_mode_changed)                                                                    \
    Trace::TraceGui(String((is_pending_new_preset_name) ? "entering create preset mode" :  \
                                                          "exiting create preset mode"  )) ;

#  define DEBUG_TRACE_CREATE_PRESET                                                \
  bool should_update = !is_create_preset_mode && !should_rename_preset ;           \
  bool is_rejecting = is_name_collision && !should_update ;                        \
  if      (is_empty_preset_name ) Trace::TraceGui("rejecting preset") ;            \
  else if (is_rejecting         ) Trace::TraceGui("rejecting preset") ;            \
  else if (is_create_preset_mode) Trace::TraceGui("creating preset") ;             \
  else if (should_rename_preset ) Trace::TraceGui("renaming preset") ;             \
  else                            Trace::TraceGui("updating preset") ;             \
  String pad = "\n                                       " ;                       \
  Trace::TraceGuiVb(String("handling preset change '") + preset_name       + "'" + \
      pad + "stored_preset_name   = '" + String(AvCaster::GetPresetName()) + "'" + \
      pad + "option_n             = "  + String(option_n                )        + \
      pad + "stored_option_n      = "  + String(AvCaster::GetPresetIdx())        + \
      pad + "is_valid_option      = "  + String(is_valid_option         )        + \
      pad + "is_static_preset     = "  + String(is_static_preset        )        + \
      pad + "is_empty_preset_name = "  + String(is_empty_preset_name    )        + \
      pad + "has_name_changed     = "  + String(has_name_changed        )        + \
      pad + "is_static_preset     = "  + String(should_rename_preset    )        ) ;

#else // DEBUG_TRACE

#  define DEBUG_TRACE_CONFIG_LOAD_CONFIG     ;
#  define DEBUG_TRACE_SET_CREATE_PRESET_MODE ;
#  define DEBUG_TRACE_CREATE_PRESET          ;

#endif // DEBUG_TRACE
#endif // _TRACECONFIG_H_

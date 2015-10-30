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


#ifndef TRACECONTROLS_H_INCLUDED
#define TRACECONTROLS_H_INCLUDED

#ifdef DEBUG

#  include "Trace.h"


#  define DEBUG_TRACE_HANDLE_PRESETCOMBO                                              \
  String pad = "\n                                       " ;                          \
  Trace::TraceVerbose(String("Controls::handlePresetCombo()")         +               \
           " preset_name          = '" + preset_name        + "'"     +               \
      pad + "stored_preset_name   = '" + stored_preset_name + "'"     +               \
      pad + "option_n             = "  + String(option_n            ) +               \
      pad + "stored_option_n      = "  + String(stored_option_n     ) +               \
      pad + "is_valid_option      = "  + String(is_valid_option     ) +               \
      pad + "is_empty             = "  + String(is_empty            ) +               \
      pad + "has_name_changed     = "  + String(has_name_changed    ) +               \
      pad + "should_rename_preset = "  + String(should_rename_preset) +               \
      pad + "should_reset_option  = "  + String(should_reset_option ) ) ;             \
  Trace::TraceGui(String("presetCombo selection changed - ")                        + \
                  ((!is_valid_option && is_empty) ? "rejecting empty preset name" :   \
                  (should_rename_preset         ) ? "renaming preset"             :   \
                  (should_reset_option          ) ? "resetting selection"         :   \
                                                    "accepting change"            ) ) ;

#  define DEBUG_TRACE_REJECT_CONFIG_CHANGE                                               \
  if (is_output_active) Trace::TraceConfig("rejecting config change - output is active") ;

#else // DEBUG

#  define DEBUG_TRACE_HANDLE_PRESETCOMBO   ;
#  define DEBUG_TRACE_REJECT_CONFIG_CHANGE ;

#endif // DEBUG
#endif // TRACECONTROLS_H_INCLUDED

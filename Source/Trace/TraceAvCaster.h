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


#ifndef _TRACEAVCASTER_H_
#define _TRACEAVCASTER_H_

#ifdef DEBUG

#  include "Trace.h"


/* state */

#  define DEBUG_TRACE_INIT_PHASE_1 Trace::TraceState("validating environment") ;

#  define DEBUG_TRACE_INIT_PHASE_2 Trace::TraceState("instantiating model") ;

#  define DEBUG_TRACE_INIT_PHASE_3 Trace::TraceState("instantiating GUI") ;

#  define DEBUG_TRACE_INIT_PHASE_4 if (IsMediaEnabled) Trace::TraceState("instantiating media") ;

#  define DEBUG_TRACE_INIT_PHASE_5 if (IsChatEnabled) Trace::TraceState("instantiating network") ;

#  define DEBUG_TRACE_INIT_PHASE_6 Trace::TraceState("AvCaster ready") ;

#  define DEBUG_TRACE_HANDLE_CLI_PARAMS_PRE_INIT                                                         \
  StringArray tokens ;                                                                                   \
  if      (CliParams.contains(APP::CLI_HELP_TOKEN           )) tokens.add("CLI_HELP_TOKEN"           ) ; \
  else if (CliParams.contains(APP::CLI_PRESETS_TOKEN        )) tokens.add("CLI_PRESETS_TOKEN"        ) ; \
  else if (CliParams.contains(APP::CLI_PRESET_TOKEN         )) tokens.add("CLI_PRESET_TOKEN"         ) ; \
  else if (CliParams.contains(APP::CLI_VERSION_TOKEN        )) tokens.add("CLI_VERSION_TOKEN"        ) ; \
  else if (CliParams.contains(APP::CLI_DISABLE_MEDIA_TOKEN  )) tokens.add("CLI_DISABLE_MEDIA_TOKEN"  ) ; \
  else if (CliParams.contains(APP::CLI_SCREEN_ONLY_TOKEN    )) tokens.add("CLI_SCREEN_ONLY_TOKEN"    ) ; \
  else if (CliParams.contains(APP::CLI_CAMERA_ONLY_TOKEN    )) tokens.add("CLI_CAMERA_ONLY_TOKEN"    ) ; \
  else if (CliParams.contains(APP::CLI_TEXT_ONLY_TOKEN      )) tokens.add("CLI_TEXT_ONLY_TOKEN"      ) ; \
  else if (CliParams.contains(APP::CLI_DISABLE_PREVIEW_TOKEN)) tokens.add("CLI_DISABLE_PREVIEW_TOKEN") ; \
  else if (CliParams.contains(APP::CLI_DISABLE_CHAT_TOKEN   )) tokens.add("CLI_DISABLE_CHAT_TOKEN"   ) ; \
  else if (CliParams.contains(APP::CLI_DISABLE_PREVIEW_TOKEN)) tokens.add("CLI_DISABLE_PREVIEW_TOKEN") ; \
  else if (CliParams.contains(APP::CLI_DISABLE_CHAT_TOKEN   )) tokens.add("CLI_DISABLE_CHAT_TOKEN"   ) ; \
  String dbg = tokens.joinIntoString(",") ;                                                              \
  if (tokens.size()) Trace::TraceConfig("found pre-init cli tokens " + dbg)                              ;

#  define DEBUG_TRACE_HANDLE_CLI_PARAMS_POST_INIT                                 \
  StringArray tokens ;                                                            \
  if (CliParams.contains(APP::CLI_PRESET_TOKEN)) tokens.add("CLI_PRESET_TOKEN") ; \
  String dbg = tokens.joinIntoString(",") ;                                       \
  if (tokens.size()) Trace::TraceConfig("found post-init cli tokens " + dbg)      ;

#  define DEBUG_TRACE_VALIDATE_ENVIRONMENT                                                 \
  bool is_err = false ; String dbg = "" ;                                                  \
  if (!APP::HOME_DIR   .isDirectory()) { is_err = true ; dbg += " invlaid HOME_DIR" ;    } \
  if (!APP::APPDATA_DIR.isDirectory()) { is_err = true ; dbg += " invlaid APPDATA_DIR" ; } \
  if (!APP::VIDEOS_DIR .isDirectory()) { is_err = true ; dbg += " invlaid VIDEOS_DIR" ;  } \
  if (is_err) Trace::TraceError(dbg) ; else Trace::TraceState("environment is sane")       ;

#  define DEBUG_TRACE_REFRESH_GUI                                                      \
  String gui = (is_config_pending) ? "Config" : (is_preview_on) ? "Preview" : "Chat" ; \
  Trace::TraceState("showing " + gui + " GUI")                                         ;

#  define DEBUG_TRACE_SHUTDOWN_PHASE_1 Trace::TraceState("shutting down network") ;

#  define DEBUG_TRACE_SHUTDOWN_PHASE_2 Trace::TraceState("shutting down media") ;

#  define DEBUG_TRACE_SHUTDOWN_PHASE_3 Trace::TraceState("shutting down storage") ;


/* config */

#  define DEBUG_TRACE_SET_CONFIG                                              \
  String    key        = (a_key.isValid()) ? String(a_key) : String("NULL") ; \
  ValueTree node       = Store->getKeyNode(a_key) ;                           \
  String    change_msg = "key '"             + key                 +          \
                         "' changing from '" + STRING(node[a_key]) +          \
                         "' to '"            + STRING(a_value    ) + "'" ;    \
  Trace::TraceGui("gui " + change_msg) ;

#  define DEBUG_TRACE_REJECT_CONFIG_CHANGE                                           \
  if (is_output_on) Trace::TraceConfig("rejecting config change - output is active") ;

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
  Trace::TraceGui(String("presetsCombo selection changed - ")                       + \
                  ((!is_valid_option && is_empty) ? "rejecting empty preset name" :   \
                  (should_rename_preset         ) ? "renaming preset"             :   \
                  (should_reset_option          ) ? "resetting selection"         :   \
                                                    "accepting change"            ) ) ;


/* helpers */

#  define DEBUG_TRACE_DUMP_CHAT_NICKS if (DEBUG_TRACE_VB)                                 \
  Trace::TraceConfig(String("sorting (") + String(nicks.size()) + ") '"                 + \
                     String(server_id)   + "' nicks=[" + nicks.joinIntoString(",") + "]") ;

#  define DEBUG_TRACE_DISPLAY_ALERT                                                     \
  if      (message_type == GUI::ALERT_TYPE_WARNING) Trace::TraceWarning(message_text) ; \
  else if (message_type == GUI::ALERT_TYPE_ERROR  ) Trace::TraceError  (message_text)   ;

#else // DEBUG

#  define DEBUG_TRACE_INIT_PHASE_1                ;
#  define DEBUG_TRACE_INIT_PHASE_2                ;
#  define DEBUG_TRACE_INIT_PHASE_3                ;
#  define DEBUG_TRACE_INIT_PHASE_4                ;
#  define DEBUG_TRACE_INIT_PHASE_5                ;
#  define DEBUG_TRACE_INIT_PHASE_6                ;
#  define DEBUG_TRACE_HANDLE_CLI_PARAMS_PRE_INIT  ;
#  define DEBUG_TRACE_HANDLE_CLI_PARAMS_POST_INIT ;
#  define DEBUG_TRACE_VALIDATE_ENVIRONMENT        ;
#  define DEBUG_TRACE_REFRESH_GUI                 ;
#  define DEBUG_TRACE_SHUTDOWN_PHASE_1            ;
#  define DEBUG_TRACE_SHUTDOWN_PHASE_2            ;
#  define DEBUG_TRACE_SHUTDOWN_PHASE_3            ;
#  define DEBUG_TRACE_SET_CONFIG                  ;
#  define DEBUG_TRACE_REJECT_CONFIG_CHANGE        ;
#  define DEBUG_TRACE_HANDLE_PRESETCOMBO          ;
#  define DEBUG_TRACE_DUMP_CHAT_NICKS             ;
#  define DEBUG_TRACE_DISPLAY_ALERT               ;

#endif // DEBUG
#endif // _TRACEAVCASTER_H_

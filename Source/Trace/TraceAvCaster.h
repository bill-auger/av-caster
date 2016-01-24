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

#ifdef DEBUG_TRACE

#  include "Trace.h"


/* feature switches */

StringArray DisabledFeatures()
{
  StringArray disabled_features = StringArray() ;
#  ifdef DISABLE_MEDIA
  disabled_features.add(APP::CLI_DISABLE_MEDIA_TOKEN) ;
#  endif // DISABLE_MEDIA
#  ifdef SCREEN_ONLY
  disabled_features.add(APP::CLI_SCREEN_ONLY_TOKEN) ;
#  endif // SCREEN_ONLY
#  ifdef CAMERA_ONLY
  disabled_features.add(APP::CLI_CAMERA_ONLY_TOKEN) ;
#  endif // CAMERA_ONLY
#  ifdef TEXT_ONLY
#    if ! TEXT_BIN_NYI
  disabled_features.add(APP::CLI_TEXT_ONLY_TOKEN) ;
#    endif // TEXT_BIN_NYI
#  endif // TEXT_ONLY
#  ifdef IMAGE_ONLY
#    if ! IMAGE_BIN_NYI
  disabled_features.add(APP::CLI_IMAGE_ONLY_TOKEN) ;
#    endif // IMAGE_BIN_NYI
#  endif // IMAGE_ONLY
#  if DISABLE_PREVIEW
  disabled_features.add(APP::CLI_DISABLE_PREVIEW_TOKEN) ;
#  endif // DISABLE_PREVIEW
#  if DISABLE_AUDIO
  disabled_features.add(APP::CLI_DISABLE_AUDIO_TOKEN) ;
#  endif // DISABLE_AUDIO
#  ifdef DISABLE_CHAT
  disabled_features.add(APP::CLI_DISABLE_CHAT_TOKEN) ;
#  endif // DISABLE_CHAT

  return disabled_features ;
}

#  if TEXT_BIN_NYI && IMAGE_BIN_NYI
#    define DISABLE_FEATURES \
  IsTextEnabled = false ;    \
  IsImageEnabled = false     ;
#  else // TEXT_BIN_NYI && IMAGE_BIN_NYI
#    if TEXT_BIN_NYI
#      define DISABLE_FEATURES \
  IsTextEnabled = false        ;
#    endif // TEXT_BIN_NYI
#    if IMAGE_BIN_NYI
#      define DISABLE_FEATURES \
  IsImageEnabled = false       ;
#    endif // IMAGE_BIN_NYI
#  endif // TEXT_BIN_NYI && IMAGE_BIN_NYI

#  define DEBUG_DISABLE_FEATURES DISABLE_FEATURES                           \
  StringArray disabled_features = DisabledFeatures() ;                      \
  if (!!disabled_features.size() || !IsTextEnabled || !IsImageEnabled)      \
    Trace::TraceState("disabling some features per #define constants") ;    \
  CliParams.addArray(disabled_features) ; CliParams.removeDuplicates(false) ;
  // CliParams.mergeArray(DisabledFeatures()) ; // TODO: new feature after upgrade


/* state */

#  define DEBUG_TRACE_INIT_PHASE_1 Trace::TraceState("validating environment") ;

#  define DEBUG_TRACE_INIT_PHASE_2 Trace::TraceState("instantiating model") ;

#  define DEBUG_TRACE_INIT_PHASE_3 Trace::TraceState("instantiating GUI") ;

#  define DEBUG_TRACE_INIT_PHASE_4                                               \
  Trace::TraceState((IsMediaEnabled) ? "instantiating media" : "media disabled") ;

#  define DEBUG_TRACE_INIT_PHASE_5                                            \
  Trace::TraceState((IsChatEnabled) ? "instantiating chat" : "chat disabled") ;

#  define DEBUG_TRACE_INIT_PHASE_6 Trace::TraceState("finalizing initialization") ;

#  define DEBUG_TRACE_INIT_PHASE_7 Trace::TraceState("AvCaster ready") ;

#  define DEBUG_TRACE_HANDLE_CLI_PARAMS_TERMINATING String token ;                      \
  if      (CliParams.contains(APP::CLI_HELP_TOKEN   )) token = APP::CLI_HELP_TOKEN ;    \
  else if (CliParams.contains(APP::CLI_PRESETS_TOKEN)) token = APP::CLI_PRESETS_TOKEN ; \
  else if (CliParams.contains(APP::CLI_VERSION_TOKEN)) token = APP::CLI_VERSION_TOKEN ; \
  if (token.isNotEmpty()) Trace::TraceConfig("found terminating cli token " + token)    ;

#  define DEBUG_TRACE_HANDLE_CLI_PARAMS StringArray tokens ;                   \
  for (String* token = CliParams.begin() ; token != CliParams.end() ; ++token) \
    if (*token == APP::CLI_PRESET_TOKEN          ||                            \
        *token == APP::CLI_DISABLE_MEDIA_TOKEN   ||                            \
        *token == APP::CLI_SCREEN_ONLY_TOKEN     ||                            \
        *token == APP::CLI_CAMERA_ONLY_TOKEN     ||                            \
/*        *token == APP::CLI_TEXT_ONLY_TOKEN       ||                            */\
/*        *token == APP::CLI_IMAGE_ONLY_TOKEN      ||                            */\
        *token == APP::CLI_DISABLE_PREVIEW_TOKEN ||                            \
        *token == APP::CLI_DISABLE_AUDIO_TOKEN   ||                            \
        *token == APP::CLI_DISABLE_CHAT_TOKEN     ) tokens.add(*token) ;       \
  String dbg = tokens.joinIntoString(",") ;                                    \
  if (tokens.size()) Trace::TraceConfig("found pre-init cli tokens " + dbg)    ;

#  define DUMP_DEBUG_MEDIA_SWITCHES                                                        \
  Trace::TraceVerbose("CliParams="                    + CliParams.joinIntoString(",")    + \
                      "\n\tAPP::N_COMPOSITOR_INPUTS=" + String(APP::N_COMPOSITOR_INPUTS) + \
                      "\n\tn_video_inputs="           + String(n_video_inputs          ) + \
                      "\n\tIsMediaEnabled="           + String(IsMediaEnabled          ) + \
                      "\n\tIsScreenEnabled="          + String(IsScreenEnabled         ) + \
                      "\n\tIsCameraEnabled="          + String(IsCameraEnabled         ) + \
                      "\n\tIsTextEnabled="            + String(IsTextEnabled           ) + \
                      "\n\tIsImageEnabled="           + String(IsImageEnabled          ) + \
                      "\n\tIsCompositorEnabled="      + String(IsCompositorEnabled     ) + \
                      "\n\tIsPreviewEnabled="         + String(IsPreviewEnabled        ) + \
                      "\n\tIsAudioEnabled="           + String(IsAudioEnabled          ) + \
                      "\n\tIsChatEnabled="            + String(IsChatEnabled           ) + \
                      "\n\tis_sane="                  + String(is_sane                 ) ) ;

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

#  define DEBUG_TRACE_DISPLAY_ALERT                                                     \
  if      (message_type == GUI::ALERT_TYPE_WARNING) Trace::TraceWarning(message_text) ; \
  else if (message_type == GUI::ALERT_TYPE_ERROR  ) Trace::TraceError  (message_text)   ;

#else // DEBUG_TRACE

#  define DEBUG_DISABLE_FEATURES                    ;
#  define DEBUG_TRACE_INIT_PHASE_1                  ;
#  define DEBUG_TRACE_INIT_PHASE_2                  ;
#  define DEBUG_TRACE_INIT_PHASE_3                  ;
#  define DEBUG_TRACE_INIT_PHASE_4                  ;
#  define DEBUG_TRACE_INIT_PHASE_5                  ;
#  define DEBUG_TRACE_INIT_PHASE_6                  ;
#  define DEBUG_TRACE_INIT_PHASE_7                  ;
#  define DEBUG_TRACE_HANDLE_CLI_PARAMS_TERMINATING ;
#  define DEBUG_TRACE_HANDLE_CLI_PARAMS             ;
#  define DUMP_DEBUG_MEDIA_SWITCHES                 ;
#  define DEBUG_TRACE_VALIDATE_ENVIRONMENT          ;
#  define DEBUG_TRACE_REFRESH_GUI                   ;
#  define DEBUG_TRACE_SHUTDOWN_PHASE_1              ;
#  define DEBUG_TRACE_SHUTDOWN_PHASE_2              ;
#  define DEBUG_TRACE_SHUTDOWN_PHASE_3              ;
#  define DEBUG_TRACE_SET_CONFIG                    ;
#  define DEBUG_TRACE_REJECT_CONFIG_CHANGE          ;
#  define DEBUG_TRACE_HANDLE_PRESETCOMBO            ;
#  define DEBUG_TRACE_DISPLAY_ALERT                 ;

#endif // DEBUG_TRACE
#endif // _TRACEAVCASTER_H_

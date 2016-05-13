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


#ifndef _TRACEAVCASTER_H_
#define _TRACEAVCASTER_H_

#ifdef DEBUG_TRACE

#  include "Trace.h"


/* feature switches */

StringArray DisableFeatures()
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

#  define DEBUG_DISABLE_FEATURES                                                \
  String dbg = "disabling feature per #define constant '" ;                     \
  cli_params.removeEmptyStrings() ;                                             \
  cli_params.addArray(DisableFeatures()) ; cli_params.removeDuplicates(false) ; \
/*cli_params.mergeArray(DisabledFeatures()) ; // TODO: JUCE 4 feature */        \
  for (int switch_n = 0 ; switch_n < cli_params.size() ; ++switch_n)            \
    Trace::TraceState(dbg + cli_params[switch_n] + "'") ;                       \
  if (TEXT_BIN_NYI ) { Trace::TraceState(dbg + "TEXT_BIN_NYI'" ) ;              \
                       DisabledFeatures.set(CONFIG::TEXT_ID  , var::null) ; }   \
  if (IMAGE_BIN_NYI) { Trace::TraceState(dbg + "IMAGE_BIN_NYI'") ;              \
                       DisabledFeatures.set(CONFIG::IMAGE_ID , var::null) ; }


void SeedIrcNetworks()
{
#  if SEED_IRC_NETWORKS
  AvCaster::SetValue(CONFIG::NETWORK_ID , var(String("irc.debian.org"))) ;
  AvCaster::SetValue(CONFIG::PORT_ID    , var(6667                    )) ;
  AvCaster::SetValue(CONFIG::NICK_ID    , var(String("[mr-cooldude]" ))) ;
  AvCaster::SetValue(CONFIG::CHANNEL_ID , var(String("#av-caster"    ))) ;
//   AvCaster::SetValue(CONFIG::NETWORK_ID , var(String("localhost"     ))) ;
//   AvCaster::SetValue(CONFIG::NICK_ID    , var(String("bill-auger"    ))) ;
//   AvCaster::SetValue(CONFIG::CHANNEL_ID , var(String("#mychat"       ))) ;
  AvCaster::StorePreset(AvCaster::GetPresetName()) ;
#  endif // SEED_IRC_NETWORKS
}

#  define DEBUG_SEED_IRC_NETWORKS SeedIrcNetworks() ;


/* state */

#  define DEBUG_TRACE_INIT_PHASE_1 Trace::TraceState("validating environment") ;

#  define DEBUG_TRACE_INIT_PHASE_2 Trace::TraceState("instantiating model") ;

#  define DEBUG_TRACE_INIT_PHASE_3 Trace::TraceState("processing CLI params") ;

#  define DEBUG_TRACE_INIT_PHASE_4 Trace::TraceState("instantiating GUI") ;

#  define DEBUG_TRACE_INIT_PHASE_5                                               \
  Trace::TraceState((IsMediaEnabled) ? "instantiating media" : "media disabled") ;

#  define DEBUG_TRACE_INIT_PHASE_6                                            \
  Trace::TraceState((IsChatEnabled) ? "instantiating chat" : "chat disabled") ;

#  define DEBUG_TRACE_INIT_PHASE_7 Trace::TraceState("finalizing initialization") ;

#  define DEBUG_TRACE_INIT_PHASE_8 Trace::TraceState("AvCaster ready") ;

#  define DEBUG_TRACE_HANDLE_CLI_PARAMS String token ;                                   \
  if      (cli_params.contains(APP::CLI_HELP_TOKEN   )) token = APP::CLI_HELP_TOKEN ;    \
  else if (cli_params.contains(APP::CLI_PRESETS_TOKEN)) token = APP::CLI_PRESETS_TOKEN ; \
  else if (cli_params.contains(APP::CLI_VERSION_TOKEN)) token = APP::CLI_VERSION_TOKEN ; \
  if (token.isNotEmpty()) Trace::TraceConfig("found terminating cli token " + token)    ;

#  define DEBUG_TRACE_PROCESS_CLI_PARAMS StringArray handled_tokens , unhandled_tokens ;        \
  for (String* token = cli_params.begin() ; token != cli_params.end() ; ++token)                \
    if (*token == APP::CLI_PRESET_TOKEN          ||                                             \
        *token == APP::CLI_DISABLE_MEDIA_TOKEN   ||                                             \
        *token == APP::CLI_SCREEN_ONLY_TOKEN     ||                                             \
        *token == APP::CLI_CAMERA_ONLY_TOKEN     ||                                             \
        *token == APP::CLI_TEXT_ONLY_TOKEN       ||                                             \
        *token == APP::CLI_IMAGE_ONLY_TOKEN      ||                                             \
        *token == APP::CLI_DISABLE_PREVIEW_TOKEN ||                                             \
        *token == APP::CLI_DISABLE_AUDIO_TOKEN   ||                                             \
        *token == APP::CLI_DISABLE_CHAT_TOKEN     )                                             \
         handled_tokens.add(*token) ;                                                           \
    else unhandled_tokens.add(*token) ;                                                         \
  if (handled_tokens  .size()) Trace::TraceConfig("found pre-init cli tokens [ "            +   \
                                                  handled_tokens  .joinIntoString(",") + "]") ; \
  if (unhandled_tokens.size()) Trace::TraceConfig("found unknown cli tokens  [ "            +   \
                                                  unhandled_tokens.joinIntoString(",") + "]") ; \
  Trace::TraceConfigVb("dumping cli_params => [" + cli_params     .joinIntoString(",") + "]")   ;

#  define DEBUG_TRACE_VALIDATE_ENVIRONMENT                                                          \
  bool is_err = false ; String dbg = "" ;                                                           \
  if (!is_sufficient_gst_version) { is_err = true ; dbg += " insufficient libgstreamer version" ; } \
  if (!is_sufficient_irc_version) { is_err = true ; dbg += " insufficient libircclient version" ; } \
  if (!is_valid_home_dir        ) { is_err = true ; dbg += " invlaid HOME_DIR" ;                  } \
  if (!is_valid_appdata_dir     ) { is_err = true ; dbg += " invlaid APPDATA_DIR" ;               } \
  if (!is_valid_pictures_dir    ) { is_err = true ; dbg += " invlaid PICTURES_DIR" ;              } \
  if (!is_valid_videos_dir      ) { is_err = true ; dbg += " invlaid VIDEOS_DIR" ;                } \
  if (is_err) Trace::TraceError(dbg) ; else Trace::TraceState("environment is sane")                ;

#  define DEBUG_TRACE_REFRESH_GUI                            \
  String gui = (!IsInitialized   ) ? "Background" :          \
               (is_config_pending) ? "Config"     :          \
               (is_preview_on    ) ? "Preview"    : "Chat" ; \
  Trace::TraceState("showing " + gui + " GUI")               ;

#  define DEBUG_TRACE_SHUTDOWN_PHASE_1 Trace::TraceState("shutting down network") ;

#  define DEBUG_TRACE_SHUTDOWN_PHASE_2 Trace::TraceState("shutting down media") ;

#  define DEBUG_TRACE_SHUTDOWN_PHASE_3 Trace::TraceState("shutting down storage") ;


/* config */

#  define DEBUG_TRACE_HANDLE_CONFIG_CHANGE                                              \
  bool   was_preset_combo_changed  = a_key == CONFIG::PRESET_ID ;                       \
  bool   was_config_button_pressed = a_key == CONFIG::IS_PENDING_ID ;                   \
  bool   is_swapping_presets       = was_preset_combo_changed  && !is_config_pending ;  \
  bool   is_enter_config_mode      = was_config_button_pressed &&  is_config_pending ;  \
  bool   is_exiting_config_mode    = was_config_button_pressed && !is_config_pending ;  \
  bool   should_logout_chat        = is_swapping_presets || is_enter_config_mode ;      \
  String pad                       = "\n              " ;                               \
  Trace::TraceConfigVb("handling config value change '" + STRING(a_key) + "'"   +       \
      pad + "is_media_toggle      = " + String(is_media_toggle       )          +       \
      pad + "is_preset_control    = " + String(is_preset_control     )          +       \
      pad + "is_stream_active     = " + String(is_stream_active      )          +       \
      pad + "is_config_pending    = " + String(is_config_pending     )          +       \
      pad + "is_swapping_presets  = " + String(is_swapping_presets   )          +       \
      pad + "is_enter_config_mode = " + String(is_enter_config_mode  )          +       \
      pad + "is_exit_config_mode  = " + String(is_exiting_config_mode)          +       \
      pad + "should_logout_chat   = " + String(should_logout_chat    )          +       \
      pad + "should_login_chat    = " + String(should_login_chat     )          )       ;


/* helpers */

#  define DEBUG_TRACE_DISPLAY_ALERT                                                     \
  if      (message_type == GUI::ALERT_TYPE_WARNING) Trace::TraceWarning(message_text) ; \
  else if (message_type == GUI::ALERT_TYPE_ERROR  ) Trace::TraceError  (message_text)   ;

#else // DEBUG_TRACE

#  define DEBUG_DISABLE_FEATURES           ;
#  define DEBUG_SEED_IRC_NETWORKS          ;
#  define DEBUG_TRACE_INIT_PHASE_1         ;
#  define DEBUG_TRACE_INIT_PHASE_2         ;
#  define DEBUG_TRACE_INIT_PHASE_3         ;
#  define DEBUG_TRACE_INIT_PHASE_4         ;
#  define DEBUG_TRACE_INIT_PHASE_5         ;
#  define DEBUG_TRACE_INIT_PHASE_6         ;
#  define DEBUG_TRACE_INIT_PHASE_7         ;
#  define DEBUG_TRACE_INIT_PHASE_8         ;
#  define DEBUG_TRACE_HANDLE_CLI_PARAMS    ;
#  define DEBUG_TRACE_PROCESS_CLI_PARAMS   ;
#  define DEBUG_TRACE_VALIDATE_ENVIRONMENT ;
#  define DEBUG_TRACE_REFRESH_GUI          ;
#  define DEBUG_TRACE_SHUTDOWN_PHASE_1     ;
#  define DEBUG_TRACE_SHUTDOWN_PHASE_2     ;
#  define DEBUG_TRACE_SHUTDOWN_PHASE_3     ;
#  define DEBUG_TRACE_HANDLE_CONFIG_CHANGE ;
#  define DEBUG_TRACE_DISPLAY_ALERT        ;

#endif // DEBUG_TRACE
#endif // _TRACEAVCASTER_H_

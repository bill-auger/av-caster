/*\
|*|  AvCaster - light-weight native gStreamer GUI for screencast, webcam, and audio streaming
|*|  Copyright 2015-2018 bill-auger <https://github.com/bill-auger/av-caster/issues>
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


#include "Gstreamer.h"
#include "AvCaster.h"
#include "../Trace/TraceAvCaster.h"


/* AvCaster public class variables */

ScopedPointer<AvCasterStore> AvCaster::Store ; // Initialize()


/* AvCaster private class variables */

JUCEApplicationBase*     AvCaster::App            = nullptr ; // Initialize()
MainContent*             AvCaster::Gui            = nullptr ; // Initialize()
#ifndef DISABLE_CHAT
ScopedPointer<IrcClient> AvCaster::Irc ;                      // Initialize()
#endif // DISABLE_CHAT
bool                     AvCaster::IsInitialized  = false ;   // Initialize()
bool                     AvCaster::IsMediaEnabled = true ;    // Initialize()
bool                     AvCaster::IsChatEnabled  = true ;    // Initialize()
NamedValueSet            AvCaster::DisabledFeatures ;         // ProcessCliParams()


/* AvCaster public class methods */

void AvCaster::Warning(String message_text) { Alert::Push(GUI::ALERT_TYPE_WARNING , message_text) ; }

void AvCaster::Error(String message_text) { Alert::Push(GUI::ALERT_TYPE_ERROR , message_text) ; }

#ifndef DISABLE_CHAT
void AvCaster::AddChatLine(String prefix , String nick , String message)
{
  Gui->chat->addChatLine(prefix , nick , message) ;
}
#endif // DISABLE_CHAT

#ifndef DISABLE_CHAT
void AvCaster::SendChat(String chat_message)
{
  Irc->sendChat(chat_message) ;
  IrcClient::AddUserChat(String::empty , IRC::YOU_NICK , chat_message) ;
}
#endif // DISABLE_CHAT

StringArray AvCaster::VersionMsg()
{
  StringArray version_msg = StringArray(GetVersionString()) ;

  version_msg.add(SystemStats::getJUCEVersion()) ;
  version_msg.add(Gstreamer::VersionMsg()) ;
#ifndef DISABLE_CHAT
  version_msg.add(IrcClient::VersionMsg()) ;
#endif // DISABLE_CHAT

  return version_msg ;
}

String AvCaster::GetVersionString()
{
#ifdef DEBUG
  return APP::APP_NAME + " v" + APP::APP_VERSION + " (DEBUG)" ;
#else // DEBUG
  return APP::APP_NAME + " v" + APP::APP_VERSION ;
#endif // DEBUG
}

Rectangle<int> AvCaster::GetPreviewBounds() { return Gui->getPreviewBounds() ; }

void AvCaster::DeactivateControl(const Identifier& a_key) { Store->deactivateControl(a_key) ; }

void AvCaster::SetValue(const Identifier& a_key , const var a_value)
{
  ValueTree storage_node = (CONFIG::RootKeys()   .contains(a_key)) ? Store->root        :
                           (CONFIG::PresetKeys() .contains(a_key)) ? Store->config      :
                           (CONFIG::NetworkKeys().contains(a_key)) ? Store->network     :
                                                                     ValueTree::invalid ;

  Store->setValueViaGui(storage_node , a_key , a_value) ;
}

void AvCaster::StorePreset(String preset_name) { Store->storePreset(preset_name) ; }

void AvCaster::RenamePreset(String preset_name) { Store->renamePreset(preset_name) ; }

void AvCaster::DeletePreset() { Store->deletePreset() ; }

void AvCaster::ResetPreset() { Store->resetPreset() ; }

// bool AvCaster::IsConfigGuiSane() { return Gui->config->validateParams() ; }

bool AvCaster::IsStaticPreset() { return AvCaster::GetPresetIdx() < CONFIG::N_STATIC_PRESETS ; }

int AvCaster::GetPresetIdx() { return int(Store->root[CONFIG::PRESET_ID]) ; }

String AvCaster::GetPresetName()
{
  ValueTree current_preset = Store->presets.getChild(GetPresetIdx()) ;

  return STRING(current_preset[CONFIG::PRESET_NAME_ID]) ;
}

bool AvCaster::GetIsPreviewActive()
{
  return bool(Store->config[CONFIG::PREVIEW_ID]) && !GetIsConfigPending() ;
}

bool AvCaster::GetIsConfigPending() { return bool(Store->root[CONFIG::IS_PENDING_ID]) ; }

StringArray AvCaster::GetPresetsNames() { return Store->presetsNames() ; }

StringArray AvCaster::GetCameraNames() { return Store->cameraNames() ; }

StringArray AvCaster::GetAudioNames() { return Store->audioNames() ; }

StringArray AvCaster::GetCameraResolutions() { return Store->getCameraResolutions() ; }

Point<int> AvCaster::GetCameraResolution()
{
  int         resolution_n = int(Store->config[CONFIG::CAMERA_RES_ID]) ;
  StringArray resolutions  = Store->getCameraResolutions() ;
  String      resolution   = resolutions[(~resolution_n) ? resolution_n : 0] ;
  StringArray res_tokens   = StringArray::fromTokens(resolution , "x" , "") ;
  int         camera_w     = res_tokens[0].getIntValue() ;
  int         camera_h     = res_tokens[1].getIntValue() ;

  return Point<int>(camera_w , camera_h) ;
}

String AvCaster::GetCameraPath()
{
  ValueTree camera_store = Store->getCameraStore() ;

  return STRING(camera_store[CONFIG::CAMERA_PATH_ID]) ;
}

int AvCaster::GetCameraRate()
{
  ValueTree camera_store    = Store->getCameraStore() ;
  int       camera_rate     = int(camera_store[CONFIG::CAMERA_RATE_ID]) ;
//   int       output_rate_idx = int(Store->config[CONFIG::FRAMERATE_ID]) ;
//   int       output_rate     = CONFIG::FRAMERATES[output_rate_idx].getIntValue() ;

  return (camera_store.isValid()) ? camera_rate : CONFIG::DEFAULT_CAMERA_RATE ;
}

StringArray AvCaster::GetChatNicks() { return Store->getChatNicks() ; }

void AvCaster::UpdateChatters(StringArray nicks) { Store->updateChatters(nicks) ; }


/* AvCaster private class methods */

bool AvCaster::Initialize(JUCEApplicationBase* main_app   , MainContent* main_content ,
                          StringArray          cli_params                             )
{
  App = main_app ;
  Gui = main_content ;

  if (HandleCliParams(cli_params)) return false ;

DEBUG_TRACE_INIT_PHASE_1

  if (!ValidateEnvironment()) return false ;

DEBUG_TRACE_INIT_PHASE_2

  // load persistent configuration
  if ((Store = new AvCasterStore()) == nullptr) return false ;

DEBUG_TRACE_INIT_PHASE_3
DEBUG_DISABLE_FEATURES

  // disable features and controls per cli args
  ProcessCliParams(cli_params) ; // populates DisabledFeatures
  IsMediaEnabled = !DisabledFeatures.contains(CONFIG::OUTPUT_ID ) ;
  IsChatEnabled  = !DisabledFeatures.contains(CONFIG::NETWORK_ID) ;
  for (int feature_n = 0 ; feature_n < DisabledFeatures.size() ; ++feature_n)
    DeactivateControl(DisabledFeatures.getName(feature_n)) ;

DEBUG_TRACE_INIT_PHASE_4

  // initialze GUI
  Gui->initialize(Store->config , Store->network , Store->chatters , DisabledFeatures) ;

DEBUG_TRACE_INIT_PHASE_5

  // initialize libgtreamer
  void* x_window = Gui->getWindowHandle() ;
  if (IsMediaEnabled &&
     !Gstreamer::Initialize(Store->config , x_window , DisabledFeatures))
    return false ;

DEBUG_TRACE_INIT_PHASE_6
DEBUG_SEED_IRC_NETWORKS

  // initialize libircclient
#ifndef DISABLE_CHAT
  if (IsChatEnabled && (Irc = new IrcClient(Store->network) == nullptr) return false ;
#endif // DISABLE_CHAT

DEBUG_TRACE_INIT_PHASE_7

  // finalize initialization
  StorePreset(GetPresetName()) ; RefreshGui() ; IsInitialized = true ;

  // subscribe to model change events
  Store->listen(true) ;

DEBUG_TRACE_INIT_PHASE_8

  return IsInitialized ;
}

void AvCaster::Shutdown()
{
  Alert::Display() ;

DEBUG_TRACE_SHUTDOWN_PHASE_1

#ifndef DISABLE_CHAT
  // shutdown network
  if (Irc != nullptr) Irc->waitForThreadToExit(5000) ; Irc = nullptr ;
#endif // DISABLE_CHAT

DEBUG_TRACE_SHUTDOWN_PHASE_2

  // shutdown media
  if (IsMediaEnabled) Gstreamer::Shutdown() ;

DEBUG_TRACE_SHUTDOWN_PHASE_3

  // shutdown storage
  if (Store != nullptr) Store->shutdown() ; Store = nullptr ;

  IsInitialized = false ;
}

void AvCaster::HandleTimer(int timer_id)
{
  switch (timer_id)
  {
    case APP::TIMER_HI_ID:                                         break ;
    case APP::TIMER_MED_ID: UpdateStatusGUI() ; Alert::Display() ; break ;
    case APP::TIMER_LO_ID:  PumpThreads() ;                        break ;
    default:                                                       break ;
  }
}

void AvCaster::UpdateStatusGUI()
{
/*
  Gui->statusbar->setStatusL("Frame: "    + String(MuxStream->currentFrame  ) + " " +
                             "FPS: "      + String(MuxStream->currentFps    )       ) ;
  Gui->statusbar->setStatusC("Bitrate: "  + String(MuxStream->currentBitrate) + " " +
                             "Q: "        + String(MuxStream->currentQ      )       ) ;
  Gui->statusbar->setStatusR("Filesize: " + String(MuxStream->currentSize   ) + " " +
                             "Duration: " + String(MuxStream->currentTime   )       ) ;
*/
}

void AvCaster::HandleConfigChanged(const Identifier& a_key)
{
  if (GetPresetIdx() == CONFIG::INVALID_IDX) return ; // renaming

  bool is_media_toggle          = Store->isMediaToggleKey (a_key) ;
  bool is_preset_control        = Store->isPresetConfigKey(a_key) ;
  bool is_stream_active         = bool(Store->config[CONFIG::OUTPUT_ID]) ;
  bool is_config_pending        = AvCaster::GetIsConfigPending() ;
  bool should_stop_stream       = is_preset_control && is_stream_active ;
  bool should_reconfigure_media = is_preset_control || is_media_toggle ;
  bool should_reconfigure_chat  = is_preset_control ;
  bool should_login_chat        = is_preset_control && !is_config_pending ;

DEBUG_TRACE_HANDLE_CONFIG_CHANGE

  if (should_stop_stream       ) Store->deactivateControl(CONFIG::OUTPUT_ID) ;
  if (!should_reconfigure_media) return ;

#ifndef DISABLE_CHAT
  // reconfigure Irc networks
  if (should_reconfigure_chat) Irc->configure(should_login_chat) ;
#endif // DISABLE_CHAT

  // reconfigure Gstreamer elements
  Gstreamer::Reconfigure(a_key) ;

  // store back changes and refresh GUI
  StorePreset(GetPresetName()) ; RefreshGui() ;
}

void AvCaster::RefreshGui()
{
  bool       is_config_pending = bool(Store->root  [CONFIG::IS_PENDING_ID]) ;
  bool       is_preview_on     = bool(Store->config[CONFIG::PREVIEW_ID   ]) ;
  Component* control_component = (is_config_pending) ? static_cast<Component*>(Gui->presets ) :
                                                       static_cast<Component*>(Gui->controls) ;
  Component* front_component   = (is_config_pending) ? static_cast<Component*>(Gui->config  ) :
                                 (is_preview_on    ) ? static_cast<Component*>(Gui->preview ) :
                                                       static_cast<Component*>(Gui->chat    ) ;

DEBUG_TRACE_REFRESH_GUI

  // propogate configuration change to all interested views
  Gui->background  ->toFront(true) ;
  control_component->toFront(true) ;
  front_component  ->toFront(true) ;

  UpdateStatus() ;
}

void AvCaster::UpdateStatus()
{
  bool   is_output_active = bool(Store->config[CONFIG::OUTPUT_ID     ]) ;
  int    sink_idx         = int (Store->config[CONFIG::OUTPUT_SINK_ID]) ;
  String title_text       = APP::APP_NAME + " - " ;
  String status_text      = String::empty ;

  // titlebar text
  if      (!is_output_active                  ) title_text += GUI::IDLE_TITLE_TEXT ;
  else if (sink_idx == CONFIG::FILE_OUTPUT_IDX) title_text += GUI::FILE_TITLE_TEXT ;
  else if (sink_idx == CONFIG::RTMP_OUTPUT_IDX) title_text += GUI::RTMP_TITLE_TEXT ;
  else                                          return ;

  // statusbar text
  if (IsInitialized) status_text = GUI::READY_STATUS_TEXT ;

  Gui->mainWindow->setName       (title_text ) ;
  Gui->statusbar ->setStatusL    (status_text) ;
#ifdef TRAY_ICON
  Gui->trayIcon  ->setIconTooltip(title_text + GUI::TRAY_TOOTIP) ;
#endif // TRAY_ICON
}

bool AvCaster::HandleCliParams(StringArray cli_params)
{
  // detect terminating CLI params
  String token = (cli_params.contains(APP::CLI_HELP_TOKEN   )) ? APP::CLI_HELP_TOKEN    :
                 (cli_params.contains(APP::CLI_VERSION_TOKEN)) ? APP::CLI_VERSION_TOKEN :
                 (cli_params.contains(APP::CLI_PRESETS_TOKEN)) ? APP::CLI_PRESETS_TOKEN :
                                                                 String::empty          ;

DEBUG_TRACE_HANDLE_CLI_PARAMS

  if (token.isEmpty()) return false ;

  StringArray cli_output ;

  // handle terminating CLI params
  if      (token == APP::CLI_HELP_TOKEN   ) cli_output = APP::CLI_USAGE_MSG ;
  else if (token == APP::CLI_VERSION_TOKEN) cli_output = VersionMsg() ;
  else if (token == APP::CLI_PRESETS_TOKEN)
  {
    // load persistent configuration as normal
    Store = new AvCasterStore() ; int n_presets = Store->presets.getNumChildren() ;
    if (Store != nullptr && n_presets > 0)
    {
      // dump preset indices and names
      cli_output.add("Presets:") ;
      for (int preset_n = 0 ; preset_n < n_presets ; ++preset_n)
      {
        ValueTree preset      = Store->presets.getChild(preset_n) ;
        String    preset_name = STRING(preset[CONFIG::PRESET_NAME_ID]) ;

        cli_output.add("\t" + String(preset_n) + ") \"" + preset_name + "\"") ;
      }
    }
  }

  if (!cli_output.isEmpty()) printf("%s\n\n" , CHARSTAR(cli_output.joinIntoString("\n"))) ;

  return true ;
}

void AvCaster::ProcessCliParams(StringArray cli_params)
{
DEBUG_TRACE_PROCESS_CLI_PARAMS

  // load initial configuration preset
  if (cli_params.contains(APP::CLI_PRESET_TOKEN))
  {
    // set initial preset from cli param
    int token_idx  = cli_params.indexOf(APP::CLI_PRESET_TOKEN) ;
    int preset_idx = cli_params[token_idx + 1].getIntValue() ;

    if (~preset_idx) SetValue(CONFIG::PRESET_ID , preset_idx) ;
  }

  // disable features
  bool is_media_enabled , is_screen_enabled  , is_camera_enabled , is_text_enabled ,
       is_image_enabled , is_preview_enabled , is_audio_enabled  , is_chat_enabled ;
       is_media_enabled = is_screen_enabled  = is_camera_enabled = is_text_enabled =
       is_image_enabled = is_preview_enabled = is_audio_enabled  = is_chat_enabled = true ;
  for (String* token = cli_params.begin() ; token != cli_params.end() ; ++token)
    if      (*token == APP::CLI_DISABLE_MEDIA_TOKEN  )
      is_media_enabled = is_screen_enabled = is_camera_enabled  =
      is_text_enabled  = is_image_enabled  = is_preview_enabled = is_audio_enabled = false ;
    else if (*token == APP::CLI_SCREEN_ONLY_TOKEN    )
      is_camera_enabled = is_text_enabled   = is_image_enabled = false ;
    else if (*token == APP::CLI_CAMERA_ONLY_TOKEN    )
      is_screen_enabled = is_text_enabled   = is_image_enabled = false ;
    else if (*token == APP::CLI_TEXT_ONLY_TOKEN      )
      is_screen_enabled = is_camera_enabled = is_image_enabled = false ;
    else if (*token == APP::CLI_IMAGE_ONLY_TOKEN     )
      is_screen_enabled = is_camera_enabled = is_text_enabled  = false ;
    else if (*token == APP::CLI_DISABLE_PREVIEW_TOKEN) is_preview_enabled = false ;
    else if (*token == APP::CLI_DISABLE_AUDIO_TOKEN  ) is_audio_enabled   = false ;
    else if (*token == APP::CLI_DISABLE_CHAT_TOKEN   ) is_chat_enabled    = false ;

  if (!is_screen_enabled ) DisabledFeatures.set(CONFIG::SCREEN_ID  , var::null) ;
  if (!is_camera_enabled ) DisabledFeatures.set(CONFIG::CAMERA_ID  , var::null) ;
  if (!is_text_enabled   ) DisabledFeatures.set(CONFIG::TEXT_ID    , var::null) ;
  if (!is_image_enabled  ) DisabledFeatures.set(CONFIG::IMAGE_ID   , var::null) ;
  if (!is_preview_enabled) DisabledFeatures.set(CONFIG::PREVIEW_ID , var::null) ;
  if (!is_audio_enabled  ) DisabledFeatures.set(CONFIG::AUDIO_ID   , var::null) ;
  if (!is_media_enabled  ) DisabledFeatures.set(CONFIG::OUTPUT_ID  , var::null) ;
  if (!is_chat_enabled   ) DisabledFeatures.set(CONFIG::NETWORK_ID , var::null) ;
}

bool AvCaster::ValidateEnvironment()
{
  bool is_sufficient_gst_version = Gstreamer::IsSufficientVersion() ;
#ifndef DISABLE_CHAT
  bool is_sufficient_irc_version = IrcClient::IsSufficientVersion() ;
#else // DISABLE_CHAT
  bool is_sufficient_irc_version = (true) ? true : (bool)1 ;
#endif // DISABLE_CHAT
  bool is_valid_home_dir         = APP::HomeDir    ().isDirectory() ;
  bool is_valid_appdata_dir      = APP::AppdataDir ().isDirectory() ;
  bool is_valid_pictures_dir     = APP::PicturesDir().isDirectory() ;
  bool is_valid_videos_dir       = APP::VideosDir  ().isDirectory() ;

DEBUG_TRACE_VALIDATE_ENVIRONMENT

  if (!is_sufficient_gst_version) AvCaster::Error(GUI::GST_INSUFFICIENT_ERROR_MSG) ;
  if (!is_sufficient_irc_version) AvCaster::Error(GUI::IRC_INSUFFICIENT_ERROR_MSG) ;

  return is_sufficient_gst_version && is_sufficient_irc_version &&
         is_valid_home_dir         && is_valid_appdata_dir      && is_valid_videos_dir ;
}

bool AvCaster::PumpThreads()
{
  bool is_quit_pending = App->getApplicationReturnValue() != 0 ;
  bool should_quit     = is_quit_pending && !Alert::AreAnyPending() ;

#ifndef DISABLE_CHAT
  if (IsChatEnabled) Irc->pump() ;
#endif // DISABLE_CHAT

  if (should_quit) App->quit() ;
}

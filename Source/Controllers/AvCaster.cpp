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
NamedValueSet            AvCaster::DisabledFeatures ;         // Initialize()
bool                     AvCaster::IsMediaEnabled = true ;    // Initialize()
bool                     AvCaster::IsChatEnabled  = true ;    // Initialize()
Array<Alert*>            AvCaster::Alerts ;                   // Warning() , Error()
bool                     AvCaster::IsAlertModal   = false ;   // GetModalCb() , OnModalDismissed()


/* AvCaster public class methods */

void AvCaster::Warning(String message_text)
{
  Alerts.add(new Alert(GUI::ALERT_TYPE_WARNING , message_text)) ;
}

void AvCaster::Error(String message_text)
{
  Alerts.add(new Alert(GUI::ALERT_TYPE_ERROR , message_text)) ;
}

void AvCaster::AddChatLine(String prefix , String nick , String message)
{
  Gui->chat->addChatLine(prefix , nick , message) ;
}

ModalComponentManager::Callback* AvCaster::GetModalCb()
{
  IsAlertModal = true ;

  return ModalCallbackFunction::create(OnModalDismissed , 0) ;
}

void AvCaster::OnModalDismissed(int result , int unused) { IsAlertModal = false ; }

#ifndef DISABLE_CHAT
void AvCaster::SendChat(String chat_message)
{
  Irc->sendChat(chat_message) ;
  IrcClient::AddUserChat(String::empty , IRC::YOU_NICK , chat_message) ;
}
#endif // DISABLE_CHAT

String AvCaster::GstVersionMsg() { return Gstreamer::VersionMsg() ; }

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

String AvCaster::GetVersionString()
{
  return APP::APP_NAME + " v" + ProjectInfo::versionString ;
}

void AvCaster::UpdateChatters(StringArray nicks) { Store->updateChatters(nicks) ; }


/* AvCaster private class methods */

bool AvCaster::Initialize(JUCEApplicationBase* main_app , MainContent* main_content)
{
  App                    = main_app ;
  Gui                    = main_content ;
  StringArray cli_params = JUCEApplicationBase::getCommandLineParameterArray() ;

  if (HandleCliParams(cli_params)) return false ;

DEBUG_TRACE_INIT_PHASE_1

  if (!ValidateEnvironment()) return false ;

DEBUG_TRACE_INIT_PHASE_2

  // load persistent configuration
  if ((Store = new AvCasterStore()) == nullptr) return false ;

DEBUG_TRACE_INIT_PHASE_3
DEBUG_DISABLE_FEATURES

  // disable features and controls per cli args
  ProcessCliParams(cli_params) ;
  IsMediaEnabled   = !DisabledFeatures.contains(CONFIG::OUTPUT_ID ) ;
  IsChatEnabled    = !DisabledFeatures.contains(CONFIG::NETWORK_ID) ;
  for (int feature_n = 0 ; feature_n < DisabledFeatures.size() ; ++feature_n)
    DeactivateControl(DisabledFeatures.getName(feature_n)) ;

DEBUG_TRACE_INIT_PHASE_4

  // initialze GUI
  NamedValueSet disabled_features = NamedValueSet(DisabledFeatures) ;
  Gui->initialize(Store->config     , Store->network , Store->chatters ,
                  disabled_features , APP::picturesDir()               ) ;

DEBUG_TRACE_INIT_PHASE_5

  // initialize libgtreamer
  void* x_window = Gui->getWindowHandle() ;
  if (IsMediaEnabled &&
     !Gstreamer::Initialize(Store->config , x_window , disabled_features , APP::videosDir()))
    return false ;

DEBUG_TRACE_INIT_PHASE_6
DEBUG_SEED_IRC_NETWORKS

  // initialize libircclient
#ifndef DISABLE_CHAT
  if (IsChatEnabled) Irc = new IrcClient(Store->network) ;
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
  if (!IsInitialized) return ;

  DisplayAlert() ;

DEBUG_TRACE_SHUTDOWN_PHASE_1

#ifndef DISABLE_CHAT
  // shutdown network
  if (IsChatEnabled) { Irc->waitForThreadToExit(5000) ; Irc = nullptr ; }
#endif // DISABLE_CHAT

DEBUG_TRACE_SHUTDOWN_PHASE_2

  // shutdown media
  if (IsMediaEnabled) Gstreamer::Shutdown() ;

DEBUG_TRACE_SHUTDOWN_PHASE_3

  // shutdown storage
  if (Store != nullptr) Store->listen(false) ; IsInitialized = false ;
  if (Store != nullptr) Store->storeConfig() ; Store         = nullptr ;
}

void AvCaster::HandleTimer(int timer_id)
{
  switch (timer_id)
  {
    case APP::TIMER_HI_ID:                                                      break ;
    case APP::TIMER_MED_ID: UpdateStatusGUI() ; DisplayAlert() ;                break ;
#ifndef DISABLE_CHAT
    case APP::TIMER_LO_ID:  if (!InitFail() && IsChatEnabled) PumpIrcClient() ; break ;
#else // DISABLE_CHAT
    case APP::TIMER_LO_ID:  InitFail() ;                                        break ;
#endif // DISABLE_CHAT
    default:                                                                    break ;
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

  bool is_stream_active           = bool(Store->config[CONFIG::OUTPUT_ID]) ;
  bool was_preset_combo_changed   = a_key == CONFIG::PRESET_ID ;
  bool was_config_button_pressed  = a_key == CONFIG::IS_PENDING_ID ;
  bool is_config_pending          = AvCaster::GetIsConfigPending() ;
  bool is_swapping_presets        = was_preset_combo_changed  && !is_config_pending ;
  bool is_exiting_config_mode     = was_config_button_pressed && !is_config_pending ;
  bool should_login_chat          = is_swapping_presets || is_exiting_config_mode ;

DEBUG_TRACE_HANDLE_CONFIG_CHANGE

  if (!Store->isMediaKey(a_key) && !Store->isReconfigureKey(a_key)) return ;
  if (Store->isReconfigureKey(a_key) && is_stream_active)
  { SetValue(CONFIG::OUTPUT_ID , false) ; return ; } // defer handling

  // reconfigure Gstreamer elements
  Gstreamer::Reconfigure(a_key) ;

  // reconfigure Irc networks
#ifndef DISABLE_CHAT
  if (Store->isReconfigureKey(a_key)) Irc->configure(should_login_chat) ;
#endif // DISABLE_CHAT

  // store changes and refresh GUI
  StorePreset(GetPresetName()) ; RefreshGui() ;
}

void AvCaster::RefreshGui()
{
  bool       is_config_pending = bool(Store->root  [CONFIG::IS_PENDING_ID]) ;
  bool       is_preview_on     = bool(Store->config[CONFIG::PREVIEW_ID   ]) ;
  Component* control_component = (is_config_pending) ? static_cast<Component*>(Gui->presets   ) :
                                                       static_cast<Component*>(Gui->controls  ) ;
  Component* view_component    = (is_config_pending) ? static_cast<Component*>(Gui->config    ) :
                                 (is_preview_on    ) ? static_cast<Component*>(Gui->preview   ) :
                                                       static_cast<Component*>(Gui->chat      ) ;

DEBUG_TRACE_REFRESH_GUI

  // propogate configuration change to all interested panes
  Gui->background  ->toFront(true) ;
  control_component->toFront(true) ;
  view_component   ->toFront(true) ;

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
DEBUG_TRACE_HANDLE_CLI_PARAMS

  // handle terminating CLI params
  if      (cli_params.contains(APP::CLI_HELP_TOKEN   ))
  { printf("%s\n" , CHARSTAR(APP::CLI_USAGE_MSG  )) ; return true ; }
  else if (cli_params.contains(APP::CLI_PRESETS_TOKEN))
  {
    // load persistent configuration as normal
    Store = new AvCasterStore() ; int n_presets = Store->presets.getNumChildren() ;
    if (Store  == nullptr || n_presets == 0) return true ;

    // dump preset indices and names then quit
    printf("Presets:\n") ;
    for (int preset_n = 0 ; preset_n < n_presets ; ++preset_n)
    {
      ValueTree preset      = Store->presets.getChild(preset_n) ;
      String    preset_name = STRING(preset[CONFIG::PRESET_NAME_ID]) ;
      printf("\t%d: \"%s\"\n" , preset_n , CHARSTAR(preset_name)) ;
    }

    return true ;
  }
  else if (cli_params.contains(APP::CLI_VERSION_TOKEN))
  { printf("%s\n" , CHARSTAR(APP::CLI_VERSION_MSG)) ; return true ; }

  return false ;
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
  bool is_sufficient_irc_version = true ;
#endif // DISABLE_CHAT
  bool is_valid_home_dir         = APP::homeDir()    .isDirectory() ;
  bool is_valid_appdata_dir      = APP::appdataDir() .isDirectory() ;
  bool is_valid_pictures_dir     = APP::picturesDir().isDirectory() ;
  bool is_valid_videos_dir       = APP::videosDir()  .isDirectory() ;

DEBUG_TRACE_VALIDATE_ENVIRONMENT

  if (!is_sufficient_gst_version) AvCaster::Error(GUI::GST_INSUFFICIENT_ERROR_MSG) ;
  if (!is_sufficient_irc_version) AvCaster::Error(GUI::IRC_INSUFFICIENT_ERROR_MSG) ;

  return is_sufficient_gst_version && is_sufficient_irc_version &&
         is_valid_home_dir         && is_valid_appdata_dir      && is_valid_videos_dir ;
}

void AvCaster::DisplayAlert()
{
  if (IsAlertModal || Alerts.size() == 0) return ;

  GUI::AlertType message_type = Alerts[0]->messageType ;
  String         message_text = Alerts[0]->messageText ;

DEBUG_TRACE_DISPLAY_ALERT

#ifdef SUPRESS_ALERTS
Alerts.remove(0) ; return ;
#endif // SUPRESS_ALERTS

  switch (message_type)
  {
    case GUI::ALERT_TYPE_WARNING: Gui->warning(message_text) ; break ;
    case GUI::ALERT_TYPE_ERROR:   Gui->error  (message_text) ; break ;
    default:                                                   break ;
  }

  Alerts.remove(0) ;
}

bool AvCaster::InitFail()
{
  bool init_fail_pending = App->getApplicationReturnValue() != 0 ;
  bool should_quit       = init_fail_pending && !IsAlertModal && Alerts.size() == 0 ;

  if (should_quit) { App->shutdown() ; App->quit() ; }

  return init_fail_pending ;
}

#ifndef DISABLE_CHAT
void AvCaster::PumpIrcClient() { if (!Irc->isThreadRunning()) Irc->startThread() ; }
#endif // DISABLE_CHAT

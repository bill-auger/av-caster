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
#include "Trace/TraceAvCaster.h"


/* AvCaster public class variables */

ScopedPointer<AvCasterStore> AvCaster::Store ; // Initialize()


/* AvCaster private class variables */

MainContent*             AvCaster::Gui            = nullptr ; // Initialize()
#ifndef DISABLE_CHAT
ScopedPointer<IrcClient> AvCaster::Irc            = nullptr ; // Initialize()
#endif // DISABLE_CHAT
StringArray              AvCaster::CliParams ;                // Initialize()
bool                     AvCaster::IsInitialized  = false ;   // Initialize()
bool                     AvCaster::IsMediaEnabled = true ;    // ProcessCliParams()
bool                     AvCaster::IsChatEnabled  = true ;    // ProcessCliParams()
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

#ifndef DISABLE_CHAT
void AvCaster::SendChat(String chat_message) { Irc->sendChat(chat_message) ; }
#else // DISABLE_CHAT
void AvCaster::SendChat(String chat_message) {}
#endif // DISABLE_CHAT

ModalComponentManager::Callback* AvCaster::GetModalCb()
{
  IsAlertModal = true ;

  return ModalCallbackFunction::create(OnModalDismissed , 0) ;
}

void AvCaster::OnModalDismissed(int result , int unused) { IsAlertModal = false ; }

Rectangle<int> AvCaster::GetPreviewBounds() { return Gui->getPreviewBounds() ; }

void AvCaster::SetConfig(const Identifier& a_key , var a_value)
{
DEBUG_TRACE_GUI_SET_CONFIG

  Store->setConfig(a_key , a_value) ;
}

ValueTree AvCaster::GetConfigStore() { return ValueTree(Store->config) ; }

void AvCaster::DeactivateControl(const Identifier& a_key) { Store->deactivateControl(a_key) ; }

void AvCaster::StorePreset(String preset_name) { Store->storePreset(preset_name) ; }

void AvCaster::RenamePreset(String preset_name) { Store->renamePreset(preset_name) ; }

void AvCaster::DeletePreset() { Store->deletePreset() ; }

void AvCaster::ResetPreset() { Store->resetPreset() ; }

bool AvCaster::SetPreset(String preset_name , int option_n)
{
  int        stored_option_n      = GetPresetIdx() ;
  String     stored_preset_name   = GetPresetName() ;
  bool       is_valid_option      = !!(~option_n) ;
  bool       is_static_preset     = IsStaticPreset() ;
  bool       is_empty             = preset_name.isEmpty() ;
  bool       has_name_changed     = preset_name != stored_preset_name && !is_empty ;
  bool       should_rename_preset = !is_valid_option && has_name_changed && !is_static_preset ;
  bool       should_reset_option  = RejectPresetChange() || should_rename_preset ;
  var        value                = var((is_valid_option) ? option_n : stored_option_n) ;

DEBUG_TRACE_HANDLE_PRESETCOMBO

  // reject empty preset name
  if (!is_valid_option && is_empty) return false ;

  // rename preset , restore selection , or commit preset change
  if (should_rename_preset) RenamePreset(preset_name) ;
  if (!should_reset_option) SetConfig(CONFIG::PRESET_ID , value) ;
  else                      RefreshGui() ;

  return true ;
}

bool AvCaster::RejectPresetChange()
{
  bool is_output_on = bool(Store->config[CONFIG::OUTPUT_ID]) ;

DEBUG_TRACE_REJECT_CONFIG_CHANGE

  if (is_output_on) Warning(GUI::CONFIG_CHANGE_ERROR_MSG) ;

  return is_output_on ;
}

// bool AvCaster::IsConfigGuiSane() { return Gui->config->validateConfigGui() ; }
bool AvCaster::IsConfigGuiSane() { return true ; }

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

String AvCaster::GetCameraResolution()
{
  int         resolution_n = int(Store->config[CONFIG::CAMERA_RES_ID]) ;
  StringArray resolutions  = Store->getCameraResolutions() ;

  return resolutions[(~resolution_n) ? resolution_n : 0] ;
}

String AvCaster::GetCameraPath()
{
  ValueTree camera_store = Store->getCameraConfig() ;

  return STRING(camera_store[CONFIG::CAMERA_PATH_ID]) ;
}

int AvCaster::GetCameraRate()
{
  ValueTree camera_store    = Store->getCameraConfig() ;
  int       camera_rate     = int(camera_store[CONFIG::CAMERA_RATE_ID]) ;
//   int       output_rate_idx = int(Store->config[CONFIG::FRAMERATE_ID]) ;
//   int       output_rate     = CONFIG::FRAMERATES[output_rate_idx].getIntValue() ;

  return (camera_store.isValid()) ? camera_rate : CONFIG::DEFAULT_CAMERA_RATE ;
}

String AvCaster::GetVersionString()
{
  return APP::APP_NAME + " v" + ProjectInfo::versionString ;
}

void AvCaster::UpdateIrcHost(StringArray alias_uris , String actual_host)
{
  Store->updateIrcHost(alias_uris , actual_host) ;
}

/*
void AvCaster::RenameServer(String requested_host , String actual_host)
{
  ValueTree  server_store   = Store->servers.getChildWithProperty(CONFIG::HOST_ID , requested_host) ;
  ValueTree  chatters_store = server_store.getChildWithName(CONFIG::CHATTERS_ID) ;
  int        server_idx     = Store->servers.indexOf(server_store) ;
  Identifier server_id      = CONFIG::FilterId(actual_host , APP::VALID_URI_CHARS) ;
  ValueTree  updated_store  = ValueTree(server_id) ;

  Store->servers.removeChild       (server_store    ,               nullptr) ;
  Store->servers.addChild          (updated_store   , server_idx  , nullptr) ;
  server_store  .removeChild       (chatters_store  ,               nullptr) ;
  updated_store .addChild          (chatters_store  , -1          , nullptr) ;
  updated_store .copyPropertiesFrom(server_store    ,               nullptr) ;
  server_store  .setProperty       (CONFIG::HOST_ID , actual_host , nullptr) ;
}
*/
#ifdef PREFIX_CHAT_NICKS
void AvCaster::UpdateChatNicks(String host , String channel , StringArray nicks)
{
  Store->updateChatNicks(host , channel , nicks) ;
  const MessageManagerLock mmLock ; Gui->chat->updateVisiblilty() ;
}
#else // PREFIX_CHAT_NICKS
void AvCaster::UpdateChatNicks(String host , StringArray nicks)
{
  Store->updateChatNicks(host , nicks) ;
  const MessageManagerLock mmLock ; Gui->chat->updateVisiblilty() ;
}
#endif // PREFIX_CHAT_NICKS

StringArray AvCaster::GetChatNicks(ValueTree chatters_store)
{
  return Store->getChatNicks(chatters_store) ;
}


/* AvCaster private class methods */

bool AvCaster::Initialize(MainContent* main_content)
{
  Gui       = main_content ;
  CliParams = JUCEApplicationBase::getCommandLineParameterArray() ;

  CliParams.removeEmptyStrings() ; CliParams.removeDuplicates(false) ;

DEBUG_DISABLE_FEATURES

  if (HandleCliParamsTerminating()) return false ;

DEBUG_TRACE_INIT_PHASE_1

  if (!ValidateEnvironment()) return false ;

DEBUG_TRACE_INIT_PHASE_2

  // load persistent configuration
  if ((Store = new AvCasterStore()) == nullptr) return false ;

DEBUG_TRACE_INIT_PHASE_3

  // initialze GUI
  Gui->initialize(Store->servers) ;

  if (!ProcessCliParams()) return false ;

DEBUG_TRACE_INIT_PHASE_4

  // initialize libgtreamer
  if (IsMediaEnabled && !Gstreamer::Initialize(Gui->getWindowHandle())) return false ;

DEBUG_TRACE_INIT_PHASE_5

  // initialize libircclient
#ifndef DISABLE_CHAT
  if (IsChatEnabled && (Irc = new IrcClient(Store->servers)) == nullptr) return false ;
#endif // DISABLE_CHAT

DEBUG_TRACE_INIT_PHASE_6

  // finalize initialization
  StorePreset(GetPresetName()) ; RefreshGui() ; IsInitialized = true ;

  // subscribe to model change events
  Store->listen(true) ;

DEBUG_TRACE_INIT_PHASE_7

  return IsInitialized ;
}

void AvCaster::Shutdown()
{
  DisplayAlert() ;

DEBUG_TRACE_SHUTDOWN_PHASE_1

#ifndef DISABLE_CHAT
  // shutdown network
  if (IsChatEnabled && Irc != nullptr && Irc->isThreadRunning()) Irc->stopThread(500) ;
  Irc = nullptr ;
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
    case APP::TIMER_HI_ID:                                          break ;
    case APP::TIMER_MED_ID: UpdateStatusGUI() ; DisplayAlert() ;    break ;
#ifndef DISABLE_CHAT
    case APP::TIMER_LO_ID:  if (IsChatEnabled) Irc->startThread() ; break ;
#endif // DISABLE_CHAT
    default:                                                        break ;
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
  if (!Store->isControlKey(a_key)) return ;

  // reconfigure gStreamer element
  Gstreamer::Reconfigure(a_key) ;

  // store changes
  StorePreset(GetPresetName()) ;

  // refresh GUI
  RefreshGui() ;
}

void AvCaster::RefreshGui()
{
  bool       is_config_pending = bool(Store->root  [CONFIG::IS_PENDING_ID]) ;
  bool       is_preview_on     = bool(Store->config[CONFIG::PREVIEW_ID   ]) &&
                                 Gstreamer::IsPreviewEnabled                 ;
  Component* control_component = (is_config_pending) ? static_cast<Component*>(Gui->presets ) :
                                                       static_cast<Component*>(Gui->controls) ;
  Component* view_component    = (is_config_pending) ? static_cast<Component*>(Gui->config ) :
                                 (is_preview_on    ) ? static_cast<Component*>(Gui->preview) :
                                                       static_cast<Component*>(Gui->chat   ) ;

DEBUG_TRACE_REFRESH_GUI

  // propogate configuration change to all interested panes
  Gui->background  ->toFront(true) ;
  control_component->toFront(true) ;
  view_component   ->toFront(true) ;

  RefreshStatus() ;
}

void AvCaster::RefreshStatus()
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

  Gui->getTopLevelComponent()->setName   (title_text ) ;
  Gui->statusbar             ->setStatusL(status_text) ;
}

bool AvCaster::HandleCliParamsTerminating()
{
DEBUG_TRACE_HANDLE_CLI_PARAMS_TERMINATING

  if      (CliParams.contains(APP::CLI_HELP_TOKEN   ))
  { printf("%s\n" , CHARSTAR(APP::CLI_USAGE_MSG  )) ; return true ; }
  else if (CliParams.contains(APP::CLI_PRESETS_TOKEN))
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
  else if (CliParams.contains(APP::CLI_VERSION_TOKEN))
  { printf("%s\n" , CHARSTAR(APP::CLI_VERSION_MSG)) ; return true ; }

  return false ;
}

bool AvCaster::ProcessCliParams()
{
DEBUG_TRACE_HANDLE_CLI_PARAMS

  // load initial configuration preset
  if (CliParams.contains(APP::CLI_PRESET_TOKEN))
  {
    // set initial preset from cli param
    int token_idx  = CliParams.indexOf(APP::CLI_PRESET_TOKEN) ;
    int preset_idx = CliParams[token_idx + 1].getIntValue() ;

    if (~preset_idx) Store->setConfig(CONFIG::PRESET_ID , preset_idx) ;
  }

  // disable features
  bool& is_screen_enabled     = Gstreamer::IsScreenEnabled ;
  bool& is_camera_enabled     = Gstreamer::IsCameraEnabled ;
  bool& is_text_enabled       = Gstreamer::IsTextEnabled ;
  bool& is_image_enabled      = Gstreamer::IsImageEnabled ;
  bool& is_compositor_enabled = Gstreamer::IsCompositorEnabled ;
  bool& is_preview_enabled    = Gstreamer::IsPreviewEnabled ;
  bool& is_audio_enabled      = Gstreamer::IsAudioEnabled ;
  for (String* token = CliParams.begin() ; token != CliParams.end() ; ++token)
    if      (*token == APP::CLI_DISABLE_MEDIA_TOKEN  )
      IsMediaEnabled   = is_screen_enabled     = is_camera_enabled  = is_text_enabled  =
      is_image_enabled = is_compositor_enabled = is_preview_enabled = is_audio_enabled = false ;
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
    else if (*token == APP::CLI_DISABLE_CHAT_TOKEN   ) IsChatEnabled      = false ;

  // assert dependent compositor elements (TODO: remove these restrictions allowing any configuration)
  int n_video_inputs    = ((is_screen_enabled) ? 1 : 0) + ((is_camera_enabled) ? 1 : 0) +
                          ((is_text_enabled  ) ? 1 : 0) + ((is_image_enabled ) ? 1 : 0) ;
  is_compositor_enabled = n_video_inputs == APP::N_COMPOSITOR_INPUTS ;
  is_preview_enabled    = is_preview_enabled && is_compositor_enabled ;
  bool is_sane          = !IsMediaEnabled || is_compositor_enabled || n_video_inputs == 1 ;

  Gui->disableControls(IsMediaEnabled   , is_screen_enabled , is_camera_enabled  ,
                       is_text_enabled  , is_image_enabled  , is_preview_enabled ,
                       is_audio_enabled                                          ) ;

DUMP_DEBUG_MEDIA_SWITCHES

  return is_sane ;
}

bool AvCaster::ValidateEnvironment()
{
DEBUG_TRACE_VALIDATE_ENVIRONMENT

  return Gstreamer::IsSufficientVersion() &&
#ifndef DISABLE_CHAT
         IrcClient::IsSufficientVersion() &&
#endif // DISABLE_CHAT
         APP::HOME_DIR   .isDirectory()   &&
         APP::APPDATA_DIR.isDirectory()   &&
         APP::VIDEOS_DIR .isDirectory()    ;
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

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


#include "Gstreamer.h"
#include "AvCaster.h"
#include "Trace/TraceAvCaster.h"


/* AvCaster public class variables */

ScopedPointer<AvCasterStore> AvCaster::Store ; // Initialize()


/* AvCaster private class variables */

MainContent*             AvCaster::Gui                 = nullptr ; // Initialize()
ScopedPointer<IrcClient> AvCaster::Irc                 = nullptr ; // Initialize()
StringArray              AvCaster::CliParams ;                     // initialize()
bool                     AvCaster::IsMediaEnabled      = true ;    // HandleCliParamsPreInit()
bool                     AvCaster::IsScreenEnabled     = true ;    // HandleCliParamsPreInit()
bool                     AvCaster::IsCameraEnabled     = true ;    // HandleCliParamsPreInit()
bool                     AvCaster::IsTextEnabled       = true ;    // HandleCliParamsPreInit()
bool                     AvCaster::IsImageEnabled      = true ;    // HandleCliParamsPreInit()
bool                     AvCaster::IsCompositorEnabled = true ;    // HandleCliParamsPreInit()
bool                     AvCaster::IsPreviewEnabled    = true ;    // HandleCliParamsPreInit()
bool                     AvCaster::IsAudioEnabled      = true ;    // HandleCliParamsPreInit()
bool                     AvCaster::IsChatEnabled       = true ;    // HandleCliParamsPreInit()
Array<Alert*>            AvCaster::Alerts ;
bool                     AvCaster::IsAlertModal        = false ;   // Warning() , Error()


/* AvCaster public class methods */

void AvCaster::SetStatusL(String status_text) { Gui->statusbar->setStatusL(status_text) ; }

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

void AvCaster::SendChat(String chat_message) { Irc->sendChat(chat_message) ; }

ModalComponentManager::Callback* AvCaster::GetModalCb()
{
  IsAlertModal = true ;

  return ModalCallbackFunction::create(OnModalDismissed , 0) ;
}

void AvCaster::OnModalDismissed(int result , int unused) { IsAlertModal = false ; }

bool AvCaster::GetIsMediaEnabled() { return IsMediaEnabled ; }

bool AvCaster::GetIsScreenEnabled() { return IsScreenEnabled ; }

bool AvCaster::GetIsCameraEnabled() { return IsCameraEnabled ; }

bool AvCaster::GetIsTextEnabled() { return IsTextEnabled ; }

bool AvCaster::GetIsImageEnabled() { return IsImageEnabled ; }

bool AvCaster::GetIsCompositorEnabled() { return IsCompositorEnabled ; }

bool AvCaster::GetIsPreviewEnabled() { return IsPreviewEnabled ; }

bool AvCaster::GetIsAudioEnabled() { return IsAudioEnabled ; }

void* AvCaster::GetGuiXwinHandle() { return Gui->getWindowHandle() ; }

Rectangle<int> AvCaster::GetPreviewBounds() { return Gui->getPreviewBounds() ; }

void AvCaster::SetConfig(const Identifier& a_key , var a_value)
{
DEBUG_TRACE_SET_CONFIG

  Store->setConfig(a_key , a_value) ;
}

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
  if (!is_valid_option) if (is_empty) return false ;

  // rename preset , restore selection , or commit preset change
  if (should_rename_preset) RenamePreset(preset_name) ;
  if (!should_reset_option) SetConfig(CONFIG::PRESET_ID , value) ;
  else                      RefreshGui() ;

  return true ;
}

ValueTree AvCaster::GetConfigStore() { return Store->config ; }

bool AvCaster::RejectPresetChange()
{
  bool is_output_on = bool(Store->config[CONFIG::IS_OUTPUT_ACTIVE_ID]) ;

DEBUG_TRACE_REJECT_CONFIG_CHANGE

  if (is_output_on) Warning(GUI::CONFIG_CHANGE_ERROR_MSG) ;

  return is_output_on ;
}

bool AvCaster::IsStaticPreset() { return AvCaster::GetPresetIdx() < CONFIG::N_STATIC_PRESETS ; }

int AvCaster::GetPresetIdx() { return int(Store->root[CONFIG::PRESET_ID]) ; }

String AvCaster::GetPresetName()
{
  ValueTree current_preset = Store->presets.getChild(GetPresetIdx()) ;

  return STRING(current_preset[CONFIG::PRESET_NAME_ID]) ;
}

bool AvCaster::GetIsPreviewActive()
{
  return bool(Store->config[CONFIG::IS_PREVIEW_ACTIVE_ID]) && !GetIsConfigPending() ;
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

  return resolutions[resolution_n] ;
}

String AvCaster::GetCameraPath()
{
  ValueTree camera_store = Store->getCameraConfig() ;

  return STRING(camera_store[CONFIG::CAMERA_PATH_ID]) ;
}

int AvCaster::GetCameraRate()
{
  ValueTree camera_store = Store->getCameraConfig() ;

  return int(camera_store[CONFIG::CAMERA_RATE_ID]) ;
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
#else // PREFIX_CHAT_NICKS
void AvCaster::UpdateChatNicks(String host , StringArray nicks)
{
  Store->updateChatNicks(host , nicks) ;
#endif // PREFIX_CHAT_NICKS

  const MessageManagerLock mmLock ; Gui->chat->updateVisiblilty() ;
}

StringArray AvCaster::GetChatNicks(ValueTree chatters_store)
{
  return Store->getChatNicks(chatters_store) ;
}


/* AvCaster private class methods */

bool AvCaster::Initialize(MainContent* main_content)
{
  Gui       = main_content ;
  CliParams = JUCEApplicationBase::getCommandLineParameterArray() ;

  // debug feature switches
#ifdef NO_INITIALIZE_MEDIA
  CliParams.add(APP::CLI_DISABLE_MEDIA_TOKEN) ;
#endif // NO_INITIALIZE_MEDIA
#ifdef SCREEN_ONLY
  CliParams.add(APP::CLI_SCREEN_ONLY_TOKEN) ;
#endif // SCREEN_ONLY
#ifdef CAMERA_ONLY
  CliParams.add(APP::CLI_CAMERA_ONLY_TOKEN) ;
#endif // CAMERA_ONLY
#ifdef TEXT_ONLY
#  ifndef DISABLE_TEXT_BIN
  CliParams.add(APP::CLI_TEXT_ONLY_TOKEN) ;
#  endif // DISABLE_TEXT_BIN
#endif // TEXT_ONLY
#ifdef IMAGE_ONLY
#  ifndef DISABLE_IMAGE_BIN
  CliParams.add(APP::CLI_IMAGE_ONLY_TOKEN) ;
#  endif // DISABLE_IMAGE_BIN
#endif // IMAGE_ONLY
#if NO_INITIALIZE_PREVIEW
  CliParams.add(APP::CLI_DISABLE_PREVIEW_TOKEN) ;
#endif // NO_INITIALIZE_PREVIEW
#if NO_INITIALIZE_AUDIO
  CliParams.add(APP::CLI_DISABLE_AUDIO_TOKEN) ;
#endif // NO_INITIALIZE_AUDIO
#ifdef NO_INSTANTIATE_IRC
  CliParams.add(APP::CLI_DISABLE_CHAT_TOKEN) ;
#endif // NO_INSTANTIATE_IRC
#ifdef DISABLE_TEXT_BIN
  IsTextEnabled = false ;
#endif // DISABLE_TEXT_BIN
#ifdef DISABLE_IMAGE_BIN
  IsImageEnabled = false ;
#endif // DISABLE_IMAGE_BIN

  if (!HandleCliParamsPreInit()) return false ;

DEBUG_TRACE_INIT_PHASE_1

  if (!ValidateEnvironment()) return false ;

DEBUG_TRACE_INIT_PHASE_2

  // load persistent configuration
  if ((Store = new AvCasterStore()) == nullptr) return false ;

DEBUG_TRACE_INIT_PHASE_3

  // initialze GUI
  Gui->initialize(Store->servers) ; SetWindowTitle() ; RefreshGui() ;

DEBUG_TRACE_INIT_PHASE_4

  // initialize libgtreamer
  if (IsMediaEnabled && !Gstreamer::Initialize()) return false ;

DEBUG_TRACE_INIT_PHASE_5

  // initialize libircclient
  if (IsChatEnabled && (Irc = new IrcClient(Store->servers)) == nullptr) return false ;

DEBUG_TRACE_INIT_PHASE_6

  if (!HandleCliParamsPostInit()) return false ;

  SetStatusL(GUI::READY_STATUS_TEXT) ;

  // subscribe to model change events
  Store->listen(true) ;

  return true ;
}

void AvCaster::Shutdown()
{
  DisplayAlert() ;

DEBUG_TRACE_SHUTDOWN_PHASE_1

  // shutdown network
  if (IsChatEnabled && Irc != nullptr && Irc->isThreadRunning()) Irc->stopThread(5000) ;
  Irc = nullptr ;

#ifndef NO_INITIALIZE_MEDIA
DEBUG_TRACE_SHUTDOWN_PHASE_2

  // shutdown media
  Gstreamer::Shutdown() ;
#endif // NO_INITIALIZE_MEDIA

DEBUG_TRACE_SHUTDOWN_PHASE_3

  // shutdown storage
  if (Store != nullptr) Store->storeConfig() ; Store = nullptr ;
}

void AvCaster::HandleTimer(int timer_id)
{
  switch (timer_id)
  {
    case APP::GUI_TIMER_HI_ID:                                          break ;
    case APP::GUI_TIMER_MED_ID: UpdateStatusGUI() ; DisplayAlert() ;    break ;
    case APP::GUI_TIMER_LO_ID:  if (IsChatEnabled) Irc->startThread() ; break ;
    default:                                                            break ;
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

  // update chat visibility
  if (a_key == CONFIG::IS_PREVIEW_ACTIVE_ID || a_key == CONFIG::IS_PENDING_ID)
    Gui->chat->updateVisiblilty() ;

  // reconfigure gStreamer element
  bool is_config_pending = bool(Store->root[CONFIG::IS_PENDING_ID   ]) ;
  if (Gstreamer::Reconfigure(a_key , is_config_pending))
  {
    StorePreset(GetPresetName()) ;

    if      (a_key == CONFIG::IS_PENDING_ID     ||
             a_key == CONFIG::PRESET_ID          ) RefreshGui() ;
    else if (a_key == CONFIG::IS_OUTPUT_ACTIVE_ID) SetWindowTitle() ;
  }
  else
  {
    Store->toogleControl(a_key) ; RefreshGui() ; return ;
  }
}

void AvCaster::RefreshGui()
{
  bool       is_config_pending = bool(Store->root  [CONFIG::IS_PENDING_ID       ]) ;
  bool       is_preview_on     = bool(Store->config[CONFIG::IS_PREVIEW_ACTIVE_ID]) && IsPreviewEnabled ;
  Component* control_component = (is_config_pending) ? static_cast<Component*>(Gui->presets ) :
                                                       static_cast<Component*>(Gui->controls) ;
  Component* view_component    = (is_config_pending) ? static_cast<Component*>(Gui->config ) :
                                 (is_preview_on    ) ? static_cast<Component*>(Gui->preview) :
                                                       static_cast<Component*>(Gui->chat   ) ;

DEBUG_TRACE_REFRESH_GUI

  Gui->background  ->toFront(true) ;
  control_component->toFront(true) ;
  view_component   ->toFront(true) ;
}

void AvCaster::SetWindowTitle()
{
  bool   is_output_active = bool(Store->config[CONFIG::IS_OUTPUT_ACTIVE_ID]) ;
  int    sink_idx         = int (Store->config[CONFIG::OUTPUT_SINK_ID     ]) ;
  String title_text ;

  if      (!is_output_active                  ) title_text = GUI::IDLE_TITLE_TEXT ;
  else if (sink_idx == CONFIG::FILE_STREAM_IDX) title_text = GUI::FILE_TITLE_TEXT ;
  else if (sink_idx == CONFIG::RTMP_STREAM_IDX) title_text = GUI::RTMP_TITLE_TEXT ;
  else                                          return ;

  Gui->getTopLevelComponent()->setName(APP::APP_NAME + " - " + title_text) ;
}

bool AvCaster::HandleCliParamsPreInit()
{
DEBUG_TRACE_HANDLE_CLI_PARAMS_PRE_INIT

  if      (CliParams.contains(APP::CLI_VERSION_TOKEN))
  { printf("%s\n" , CHARSTAR(APP::CLI_VERSION_MSG)) ; return false ; }
  else if (CliParams.contains(APP::CLI_HELP_TOKEN   ))
  { printf("%s\n" , CHARSTAR(APP::CLI_USAGE_MSG  )) ; return false ; }
  else if (CliParams.contains(APP::CLI_PRESETS_TOKEN))
  {
    int n_presets = Store->presets.getNumChildren() ; if (n_presets == 0) return false ;

    // dump preset indices and names then quit
    printf("Presets:\n") ;
    for (int preset_n = 0 ; preset_n < n_presets ; ++preset_n)
    {
      ValueTree preset      = Store->presets.getChild(preset_n) ;
      String    preset_name = STRING(preset[CONFIG::PRESET_NAME_ID]) ;
      printf("\t%d: \"%s\"\n" , preset_n , CHARSTAR(preset_name)) ;
    }

    return false ;
  }
  else if (CliParams.contains(APP::CLI_DISABLE_MEDIA_TOKEN  ))
    IsMediaEnabled = IsScreenEnabled     = IsCameraEnabled  =
    IsTextEnabled  = IsCompositorEnabled = IsPreviewEnabled = false ;
  else if (CliParams.contains(APP::CLI_SCREEN_ONLY_TOKEN    ))
    IsCameraEnabled = IsTextEnabled   = IsImageEnabled = IsCompositorEnabled = false ;
  else if (CliParams.contains(APP::CLI_CAMERA_ONLY_TOKEN    ))
    IsScreenEnabled = IsTextEnabled   = IsImageEnabled = IsCompositorEnabled = false ;
  else if (CliParams.contains(APP::CLI_TEXT_ONLY_TOKEN      ))
    IsScreenEnabled = IsCameraEnabled = IsImageEnabled = IsCompositorEnabled = false ;
  else if (CliParams.contains(APP::CLI_IMAGE_ONLY_TOKEN     ))
    IsScreenEnabled = IsCameraEnabled = IsTextEnabled  = IsCompositorEnabled = false ;
  else if (CliParams.contains(APP::CLI_DISABLE_PREVIEW_TOKEN)) IsPreviewEnabled = false ;
  else if (CliParams.contains(APP::CLI_DISABLE_AUDIO_TOKEN  )) IsAudioEnabled   = false ;
  else if (CliParams.contains(APP::CLI_DISABLE_CHAT_TOKEN   )) IsChatEnabled    = false ;

  return true ;
}

bool AvCaster::HandleCliParamsPostInit()
{
DEBUG_TRACE_HANDLE_CLI_PARAMS_POST_INIT

  if (CliParams.contains(APP::CLI_PRESET_TOKEN))
  {
    // set initial preset from cli param
    int token_idx  = CliParams.indexOf(APP::CLI_PRESET_TOKEN) ;
    int preset_idx = CliParams[token_idx + 1].getIntValue() ;

    if (~preset_idx) Store->setConfig(CONFIG::PRESET_ID , preset_idx) ;
  }

   return true ;
}

bool AvCaster::ValidateEnvironment()
{
DEBUG_TRACE_VALIDATE_ENVIRONMENT

  return Gstreamer::IsSufficientVersion() &&
         IrcClient::IsSufficientVersion() &&
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

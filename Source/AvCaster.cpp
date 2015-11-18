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

MainContent*             AvCaster::Gui          = nullptr ; // Initialize()
ScopedPointer<IrcClient> AvCaster::Irc          = nullptr ; // Initialize()
StringArray              AvCaster::CliParams ;              // initialize()
Array<Alert*>            AvCaster::Alerts ;
bool                     AvCaster::IsAlertModal = false ;   // Warning() , Error()


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

void AvCaster::AddChatLine(String nick , String message)
{
  Gui->chat->addChatLine(nick , message) ;
}

void AvCaster::SendChat(String chat_message) { Irc->sendChat(chat_message) ; }

ModalComponentManager::Callback* AvCaster::GetModalCb()
{
  IsAlertModal = true ;

  return ModalCallbackFunction::create(OnModalDismissed , 0) ;
}

void AvCaster::OnModalDismissed(int result , int unused) { IsAlertModal = false ; }

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

ValueTree AvCaster::GetConfigStore() { return Store->config ; }

bool AvCaster::IsStaticPreset() { return AvCaster::GetPresetIdx() < CONFIG::N_STATIC_PRESETS ; }

int AvCaster::GetPresetIdx() { return int(Store->root[CONFIG::PRESET_ID]) ; }

String AvCaster::GetPresetName()
{
  ValueTree current_preset = Store->presets.getChild(GetPresetIdx()) ;

  return STRING(current_preset[CONFIG::PRESET_NAME_ID]) ;
}

bool AvCaster::GetIsPreviewOn()
{
  return bool(Store->config[CONFIG::IS_PREVIEW_ON_ID]) && !GetIsConfigPending() ;
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

void AvCaster::UpdateChatNicks(StringArray nicks)
{
  for (String* nick = nicks.begin() ; nick != nicks.end() ; ++nick)
  {
    Identifier user_id       = CONFIG::FilterId(*nick , APP::VALID_NICK_CHARS) ;
    ValueTree  chatter_store = Store->chatters.getChildWithName(user_id) ;

DEBUG_TRACE_ADD_CHAT_NICK

    if (!chatter_store.isValid())
    {
      chatter_store = ValueTree(user_id) ;
      chatter_store.setProperty(CONFIG::CHAT_NICK_ID , var(*nick) , nullptr) ;
      Store->chatters.addChild(chatter_store , -1 , nullptr) ;
    }
  }

  for (int chatter_n = 0 ; chatter_n < Store->chatters.getNumChildren() ; ++chatter_n)
  {
    ValueTree chatter_store = Store->chatters.getChild(chatter_n) ;

DEBUG_TRACE_REMOVE_CHAT_NICK

    if (!nicks.contains(STRING(chatter_store[CONFIG::CHAT_NICK_ID])))
      Store->chatters.removeChild(chatter_store , nullptr) ;
  }

  Gui->chat->updateVisiblilty() ;
}

StringArray AvCaster::GetChatNicks()
{
  return AvCasterStore::PropertyValues(Store->chatters , CONFIG::CHAT_NICK_ID) ;
}


/* AvCaster private class methods */

bool AvCaster::Initialize(MainContent* main_content)
{
  Gui       = main_content ;
  CliParams = JUCEApplicationBase::getCommandLineParameterArray() ;

DEBUG_TRACE_INIT_VERSION

  if (!HandleCliParamsPreInit()) return false ;

DEBUG_TRACE_INIT_PHASE_1

  if (!ValidateEnvironment()) return false ;

DEBUG_TRACE_INIT_PHASE_2

  // load persistent configuration
  if ((Store = new AvCasterStore()) == nullptr) return false ;

DEBUG_TRACE_INIT_PHASE_3

  // initialze GUI
  Gui->initialize(Store->chatters) ; SetWindowTitle() ; RefreshGui() ;

#ifndef NO_INITIALIZE_MEDIA
DEBUG_TRACE_INIT_PHASE_4

  // initialize gStreamer
  if (!Gstreamer::Initialize()) return false ;
#endif // NO_INITIALIZE_MEDIA

#ifndef NO_INITIALIZE_NETWORK
DEBUG_TRACE_INIT_PHASE_5

  // initialize libircclient
  if ((Irc = new IrcClient(APP::IRC_THREAD_NAME)) == nullptr) return false ;
#endif // NO_INITIALIZE_NETWORK

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

#ifndef NO_INITIALIZE_NETWORK
DEBUG_TRACE_SHUTDOWN_PHASE_1
#ifdef RUN_NETWORK_AS_THREAD

  // shutdown network
  if (Irc->isThreadRunning()) Irc->stopThread(5000) ; delete Irc ; Irc = nullptr ;
#else // RUN_NETWORK_AS_THREAD
//   delete Irc ;
  Irc = nullptr ;
#endif // RUN_NETWORK_AS_THREAD
#endif // NO_INITIALIZE_NETWORK

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
    case APP::GUI_TIMER_HI_ID:                                       break ;
#ifdef NO_INITIALIZE_NETWORK
    case APP::GUI_TIMER_MED_ID: UpdateStatusGUI() ; DisplayAlert() ; break ;
#else // NO_INITIALIZE_NETWORK
#  ifdef RUN_NETWORK_AS_THREAD
    case APP::GUI_TIMER_MED_ID: UpdateStatusGUI() ; DisplayAlert() ; break ;
    case APP::GUI_TIMER_LO_ID:  Irc->startThread() ;                 break ;
#  else // RUN_NETWORK_AS_THREAD
    case APP::GUI_TIMER_MED_ID: UpdateStatusGUI() ; Irc->run() ; DisplayAlert() ; break ;
    case APP::GUI_TIMER_LO_ID:                                                    break ;
#  endif // RUN_NETWORK_AS_THREAD
#endif // NO_INITIALIZE_NETWORK
    default:                                                         break ;
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
  if (a_key == CONFIG::IS_PREVIEW_ON_ID || a_key == CONFIG::IS_PENDING_ID)
    Gui->chat->updateVisiblilty() ;

  // reconfigure gStreamer element
  bool is_config_pending = bool(Store->root[CONFIG::IS_PENDING_ID   ]) ;
  if (Gstreamer::Reconfigure(a_key , is_config_pending))
  {
    StorePreset(GetPresetName()) ;

    if      (a_key == CONFIG::IS_PENDING_ID ||
             a_key == CONFIG::PRESET_ID      ) RefreshGui() ;
    else if (a_key == CONFIG::IS_OUTPUT_ON_ID) SetWindowTitle() ;
  }
  else
  {
    Store->toogleControl(a_key) ; RefreshGui() ; return ;
  }
}

void AvCaster::RefreshGui()
{
  bool       is_config_pending = bool(Store->root  [CONFIG::IS_PENDING_ID   ]) ;
  bool       is_preview_on     = bool(Store->config[CONFIG::IS_PREVIEW_ON_ID]) ;
  Component* front_component   = (is_config_pending) ? static_cast<Component*>(Gui->config ) :
                                 (is_preview_on    ) ? static_cast<Component*>(Gui->preview) :
                                                       static_cast<Component*>(Gui->chat   ) ;

DEBUG_TRACE_REFRESH_GUI

  Gui->background->toFront(true) ;
  Gui->controls  ->toFront(true) ;
  front_component->toFront(true) ;
}

void AvCaster::SetWindowTitle()
{
  bool   is_output_enabled = bool(Store->config[CONFIG::IS_OUTPUT_ON_ID]) ;
  int    sink_idx          = int (Store->config[CONFIG::OUTPUT_SINK_ID ]) ;
  String title_text ;

  if      (!is_output_enabled                 ) title_text = GUI::IDLE_TITLE_TEXT ;
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

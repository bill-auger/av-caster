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


#include "AvCaster.h"
#include "Gstreamer.h"
#include "Trace/TraceAvCaster.h"


/* AvCaster public class variables */

ScopedPointer<AvCasterStore> AvCaster::Store ; // Initialize()


/* AvCaster private class variables */

MainContent*  AvCaster::Gui          = nullptr ; // Initialize()
StringArray   AvCaster::CliParams ;              // initialize()
Array<Alert*> AvCaster::Alerts ;
bool          AvCaster::IsAlertModal = false ;   // Warning() , Error()


/* AvCaster public class methods */

void AvCaster::Warning(String message_text)
{
  Alerts.add(new Alert(GUI::ALERT_TYPE_WARNING , message_text)) ;
}

void AvCaster::Error(String message_text)
{
  Alerts.add(new Alert(GUI::ALERT_TYPE_ERROR , message_text)) ;
}

ModalComponentManager::Callback* AvCaster::GetModalCb()
{
  IsAlertModal = true ;

  return ModalCallbackFunction::create(OnModalDismissed , 0) ;
}

void AvCaster::OnModalDismissed(int result , int unused) { IsAlertModal = false ; }

void AvCaster::SetConfig(Identifier a_key , var a_value)
{
  ValueTree storage_node = (a_key == CONFIG::PRESET_ID          ||
                            a_key == CONFIG::IS_CONFIG_PENDING_ID) ? Store->configRoot  :
                                                                     Store->configStore ;
DEBUG_TRACE_SET_CONFIG

  if (a_key.isValid()) storage_node.setProperty(a_key , a_value , nullptr) ;
}

void AvCaster::StorePreset(String preset_name) { Store->storePreset(preset_name) ; }

void AvCaster::RenamePreset(String preset_name) { Store->renamePreset(preset_name) ; }

void AvCaster::DeletePreset() { Store->deletePreset() ; }

void AvCaster::ResetPreset() { Store->resetPreset() ; }

ValueTree AvCaster::GetConfigStore() { return Store->configStore ; }

bool AvCaster::IsStaticPreset() { return AvCaster::GetPresetIdx() < CONFIG::N_STATIC_PRESETS ; }

int AvCaster::GetPresetIdx() { return int(Store->configRoot[CONFIG::PRESET_ID]) ; }

String AvCaster::GetPresetName()
{
  ValueTree current_preset = Store->configPresets.getChild(GetPresetIdx()) ;

  return STRING(current_preset[CONFIG::PRESET_NAME_ID]) ;
}

bool AvCaster::GetIsConfigPending() { return bool(Store->configRoot[CONFIG::IS_CONFIG_PENDING_ID]) ; }

StringArray AvCaster::GetPresetsNames() { return Store->presetsNames() ; }

StringArray AvCaster::GetCameraNames() { return Store->cameraNames() ; }

StringArray AvCaster::GetAudioNames() { return Store->audioNames() ; }

StringArray AvCaster::GetCameraResolutions() { return Store->getCameraResolutions() ; }

String AvCaster::GetCameraResolution()
{
  int         resolution_n = int(Store->configStore[CONFIG::CAMERA_RES_ID]) ;
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


/* AvCaster private class methods */

bool AvCaster::Initialize(MainContent* main_content)
{
  Gui       = main_content ;
  CliParams = JUCEApplicationBase::getCommandLineParameterArray() ;

DEBUG_TRACE_INIT_PHASE_1

  if (!ValidateEnvironment()) return false ;

DEBUG_TRACE_INIT_PHASE_2

  // load persistent configuration
  if ((Store = new AvCasterStore()) == nullptr) return false ;

DEBUG_TRACE_INIT_PHASE_3

  // instantiate GUI
  Gui->instantiate(Store->configRoot    , Store->configStore ,
                   Store->cameraDevices , Store->audioDevices) ;
  RefreshGui() ;

DEBUG_TRACE_INIT_PHASE_4

  // initialize gStreamer
  if (!Gstreamer::Initialize(Gui->getWindowHandle())) return false ;

DEBUG_TRACE_INIT_PHASE_5

  Gui->statusbar->setStatusL(GUI::READY_STATUS_TEXT) ;

  if (!HandleCliParams()) return false ;

  return true ;
}

void AvCaster::Shutdown()
{
  DisplayAlert() ;

  Gstreamer::Shutdown() ;

  if (Store != nullptr) Store->storeConfig() ; Store = nullptr ;
}

void AvCaster::HandleTimer(int timer_id)
{
  switch (timer_id)
  {
    case APP::GUI_TIMER_HI_ID:                                       break ;
    case APP::GUI_TIMER_MED_ID: UpdateStatusGUI() ; DisplayAlert() ; break ;
    case APP::GUI_TIMER_LO_ID:                                       break ;
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
  if      (a_key == CONFIG::IS_CONFIG_PENDING_ID ||
           a_key == CONFIG::PRESET_ID             ) RefreshGui() ;
  else if (Gstreamer::Reconfigure(a_key))           StorePreset(GetPresetName()) ;
  else                                              Store->toogleControl(a_key) ;
}

void AvCaster::RefreshGui()
{
DEBUG_TRACE_REFRESH_GUI

  bool is_config_pending = bool(Store->configRoot[CONFIG::IS_CONFIG_PENDING_ID]) ;

  Gui->background->toFront(true) ;
  if (is_config_pending) { Gui->controls->toFront(true) ; Gui->config  ->toFront(true) ; }
  else                   { Gui->config  ->toFront(true) ; Gui->controls->toFront(true) ; }

  if (!is_config_pending) Gstreamer::ConfigurePipeline() ;
}

bool AvCaster::HandleCliParams()
{
DEBUG_TRACE_HANDLE_CLI_PARAMS

  if      (CliParams.contains(APP::CLI_QUIT_TOKEN   )) return false ;
  if      (CliParams.contains(APP::CLI_HELP_TOKEN   ))
  { printf("%s\n" , CHARSTAR(APP::CLI_USAGE_MSG)) ; return false ; }
  else if (CliParams.contains(APP::CLI_PRESETS_TOKEN))
  {
    int n_presets = Store->configPresets.getNumChildren() ; if (n_presets == 0) return false ;

    // dump preset indices and names then quit
    printf("Presets:\n") ;
    for (int preset_n = 0  ; preset_n < n_presets ; ++preset_n)
    {
      ValueTree preset      = Store->configPresets.getChild(preset_n) ;
      String    preset_name = STRING(preset[CONFIG::PRESET_NAME_ID]) ;
      printf("\t%d: \"%s\"\n" , preset_n , CHARSTAR(preset_name)) ;
    }

    return false ;
  }
  else if (CliParams.contains(APP::CLI_PRESET_TOKEN))
  {
    // set initial preset from cli param
    int token_idx  = CliParams.indexOf(APP::CLI_PRESET_TOKEN) ;
    int preset_idx = CliParams[token_idx + 1].getIntValue() ;
DBG("preloading preset_n=" + preset_idx) ;
    if (~preset_idx) SetConfig(CONFIG::PRESET_ID , preset_idx) ;
  }

   return true ;
}

bool AvCaster::ValidateEnvironment()
{
DEBUG_TRACE_VALIDATE_ENVIRONMENT

  return APP::HOME_DIR   .isDirectory()           &&
         APP::APPDATA_DIR.isDirectory()           &&
         APP::VIDEOS_DIR .isDirectory()            ;
}

void AvCaster::DisplayAlert()
{
  if (IsAlertModal || Alerts.size() == 0) return ;

  GUI::AlertType message_type = Alerts[0]->messageType ;
  String         message_text = Alerts[0]->messageText ;

DISPLAY_ALERT

  switch (message_type)
  {
    case GUI::ALERT_TYPE_WARNING: Gui->warning(message_text) ; break ;
    case GUI::ALERT_TYPE_ERROR:   Gui->error  (message_text) ; break ;
    default:                                                   break ;
  }

  Alerts.remove(0) ;
}

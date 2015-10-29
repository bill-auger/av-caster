/*
  ==============================================================================

    AvCaster.cpp
    Created: 12 Sep 2015 10:26:17am
    Author:  bill-auger

  ==============================================================================
*/

#include "AvCaster.h"
#include "Gstreamer.h"
#include "Trace/TraceAvCaster.h"


/* AvCaster public class variables */

ScopedPointer<AvCasterStore> AvCaster::Store ; // Initialize()


/* AvCaster private class variables */

MainContent*  AvCaster::Gui          = nullptr ; // Initialize()
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

StringArray AvCaster::PresetsNames() { return Store->presetsNames() ; }

StringArray AvCaster::DevicesNames(ValueTree a_devices_node)
{
  return Store->devicesNames(a_devices_node) ;
}

void AvCaster::SetConfig(Identifier a_key , var a_value)
{
  ValueTree storage_node = (a_key == CONFIG::PRESET_ID          ||
                            a_key == CONFIG::IS_CONFIG_PENDING_ID) ? Store->configRoot  :
                                                                     Store->configStore ;

DEBUG_TRACE_SET_CONFIG

  storage_node.setProperty(a_key , a_value , nullptr) ;
}

void AvCaster::StorePreset(String preset_name) { Store->storePreset(preset_name) ; }

void AvCaster::DeletePreset() { Store->deletePreset() ; }


/* AvCaster private class methods */

bool AvCaster::Initialize(MainContent* main_content)
{
  Gui = main_content ;

DEBUG_TRACE_INIT_PHASE_1

  // load persistent configuration
  if ((Store = new AvCasterStore()) == nullptr) return false ;

DEBUG_TRACE_INIT_PHASE_2

  // instantiate GUI
  Gui->instantiate(Store->configRoot    , Store->configStore ,
                   Store->cameraDevices , Store->audioDevices) ;
  ToggleConfig() ;

DEBUG_TRACE_INIT_PHASE_3

  // initialize gStreamer
  if (!Gstreamer::Initialize(Gui->getWindowHandle())) return false ;

DEBUG_TRACE_INIT_PHASE_4

  return true ;
}

void AvCaster::Shutdown()
{
  DisplayAlert() ;

  Gstreamer::Shutdown() ;

  Store->storeConfig() ; Store = nullptr ;
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
  if (a_key == CONFIG::IS_OUTPUT_ON_ID      ) { ToggleOutput() ;    Gstreamer::Configure() ; }
  if (a_key == CONFIG::IS_INTERSTITIAL_ON_ID) { TogglePreview() ;   Gstreamer::Configure() ; }
  if (a_key == CONFIG::IS_SCREENCAP_ON_ID   ) { ToggleScreencap() ; Gstreamer::Configure() ; }
  if (a_key == CONFIG::IS_CAMERA_ON_ID      ) { ToggleCamera() ;    Gstreamer::Configure() ; }
  if (a_key == CONFIG::IS_TEXT_ON_ID        ) { ToggleText() ;      Gstreamer::Configure() ; }
  if (a_key == CONFIG::IS_PREVIEW_ON_ID     ) { TogglePreview() ;   Gstreamer::Configure() ; }
  if (a_key == CONFIG::IS_CONFIG_PENDING_ID ) { ToggleConfig() ;    Gstreamer::Configure() ; }
  if (a_key == CONFIG::PRESET_ID            ) { Gui->config ->toBack() ; ToggleConfig() ; }
}

void AvCaster::ToggleOutput() { /* TODO: */ }
void AvCaster::ToggleInterstitial() { /* TODO: */ }
void AvCaster::ToggleScreencap() { /* TODO: */ }
void AvCaster::ToggleCamera() { /* TODO: */ }
void AvCaster::ToggleText() { /* TODO: */ }
void AvCaster::TogglePreview() { /* TODO: */ }
void AvCaster::ToggleConfig()
{
  bool is_config_pending = bool(Store->configRoot[CONFIG::IS_CONFIG_PENDING_ID]) ;

  Gui->background->toFront(true) ;
  if (is_config_pending) { Gui->controls->toFront(true) ; Gui->config  ->toFront(true) ; }
  else                   { Gui->config  ->toFront(true) ; Gui->controls->toFront(true) ; }
}

void AvCaster::DisplayAlert()
{
  if (IsAlertModal || Alerts.size() == 0) return ;

  switch (Alerts[0]->messageType)
  {
    case GUI::ALERT_TYPE_WARNING:
      Gui->warning(Alerts[0]->messageText) ; Alerts.remove(0) ; break ;
    case GUI::ALERT_TYPE_ERROR:
      Gui->error  (Alerts[0]->messageText) ; Alerts.remove(0) ; break ;
    default:                                                    break ;
  }
}

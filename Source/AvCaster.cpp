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

ScopedPointer<AvCasterConfig> AvCaster::Config ; // Initialize()


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

StringArray AvCaster::DevicesNames(ValueTree a_devices_node)
{
  return Config->devicesNames(a_devices_node) ;
}


/* AvCaster private class methods */

bool AvCaster::Initialize(MainContent* main_content)
{
  Gui = main_content ;

DEBUG_TRACE_INIT_PHASE_1

  // load persistent configuration
  if ((Config = new AvCasterConfig()) == nullptr) return false ;

DEBUG_TRACE_INIT_PHASE_2

  // instantiate GUI
  Gui->instantiate(Config->configStore , Config->cameraDevices , Config->audioDevices) ;

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

  Config = nullptr ;
}

void AvCaster::HandleTimer(int timer_id)
{
  switch (timer_id)
  {
    case APP::GUI_TIMER_HI_ID:  UpdateStatusGUI() ; break ;
    case APP::GUI_TIMER_MED_ID: DisplayAlert() ;    break ;
    case APP::GUI_TIMER_LO_ID:                      break ;
    default:                                        break ;
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

/* TODO: we may want to reconfigure the stream here (e.g. text position)
 *         => ConfigureStream() ;
 *       or perform validations (e.g. screen resolution/orientation has changed)
 *         => Gui->config->loadConfig() ;                                    */
void AvCaster::HandleConfigChanged(const Identifier& a_key)
{
#if fully_working_version
  if (a_key == CONFIG::IS_PREVIEW_ON_ID) TogglePreview() ;
#endif // fully_working_version
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

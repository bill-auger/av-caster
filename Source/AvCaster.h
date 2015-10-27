/*
  ==============================================================================

    Constants.h
    Author:  bill-auger

  ==============================================================================
*/

#ifndef AVCASTER_H_INCLUDED
#define AVCASTER_H_INCLUDED


#include "Constants.h"
#include "AvCasterConfig.h"
#include "MainContent.h"


class Alert
{
public:

  Alert(GUI::AlertType message_type , String message_text)
  {
    this->messageType = message_type ;
    this->messageText = message_text ;
  }

  GUI::AlertType messageType ;
  String         messageText ;
} ;


class AvCaster
{
  friend class AvCasterApplication ;
  friend class AvCasterConfig ;


public:

  // GUI dispatchers
  static void Warning(String message_text) ;
  static void Error(  String message_text) ;

  // callbacks and event handlers
  static ModalComponentManager::Callback* GetModalCb() ;
  static void                             OnModalDismissed(int result , int unused) ;

  // helpers
  static StringArray DevicesNames(ValueTree a_devices_node) ;

  // persistence
  static ScopedPointer<AvCasterConfig> Config ;


private:

  // setup
  static bool Initialize(MainContent* main_content) ;
  static void Shutdown() ;

  // callbacks and event handlers
  static void HandleTimer        (int timer_id) ;
  static void UpdateStatusGUI() ;
  static void HandleConfigChanged(const Identifier& a_key) ;

  // helpers
  static void DisplayAlert() ;


  static MainContent*  Gui ;
  static Array<Alert*> Alerts ;
  static bool          IsAlertModal ;
} ;

#endif  // AVCASTER_H_INCLUDED

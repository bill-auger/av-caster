/*
  ==============================================================================

    Constants.h
    Author:  bill-auger

  ==============================================================================
*/

#ifndef AVCASTER_H_INCLUDED
#define AVCASTER_H_INCLUDED


#include "Constants.h"
#include "AvCasterStore.h"
#include "MainContent.h"


/**
  Alert is a helper class for the AvCaster application.
  It queues and presents GUI message boxes to the user.
*/
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


/**
  AvCaster is the controller class for the AvCaster application.
  It instantiates, initializes, and configures the runtime components
      and mediates communication amongst other parts of the application.
*/
class AvCaster
{
  friend class AvCasterApplication ;
  friend class AvCasterStore ;


public:

  // GUI dispatchers
  static void Warning(String message_text) ;
  static void Error  (String message_text) ;

  // callbacks and event handlers
  static ModalComponentManager::Callback* GetModalCb() ;
  static void                             OnModalDismissed(int result , int unused) ;

  // helpers
  static StringArray PresetsNames() ;
  static StringArray DevicesNames(ValueTree a_devices_node) ;
  static void        SetConfig   (Identifier a_key , var a_value) ;
  static void        StorePreset (String preset_name) ;
  static void        DeletePreset() ;

  // persistence
  static ScopedPointer<AvCasterStore> Store ;


private:

  // setup
  static bool Initialize(MainContent* main_content) ;
  static void Shutdown  () ;

  // callbacks and event handlers
  static void HandleTimer        (int timer_id) ;
  static void UpdateStatusGUI    () ;
  static void HandleConfigChanged(const Identifier& a_key) ;
  static void ToggleOutput       () ;
  static void ToggleInterstitial () ;
  static void ToggleScreencap    () ;
  static void ToggleCamera       () ;
  static void ToggleText         () ;
  static void TogglePreview      () ;
  static void ToggleConfig       () ;

  // helpers
  static void DisplayAlert() ;


  static MainContent*  Gui ;
  static Array<Alert*> Alerts ;
  static bool          IsAlertModal ;
} ;

#endif  // AVCASTER_H_INCLUDED

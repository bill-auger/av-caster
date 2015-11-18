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


#ifndef AVCASTER_H_INCLUDED
#define AVCASTER_H_INCLUDED

#include "Constants.h"
#include "AvCasterStore.h"
#include "MainContent.h"
#include "IrcClient.h"


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
  static void SetStatusL (String status_text) ;
  static void Warning    (String message_text) ;
  static void Error      (String message_text) ;
  static void AddChatLine(String nick , String message) ;
  static void SendChat   (String chat_message) ;

  // callbacks and event handlers
  static ModalComponentManager::Callback* GetModalCb() ;
  static void                             OnModalDismissed(int result , int unused) ;

  // getters/setters
  static void*          GetGuiXwinHandle    () ;
  static Rectangle<int> GetPreviewBounds    () ;
  static void           SetConfig           (const Identifier& a_key , var a_value) ;
  static void           StorePreset         (String preset_name) ;
  static void           RenamePreset        (String preset_name) ;
  static void           DeletePreset        () ;
  static void           ResetPreset         () ;
  static ValueTree      GetConfigStore      () ;
  static bool           IsStaticPreset      () ;
  static int            GetPresetIdx        () ;
  static String         GetPresetName       () ;
  static bool           GetIsPreviewOn      () ;
  static bool           GetIsConfigPending  () ;
  static StringArray    GetPresetsNames     () ;
  static StringArray    GetCameraNames      () ;
  static StringArray    GetAudioNames       () ;
  static StringArray    GetCameraResolutions() ;
  static String         GetCameraResolution () ;
  static String         GetCameraPath       () ;
  static int            GetCameraRate       () ;
  static String         GetVersionString    () ;
  static void           UpdateChatNicks     (StringArray nicks) ;
  static StringArray    GetChatNicks        () ;


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
  static void RefreshGui         () ;
  static void SetWindowTitle     () ;

  // helpers
  static bool HandleCliParamsPreInit () ;
  static bool HandleCliParamsPostInit() ;
  static bool ValidateEnvironment    () ;
  static void DisplayAlert           () ;


  static MainContent*             Gui ;
  static ScopedPointer<IrcClient> Irc ;
  static StringArray              CliParams ;
  static Array<Alert*>            Alerts ;
  static bool                     IsAlertModal ;
} ;

#endif // AVCASTER_H_INCLUDED

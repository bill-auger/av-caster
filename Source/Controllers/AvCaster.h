/*\
|*|  Copyright 2015-2016 bill-auger <https://github.com/bill-auger/av-caster/issues>
|*|
|*|  This file is part of the AvCaster program.
|*|
|*|  AvCaster is free software: you can redistribute it and/or modify
|*|  it under the terms of the GNU General Public License version 3
|*|  as published by the Free Software Foundation.
|*|
|*|  AvCaster is distributed in the hope that it will be useful,
|*|  but WITHOUT ANY WARRANTY; without even the implied warranty of
|*|  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|*|  GNU General Public License for more details.
|*|
|*|  You should have received a copy of the GNU General Public License
|*|  along with AvCaster.  If not, see <http://www.gnu.org/licenses/>.
\*/


#ifndef _AVCASTER_H_
#define _AVCASTER_H_

#include "../Constants/Constants.h"
#include "../Models/AvCasterStore.h"
#include "../Views/MainContent.h"
#include "IrcClient.h"


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
  static void Warning    (String message_text) ;
  static void Error      (String message_text) ;
#ifndef DISABLE_CHAT
  static void AddChatLine(String prefix , String nick , String message) ;
  static void SendChat   (String chat_message) ;
#endif // DISABLE_CHAT

  // getters/setters
  static StringArray    VersionMsg          () ;
  static String         GetVersionString    () ;
  static Rectangle<int> GetPreviewBounds    () ;
  static void           DeactivateControl   (const Identifier& a_key) ;
  static void           SetValue            (const Identifier& a_key , const var a_value) ;
  static void           StorePreset         (String preset_name) ;
  static void           RenamePreset        (String preset_name) ;
  static void           DeletePreset        () ;
  static void           ResetPreset         () ;
//   static bool           IsConfigGuiSane     () ;
  static bool           IsStaticPreset      () ;
  static int            GetPresetIdx        () ;
  static String         GetPresetName       () ;
  static bool           GetIsPreviewActive  () ;
  static bool           GetIsConfigPending  () ;
  static StringArray    GetPresetsNames     () ;
  static StringArray    GetCameraNames      () ;
  static StringArray    GetAudioNames       () ;
  static StringArray    GetCameraResolutions() ;
  static Point<int>     GetCameraResolution () ;
  static String         GetCameraPath       () ;
  static int            GetCameraRate       () ;
  static StringArray    GetChatNicks        () ;
  static void           DeleteServer        (ValueTree network_store) ;
  static void           UpdateChatters      (StringArray nicks) ;


private:

  // setup
  static bool Initialize(JUCEApplicationBase* main_app   , MainContent* main_content ,
                         StringArray          cli_params                             ) ;
  static void Shutdown  () ;

  // callbacks and event handlers
  static void HandleTimer        (int timer_id) ;
  static void UpdateStatusGUI    () ;
  static void HandleConfigChanged(const Identifier& a_key) ;
  static void RefreshGui         () ;
  static void UpdateStatus       () ;

  // init args handlers and validations
  static bool HandleCliParams    (StringArray cli_params) ;
  static void ProcessCliParams   (StringArray cli_params) ;
  static bool ValidateEnvironment() ;

  // helpers
  static bool PumpThreads() ;

  // collaborator handles
  static JUCEApplicationBase*     App ;
  static MainContent*             Gui ;
#ifndef DISABLE_CHAT
  static ScopedPointer<IrcClient> Irc ;
#endif // DISABLE_CHAT

  // model/persistence
  static ScopedPointer<AvCasterStore> Store ;

  // intialization flags
  static bool          IsInitialized ;
  static NamedValueSet DisabledFeatures ;
  static bool          IsMediaEnabled ;
  static bool          IsChatEnabled ;
} ;

#endif // _AVCASTER_H_

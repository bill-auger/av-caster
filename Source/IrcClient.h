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


#include "Constants.h"
#ifndef DISABLE_CHAT

#ifndef _IRCCLIENT_H_
#define _IRCCLIENT_H_


#include <libircclient/libircclient.h>

#include "Constants.h"


/**
  IrcClient is the IRC network communications class for the AvCaster application.
  It encapsulates interactions with the libircclient C library
      and provides cross-network channel bridging.

  Each instance can manage multiple network connections
      but aech network session is restricted to a single channel.
*/
class IrcClient : public Thread
{
  friend class AvCaster ;


public:

  ~IrcClient() ;

  // session management
  void configure(bool should_create_sessions , bool should_show_timestamps ,
                                               bool should_show_joinparts  ) ;


private:

  typedef struct IrcNetworkInfo
  {
    irc_session_t* session ;
    Identifier     network_id ;
    String         network ;
    unsigned short port ;
    String         nick ;
    String         pass ;
    String         channel ;
    String         greeting ;
    StringArray    nicks ;
  } IrcNetworkInfo ;


  IrcClient(ValueTree networks_store , bool should_show_timestamps , bool should_show_joinparts) ;

  // libircclient callbacks
  static void OnConnect   (irc_session_t* session , const char* event  , const char* origin ,
                           const char**   params  , unsigned int count                      ) ;
  static void OnChannelMsg(irc_session_t* session , const char* event  , const char* origin ,
                           const char**   params  , unsigned int count                      ) ;
  static void OnJoin      (irc_session_t* session , const char* event  , const char* origin ,
                           const char**   params  , unsigned int count                      ) ;
  static void OnPart      (irc_session_t* session , const char* event  , const char* origin ,
                           const char**   params  , unsigned int count                      ) ;
  static void OnNickChange(irc_session_t* session , const char* event  , const char* origin ,
                           const char**   params  , unsigned int count                     ) ;
  static void OnNumeric   (irc_session_t* session , unsigned int event , const char* origin ,
                           const char**   params  , unsigned int count                      ) ;

  // helpers
  static bool            IsSufficientVersion() ;
  static IrcNetworkInfo* GetNetworkInfo     (irc_session_t* session) ;
  static void            SetRetries         (Identifier network_id , int n_retries) ;
  static int             GetRetries         (Identifier network_id) ;
  static void            HandleNicks        (IrcNetworkInfo* network_info , String nicks) ;
  static void            UpdateNicks        (IrcNetworkInfo* network_info) ;
  static String          ProcessTextMeta    (const char* message) ;
  static StringArray     ProcessTimestamp   (String message) ;
  static void            AddServerChat      (String message) ;
  static void            AddClientChat      (String message) ;
  static void            AddUserChat        (String prefix , String nick , String message) ;

  // session management
  void createSessions () ;
  void destroySessions() ;
  void run            () override ;
  bool login          (IrcNetworkInfo* network_info) ;
  void sendChat       (String chat_message) ;


  static irc_callbacks_t ServerCallbacks ;
  static bool            ShouldShowTimestamps ;
  static bool            ShouldShowJoinParts ;

  ValueTree                  networksStore ;
  OwnedArray<IrcNetworkInfo> networks ;
} ;

#endif // _IRCCLIENT_H_

#endif // DISABLE_CHAT

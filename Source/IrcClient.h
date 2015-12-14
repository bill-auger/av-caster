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


#ifndef _IRC_H_
#define _IRC_H_


#include <libircclient.h>

#include "Constants.h"


typedef struct IrcServerInfo
{
  irc_session_t* session  ;
  String         host     ;
  unsigned short port     ;
  String         nick     ;
} IrcServerInfo ;


/**
  IrcClient is the IRC network communications class for the AvCaster application.
  It encapsulates interactions with the libircclient C library
      and provides cross-network channel bridging.
*/
#ifdef RUN_NETWORK_AS_THREAD
class IrcClient : public Thread
#else // RUN_NETWORK_AS_THREAD
class IrcClient
#endif // RUN_NETWORK_AS_THREAD
{
  friend class AvCaster ;


public:

  ~IrcClient() ;


private:

  IrcClient(ValueTree servers_store) ;

  // helpers
  static bool IsValidServerInfo  (IrcServerInfo* a_server_info) ;
  static bool IsSufficientVersion() ;
  static void AddServerChat      (String message) ;
  static void AddClientChat      (String message) ;
  static void AddUserChat        (String nick , String message) ;

  // libircclient callbacks
  static void OnConnect   (irc_session_t* session , const char*  event , const char* origin ,
                           const char**   params  , unsigned int count                      ) ;
  static void OnChannelMsg(irc_session_t* session , const char*  event , const char* origin ,
                           const char**   params  , unsigned int count                      ) ;
  static void OnJoin      (irc_session_t* session , const char*  event , const char* origin ,
                           const char**   params  , unsigned int count                      ) ;
  static void OnPart      (irc_session_t* session , const char*  event , const char* origin ,
                           const char**   params  , unsigned int count                      ) ;
  static void OnNumeric   (irc_session_t* session , unsigned int event , const char* origin ,
                           const char**   params  , unsigned int count                      ) ;
  static void HandleNicks (String host , String channel , StringArray nicks) ;

  // session management
  IrcServerInfo createSession(ValueTree server_store) ;
  bool          login        (IrcServerInfo* a_server_info) ;
#ifdef RUN_NETWORK_AS_THREAD
  void          run          () override ;
#else // RUN_NETWORK_AS_THREAD
  void          run          () ;
#endif // RUN_NETWORK_AS_THREAD

  void sendChat(String chat_msg) ;


  irc_callbacks_t      callbacks ;
  Array<IrcServerInfo> servers ;
  ValueTree            serversStore ; // TODO: replace servers?? replace IrcServerInfo
} ;

#endif // _IRC_H_

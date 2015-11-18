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


#ifndef IRC_H_INCLUDED
#define IRC_H_INCLUDED


#include <libircclient.h>

#include "Constants.h"


/**
  IrcClient is the IRC network communications class for the AvCaster application.
  It encapsulates interactions with the libircclient C library
      and provides cross-network channel bridging.
*/
class IrcClient : public Thread
{
  friend class AvCaster ;


  typedef struct IrcServerInfo
  {
    irc_session_t* session  ;
    const char*    host     ;
    unsigned short port     ;
    const char*    password ;
    const char*    nick     ;
    const char*    username ;
    const char*    realname ;
  } IrcServerInfo ;


public:

  ~IrcClient() ;


private:

  IrcClient(const String& thread_name) ;

  static bool IsSufficientVersion() ;

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
  static void HandleNicks (const char** params) ;

  // session management
  void createSession(IrcServerInfo a_server) ;
  bool login        (IrcServerInfo a_server) ;
  void run          () override ;

  void sendChat(String chat_msg) ;


  irc_callbacks_t      callbacks ;
  Array<IrcServerInfo> servers ;
} ;

#endif // IRC_H_INCLUDED

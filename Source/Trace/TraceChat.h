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

#ifndef _TRACECHAT_H_
#define _TRACECHAT_H_

#ifdef DEBUG_TRACE

#  include "Trace.h"


#  define DEBUG_TRACE_CHAT_VISIBILITY                                          \
  if (chatHistoryGroup->isVisible() != is_visible)                             \
    Trace::TraceGui((is_visible) ? "showing chat panel" : "hiding chat panel") ;

#  define DEBUG_TRACE_LOCATE_SORTED_CHILD                                         \
  Identifier server_id = chatters_store.getParent().getType() ;                   \
  if (!(~item_idx) && DEBUG_TRACE_VB)                                             \
    Trace::TraceError(String("error locating component for chatter ") +           \
      " nick="           + nick                                       +           \
      " chatters_store=" + String(chatters_store.getType())           +           \
      " server_id="      + String(server_id)                          +           \
      " item_idx="       + String(item_idx)                           ) ;         \
  if (1) Trace::TraceGui(String("searching (") + String(nicks.size())           + \
                                ") nicks on '" + String(server_id)              + \
                                "' nicks=["    + nicks.joinIntoString(",") + "]") ;

#  define DEBUG_TRACE_ADD_CHAT_LIST_ITEM                                             \
  Trace::TraceGui("adding chatter '" + STRING(chatter_store[CONFIG::NICK_ID]) + "'") ;

#  define DEBUG_TRACE_REMOVE_CHAT_LIST_ITEM                                       \
  String nick = STRING(chatter_store[CONFIG::NICK_ID]) ;                          \
  String dbg  = "removing chatter '" + nick + "' at index " + String(item_idx) ;  \
  if (!a_list_item) Trace::TraceError("error " + dbg) ; else Trace::TraceGui(dbg) ;

#  define DEBUG_TRACE_MOVE_CHAT_LIST if (DEBUG_TRACE_VB)                \
  Trace::TraceGui("moving ChatList[" + String(server_n) + "] '"       + \
                  chatList->getComponentID() + "' from "              + \
                  String(chatList->getPosition().toString()) + " to " + \
                  Point(list_x , list_y).toString()                   ) ;

#  define DEBUG_TRACE_RESIZE_CHAT_LIST if (DEBUG_TRACE_VB)                   \
    Trace::TraceGui("resizing ChatList '" + getComponentID() + "' from "   + \
                  Point<int>(getWidth() , getHeight()).toString() + " to " + \
                  Point<int>(GUI::CHATLIST_W , list_h).toString()          ) ;

#  define DEBUG_TRACE_MOVE_CHAT_LIST_ITEM if (DEBUG_TRACE_VB)            \
  Trace::TraceGui("moving ChatListItem[" + String(child_n) + "] '"     + \
                  list_item->getName() + "' from "                     + \
                  String(list_item->getPosition().toString()) + " to " + \
                  Point<int>(list_item_x , list_item_y).toString()     ) ;

#else // DEBUG_TRACE

#  define DEBUG_TRACE_CHAT_VISIBILITY       ;
#  define DEBUG_TRACE_LOCATE_SORTED_CHILD   ;
#  define DEBUG_TRACE_ADD_CHAT_LIST_ITEM    ;
#  define DEBUG_TRACE_REMOVE_CHAT_LIST_ITEM ;
#  define DEBUG_TRACE_MOVE_CHAT_LIST        ;
#  define DEBUG_TRACE_RESIZE_CHAT_LIST      ;
#  define DEBUG_TRACE_MOVE_CHAT_LIST_ITEM   ;

#endif // DEBUG_TRACE
#endif // _TRACECHAT_H_

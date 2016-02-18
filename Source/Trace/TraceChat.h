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

#  define DEBUG_TRACE_CHATLIST_TREE_CHANGED Trace::TraceTreeChanged(a_node , a_key) ;

#  define DEBUG_TRACE_ADD_CHATLIST_ITEM                                              \
  Trace::TraceGui("adding chatter '" + STRING(chatter_store[CONFIG::NICK_ID]) + "'") ;

#  define DEBUG_TRACE_REMOVE_CHATLIST_ITEM                                              \
  String userid    = String(chatter_store     .getType()) ;                             \
  String networkid = String(this->networkStore.getType()) ;                             \
  String nick      = STRING(chatter_store     [CONFIG::NICK_ID   ]) ;                   \
  String network   = STRING(this->networkStore[CONFIG::NETWORK_ID]) ;                   \
  String dbg       = "removing chatter '" + userid           + "' (" + nick + ")"     + \
                     " from '"            + networkid        + "' (" + network  + ")" + \
                     "' at index "        + String(item_idx) ;                          \
  if (!chat_list_item) Trace::TraceError("error " + dbg) ; else Trace::TraceGui(dbg)    ;

#  define DEBUG_TRACE_LOCATE_SORTED_CHILD                                                 \
  String userid    = String(chatter_store     .getType()) ;                               \
  String networkid = String(this->networkStore.getType()) ;                               \
  String network   = STRING(this->networkStore[CONFIG::NETWORK_ID]) ;                     \
  int    item_idx  = nicks.indexOf(nick) ;                                                \
  if (~item_idx)                                                                          \
    Trace::TraceGuiVb(String("sorted chatter (" + String(item_idx)      + ") '")      +   \
                      userid                    + "' (" + nick + ")"    + " in ("     +   \
                      String(nicks.size())      + ") nicks on '"                      +   \
                      networkid                 + "' (" + network + ")" + "' nicks=[" +   \
                      nicks.joinIntoString(",") + "]"                                 ) ; \
  else if (DEBUG_TRACE_GUI_VB)                                                          \
    Trace::TraceError(String("error locating component for chatter ") +                 \
      " nick="           + nick                                       +                 \
      " chatters_store=" + String(this->chattersStore.getType())      +                 \
      " network_id="     + networkid                                  +                 \
      " item_idx="       + String(item_idx)                           )                 ;

#  define DEBUG_TRACE_MOVE_CHATLIST                                                            \
  if (!is_visible) Trace::TraceGuiVb("ChatList[" + String(network_n) + "] '"        +          \
                                     chat_list->getComponentID()     + "' is hidden") ;        \
  else             Trace::TraceGuiVb("moving ChatList[" + String(network_n)      + "] '"     + \
                                     chat_list->getComponentID()                 + "' from " + \
                                     String(chat_list->getPosition().toString()) + " to "    + \
                                     Point<int>(list_x , list_y).toString()                  ) ;

#  define DEBUG_TRACE_RESIZE_CHATLIST                                                             \
  if (!is_visible) Trace::TraceGuiVb("hiding ChatList '"   + getComponentID()        + "'") ;     \
  else             Trace::TraceGuiVb("resizing ChatList '" + getComponentID()        + " from " + \
                                     Point<int>(getWidth() , getHeight()).toString() + " to "   + \
                                     Point<int>(GUI::CHATLIST_W , list_h).toString()            ) ;

#  define DEBUG_TRACE_MOVE_CHATLIST_ITEM                                   \
  Trace::TraceGuiVb("moving ChatListItem[" + String(child_n) + "] '"     + \
                    list_item->getComponentID() + "' from "              + \
                    String(list_item->getPosition().toString()) + " to " + \
                    Point<int>(list_item_x , list_item_y).toString()     ) ;

#else // DEBUG_TRACE

#  define DEBUG_TRACE_CHAT_VISIBILITY       ;
#  define DEBUG_TRACE_CHATLIST_TREE_CHANGED ;
#  define DEBUG_TRACE_ADD_CHATLIST_ITEM     ;
#  define DEBUG_TRACE_REMOVE_CHATLIST_ITEM  ;
#  define DEBUG_TRACE_LOCATE_SORTED_CHILD   ;
#  define DEBUG_TRACE_MOVE_CHATLIST         ;
#  define DEBUG_TRACE_RESIZE_CHATLIST       ;
#  define DEBUG_TRACE_MOVE_CHATLIST_ITEM    ;

#endif // DEBUG_TRACE
#endif // _TRACECHAT_H_

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

#ifndef _TRACECHAT_H_
#define _TRACECHAT_H_

#ifdef DEBUG_TRACE

#  include "Trace.h"


#  define DEBUG_TRACE_CHAT_VISIBILITY if (!!getParentComponent())              \
  if (chatHistoryGroup->isVisible() != is_visible)                             \
    Trace::TraceGui((is_visible) ? "showing chat panel" : "hiding chat panel") ;

#  define DEBUG_TRACE_ADD_CHATLIST_ITEM                                        \
  String userid = STRING(chatter_store.getType()) ;                            \
  String nick   = STRING(chatter_store[CONFIG::NICK_ID]) ;                     \
  Trace::TraceGui("adding chatter '" + userid           + "' (" + nick + ")" + \
                  " at index "       + String(item_idx)                      ) ;

#  define DEBUG_TRACE_REMOVE_CHATLIST_ITEM                                           \
  String userid = STRING(chatter_store.getType()) ;                                  \
  String nick   = STRING(chatter_store[CONFIG::NICK_ID]) ;                           \
  String dbg    = "removing chatter '" + userid           + "' (" + nick + ")" +     \
                  " from index "       + String(item_idx) ;                          \
  if (!chat_list_item) Trace::TraceError("error " + dbg) ; else Trace::TraceGui(dbg) ;

#  define DEBUG_TRACE_LOCATE_SORTED_CHILD                                             \
  String userid   = STRING(chatter_store.getType()) ;                                 \
  int    nick_idx = nicks.indexOf(nick) ;                                             \
  String dbg      = String(" chatter ("              + String(nick_idx)   + ") '")  + \
                           userid                    + "' (" + nick + ")" + " in (" + \
                           String(nicks.size())      + ") nicks => ["               + \
                           nicks.joinIntoString(",") + "]"                          ; \
  if      (~nick_idx          ) Trace::TraceGuiVb(String("sorted")        + dbg) ;    \
  else if (Trace::GuiVbEnabled) Trace::TraceError(String("error sorting") + dbg)      ;

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

#  define DEBUG_TRACE_SET_FONTSIZE                                                   \
  String prev_size = String(this->chatHistoryText->getFont().getHeight()) ;          \
  String next_size = String(getFontSize()                               ) ;          \
  if (!!getParentComponent())                                                        \
    Trace::TraceGui("chat font size changed from " + prev_size + " to " + next_size) ;

#else // DEBUG_TRACE

#  define DEBUG_TRACE_CHAT_VISIBILITY       ;
#  define DEBUG_TRACE_ADD_CHATLIST_ITEM     ;
#  define DEBUG_TRACE_REMOVE_CHATLIST_ITEM  ;
#  define DEBUG_TRACE_LOCATE_SORTED_CHILD   ;
#  define DEBUG_TRACE_RESIZE_CHATLIST       ;
#  define DEBUG_TRACE_MOVE_CHATLIST_ITEM    ;
#  define DEBUG_TRACE_SET_FONTSIZE          ;

#endif // DEBUG_TRACE
#endif // _TRACECHAT_H_

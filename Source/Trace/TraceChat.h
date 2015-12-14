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

#ifndef _TRACECHAT_H_
#define _TRACECHAT_H_

#ifdef DEBUG

#  include "Trace.h"


#  define DEBUG_TRACE_CHAT_VISIBILITY                                          \
  if (chatHistoryGroup->isVisible() != is_visible)                             \
    Trace::TraceGui((is_visible) ? "showing chat panel" : "hiding chat panel") ;

#  define DEBUG_TRACE_RELOAD_NICKS                                                        \
  StringArray nix = this->nicks[server_n] ;                                               \
  Trace::TraceGui(String("loading (") + String(nix.size()) +                              \
                  ") nicks from server[" + String(server_n) + "] '" + String(server_id) + \
                  "' nicks=[" + nix.joinIntoString(",") + "]"                           ) ;

#  define DEBUG_TRACE_LOCATE_SORTED_CHILD if (!(~child_idx) && DEBUG_TRACE_VB)            \
  Trace::TraceError(String("error locating component for chatter ")             +         \
    " nick="          + nick                                                    +         \
    " a_parent_node=" + String(a_parent_node.getType())                         +         \
    " server_id="     + String(server_id)                                       +         \
    " server_store="  + String((server_store.isValid()) ? "valid" : " invalid") +         \
    " server_idx="    + String(server_idx)                                      +         \
    " child_idx="     + String(child_idx)                                       ) ;       \
  StringArray nix = this->nicks[server_idx] ;                                             \
  Trace::TraceGui(String("searching (") + String(nix.size()) +                            \
                  ") nicks on server[" + String(server_idx) + "] '" + String(server_id) + \
                  "' nicks=[" + nix.joinIntoString(",") + "]"                           ) ;

#  define DEBUG_TRACE_ADD_CHAT_LIST_ITEM                                           \
  Trace::TraceGui("adding chatter '" + STRING(a_node[CONFIG::CHAT_NICK_ID]) + "'") ;

#  define DEBUG_TRACE_REMOVE_CHAT_LIST_ITEM                                        \
  String nick = STRING(a_node[CONFIG::CHAT_NICK_ID]) ;                             \
  String dbg  = "removing chatter '" + nick + "' at index " + String(child_idx) ;  \
  if (!a_list_item) Trace::TraceError("error " + dbg) ; else Trace::TraceGui(dbg)  ;

#else // DEBUG

#  define DEBUG_TRACE_CHAT_VISIBILITY       ;
#  define DEBUG_TRACE_RELOAD_NICKS          ;
#  define DEBUG_TRACE_LOCATE_SORTED_CHILD   ;
#  define DEBUG_TRACE_ADD_CHAT_LIST_ITEM    ;
#  define DEBUG_TRACE_REMOVE_CHAT_LIST_ITEM ;

#endif // DEBUG
#endif // _TRACECHAT_H_

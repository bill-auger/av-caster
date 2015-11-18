
#ifndef TRACECHAT_H_INCLUDED
#define TRACECHAT_H_INCLUDED

#ifdef DEBUG

#  include "Trace.h"

#  define DEBUG_TRACE_CHAT_VISIBILITY                                          \
  if (chatHistoryGroup->isVisible() != is_visible)                             \
    Trace::TraceGui((is_visible) ? "showing chat panel" : "hiding chat panel") ;

#  define DEBUG_TRACE_ADD_CHAT_LIST_ITEM                                           \
  Trace::TraceGui("adding chatter '" + STRING(a_node[CONFIG::CHAT_NICK_ID]) + "'") ;

#  define DEBUG_TRACE_REMOVE_CHAT_LIST_ITEM                                          \
  Trace::TraceGui("removing chatter '" + STRING(a_node[CONFIG::CHAT_NICK_ID]) + "'") ;

#else // DEBUG

#  define DEBUG_TRACE_CHAT_VISIBILITY       ;
#  define DEBUG_TRACE_ADD_CHAT_LIST_ITEM    ;
#  define DEBUG_TRACE_REMOVE_CHAT_LIST_ITEM ;

#endif // DEBUG
#endif // TRACECHAT_H_INCLUDED

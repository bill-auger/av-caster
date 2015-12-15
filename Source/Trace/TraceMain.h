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


#ifndef _TRACEMAIN_H_
#define _TRACEMAIN_H_

#ifdef DEBUG

#  include "Trace.h"


/* state */

#  define DEBUG_TRACE_INIT_VERSION printf("%s\n" , CHARSTAR(APP::CLI_VERSION_MSG)) ;

#  define DEBUG_TRACE_SHUTDOWN_IN  Trace::TraceState("shutting down") ;

#  define DEBUG_TRACE_SHUTDOWN_OUT Trace::TraceState("clean shutdown - bye") ;

#else // DEBUG

#  define DEBUG_TRACE_INIT_VERSION ;
#  define DEBUG_TRACE_SHUTDOWN_IN  ;
#  define DEBUG_TRACE_SHUTDOWN_OUT ;

#endif // DEBUG
#endif // _TRACEMAIN_H_

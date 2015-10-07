/*
  ==============================================================================

    TraceAvCasterConfig.h
    Author: bill-auger

  ==============================================================================
*/

#ifndef TRACEAVCASTERCONFIG_H_INCLUDED
#define TRACEAVCASTERCONFIG_H_INCLUDED

#ifdef DEBUG

#  include "Trace.h"


/* persistence */

#  define DEBUG_TRACE_VALIDATE_CONFIG                                                      \
  String success_msg    = "stored config parsed successfully v" + String(stored_version) ; \
  String not_found_msg  = "stored config not found - restoring defaults" ;                 \
  String invlaid_msg    = "stored config not invalid - restoring defaults" ;               \
  Trace::TraceConfig(((!stored_config.isValid())             ? not_found_msg   :           \
                     ((!stored_config.hasType(root_node_id)) ? invlaid_msg   :             \
                                                               success_msg   ) )) ;

#  define DEBUG_TRACE_SANITIZE_CONFIG                                                      \
  if (!do_versions_match)                                                                  \
    Trace::TraceConfig("upgrading config version to v" + String(CONFIG::CONFIG_VERSION)) ; \
  Trace::TraceMissingProperty(this->configStore , CONFIG::CONFIG_VERSION_ID  ) ;           \
  Trace::TraceMissingProperty(this->configStore , CONFIG::DISPLAY_N_ID       ) ;           \
  Trace::TraceMissingProperty(this->configStore , CONFIG::SCREEN_N_ID        ) ;           \
  Trace::TraceMissingProperty(this->configStore , CONFIG::SCREENCAP_W_ID     ) ;           \
  Trace::TraceMissingProperty(this->configStore , CONFIG::SCREENCAP_H_ID     ) ;           \
  Trace::TraceMissingProperty(this->configStore , CONFIG::OFFSET_X_ID        ) ;           \
  Trace::TraceMissingProperty(this->configStore , CONFIG::CAMERA_DEV_ID      ) ;           \
  Trace::TraceMissingProperty(this->configStore , CONFIG::CAMERA_DEV_ID      ) ;           \
  Trace::TraceMissingProperty(this->configStore , CONFIG::CAMERA_RES_ID      ) ;           \
  Trace::TraceMissingProperty(this->configStore , CONFIG::AUDIO_API_ID       ) ;           \
  Trace::TraceMissingProperty(this->configStore , CONFIG::AUDIO_DEVICE_ID    ) ;           \
  Trace::TraceMissingProperty(this->configStore , CONFIG::AUDIO_CODEC_ID     ) ;           \
  Trace::TraceMissingProperty(this->configStore , CONFIG::N_CHANNELS_ID      ) ;           \
  Trace::TraceMissingProperty(this->configStore , CONFIG::SAMPLERATE_ID      ) ;           \
  Trace::TraceMissingProperty(this->configStore , CONFIG::AUDIO_BITRATE_ID   ) ;           \
  Trace::TraceMissingProperty(this->configStore , CONFIG::OVERLAY_TEXT_ID    ) ;           \
  Trace::TraceMissingProperty(this->configStore , CONFIG::TEXT_STYLE_ID      ) ;           \
  Trace::TraceMissingProperty(this->configStore , CONFIG::TEXT_POS_ID        ) ;           \
  Trace::TraceMissingProperty(this->configStore , CONFIG::OUTPUT_STREAM_ID   ) ;           \
  Trace::TraceMissingProperty(this->configStore , CONFIG::OUTPUT_CONTAINER_ID) ;           \
  Trace::TraceMissingProperty(this->configStore , CONFIG::OUTPUT_W_ID        ) ;           \
  Trace::TraceMissingProperty(this->configStore , CONFIG::OUTPUT_H_ID        ) ;           \
  Trace::TraceMissingProperty(this->configStore , CONFIG::FRAMERATE_ID       ) ;           \
  Trace::TraceMissingProperty(this->configStore , CONFIG::BITRATE_ID         ) ;           \
  Trace::TraceMissingProperty(this->configStore , CONFIG::OUTPUT_DEST_ID     ) ;           \
  Trace::TraceMissingProperty(this->configStore , CONFIG::IS_PREVIEW_ON_ID   ) ;


/* state */

#  define DEBUG_TRACE_CONFIG_TREE_CHANGED                     \
  String key = String(a_key) ;                                \
  String val = a_node[a_key].toString() ;                     \
  Trace::TraceEvent("value changed => " + key + " => " + val) ;

#else // DEBUG

#  define DEBUG_TRACE_VALIDATE_CONFIG     ;
#  define DEBUG_TRACE_SANITIZE_CONFIG     ;
#  define DEBUG_TRACE_CONFIG_TREE_CHANGED ;

#endif // DEBUG
#endif  // TRACEAVCASTERCONFIG_H_INCLUDED

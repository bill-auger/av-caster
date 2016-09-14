#ifndef _GSTCONSTANTS_H_
#define _GSTCONSTANTS_H_


/** the GST class defines configuration and runtime constants
        pertaining to the Gstreamer media backend class       */
class GST
{
public:

  static const uint8 MIN_MAJOR_VERSION ;
  static const uint8 MIN_MINOR_VERSION ;

  // NOTE: compositor inputs are either mutually exclusive (compositor disabled)
  //           or must all be enabled (compositor enabled)
  //       N_COMPOSITOR_INPUTS is coupled to the state of AvCaster::DisabledFeatures
  static const int N_COMPOSITOR_INPUTS ;

  // element IDs
  static const String PIPELINE_ID ;
  static const String SCREENCAP_BIN_ID ;
  static const String CAMERA_BIN_ID ;
  static const String TEXT_BIN_ID ;
  static const String IMAGE_BIN_ID ;
  static const String COMPOSITOR_BIN_ID ;
  static const String PREVIEW_BIN_ID ;
  static const String PREVIEW_SINK_ID ;
  static const String PREVIEW_FAUXSINK_ID ;
  static const String PREVIEW_SINKPAD_ID ;
  static const String AUDIO_BIN_ID ;
  static const String MUXER_BIN_ID ;
  static const String OUTPUT_BIN_ID ;
  // plugin IDs
#if JUCE_LINUX
  static const String SCREEN_PLUGIN_ID ;
  static const String CAMERA_PLUGIN_ID ;
  static const String ALSA_PLUGIN_ID ;
  static const String PULSE_PLUGIN_ID ;
  static const String JACK_PLUGIN_ID ;
  static const String PREVIEW_PLUGIN_ID ;
#endif //JUCE_LINUX
  static const String FAUXSRC_PLUGIN_ID ;
  static const String FAUXSINK_PLUGIN_ID ;
  static const String TESTVIDEO_PLUGIN_ID ;
  static const String TESTAUDIO_PLUGIN_ID ;
  static const String FILESINK_PLUGIN_ID ;
  static const String RTMPSINK_PLUGIN_ID ;

  static const String LCTV_RTMP_URL ;

  // library error messages
  static const String ALSA_INIT_ERROR ;
  static const String PULSE_INIT_ERROR ;
  static const String JACK_INIT_ERROR ;
  static const String XV_INIT_ERROR ;
  static const String FILE_SINK_ERROR ;
} ;

#endif // _GSTCONSTANTS_H_

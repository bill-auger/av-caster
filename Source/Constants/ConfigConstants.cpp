
#include "Constants.h"


Identifier CONFIG::FilterId(String a_string , String retain_chars)
{
  return a_string.retainCharacters(retain_chars)
                 .toLowerCase()
                 .replaceCharacters(APP::FILTER_CHARS , APP::REPLACE_CHARS) ;
}


// config indices
const int CONFIG::INVALID_IDX = -1 ;

// config strings
const StringArray CONFIG::CAMERA_RESOLUTIONS = StringArray::fromLines("160x120" + newLine +
                                                                      "320x240" + newLine +
                                                                      "640x480"           ) ;
const StringArray CONFIG::AUDIO_APIS         = StringArray::fromLines("ALSA"    + newLine +
                                                                      "Pulse"   + newLine +
                                                                      "JACK"              ) ;
const StringArray CONFIG::AUDIO_CODECS       = StringArray::fromLines("MP3"     + newLine +
                                                                      "AAC"               ) ;
const StringArray CONFIG::AUDIO_SAMPLERATES  = StringArray::fromLines("11025"   + newLine +
                                                                      "22050"   + newLine +
                                                                      "44100"   + newLine +
                                                                      "48000"             ) ;
const StringArray CONFIG::AUDIO_BITRATES     = StringArray::fromLines("64k"     + newLine +
                                                                      "96k"     + newLine +
                                                                      "128k"    + newLine +
                                                                      "192k"              ) ;
const StringArray CONFIG::TEXT_STYLES        = StringArray::fromLines("Static"  + newLine +
                                                                      "Marquee"           ) ;
const StringArray CONFIG::TEXT_POSITIONS     = StringArray::fromLines("Top"     + newLine +
                                                                      "Bottom"            ) ;
const StringArray CONFIG::OUTPUT_SINKS       = StringArray::fromLines("File"    + newLine +
                                                                      "RTMP"              ) ;
const StringArray CONFIG::OUTPUT_MUXERS      = StringArray::fromLines(".flv"              ) ;
const StringArray CONFIG::FRAMERATES         = StringArray::fromLines("8"       + newLine +
                                                                      "12"      + newLine +
                                                                      "20"      + newLine +
                                                                      "30"                ) ;
const StringArray CONFIG::VIDEO_BITRATES     = StringArray::fromLines("800k"    + newLine +
                                                                      "1200k"             ) ;

// storage nodes
const Identifier CONFIG::STORAGE_ID            = "av-caster-config" ;
const Identifier CONFIG::PRESETS_ID            = "presets" ;
const Identifier CONFIG::VOLATILE_CONFIG_ID    = "volatile-config" ;
const Identifier CONFIG::CAMERA_DEVICES_ID     = "camera-devices" ;
const Identifier CONFIG::AUDIO_DEVICES_ID      = "audio-devices" ;
// root IDs
const Identifier CONFIG::CONFIG_VERSION_ID     = "config-version" ;
const Identifier CONFIG::PRESET_ID             = "current-preset-idx" ;
const Identifier CONFIG::IS_PENDING_ID         = "is-config-pending" ;
// Controls IDs
const Identifier CONFIG::PRESET_NAME_ID        = "preset-name" ;
const Identifier CONFIG::SCREEN_ID             = "is-screencap-on" ;
const Identifier CONFIG::CAMERA_ID             = "is-camera-on" ;
const Identifier CONFIG::TEXT_ID               = "is-text-on" ;
const Identifier CONFIG::PREVIEW_ID            = "is-preview-on" ;
const Identifier CONFIG::AUDIO_ID              = "is-audio-on" ;
const Identifier CONFIG::IMAGE_ID              = "is-interstitial-on" ;
const Identifier CONFIG::OUTPUT_ID             = "is-output-on" ;
// ConfigScreen IDs
const Identifier CONFIG::DISPLAY_N_ID          = "display-n" ;
const Identifier CONFIG::SCREEN_N_ID           = "screen-n" ;
const Identifier CONFIG::SCREENCAP_W_ID        = "sceencap-w" ;
const Identifier CONFIG::SCREENCAP_H_ID        = "sceencap-h" ;
const Identifier CONFIG::OFFSET_X_ID           = "offset-x" ;
const Identifier CONFIG::OFFSET_Y_ID           = "offset-y" ;
// ConfigCamera IDs
const Identifier CONFIG::CAMERA_DEVICE_ID      = "camera-dev-idx" ;
const Identifier CONFIG::CAMERA_RES_ID         = "camera-res-idx" ;
const Identifier CONFIG::CAMERA_PATH_ID        = "camera-dev-path" ;
const Identifier CONFIG::CAMERA_NAME_ID        = "camera-dev-name" ;
const Identifier CONFIG::CAMERA_RATE_ID        = "camera-framerate" ;
const Identifier CONFIG::CAMERA_RESOLUTIONS_ID = "camera-resolutions" ;
// ConfigAudio IDs
const Identifier CONFIG::AUDIO_API_ID          = "audio-api-idx" ;
const Identifier CONFIG::AUDIO_DEVICE_ID       = "audio-dev-idx" ;
const Identifier CONFIG::AUDIO_CODEC_ID        = "audio-codec-idx" ;
const Identifier CONFIG::N_CHANNELS_ID         = "n-channels" ;
const Identifier CONFIG::SAMPLERATE_ID         = "samplerate-idx" ;
const Identifier CONFIG::AUDIO_BITRATE_ID      = "audio-bitrate-idx" ;
// ConfigText IDs
const Identifier CONFIG::MOTD_TEXT_ID          = "motd-text" ;
const Identifier CONFIG::TEXT_STYLE_ID         = "text-style-idx" ;
const Identifier CONFIG::TEXT_POSITION_ID      = "text-pos-idx" ;
// ConfigImage IDs
const Identifier CONFIG::IMAGE_LOC_ID          = "interstitial-img" ;
// ConfigOutput IDs
const Identifier CONFIG::OUTPUT_SINK_ID        = "output-sink-idx" ;
const Identifier CONFIG::OUTPUT_MUXER_ID       = "output-muxer-idx" ;
const Identifier CONFIG::OUTPUT_W_ID           = "output-w" ;
const Identifier CONFIG::OUTPUT_H_ID           = "output-h" ;
const Identifier CONFIG::FRAMERATE_ID          = "framerate-idx" ;
const Identifier CONFIG::VIDEO_BITRATE_ID      = "video-bitrate-idx" ;
const Identifier CONFIG::OUTPUT_DEST_ID        = "output-dest" ;
// ConfigChat IDs
const Identifier CONFIG::NETWORK_ID            = "chat-network" ;
const Identifier CONFIG::HOST_ID               = "chat-host" ;
const Identifier CONFIG::PORT_ID               = "chat-port" ;
const Identifier CONFIG::NICK_ID               = "chat-nick" ;
const Identifier CONFIG::PASS_ID               = "chat-pass" ;
const Identifier CONFIG::CHANNEL_ID            = "chat-channel" ;
const Identifier CONFIG::TIMESTAMPS_ID         = "show-timestamps" ;
const Identifier CONFIG::JOINPARTS_ID          = "show-joins-parts" ;
const Identifier CONFIG::GREETING_ID           = "chat-greeting" ;
const Identifier CONFIG::RETRIES_ID            = "n-connect-retries" ;
const Identifier CONFIG::CHATTERS_ID           = "active-chatters" ;

// root defaults
#if JUCE_LINUX
const String     CONFIG::STORAGE_DIRNAME           = ".config/" + APP::APP_CMD + "/" ;
const String     CONFIG::STORAGE_FILENAME          = APP::APP_CMD + ".bin" ;
#endif // JUCE_LINUX
#if JUCE_WINDOWS
const String     CONFIG::STORAGE_DIRNAME           = APP::APP_NAME + "\\" ;
const String     CONFIG::STORAGE_FILENAME          = APP::APP_NAME + ".bin" ;
#endif // JUCE_WINDOWS
const double     CONFIG::CONFIG_VERSION            = 0.4 ;
const int        CONFIG::DEFAULT_PRESET_IDX        = FILE_PRESET_IDX ; // ASSERT: must be 0
const int        CONFIG::N_STATIC_PRESETS          = 3 ; // ASSERT: num PresetSeed::PresetSeeds() child nodes
const bool       CONFIG::DEFAULT_IS_PENDING        = false ;
// Controls defaults
const bool       CONFIG::DEFAULT_IS_SCREEN_ACTIVE  = false ;
const bool       CONFIG::DEFAULT_IS_CAMERA_ACTIVE  = false ;
const bool       CONFIG::DEFAULT_IS_TEXT_ACTIVE    = false ;
const bool       CONFIG::DEFAULT_IS_IMAGE_ACTIVE   = true ;
const bool       CONFIG::DEFAULT_IS_PREVIEW_ACTIVE = true ;
const bool       CONFIG::DEFAULT_IS_AUDIO_ACTIVE   = false ;
const bool       CONFIG::DEFAULT_IS_OUTPUT_ACTIVE  = false ;
// Presets defaults
const String     CONFIG::FILE_PRESET_NAME          = "Local File" ;
const String     CONFIG::RTMP_PRESET_NAME          = "RTMP Server" ;
const String     CONFIG::LCTV_PRESET_NAME          = "livecoding.tv" ;
const String     CONFIG::DEFAULT_PRESET_NAME       = FILE_PRESET_NAME ;
const Identifier CONFIG::FILE_PRESET_ID            = FilterId(FILE_PRESET_NAME    , APP::VALID_ID_CHARS) ;
const Identifier CONFIG::RTMP_PRESET_ID            = FilterId(RTMP_PRESET_NAME    , APP::VALID_ID_CHARS) ;
const Identifier CONFIG::LCTV_PRESET_ID            = FilterId(LCTV_PRESET_NAME    , APP::VALID_ID_CHARS) ;
const Identifier CONFIG::DEFAULT_PRESET_ID         = FilterId(DEFAULT_PRESET_NAME , APP::VALID_ID_CHARS) ;
// ConfigScreen defaults
const int        CONFIG::DEFAULT_DISPLAY_N         = 0 ;
const int        CONFIG::DEFAULT_SCREEN_N          = 0 ;
const int        CONFIG::DEFAULT_SCREENCAP_W       = 640 ;
const int        CONFIG::DEFAULT_SCREENCAP_H       = 480 ;
const int        CONFIG::DEFAULT_OFFSET_X          = 0 ;
const int        CONFIG::DEFAULT_OFFSET_Y          = 0 ;
// ConfigCamera defaults
const int        CONFIG::DEFAULT_CAMERA_DEVICE_IDX = CONFIG::INVALID_IDX ;
const int        CONFIG::DEFAULT_CAMERA_RES_IDX    = CONFIG::INVALID_IDX ;
const int        CONFIG::DEFAULT_CAMERA_RATE       = 30 ;
// ConfigAudio defaults
const int        CONFIG::DEFAULT_AUDIO_API_IDX     = CONFIG::ALSA_AUDIO_IDX ;
const int        CONFIG::DEFAULT_AUDIO_DEVICE_IDX  = CONFIG::INVALID_IDX ;
const int        CONFIG::DEFAULT_AUDIO_CODEC_IDX   = CONFIG::MP3_AUDIO_IDX ;
const int        CONFIG::DEFAULT_N_CHANNELS        = 2 ;
const int        CONFIG::DEFAULT_SAMPLERATE_IDX    = 0 ;
const int        CONFIG::DEFAULT_AUDIO_BITRATE_IDX = 0 ;
// ConfigText defaults
const String     CONFIG::DEFAULT_MOTD_TEXT         = "" ;
const int        CONFIG::DEFAULT_TEXT_STYLE_IDX    = 0 ;
const int        CONFIG::DEFAULT_TEXT_POSITION_IDX = 0 ;
// ConfigImage defaults
const String     CONFIG::DEFAULT_IMAGE_LOCATION    = "" ;
// ConfigOutput defaults
const int        CONFIG::DEFAULT_OUTPUT_SINK_IDX   = FILE_OUTPUT_IDX ;
const int        CONFIG::DEFAULT_OUTPUT_MUXER_IDX  = 0 ;
const int        CONFIG::DEFAULT_OUTPUT_W          = 640 ;
const int        CONFIG::DEFAULT_OUTPUT_H          = 480 ;
const int        CONFIG::DEFAULT_FRAMERATE_IDX     = 0 ;
const int        CONFIG::DEFAULT_VIDEO_BITRATE_IDX = 0 ;
const String     CONFIG::DEFAULT_OUTPUT_DEST       = APP::APP_NAME + ".flv" ;
// ConfigChat defaults
const String     CONFIG::DEFAULT_NETWORK           = "" ;
const String     CONFIG::DEFAULT_HOST              = "" ;
const int        CONFIG::DEFAULT_PORT              = 0 ;
const String     CONFIG::DEFAULT_NICK              = "" ;
const String     CONFIG::DEFAULT_PASS              = "" ;
const String     CONFIG::DEFAULT_CHANNEL           = "" ;
const bool       CONFIG::DEFAULT_SHOW_TIMESTAMPS   = false ;
const bool       CONFIG::DEFAULT_SHOW_JOINPARTS    = true ;
const String     CONFIG::DEFAULT_GREETING          = "" ;
const int        CONFIG::DEFAULT_N_RETRIES         = IRC::STATE_FAILED ; // 0

// filter keys
#define ROOT_PERSISTENT_NODE_IDS    String(PRESETS_ID       )
#define ROOT_TRANSIENT_NODE_IDS     String(""               )
#define ROOT_PERSISTENT_IDS         String(CONFIG_VERSION_ID) + " " + String(PRESET_ID       ) + " " + \
                                    String(PRESETS_ID       )
#define ROOT_TRANSIENT_IDS          String(IS_PENDING_ID    )
#define PRESET_PERSISTENT_NODE_IDS  String(NETWORK_ID)
#define PRESET_TRANSIENT_NODE_IDS   String(""               )
#define PRESET_PERSISTENT_IDS       String(PRESET_NAME_ID   ) + " " + String(SCREEN_ID       ) + " " + \
                                    String(CAMERA_ID        ) + " " + String(TEXT_ID         ) + " " + \
                                    String(IMAGE_ID         ) + " " + String(PREVIEW_ID      ) + " " + \
                                    String(AUDIO_ID         )                                  + " " + \
                                    String(DISPLAY_N_ID     ) + " " + String(SCREEN_N_ID     ) + " " + \
                                    String(SCREENCAP_W_ID   ) + " " + String(SCREENCAP_H_ID  ) + " " + \
                                    String(OFFSET_X_ID      ) + " " + String(OFFSET_Y_ID     ) + " " + \
                                    String(CAMERA_DEVICE_ID ) + " " + String(CAMERA_RES_ID   ) + " " + \
                                    String(AUDIO_API_ID     ) + " " + String(AUDIO_DEVICE_ID ) + " " + \
                                    String(AUDIO_CODEC_ID   ) + " " + String(N_CHANNELS_ID   ) + " " + \
                                    String(SAMPLERATE_ID    ) + " " + String(AUDIO_BITRATE_ID) + " " + \
                                    String(MOTD_TEXT_ID     ) + " " + String(TEXT_STYLE_ID   ) + " " + \
                                    String(TEXT_POSITION_ID ) + " "                                  + \
                                    String(IMAGE_LOC_ID     ) + " "                                  + \
                                    String(OUTPUT_SINK_ID   ) + " " + String(OUTPUT_MUXER_ID ) + " " + \
                                    String(OUTPUT_W_ID      ) + " " + String(OUTPUT_H_ID     ) + " " + \
                                    String(FRAMERATE_ID     ) + " " + String(VIDEO_BITRATE_ID) + " " + \
                                    String(OUTPUT_DEST_ID   )
#define PRESET_TRANSIENT_IDS        String(OUTPUT_ID)
#define NETWORK_PERSISTENT_NODE_IDS String(""               )
#define NETWORK_TRANSIENT_NODE_IDS  String(CHATTERS_ID      )
#define NETWORK_PERSISTENT_IDS      String(NETWORK_ID       ) + " " + String(PORT_ID         ) + " " + \
                                    String(NICK_ID          ) + " " + String(PASS_ID         ) + " " + \
                                    String(CHANNEL_ID       ) + " " + String(TIMESTAMPS_ID   ) + " " + \
                                    String(JOINPARTS_ID     ) + " " + String(GREETING_ID     )
#define NETWORK_TRANSIENT_IDS       String(HOST_ID          ) + " " + String(RETRIES_ID      )
#define CHATTER_TRANSIENT_IDS       String(NICK_ID          )
#define CAMERA_TRANSIENT_IDS        String(""               )
#define AUDIO_TRANSIENT_IDS         String(""               )
#define MEDIA_IDS                   String(SCREEN_ID        ) + " " + String(CAMERA_ID       ) + " " + \
                                    String(TEXT_ID          ) + " " + String(IMAGE_ID        ) + " " + \
                                    String(PREVIEW_ID       ) + " " + String(AUDIO_ID        ) + " " + \
                                    String(OUTPUT_ID        )
#define RECONFIGURE_IDS             String(IS_PENDING_ID    ) + " " + String(PRESET_ID)
const StringArray CONFIG::ROOT_PERSISTENT_NODES    = StringArray::fromTokens(ROOT_PERSISTENT_NODE_IDS    , false) ;
const StringArray CONFIG::ROOT_NODES               = StringArray::fromTokens(ROOT_PERSISTENT_NODE_IDS    + " "  +
                                                                             ROOT_TRANSIENT_NODE_IDS     , false) ;
const StringArray CONFIG::ROOT_PERSISTENT_KEYS     = StringArray::fromTokens(ROOT_PERSISTENT_IDS         , false) ;
const StringArray CONFIG::ROOT_KEYS                = StringArray::fromTokens(ROOT_PERSISTENT_IDS         + " "  +
                                                                             ROOT_TRANSIENT_IDS          , false) ;
const StringArray CONFIG::PRESET_PERSISTENT_NODES  = StringArray::fromTokens(PRESET_PERSISTENT_NODE_IDS  , false) ;
const StringArray CONFIG::PRESET_NODES             = StringArray::fromTokens(PRESET_PERSISTENT_NODE_IDS  + " "  +
                                                                             PRESET_TRANSIENT_NODE_IDS   , false) ;
const StringArray CONFIG::PRESET_PERSISTENT_KEYS   = StringArray::fromTokens(PRESET_PERSISTENT_IDS       , false) ;
const StringArray CONFIG::PRESET_KEYS              = StringArray::fromTokens(PRESET_PERSISTENT_IDS       + " "  +
                                                                             PRESET_TRANSIENT_IDS        , false) ;
const StringArray CONFIG::NETWORK_PERSISTENT_NODES = StringArray::fromTokens(NETWORK_PERSISTENT_NODE_IDS , false) ;
const StringArray CONFIG::NETWORK_NODES            = StringArray::fromTokens(NETWORK_PERSISTENT_NODE_IDS + " "  +
                                                                             NETWORK_TRANSIENT_NODE_IDS  , false) ;
const StringArray CONFIG::NETWORK_PERSISTENT_KEYS  = StringArray::fromTokens(NETWORK_PERSISTENT_IDS      , false) ;
const StringArray CONFIG::NETWORK_KEYS             = StringArray::fromTokens(NETWORK_PERSISTENT_IDS      + " "  +
                                                                             NETWORK_TRANSIENT_IDS       , false) ;
const StringArray CONFIG::CHATTER_KEYS             = StringArray::fromTokens(CHATTER_TRANSIENT_IDS       , false) ;
const StringArray CONFIG::CAMERA_KEYS              = StringArray::fromTokens(CAMERA_TRANSIENT_IDS        , false) ;
const StringArray CONFIG::AUDIO_KEYS               = StringArray::fromTokens(AUDIO_TRANSIENT_IDS         , false) ;
const StringArray CONFIG::MEDIA_KEYS               = StringArray::fromTokens(MEDIA_IDS                   , false) ;
const StringArray CONFIG::RECONFIGURE_KEYS         = StringArray::fromTokens(RECONFIGURE_IDS             , false) ;

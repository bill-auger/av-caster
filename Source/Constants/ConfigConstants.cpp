
#include "Constants.h"

// config indices
const int CONFIG::INVALID_IDX = -1 ;

// storage nodes
const Identifier CONFIG::STORAGE_ID            = "av-caster-config"   ;
const Identifier CONFIG::PRESETS_ID            = "presets"            ;
const Identifier CONFIG::VOLATILE_CONFIG_ID    = "volatile-config"    ;
const Identifier CONFIG::CAMERA_DEVICES_ID     = "camera-devices"     ;
const Identifier CONFIG::AUDIO_DEVICES_ID      = "audio-devices"      ;
// root IDs
const Identifier CONFIG::CONFIG_VERSION_ID     = "config-version"     ;
const Identifier CONFIG::PRESET_ID             = "current-preset-idx" ;
const Identifier CONFIG::IS_PENDING_ID         = "is-config-pending"  ;
// Controls IDs
const Identifier CONFIG::PRESET_NAME_ID        = "preset-name"        ;
const Identifier CONFIG::SCREEN_ID             = "is-screencap-on"    ;
const Identifier CONFIG::CAMERA_ID             = "is-camera-on"       ;
const Identifier CONFIG::TEXT_ID               = "is-text-on"         ;
const Identifier CONFIG::PREVIEW_ID            = "is-preview-on"      ;
const Identifier CONFIG::AUDIO_ID              = "is-audio-on"        ;
const Identifier CONFIG::IMAGE_ID              = "is-interstitial-on" ;
const Identifier CONFIG::OUTPUT_ID             = "is-output-on"       ;
// ConfigScreen IDs
const Identifier CONFIG::DISPLAY_N_ID          = "display-n"          ;
const Identifier CONFIG::SCREEN_N_ID           = "screen-n"           ;
const Identifier CONFIG::SCREENCAP_W_ID        = "sceencap-w"         ;
const Identifier CONFIG::SCREENCAP_H_ID        = "sceencap-h"         ;
const Identifier CONFIG::OFFSET_X_ID           = "offset-x"           ;
const Identifier CONFIG::OFFSET_Y_ID           = "offset-y"           ;
// ConfigCamera IDs
const Identifier CONFIG::CAMERA_DEVICE_ID      = "camera-dev-idx"     ;
const Identifier CONFIG::CAMERA_RES_ID         = "camera-res-idx"     ;
const Identifier CONFIG::CAMERA_PATH_ID        = "camera-dev-path"    ;
const Identifier CONFIG::CAMERA_NAME_ID        = "camera-dev-name"    ;
const Identifier CONFIG::CAMERA_RATE_ID        = "camera-framerate"   ;
const Identifier CONFIG::CAMERA_RESOLUTIONS_ID = "camera-resolutions" ;
// ConfigAudio IDs
const Identifier CONFIG::AUDIO_API_ID          = "audio-api-idx"      ;
const Identifier CONFIG::AUDIO_DEVICE_ID       = "audio-dev-idx"      ;
const Identifier CONFIG::AUDIO_CODEC_ID        = "audio-codec-idx"    ;
const Identifier CONFIG::N_CHANNELS_ID         = "n-channels"         ;
const Identifier CONFIG::SAMPLERATE_ID         = "samplerate-idx"     ;
const Identifier CONFIG::AUDIO_BITRATE_ID      = "audio-bitrate-idx"  ;
// ConfigText IDs
const Identifier CONFIG::MOTD_TEXT_ID          = "motd-text"          ;
const Identifier CONFIG::TEXT_STYLE_ID         = "text-style-idx"     ;
const Identifier CONFIG::TEXT_POSITION_ID      = "text-pos-idx"       ;
// ConfigImage IDs
const Identifier CONFIG::IMAGE_LOC_ID          = "interstitial-img"   ;
// ConfigOutput IDs
const Identifier CONFIG::OUTPUT_SINK_ID        = "output-sink-idx"    ;
const Identifier CONFIG::OUTPUT_MUXER_ID       = "output-muxer-idx"   ;
const Identifier CONFIG::OUTPUT_W_ID           = "output-w"           ;
const Identifier CONFIG::OUTPUT_H_ID           = "output-h"           ;
const Identifier CONFIG::FRAMERATE_ID          = "framerate-idx"      ;
const Identifier CONFIG::VIDEO_BITRATE_ID      = "video-bitrate-idx"  ;
const Identifier CONFIG::OUTPUT_DEST_ID        = "output-dest"        ;
// ConfigChat IDs
const Identifier CONFIG::NETWORK_ID            = "chat-network"       ;
const Identifier CONFIG::HOST_ID               = "chat-host"          ;
const Identifier CONFIG::PORT_ID               = "chat-port"          ;
const Identifier CONFIG::NICK_ID               = "chat-nick"          ;
const Identifier CONFIG::PASS_ID               = "chat-pass"          ;
const Identifier CONFIG::CHANNEL_ID            = "chat-channel"       ;
const Identifier CONFIG::TIMESTAMPS_ID         = "show-timestamps"    ;
const Identifier CONFIG::JOINPARTS_ID          = "show-joins-parts"   ;
const Identifier CONFIG::GREETING_ID           = "chat-greeting"      ;
const Identifier CONFIG::RETRIES_ID            = "n-connect-retries"  ;
const Identifier CONFIG::CHATTERS_ID           = "active-chatters"    ;

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
const String     CONFIG::DEFAULT_OUTPUT_DEST       = APP::APP_NAME + APP::FLV_FILE_EXT ;
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


Identifier CONFIG::FilterId(String a_string , String retain_chars)
{
  return a_string.retainCharacters(retain_chars)
                 .toLowerCase()
                 .replaceCharacters(APP::FILTER_CHARS , APP::REPLACE_CHARS) ;
}


// GUI/config strings
StringArray CONFIG::CameraResolutions() { return StringArray::fromLines(String("160x120") + newLine +
                                                                        String("320x240") + newLine +
                                                                        String("640x480")           ) ; }
StringArray CONFIG::AudioApis()         { return StringArray::fromLines(String("ALSA"   ) + newLine +
                                                                        String("Pulse"  ) + newLine +
                                                                        String("JACK"   )           ) ; }
StringArray CONFIG::AudioCodecs()       { return StringArray::fromLines(String("MP3"    ) + newLine +
                                                                        String("AAC"    )           ) ; }
StringArray CONFIG::AudioSampleRates()  { return StringArray::fromLines(String("11025"  ) + newLine +
                                                                        String("22050"  ) + newLine +
                                                                        String("44100"  ) + newLine +
                                                                        String("48000"  )           ) ; }
StringArray CONFIG::AudioBitRates()     { return StringArray::fromLines(String("64k"    ) + newLine +
                                                                        String("96k"    ) + newLine +
                                                                        String("128k"   ) + newLine +
                                                                        String("192k"   )           ) ; }
StringArray CONFIG::TextStyles()        { return StringArray::fromLines(String("Static" ) + newLine +
                                                                        String("Marquee")           ) ; }
StringArray CONFIG::TextPositions()     { return StringArray::fromLines(String("Top"    ) + newLine +
                                                                        String("Bottom" )           ) ; }
StringArray CONFIG::OutputSinks()       { return StringArray::fromLines(String("File"   ) + newLine +
                                                                        String("RTMP"   )           ) ; }
StringArray CONFIG::OutputMuxers()      { return StringArray::fromLines(String(".flv"   )           ) ; }
StringArray CONFIG::FrameRates()        { return StringArray::fromLines(String("8"      ) + newLine +
                                                                        String("12"     ) + newLine +
                                                                        String("20"     ) + newLine +
                                                                        String("30"     )           ) ; }
StringArray CONFIG::VideoBitRates()     { return StringArray::fromLines(String("800k"   ) + newLine +
                                                                        String("1200k"  )           ) ; }

// filter keys
#define ROOT_PERSISTENT_NODE_IDS    STRING(PRESETS_ID       )
#define ROOT_TRANSIENT_NODE_IDS     String::empty
#define ROOT_PERSISTENT_IDS         STRING(CONFIG_VERSION_ID) + newLine + STRING(PRESET_ID       ) + newLine + \
                                    STRING(PRESETS_ID       )
#define ROOT_TRANSIENT_IDS          STRING(IS_PENDING_ID    )
#define PRESET_PERSISTENT_NODE_IDS  STRING(NETWORK_ID       )
#define PRESET_TRANSIENT_NODE_IDS   String::empty
#define PRESET_PERSISTENT_IDS       STRING(PRESET_NAME_ID   ) + newLine + STRING(SCREEN_ID       ) + newLine + \
                                    STRING(CAMERA_ID        ) + newLine + STRING(TEXT_ID         ) + newLine + \
                                    STRING(IMAGE_ID         ) + newLine + STRING(PREVIEW_ID      ) + newLine + \
                                    STRING(AUDIO_ID         ) +                                      newLine + \
                                    STRING(DISPLAY_N_ID     ) + newLine + STRING(SCREEN_N_ID     ) + newLine + \
                                    STRING(SCREENCAP_W_ID   ) + newLine + STRING(SCREENCAP_H_ID  ) + newLine + \
                                    STRING(OFFSET_X_ID      ) + newLine + STRING(OFFSET_Y_ID     ) + newLine + \
                                    STRING(CAMERA_DEVICE_ID ) + newLine + STRING(CAMERA_RES_ID   ) + newLine + \
                                    STRING(AUDIO_API_ID     ) + newLine + STRING(AUDIO_DEVICE_ID ) + newLine + \
                                    STRING(AUDIO_CODEC_ID   ) + newLine + STRING(N_CHANNELS_ID   ) + newLine + \
                                    STRING(SAMPLERATE_ID    ) + newLine + STRING(AUDIO_BITRATE_ID) + newLine + \
                                    STRING(MOTD_TEXT_ID     ) + newLine + STRING(TEXT_STYLE_ID   ) + newLine + \
                                    STRING(TEXT_POSITION_ID ) +                                      newLine + \
                                    STRING(IMAGE_LOC_ID     ) +                                      newLine + \
                                    STRING(OUTPUT_SINK_ID   ) + newLine + STRING(OUTPUT_MUXER_ID ) + newLine + \
                                    STRING(OUTPUT_W_ID      ) + newLine + STRING(OUTPUT_H_ID     ) + newLine + \
                                    STRING(FRAMERATE_ID     ) + newLine + STRING(VIDEO_BITRATE_ID) + newLine + \
                                    STRING(OUTPUT_DEST_ID   )
#define PRESET_TRANSIENT_IDS        STRING(OUTPUT_ID        )
#define NETWORK_PERSISTENT_NODE_IDS String::empty
#define NETWORK_TRANSIENT_NODE_IDS  STRING(CHATTERS_ID      )
#define NETWORK_PERSISTENT_IDS      STRING(NETWORK_ID       ) + newLine + STRING(PORT_ID         ) + newLine + \
                                    STRING(NICK_ID          ) + newLine + STRING(PASS_ID         ) + newLine + \
                                    STRING(CHANNEL_ID       ) + newLine + STRING(TIMESTAMPS_ID   ) + newLine + \
                                    STRING(JOINPARTS_ID     ) + newLine + STRING(GREETING_ID     )
#define NETWORK_TRANSIENT_IDS       STRING(HOST_ID          ) + newLine + STRING(RETRIES_ID      )
#define CHATTER_TRANSIENT_IDS       STRING(NICK_ID          )
#define CAMERA_TRANSIENT_IDS        String::empty
#define AUDIO_TRANSIENT_IDS         String::empty
#define MEDIA_IDS                   STRING(SCREEN_ID        ) + newLine + STRING(CAMERA_ID       ) + newLine + \
                                    STRING(TEXT_ID          ) + newLine + STRING(IMAGE_ID        ) + newLine + \
                                    STRING(PREVIEW_ID       ) + newLine + STRING(AUDIO_ID        ) + newLine + \
                                    STRING(OUTPUT_ID        )
#define RECONFIGURE_IDS             STRING(IS_PENDING_ID    ) + newLine + STRING(PRESET_ID)


StringArray CONFIG::RootPersistentNodes()    { return StringArray::fromLines(ROOT_PERSISTENT_NODE_IDS              ) ; }
StringArray CONFIG::RootNodes()              { return StringArray::fromLines(ROOT_PERSISTENT_NODE_IDS    + newLine +
                                                                             ROOT_TRANSIENT_NODE_IDS               ) ; }
StringArray CONFIG::RootPersistentKeys()     { return StringArray::fromLines(ROOT_PERSISTENT_IDS                   ) ; }
StringArray CONFIG::RootKeys()               { return StringArray::fromLines(ROOT_PERSISTENT_IDS         + newLine +
                                                                             ROOT_TRANSIENT_IDS                    ) ; }
StringArray CONFIG::PresetPersistentNodes()  { return StringArray::fromLines(PRESET_PERSISTENT_NODE_IDS            ) ; }
StringArray CONFIG::PresetNodes()            { return StringArray::fromLines(PRESET_PERSISTENT_NODE_IDS  + newLine +
                                                                             PRESET_TRANSIENT_NODE_IDS             ) ; }
StringArray CONFIG::PresetPersistentKeys()   { return StringArray::fromLines(PRESET_PERSISTENT_IDS                 ) ; }
StringArray CONFIG::PresetKeys()             { return StringArray::fromLines(PRESET_PERSISTENT_IDS       + newLine +
                                                                             PRESET_TRANSIENT_IDS                  ) ; }
StringArray CONFIG::NetworkPersistentNodes() { return StringArray::fromLines(NETWORK_PERSISTENT_NODE_IDS           ) ; }
StringArray CONFIG::NetworkNodes()           { return StringArray::fromLines(NETWORK_PERSISTENT_NODE_IDS + newLine +
                                                                             NETWORK_TRANSIENT_NODE_IDS            ) ; }
StringArray CONFIG::NetworkPersistentKeys()  { return StringArray::fromLines(NETWORK_PERSISTENT_IDS                ) ; }
StringArray CONFIG::NetworkKeys()            { return StringArray::fromLines(NETWORK_PERSISTENT_IDS      + newLine +
                                                                             NETWORK_TRANSIENT_IDS                 ) ; }
StringArray CONFIG::ChatterKeys()            { return StringArray::fromLines(CHATTER_TRANSIENT_IDS                 ) ; }
StringArray CONFIG::CameraKeys()             { return StringArray::fromLines(CAMERA_TRANSIENT_IDS                  ) ; }
StringArray CONFIG::AudioKeys()              { return StringArray::fromLines(AUDIO_TRANSIENT_IDS                   ) ; }
StringArray CONFIG::MediaKeys()              { return StringArray::fromLines(MEDIA_IDS                             ) ; }
StringArray CONFIG::ReconfigureKeys()        { return StringArray::fromLines(RECONFIGURE_IDS                       ) ; }

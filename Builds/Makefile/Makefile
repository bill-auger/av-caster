# Automatically generated makefile, created by the Introjucer
# Don't edit this file! Your changes will be overwritten when you re-save the Introjucer project!

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifndef CONFIG
  CONFIG=Debug
endif

ifeq ($(CONFIG),Debug)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Debug
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -std=c++11 -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_9CCEB774=1" -D "JUCE_APP_VERSION=0.16.002" -D "JUCE_APP_VERSION_HEX=0x1002" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../JuceLibraryCode/modules
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0 `pkg-config --cflags gstreamer-1.0`
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -lX11 -lXext -lXinerama -ldl -lfreetype -lpthread -lrt -lircclient `pkg-config --libs gstreamer-1.0` `pkg-config --libs gstreamer-video-1.0`
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_9CCEB774=1" -D "JUCE_APP_VERSION=0.16.002" -D "JUCE_APP_VERSION_HEX=0x1002" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../JuceLibraryCode/modules
  TARGET := av-caster-dbg
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

ifeq ($(CONFIG),Release)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -std=c++11 -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_9CCEB774=1" -D "JUCE_APP_VERSION=0.16.002" -D "JUCE_APP_VERSION_HEX=0x1002" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../JuceLibraryCode/modules
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -O3 `pkg-config --cflags gstreamer-1.0`
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -fvisibility=hidden -lX11 -lXext -lXinerama -ldl -lfreetype -lpthread -lrt -lircclient `pkg-config --libs gstreamer-1.0` `pkg-config --libs gstreamer-video-1.0`
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_9CCEB774=1" -D "JUCE_APP_VERSION=0.16.002" -D "JUCE_APP_VERSION_HEX=0x1002" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../JuceLibraryCode/modules
  TARGET := av-caster
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

OBJECTS := \
  $(OBJDIR)/AvCaster_772dbfa2.o \
  $(OBJDIR)/Gstreamer_6a628f1d.o \
  $(OBJDIR)/IrcClient_3839b5ce.o \
  $(OBJDIR)/Background_ec1b7e98.o \
  $(OBJDIR)/Chat_35024382.o \
  $(OBJDIR)/ChatList_a86aac0.o \
  $(OBJDIR)/ChatListItem_22e3caf3.o \
  $(OBJDIR)/Config_d1fea52c.o \
  $(OBJDIR)/ConfigAudio_65d50354.o \
  $(OBJDIR)/ConfigCamera_832c34b1.o \
  $(OBJDIR)/ConfigChat_2f3e1d24.o \
  $(OBJDIR)/ConfigImage_2645c659.o \
  $(OBJDIR)/ConfigOutput_af2d3c8d.o \
  $(OBJDIR)/ConfigScreen_e23a3678.o \
  $(OBJDIR)/ConfigText_9dbedc79.o \
  $(OBJDIR)/Controls_21545560.o \
  $(OBJDIR)/MainContent_91787020.o \
  $(OBJDIR)/Presets_30a0e894.o \
  $(OBJDIR)/Preview_227d08e8.o \
  $(OBJDIR)/Statusbar_b88450c1.o \
  $(OBJDIR)/AvCasterStore_83095ca4.o \
  $(OBJDIR)/PresetSeed_9f55d1b6.o \
  $(OBJDIR)/Trace_fd3024bc.o \
  $(OBJDIR)/AppConstants_f2699997.o \
  $(OBJDIR)/ConfigConstants_11c08e2e.o \
  $(OBJDIR)/GstConstants_d0de3210.o \
  $(OBJDIR)/GuiConstants_d00d5cbd.o \
  $(OBJDIR)/IrcConstants_3a6c1ffe.o \
  $(OBJDIR)/Main_90ebc5c2.o \
  $(OBJDIR)/BinaryData_ce4232d4.o \
  $(OBJDIR)/juce_core_aff681cc.o \
  $(OBJDIR)/juce_data_structures_bdd6d488.o \
  $(OBJDIR)/juce_events_79b2840.o \
  $(OBJDIR)/juce_graphics_c8f1e7a4.o \
  $(OBJDIR)/juce_gui_basics_a630dd20.o \

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking AvCaster
	-@mkdir -p $(BINDIR)
	-@mkdir -p $(LIBDIR)
	-@mkdir -p $(OUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning AvCaster
	@$(CLEANCMD)

strip:
	@echo Stripping AvCaster
	-@strip --strip-unneeded $(OUTDIR)/$(TARGET)

$(OBJDIR)/AvCaster_772dbfa2.o: ../../Source/Controllers/AvCaster.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling AvCaster.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Gstreamer_6a628f1d.o: ../../Source/Controllers/Gstreamer.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Gstreamer.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/IrcClient_3839b5ce.o: ../../Source/Controllers/IrcClient.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling IrcClient.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Background_ec1b7e98.o: ../../Source/Views/Background.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Background.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Chat_35024382.o: ../../Source/Views/Chat.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Chat.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ChatList_a86aac0.o: ../../Source/Views/ChatList.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ChatList.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ChatListItem_22e3caf3.o: ../../Source/Views/ChatListItem.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ChatListItem.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Config_d1fea52c.o: ../../Source/Views/Config.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Config.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ConfigAudio_65d50354.o: ../../Source/Views/ConfigAudio.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ConfigAudio.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ConfigCamera_832c34b1.o: ../../Source/Views/ConfigCamera.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ConfigCamera.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ConfigChat_2f3e1d24.o: ../../Source/Views/ConfigChat.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ConfigChat.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ConfigImage_2645c659.o: ../../Source/Views/ConfigImage.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ConfigImage.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ConfigOutput_af2d3c8d.o: ../../Source/Views/ConfigOutput.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ConfigOutput.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ConfigScreen_e23a3678.o: ../../Source/Views/ConfigScreen.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ConfigScreen.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ConfigText_9dbedc79.o: ../../Source/Views/ConfigText.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ConfigText.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Controls_21545560.o: ../../Source/Views/Controls.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Controls.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MainContent_91787020.o: ../../Source/Views/MainContent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MainContent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Presets_30a0e894.o: ../../Source/Views/Presets.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Presets.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Preview_227d08e8.o: ../../Source/Views/Preview.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Preview.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Statusbar_b88450c1.o: ../../Source/Views/Statusbar.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Statusbar.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/AvCasterStore_83095ca4.o: ../../Source/Models/AvCasterStore.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling AvCasterStore.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PresetSeed_9f55d1b6.o: ../../Source/Models/PresetSeed.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PresetSeed.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Trace_fd3024bc.o: ../../Source/Trace/Trace.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Trace.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/AppConstants_f2699997.o: ../../Source/Constants/AppConstants.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling AppConstants.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ConfigConstants_11c08e2e.o: ../../Source/Constants/ConfigConstants.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ConfigConstants.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/GstConstants_d0de3210.o: ../../Source/Constants/GstConstants.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling GstConstants.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/GuiConstants_d00d5cbd.o: ../../Source/Constants/GuiConstants.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling GuiConstants.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/IrcConstants_3a6c1ffe.o: ../../Source/Constants/IrcConstants.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling IrcConstants.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Main_90ebc5c2.o: ../../Source/Main.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Main.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BinaryData_ce4232d4.o: ../../JuceLibraryCode/BinaryData.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BinaryData.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_core_aff681cc.o: ../../JuceLibraryCode/modules/juce_core/juce_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_data_structures_bdd6d488.o: ../../JuceLibraryCode/modules/juce_data_structures/juce_data_structures.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_events_79b2840.o: ../../JuceLibraryCode/modules/juce_events/juce_events.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_events.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_graphics_c8f1e7a4.o: ../../JuceLibraryCode/modules/juce_graphics/juce_graphics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_basics_a630dd20.o: ../../JuceLibraryCode/modules/juce_gui_basics/juce_gui_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)

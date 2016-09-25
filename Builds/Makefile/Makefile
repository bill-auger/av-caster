# Automatically generated makefile, created by the Projucer (GNU Edition)
# Don't edit this file! Your changes will be overwritten when you re-save the Projucer project!

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifndef STRIP
  STRIP=strip
endif

ifndef AR
  AR=ar
endif

ifndef CONFIG
  CONFIG=Release
endif

ifndef DESTDIR
  DESTDIR=
endif

ifndef PREFIX
  PREFIX=/usr
endif

INSTALLDIR=$(DESTDIR)$(PREFIX)

ifeq ($(CONFIG),Release)
  JUCE_BINDIR := build
  JUCE_LIBDIR := build
  JUCE_OBJDIR := build/intermediate/Release
  JUCE_OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  JUCE_CPPFLAGS := $(DEPFLAGS) -DLINUX=1 -DNDEBUG=1 -DJUCER_LINUX_MAKE_9CCEB774=1 -DJUCE_APP_VERSION=0.16.005 -DJUCE_APP_VERSION_HEX=0x1005 $(shell pkg-config --cflags freetype2 x11 xext xinerama) -pthread -I../../JuceLibraryCode -I../../JuceLibraryCode/modules
  JUCE_CFLAGS += $(CFLAGS) $(JUCE_CPPFLAGS) $(TARGET_ARCH) -O3 $(if $(filter-out x86_64 , $(shell uname -m)) , -malign-double , -fPIC) `pkg-config --cflags gstreamer-1.0` -I /usr/include/libircclient
  JUCE_CXXFLAGS += $(CXXFLAGS) $(JUCE_CFLAGS) -std=c++11
  JUCE_LDFLAGS += $(LDFLAGS) $(TARGET_ARCH) -L$(JUCE_BINDIR) -L$(JUCE_LIBDIR) -fvisibility=hidden $(shell pkg-config --libs freetype2 x11 xext xinerama) -ldl -lpthread -lrt -lircclient `pkg-config --libs gstreamer-1.0` `pkg-config --libs gstreamer-video-1.0`

  TARGET := av-caster
  BLDCMD = $(CXX) -o $(JUCE_OUTDIR)/$(TARGET) $(OBJECTS) $(JUCE_LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(JUCE_OUTDIR)/$(TARGET) $(JUCE_OBJDIR)
endif

ifeq ($(CONFIG),Debug)
  JUCE_BINDIR := build
  JUCE_LIBDIR := build
  JUCE_OBJDIR := build/intermediate/Debug
  JUCE_OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  JUCE_CPPFLAGS := $(DEPFLAGS) -DLINUX=1 -DDEBUG=1 -D_DEBUG=1 -DJUCER_LINUX_MAKE_9CCEB774=1 -DJUCE_APP_VERSION=0.16.005 -DJUCE_APP_VERSION_HEX=0x1005 $(shell pkg-config --cflags freetype2 x11 xext xinerama) -pthread -I../../JuceLibraryCode -I../../JuceLibraryCode/modules
  JUCE_CFLAGS += $(CFLAGS) $(JUCE_CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0 $(if $(filter-out x86_64 , $(shell uname -m)) , -malign-double , -fPIC) `pkg-config --cflags gstreamer-1.0` -I /usr/include/libircclient
  JUCE_CXXFLAGS += $(CXXFLAGS) $(JUCE_CFLAGS) -std=c++11
  JUCE_LDFLAGS += $(LDFLAGS) $(TARGET_ARCH) -L$(JUCE_BINDIR) -L$(JUCE_LIBDIR) $(shell pkg-config --libs freetype2 x11 xext xinerama) -ldl -lpthread -lrt -lircclient `pkg-config --libs gstreamer-1.0` `pkg-config --libs gstreamer-video-1.0`

  TARGET := av-caster-dbg
  BLDCMD = $(CXX) -o $(JUCE_OUTDIR)/$(TARGET) $(OBJECTS) $(JUCE_LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(JUCE_OUTDIR)/$(TARGET) $(JUCE_OBJDIR)
endif

OBJECTS := \
  $(JUCE_OBJDIR)/AppConstants_f2699997.o \
  $(JUCE_OBJDIR)/ConfigConstants_11c08e2e.o \
  $(JUCE_OBJDIR)/GstConstants_d0de3210.o \
  $(JUCE_OBJDIR)/GuiConstants_d00d5cbd.o \
  $(JUCE_OBJDIR)/IrcConstants_3a6c1ffe.o \
  $(JUCE_OBJDIR)/AvCaster_772dbfa2.o \
  $(JUCE_OBJDIR)/Gstreamer_6a628f1d.o \
  $(JUCE_OBJDIR)/IrcClient_3839b5ce.o \
  $(JUCE_OBJDIR)/AvCasterStore_83095ca4.o \
  $(JUCE_OBJDIR)/Seeds_7de92226.o \
  $(JUCE_OBJDIR)/Trace_fd3024bc.o \
  $(JUCE_OBJDIR)/Background_ec1b7e98.o \
  $(JUCE_OBJDIR)/Chat_35024382.o \
  $(JUCE_OBJDIR)/ChatList_a86aac0.o \
  $(JUCE_OBJDIR)/ChatListItem_22e3caf3.o \
  $(JUCE_OBJDIR)/Config_d1fea52c.o \
  $(JUCE_OBJDIR)/ConfigAudio_65d50354.o \
  $(JUCE_OBJDIR)/ConfigCamera_832c34b1.o \
  $(JUCE_OBJDIR)/ConfigChat_2f3e1d24.o \
  $(JUCE_OBJDIR)/ConfigImage_2645c659.o \
  $(JUCE_OBJDIR)/ConfigOutput_af2d3c8d.o \
  $(JUCE_OBJDIR)/ConfigScreen_e23a3678.o \
  $(JUCE_OBJDIR)/ConfigText_9dbedc79.o \
  $(JUCE_OBJDIR)/Controls_21545560.o \
  $(JUCE_OBJDIR)/MainContent_91787020.o \
  $(JUCE_OBJDIR)/Presets_30a0e894.o \
  $(JUCE_OBJDIR)/Preview_227d08e8.o \
  $(JUCE_OBJDIR)/Statusbar_b88450c1.o \
  $(JUCE_OBJDIR)/Main_90ebc5c2.o \
  $(JUCE_OBJDIR)/BinaryData_ce4232d4.o \
  $(JUCE_OBJDIR)/juce_core_75b14332.o \
  $(JUCE_OBJDIR)/juce_data_structures_72d3da2c.o \
  $(JUCE_OBJDIR)/juce_events_d2be882c.o \
  $(JUCE_OBJDIR)/juce_graphics_9c18891e.o \
  $(JUCE_OBJDIR)/juce_gui_basics_8a6da59c.o \

.PHONY: clean

$(JUCE_OUTDIR)/$(TARGET): check-pkg-config $(OBJECTS) $(RESOURCES)
	@echo Linking AvCaster
	-@mkdir -p $(JUCE_BINDIR)
	-@mkdir -p $(JUCE_LIBDIR)
	-@mkdir -p $(JUCE_OUTDIR)
	@$(BLDCMD)

check-pkg-config:
	@command -v pkg-config >/dev/null 2>&1 || { echo >&2 "pkg-config not installed. Please, install it."; exit 1; }
	@pkg-config --print-errors freetype2 x11 xext xinerama

install:
	@echo Installing AvCaster
	@install -m 755 $(OUTDIR)/$(TARGET) $(INSTALLDIR)/bin/

uninstall:
	@echo Uninstalling AvCaster
	@rm $(INSTALLDIR)/bin/$(TARGET) > /dev/null

clean:
	@echo Cleaning AvCaster
	@$(CLEANCMD)

strip:
	@echo Stripping AvCaster
	-@$(STRIP) --strip-unneeded $(JUCE_OUTDIR)/$(TARGET)

$(JUCE_OBJDIR)/AppConstants_f2699997.o: ../../Source/Constants/AppConstants.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling AppConstants.cpp ($(CONFIG))"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ConfigConstants_11c08e2e.o: ../../Source/Constants/ConfigConstants.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ConfigConstants.cpp ($(CONFIG))"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/GstConstants_d0de3210.o: ../../Source/Constants/GstConstants.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling GstConstants.cpp ($(CONFIG))"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/GuiConstants_d00d5cbd.o: ../../Source/Constants/GuiConstants.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling GuiConstants.cpp ($(CONFIG))"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IrcConstants_3a6c1ffe.o: ../../Source/Constants/IrcConstants.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling IrcConstants.cpp ($(CONFIG))"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/AvCaster_772dbfa2.o: ../../Source/Controllers/AvCaster.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling AvCaster.cpp ($(CONFIG))"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Gstreamer_6a628f1d.o: ../../Source/Controllers/Gstreamer.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Gstreamer.cpp ($(CONFIG))"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/IrcClient_3839b5ce.o: ../../Source/Controllers/IrcClient.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling IrcClient.cpp ($(CONFIG))"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/AvCasterStore_83095ca4.o: ../../Source/Models/AvCasterStore.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling AvCasterStore.cpp ($(CONFIG))"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Seeds_7de92226.o: ../../Source/Models/Seeds.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Seeds.cpp ($(CONFIG))"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Trace_fd3024bc.o: ../../Source/Trace/Trace.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Trace.cpp ($(CONFIG))"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Background_ec1b7e98.o: ../../Source/Views/Background.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Background.cpp ($(CONFIG))"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Chat_35024382.o: ../../Source/Views/Chat.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Chat.cpp ($(CONFIG))"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ChatList_a86aac0.o: ../../Source/Views/ChatList.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ChatList.cpp ($(CONFIG))"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ChatListItem_22e3caf3.o: ../../Source/Views/ChatListItem.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ChatListItem.cpp ($(CONFIG))"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Config_d1fea52c.o: ../../Source/Views/Config.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Config.cpp ($(CONFIG))"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ConfigAudio_65d50354.o: ../../Source/Views/ConfigAudio.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ConfigAudio.cpp ($(CONFIG))"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ConfigCamera_832c34b1.o: ../../Source/Views/ConfigCamera.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ConfigCamera.cpp ($(CONFIG))"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ConfigChat_2f3e1d24.o: ../../Source/Views/ConfigChat.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ConfigChat.cpp ($(CONFIG))"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ConfigImage_2645c659.o: ../../Source/Views/ConfigImage.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ConfigImage.cpp ($(CONFIG))"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ConfigOutput_af2d3c8d.o: ../../Source/Views/ConfigOutput.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ConfigOutput.cpp ($(CONFIG))"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ConfigScreen_e23a3678.o: ../../Source/Views/ConfigScreen.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ConfigScreen.cpp ($(CONFIG))"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ConfigText_9dbedc79.o: ../../Source/Views/ConfigText.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ConfigText.cpp ($(CONFIG))"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Controls_21545560.o: ../../Source/Views/Controls.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Controls.cpp ($(CONFIG))"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/MainContent_91787020.o: ../../Source/Views/MainContent.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling MainContent.cpp ($(CONFIG))"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Presets_30a0e894.o: ../../Source/Views/Presets.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Presets.cpp ($(CONFIG))"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Preview_227d08e8.o: ../../Source/Views/Preview.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Preview.cpp ($(CONFIG))"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Statusbar_b88450c1.o: ../../Source/Views/Statusbar.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Statusbar.cpp ($(CONFIG))"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Main_90ebc5c2.o: ../../Source/Main.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Main.cpp ($(CONFIG))"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/BinaryData_ce4232d4.o: ../../JuceLibraryCode/BinaryData.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling BinaryData.cpp ($(CONFIG))"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_core_75b14332.o: ../../JuceLibraryCode/juce_core.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_core.cpp ($(CONFIG))"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_data_structures_72d3da2c.o: ../../JuceLibraryCode/juce_data_structures.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_data_structures.cpp ($(CONFIG))"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_events_d2be882c.o: ../../JuceLibraryCode/juce_events.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_events.cpp ($(CONFIG))"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_graphics_9c18891e.o: ../../JuceLibraryCode/juce_graphics.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_graphics.cpp ($(CONFIG))"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

$(JUCE_OBJDIR)/juce_gui_basics_8a6da59c.o: ../../JuceLibraryCode/juce_gui_basics.cpp
	-@mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling juce_gui_basics.cpp ($(CONFIG))"
	@$(CXX) $(JUCE_CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)

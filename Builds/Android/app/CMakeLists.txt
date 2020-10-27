# Automatically generated makefile, created by the Projucer
# Don't edit this file! Your changes will be overwritten when you re-save the Projucer project!

cmake_minimum_required(VERSION 3.4.1)

SET(BINARY_NAME "juce_jni")

add_library("cpufeatures" STATIC "${ANDROID_NDK}/sources/android/cpufeatures/cpu-features.c")
set_source_files_properties("${ANDROID_NDK}/sources/android/cpufeatures/cpu-features.c" PROPERTIES COMPILE_FLAGS "-Wno-sign-conversion -Wno-gnu-statement-expression")

add_definitions("-DJUCE_ANDROID=1" "-DJUCE_ANDROID_API_VERSION=16" "-DJUCE_PUSH_NOTIFICATIONS=1" "-DJUCE_PUSH_NOTIFICATIONS_ACTIVITY=\"com/roli/juce/JuceActivity\"" "-DJUCER_ANDROIDSTUDIO_7F0E4A25=1" "-DJUCE_APP_VERSION=0.16.005-pre6" "-DJUCE_APP_VERSION_HEX=0x1005")

include_directories( AFTER
    "../../../JuceLibraryCode"
    "../../../JuceLibraryCode/modules"
    "${ANDROID_NDK}/sources/android/cpufeatures"
)

enable_language(ASM)

IF(JUCE_BUILD_CONFIGURATION MATCHES "DEBUG")
    add_definitions("-DDEBUG=1" "-D_DEBUG=1")
    include_directories( AFTER
        "/usr/include/libircclient"
    )

ELSEIF(JUCE_BUILD_CONFIGURATION MATCHES "RELEASE")
    add_definitions("-DNDEBUG=1")
    include_directories( AFTER
        "/usr/include/libircclient"
    )

ELSE(JUCE_BUILD_CONFIGURATION MATCHES "DEBUG")
    MESSAGE( FATAL_ERROR "No matching build-configuration found." )
ENDIF(JUCE_BUILD_CONFIGURATION MATCHES "DEBUG")

add_library( ${BINARY_NAME}

    SHARED

    "../../../Blobs/avcaster-logo-48.png"
    "../../../Blobs/avcaster-logo-128.png"
    "../../../Blobs/config-hover.png"
    "../../../Blobs/config-pushed.png"
    "../../../Blobs/config.png"
    "../../../Source/Constants/AppConstants.h"
    "../../../Source/Constants/ConfigConstants.h"
    "../../../Source/Constants/Constants.h"
    "../../../Source/Constants/GstConstants.h"
    "../../../Source/Constants/GuiConstants.h"
    "../../../Source/Constants/IrcConstants.h"
    "../../../Source/Controllers/AvCaster.h"
    "../../../Source/Controllers/Gstreamer.h"
    "../../../Source/Controllers/IrcClient.h"
    "../../../Source/Models/AvCasterStore.h"
    "../../../Source/Models/Seeds.h"
    "../../../Source/Trace/Trace.h"
    "../../../Source/Trace/TraceAvCaster.h"
    "../../../Source/Trace/TraceAvCasterStore.h"
    "../../../Source/Trace/TraceChat.h"
    "../../../Source/Trace/TraceConfig.h"
    "../../../Source/Trace/TraceControls.h"
    "../../../Source/Trace/TraceGstreamer.h"
    "../../../Source/Trace/TraceIrcClient.h"
    "../../../Source/Trace/TraceMain.h"
    "../../../Source/Views/Background.h"
    "../../../Source/Views/Chat.h"
    "../../../Source/Views/ChatList.h"
    "../../../Source/Views/ChatListItem.h"
    "../../../Source/Views/Config.h"
    "../../../Source/Views/ConfigAudio.h"
    "../../../Source/Views/ConfigCamera.h"
    "../../../Source/Views/ConfigChat.h"
    "../../../Source/Views/ConfigImage.h"
    "../../../Source/Views/ConfigOutput.h"
    "../../../Source/Views/ConfigScreen.h"
    "../../../Source/Views/ConfigText.h"
    "../../../Source/Views/Controls.h"
    "../../../Source/Views/MainContent.h"
    "../../../Source/Views/Presets.h"
    "../../../Source/Views/Preview.h"
    "../../../Source/Views/Statusbar.h"
    "../../../Source/Constants/AppConstants.cpp"
    "../../../Source/Constants/ConfigConstants.cpp"
    "../../../Source/Constants/GstConstants.cpp"
    "../../../Source/Constants/GuiConstants.cpp"
    "../../../Source/Constants/IrcConstants.cpp"
    "../../../Source/Controllers/AvCaster.cpp"
    "../../../Source/Controllers/Gstreamer.cpp"
    "../../../Source/Controllers/IrcClient.cpp"
    "../../../Source/Models/AvCasterStore.cpp"
    "../../../Source/Models/Seeds.cpp"
    "../../../Source/Trace/Trace.cpp"
    "../../../Source/Views/Background.cpp"
    "../../../Source/Views/Chat.cpp"
    "../../../Source/Views/ChatList.cpp"
    "../../../Source/Views/ChatListItem.cpp"
    "../../../Source/Views/Config.cpp"
    "../../../Source/Views/ConfigAudio.cpp"
    "../../../Source/Views/ConfigCamera.cpp"
    "../../../Source/Views/ConfigChat.cpp"
    "../../../Source/Views/ConfigImage.cpp"
    "../../../Source/Views/ConfigOutput.cpp"
    "../../../Source/Views/ConfigScreen.cpp"
    "../../../Source/Views/ConfigText.cpp"
    "../../../Source/Views/Controls.cpp"
    "../../../Source/Views/MainContent.cpp"
    "../../../Source/Views/Presets.cpp"
    "../../../Source/Views/Preview.cpp"
    "../../../Source/Views/Statusbar.cpp"
    "../../../Source/Main.cpp"
    "../../../JuceLibraryCode/modules/juce_core/containers/juce_AbstractFifo.cpp"
    "../../../JuceLibraryCode/modules/juce_core/containers/juce_AbstractFifo.h"
    "../../../JuceLibraryCode/modules/juce_core/containers/juce_Array.h"
    "../../../JuceLibraryCode/modules/juce_core/containers/juce_ArrayAllocationBase.h"
    "../../../JuceLibraryCode/modules/juce_core/containers/juce_ArrayBase.cpp"
    "../../../JuceLibraryCode/modules/juce_core/containers/juce_ArrayBase.h"
    "../../../JuceLibraryCode/modules/juce_core/containers/juce_DynamicObject.cpp"
    "../../../JuceLibraryCode/modules/juce_core/containers/juce_DynamicObject.h"
    "../../../JuceLibraryCode/modules/juce_core/containers/juce_ElementComparator.h"
    "../../../JuceLibraryCode/modules/juce_core/containers/juce_HashMap.h"
    "../../../JuceLibraryCode/modules/juce_core/containers/juce_HashMap_test.cpp"
    "../../../JuceLibraryCode/modules/juce_core/containers/juce_LinkedListPointer.h"
    "../../../JuceLibraryCode/modules/juce_core/containers/juce_ListenerList.h"
    "../../../JuceLibraryCode/modules/juce_core/containers/juce_NamedValueSet.cpp"
    "../../../JuceLibraryCode/modules/juce_core/containers/juce_NamedValueSet.h"
    "../../../JuceLibraryCode/modules/juce_core/containers/juce_OwnedArray.cpp"
    "../../../JuceLibraryCode/modules/juce_core/containers/juce_OwnedArray.h"
    "../../../JuceLibraryCode/modules/juce_core/containers/juce_PropertySet.cpp"
    "../../../JuceLibraryCode/modules/juce_core/containers/juce_PropertySet.h"
    "../../../JuceLibraryCode/modules/juce_core/containers/juce_ReferenceCountedArray.cpp"
    "../../../JuceLibraryCode/modules/juce_core/containers/juce_ReferenceCountedArray.h"
    "../../../JuceLibraryCode/modules/juce_core/containers/juce_ScopedValueSetter.h"
    "../../../JuceLibraryCode/modules/juce_core/containers/juce_SortedSet.h"
    "../../../JuceLibraryCode/modules/juce_core/containers/juce_SparseSet.cpp"
    "../../../JuceLibraryCode/modules/juce_core/containers/juce_SparseSet.h"
    "../../../JuceLibraryCode/modules/juce_core/containers/juce_Variant.cpp"
    "../../../JuceLibraryCode/modules/juce_core/containers/juce_Variant.h"
    "../../../JuceLibraryCode/modules/juce_core/files/juce_DirectoryIterator.cpp"
    "../../../JuceLibraryCode/modules/juce_core/files/juce_DirectoryIterator.h"
    "../../../JuceLibraryCode/modules/juce_core/files/juce_File.cpp"
    "../../../JuceLibraryCode/modules/juce_core/files/juce_File.h"
    "../../../JuceLibraryCode/modules/juce_core/files/juce_FileFilter.cpp"
    "../../../JuceLibraryCode/modules/juce_core/files/juce_FileFilter.h"
    "../../../JuceLibraryCode/modules/juce_core/files/juce_FileInputStream.cpp"
    "../../../JuceLibraryCode/modules/juce_core/files/juce_FileInputStream.h"
    "../../../JuceLibraryCode/modules/juce_core/files/juce_FileOutputStream.cpp"
    "../../../JuceLibraryCode/modules/juce_core/files/juce_FileOutputStream.h"
    "../../../JuceLibraryCode/modules/juce_core/files/juce_FileSearchPath.cpp"
    "../../../JuceLibraryCode/modules/juce_core/files/juce_FileSearchPath.h"
    "../../../JuceLibraryCode/modules/juce_core/files/juce_MemoryMappedFile.h"
    "../../../JuceLibraryCode/modules/juce_core/files/juce_TemporaryFile.cpp"
    "../../../JuceLibraryCode/modules/juce_core/files/juce_TemporaryFile.h"
    "../../../JuceLibraryCode/modules/juce_core/files/juce_WildcardFileFilter.cpp"
    "../../../JuceLibraryCode/modules/juce_core/files/juce_WildcardFileFilter.h"
    "../../../JuceLibraryCode/modules/juce_core/javascript/juce_Javascript.cpp"
    "../../../JuceLibraryCode/modules/juce_core/javascript/juce_Javascript.h"
    "../../../JuceLibraryCode/modules/juce_core/javascript/juce_JSON.cpp"
    "../../../JuceLibraryCode/modules/juce_core/javascript/juce_JSON.h"
    "../../../JuceLibraryCode/modules/juce_core/logging/juce_FileLogger.cpp"
    "../../../JuceLibraryCode/modules/juce_core/logging/juce_FileLogger.h"
    "../../../JuceLibraryCode/modules/juce_core/logging/juce_Logger.cpp"
    "../../../JuceLibraryCode/modules/juce_core/logging/juce_Logger.h"
    "../../../JuceLibraryCode/modules/juce_core/maths/juce_BigInteger.cpp"
    "../../../JuceLibraryCode/modules/juce_core/maths/juce_BigInteger.h"
    "../../../JuceLibraryCode/modules/juce_core/maths/juce_Expression.cpp"
    "../../../JuceLibraryCode/modules/juce_core/maths/juce_Expression.h"
    "../../../JuceLibraryCode/modules/juce_core/maths/juce_MathsFunctions.h"
    "../../../JuceLibraryCode/modules/juce_core/maths/juce_NormalisableRange.h"
    "../../../JuceLibraryCode/modules/juce_core/maths/juce_Random.cpp"
    "../../../JuceLibraryCode/modules/juce_core/maths/juce_Random.h"
    "../../../JuceLibraryCode/modules/juce_core/maths/juce_Range.h"
    "../../../JuceLibraryCode/modules/juce_core/maths/juce_StatisticsAccumulator.h"
    "../../../JuceLibraryCode/modules/juce_core/memory/juce_Atomic.h"
    "../../../JuceLibraryCode/modules/juce_core/memory/juce_ByteOrder.h"
    "../../../JuceLibraryCode/modules/juce_core/memory/juce_ContainerDeletePolicy.h"
    "../../../JuceLibraryCode/modules/juce_core/memory/juce_HeapBlock.h"
    "../../../JuceLibraryCode/modules/juce_core/memory/juce_HeavyweightLeakedObjectDetector.h"
    "../../../JuceLibraryCode/modules/juce_core/memory/juce_LeakedObjectDetector.h"
    "../../../JuceLibraryCode/modules/juce_core/memory/juce_Memory.h"
    "../../../JuceLibraryCode/modules/juce_core/memory/juce_MemoryBlock.cpp"
    "../../../JuceLibraryCode/modules/juce_core/memory/juce_MemoryBlock.h"
    "../../../JuceLibraryCode/modules/juce_core/memory/juce_OptionalScopedPointer.h"
    "../../../JuceLibraryCode/modules/juce_core/memory/juce_ReferenceCountedObject.h"
    "../../../JuceLibraryCode/modules/juce_core/memory/juce_ScopedPointer.h"
    "../../../JuceLibraryCode/modules/juce_core/memory/juce_SharedResourcePointer.h"
    "../../../JuceLibraryCode/modules/juce_core/memory/juce_Singleton.h"
    "../../../JuceLibraryCode/modules/juce_core/memory/juce_WeakReference.h"
    "../../../JuceLibraryCode/modules/juce_core/misc/juce_ConsoleApplication.cpp"
    "../../../JuceLibraryCode/modules/juce_core/misc/juce_ConsoleApplication.h"
    "../../../JuceLibraryCode/modules/juce_core/misc/juce_Result.cpp"
    "../../../JuceLibraryCode/modules/juce_core/misc/juce_Result.h"
    "../../../JuceLibraryCode/modules/juce_core/misc/juce_RuntimePermissions.cpp"
    "../../../JuceLibraryCode/modules/juce_core/misc/juce_RuntimePermissions.h"
    "../../../JuceLibraryCode/modules/juce_core/misc/juce_Uuid.cpp"
    "../../../JuceLibraryCode/modules/juce_core/misc/juce_Uuid.h"
    "../../../JuceLibraryCode/modules/juce_core/misc/juce_WindowsRegistry.h"
    "../../../JuceLibraryCode/modules/juce_core/native/java/README.txt"
    "../../../JuceLibraryCode/modules/juce_core/native/juce_android_Files.cpp"
    "../../../JuceLibraryCode/modules/juce_core/native/juce_android_JNIHelpers.cpp"
    "../../../JuceLibraryCode/modules/juce_core/native/juce_android_JNIHelpers.h"
    "../../../JuceLibraryCode/modules/juce_core/native/juce_android_Misc.cpp"
    "../../../JuceLibraryCode/modules/juce_core/native/juce_android_Network.cpp"
    "../../../JuceLibraryCode/modules/juce_core/native/juce_android_RuntimePermissions.cpp"
    "../../../JuceLibraryCode/modules/juce_core/native/juce_android_SystemStats.cpp"
    "../../../JuceLibraryCode/modules/juce_core/native/juce_android_Threads.cpp"
    "../../../JuceLibraryCode/modules/juce_core/native/juce_BasicNativeHeaders.h"
    "../../../JuceLibraryCode/modules/juce_core/native/juce_curl_Network.cpp"
    "../../../JuceLibraryCode/modules/juce_core/native/juce_linux_CommonFile.cpp"
    "../../../JuceLibraryCode/modules/juce_core/native/juce_linux_Files.cpp"
    "../../../JuceLibraryCode/modules/juce_core/native/juce_linux_Network.cpp"
    "../../../JuceLibraryCode/modules/juce_core/native/juce_linux_SystemStats.cpp"
    "../../../JuceLibraryCode/modules/juce_core/native/juce_linux_Threads.cpp"
    "../../../JuceLibraryCode/modules/juce_core/native/juce_mac_ClangBugWorkaround.h"
    "../../../JuceLibraryCode/modules/juce_core/native/juce_mac_Files.mm"
    "../../../JuceLibraryCode/modules/juce_core/native/juce_mac_Network.mm"
    "../../../JuceLibraryCode/modules/juce_core/native/juce_mac_Strings.mm"
    "../../../JuceLibraryCode/modules/juce_core/native/juce_mac_SystemStats.mm"
    "../../../JuceLibraryCode/modules/juce_core/native/juce_mac_Threads.mm"
    "../../../JuceLibraryCode/modules/juce_core/native/juce_osx_ObjCHelpers.h"
    "../../../JuceLibraryCode/modules/juce_core/native/juce_posix_IPAddress.h"
    "../../../JuceLibraryCode/modules/juce_core/native/juce_posix_NamedPipe.cpp"
    "../../../JuceLibraryCode/modules/juce_core/native/juce_posix_SharedCode.h"
    "../../../JuceLibraryCode/modules/juce_core/native/juce_win32_ComSmartPtr.h"
    "../../../JuceLibraryCode/modules/juce_core/native/juce_win32_Files.cpp"
    "../../../JuceLibraryCode/modules/juce_core/native/juce_win32_Network.cpp"
    "../../../JuceLibraryCode/modules/juce_core/native/juce_win32_Registry.cpp"
    "../../../JuceLibraryCode/modules/juce_core/native/juce_win32_SystemStats.cpp"
    "../../../JuceLibraryCode/modules/juce_core/native/juce_win32_Threads.cpp"
    "../../../JuceLibraryCode/modules/juce_core/network/juce_IPAddress.cpp"
    "../../../JuceLibraryCode/modules/juce_core/network/juce_IPAddress.h"
    "../../../JuceLibraryCode/modules/juce_core/network/juce_MACAddress.cpp"
    "../../../JuceLibraryCode/modules/juce_core/network/juce_MACAddress.h"
    "../../../JuceLibraryCode/modules/juce_core/network/juce_NamedPipe.cpp"
    "../../../JuceLibraryCode/modules/juce_core/network/juce_NamedPipe.h"
    "../../../JuceLibraryCode/modules/juce_core/network/juce_Socket.cpp"
    "../../../JuceLibraryCode/modules/juce_core/network/juce_Socket.h"
    "../../../JuceLibraryCode/modules/juce_core/network/juce_URL.cpp"
    "../../../JuceLibraryCode/modules/juce_core/network/juce_URL.h"
    "../../../JuceLibraryCode/modules/juce_core/network/juce_WebInputStream.cpp"
    "../../../JuceLibraryCode/modules/juce_core/network/juce_WebInputStream.h"
    "../../../JuceLibraryCode/modules/juce_core/streams/juce_BufferedInputStream.cpp"
    "../../../JuceLibraryCode/modules/juce_core/streams/juce_BufferedInputStream.h"
    "../../../JuceLibraryCode/modules/juce_core/streams/juce_FileInputSource.cpp"
    "../../../JuceLibraryCode/modules/juce_core/streams/juce_FileInputSource.h"
    "../../../JuceLibraryCode/modules/juce_core/streams/juce_InputSource.h"
    "../../../JuceLibraryCode/modules/juce_core/streams/juce_InputStream.cpp"
    "../../../JuceLibraryCode/modules/juce_core/streams/juce_InputStream.h"
    "../../../JuceLibraryCode/modules/juce_core/streams/juce_MemoryInputStream.cpp"
    "../../../JuceLibraryCode/modules/juce_core/streams/juce_MemoryInputStream.h"
    "../../../JuceLibraryCode/modules/juce_core/streams/juce_MemoryOutputStream.cpp"
    "../../../JuceLibraryCode/modules/juce_core/streams/juce_MemoryOutputStream.h"
    "../../../JuceLibraryCode/modules/juce_core/streams/juce_OutputStream.cpp"
    "../../../JuceLibraryCode/modules/juce_core/streams/juce_OutputStream.h"
    "../../../JuceLibraryCode/modules/juce_core/streams/juce_SubregionStream.cpp"
    "../../../JuceLibraryCode/modules/juce_core/streams/juce_SubregionStream.h"
    "../../../JuceLibraryCode/modules/juce_core/streams/juce_URLInputSource.cpp"
    "../../../JuceLibraryCode/modules/juce_core/streams/juce_URLInputSource.h"
    "../../../JuceLibraryCode/modules/juce_core/system/juce_CompilerSupport.h"
    "../../../JuceLibraryCode/modules/juce_core/system/juce_PlatformDefs.h"
    "../../../JuceLibraryCode/modules/juce_core/system/juce_StandardHeader.h"
    "../../../JuceLibraryCode/modules/juce_core/system/juce_SystemStats.cpp"
    "../../../JuceLibraryCode/modules/juce_core/system/juce_SystemStats.h"
    "../../../JuceLibraryCode/modules/juce_core/system/juce_TargetPlatform.h"
    "../../../JuceLibraryCode/modules/juce_core/text/juce_Base64.cpp"
    "../../../JuceLibraryCode/modules/juce_core/text/juce_Base64.h"
    "../../../JuceLibraryCode/modules/juce_core/text/juce_CharacterFunctions.cpp"
    "../../../JuceLibraryCode/modules/juce_core/text/juce_CharacterFunctions.h"
    "../../../JuceLibraryCode/modules/juce_core/text/juce_CharPointer_ASCII.h"
    "../../../JuceLibraryCode/modules/juce_core/text/juce_CharPointer_UTF8.h"
    "../../../JuceLibraryCode/modules/juce_core/text/juce_CharPointer_UTF16.h"
    "../../../JuceLibraryCode/modules/juce_core/text/juce_CharPointer_UTF32.h"
    "../../../JuceLibraryCode/modules/juce_core/text/juce_Identifier.cpp"
    "../../../JuceLibraryCode/modules/juce_core/text/juce_Identifier.h"
    "../../../JuceLibraryCode/modules/juce_core/text/juce_LocalisedStrings.cpp"
    "../../../JuceLibraryCode/modules/juce_core/text/juce_LocalisedStrings.h"
    "../../../JuceLibraryCode/modules/juce_core/text/juce_NewLine.h"
    "../../../JuceLibraryCode/modules/juce_core/text/juce_String.cpp"
    "../../../JuceLibraryCode/modules/juce_core/text/juce_String.h"
    "../../../JuceLibraryCode/modules/juce_core/text/juce_StringArray.cpp"
    "../../../JuceLibraryCode/modules/juce_core/text/juce_StringArray.h"
    "../../../JuceLibraryCode/modules/juce_core/text/juce_StringPairArray.cpp"
    "../../../JuceLibraryCode/modules/juce_core/text/juce_StringPairArray.h"
    "../../../JuceLibraryCode/modules/juce_core/text/juce_StringPool.cpp"
    "../../../JuceLibraryCode/modules/juce_core/text/juce_StringPool.h"
    "../../../JuceLibraryCode/modules/juce_core/text/juce_StringRef.h"
    "../../../JuceLibraryCode/modules/juce_core/text/juce_TextDiff.cpp"
    "../../../JuceLibraryCode/modules/juce_core/text/juce_TextDiff.h"
    "../../../JuceLibraryCode/modules/juce_core/threads/juce_ChildProcess.cpp"
    "../../../JuceLibraryCode/modules/juce_core/threads/juce_ChildProcess.h"
    "../../../JuceLibraryCode/modules/juce_core/threads/juce_CriticalSection.h"
    "../../../JuceLibraryCode/modules/juce_core/threads/juce_DynamicLibrary.h"
    "../../../JuceLibraryCode/modules/juce_core/threads/juce_HighResolutionTimer.cpp"
    "../../../JuceLibraryCode/modules/juce_core/threads/juce_HighResolutionTimer.h"
    "../../../JuceLibraryCode/modules/juce_core/threads/juce_InterProcessLock.h"
    "../../../JuceLibraryCode/modules/juce_core/threads/juce_Process.h"
    "../../../JuceLibraryCode/modules/juce_core/threads/juce_ReadWriteLock.cpp"
    "../../../JuceLibraryCode/modules/juce_core/threads/juce_ReadWriteLock.h"
    "../../../JuceLibraryCode/modules/juce_core/threads/juce_ScopedLock.h"
    "../../../JuceLibraryCode/modules/juce_core/threads/juce_ScopedReadLock.h"
    "../../../JuceLibraryCode/modules/juce_core/threads/juce_ScopedWriteLock.h"
    "../../../JuceLibraryCode/modules/juce_core/threads/juce_SpinLock.h"
    "../../../JuceLibraryCode/modules/juce_core/threads/juce_Thread.cpp"
    "../../../JuceLibraryCode/modules/juce_core/threads/juce_Thread.h"
    "../../../JuceLibraryCode/modules/juce_core/threads/juce_ThreadLocalValue.h"
    "../../../JuceLibraryCode/modules/juce_core/threads/juce_ThreadPool.cpp"
    "../../../JuceLibraryCode/modules/juce_core/threads/juce_ThreadPool.h"
    "../../../JuceLibraryCode/modules/juce_core/threads/juce_TimeSliceThread.cpp"
    "../../../JuceLibraryCode/modules/juce_core/threads/juce_TimeSliceThread.h"
    "../../../JuceLibraryCode/modules/juce_core/threads/juce_WaitableEvent.cpp"
    "../../../JuceLibraryCode/modules/juce_core/threads/juce_WaitableEvent.h"
    "../../../JuceLibraryCode/modules/juce_core/time/juce_PerformanceCounter.cpp"
    "../../../JuceLibraryCode/modules/juce_core/time/juce_PerformanceCounter.h"
    "../../../JuceLibraryCode/modules/juce_core/time/juce_RelativeTime.cpp"
    "../../../JuceLibraryCode/modules/juce_core/time/juce_RelativeTime.h"
    "../../../JuceLibraryCode/modules/juce_core/time/juce_Time.cpp"
    "../../../JuceLibraryCode/modules/juce_core/time/juce_Time.h"
    "../../../JuceLibraryCode/modules/juce_core/unit_tests/juce_UnitTest.cpp"
    "../../../JuceLibraryCode/modules/juce_core/unit_tests/juce_UnitTest.h"
    "../../../JuceLibraryCode/modules/juce_core/unit_tests/juce_UnitTestCategories.h"
    "../../../JuceLibraryCode/modules/juce_core/xml/juce_XmlDocument.cpp"
    "../../../JuceLibraryCode/modules/juce_core/xml/juce_XmlDocument.h"
    "../../../JuceLibraryCode/modules/juce_core/xml/juce_XmlElement.cpp"
    "../../../JuceLibraryCode/modules/juce_core/xml/juce_XmlElement.h"
    "../../../JuceLibraryCode/modules/juce_core/zip/juce_GZIPCompressorOutputStream.cpp"
    "../../../JuceLibraryCode/modules/juce_core/zip/juce_GZIPCompressorOutputStream.h"
    "../../../JuceLibraryCode/modules/juce_core/zip/juce_GZIPDecompressorInputStream.cpp"
    "../../../JuceLibraryCode/modules/juce_core/zip/juce_GZIPDecompressorInputStream.h"
    "../../../JuceLibraryCode/modules/juce_core/zip/juce_ZipFile.cpp"
    "../../../JuceLibraryCode/modules/juce_core/zip/juce_ZipFile.h"
    "../../../JuceLibraryCode/modules/juce_core/juce_core.cpp"
    "../../../JuceLibraryCode/modules/juce_core/juce_core.mm"
    "../../../JuceLibraryCode/modules/juce_core/juce_core.h"
    "../../../JuceLibraryCode/modules/juce_data_structures/app_properties/juce_ApplicationProperties.cpp"
    "../../../JuceLibraryCode/modules/juce_data_structures/app_properties/juce_ApplicationProperties.h"
    "../../../JuceLibraryCode/modules/juce_data_structures/app_properties/juce_PropertiesFile.cpp"
    "../../../JuceLibraryCode/modules/juce_data_structures/app_properties/juce_PropertiesFile.h"
    "../../../JuceLibraryCode/modules/juce_data_structures/undomanager/juce_UndoableAction.h"
    "../../../JuceLibraryCode/modules/juce_data_structures/undomanager/juce_UndoManager.cpp"
    "../../../JuceLibraryCode/modules/juce_data_structures/undomanager/juce_UndoManager.h"
    "../../../JuceLibraryCode/modules/juce_data_structures/values/juce_CachedValue.cpp"
    "../../../JuceLibraryCode/modules/juce_data_structures/values/juce_CachedValue.h"
    "../../../JuceLibraryCode/modules/juce_data_structures/values/juce_Value.cpp"
    "../../../JuceLibraryCode/modules/juce_data_structures/values/juce_Value.h"
    "../../../JuceLibraryCode/modules/juce_data_structures/values/juce_ValueTree.cpp"
    "../../../JuceLibraryCode/modules/juce_data_structures/values/juce_ValueTree.h"
    "../../../JuceLibraryCode/modules/juce_data_structures/values/juce_ValueTreeSynchroniser.cpp"
    "../../../JuceLibraryCode/modules/juce_data_structures/values/juce_ValueTreeSynchroniser.h"
    "../../../JuceLibraryCode/modules/juce_data_structures/values/juce_ValueWithDefault.cpp"
    "../../../JuceLibraryCode/modules/juce_data_structures/values/juce_ValueWithDefault.h"
    "../../../JuceLibraryCode/modules/juce_data_structures/juce_data_structures.cpp"
    "../../../JuceLibraryCode/modules/juce_data_structures/juce_data_structures.mm"
    "../../../JuceLibraryCode/modules/juce_data_structures/juce_data_structures.h"
    "../../../JuceLibraryCode/modules/juce_events/broadcasters/juce_ActionBroadcaster.cpp"
    "../../../JuceLibraryCode/modules/juce_events/broadcasters/juce_ActionBroadcaster.h"
    "../../../JuceLibraryCode/modules/juce_events/broadcasters/juce_ActionListener.h"
    "../../../JuceLibraryCode/modules/juce_events/broadcasters/juce_AsyncUpdater.cpp"
    "../../../JuceLibraryCode/modules/juce_events/broadcasters/juce_AsyncUpdater.h"
    "../../../JuceLibraryCode/modules/juce_events/broadcasters/juce_ChangeBroadcaster.cpp"
    "../../../JuceLibraryCode/modules/juce_events/broadcasters/juce_ChangeBroadcaster.h"
    "../../../JuceLibraryCode/modules/juce_events/broadcasters/juce_ChangeListener.h"
    "../../../JuceLibraryCode/modules/juce_events/interprocess/juce_ConnectedChildProcess.cpp"
    "../../../JuceLibraryCode/modules/juce_events/interprocess/juce_ConnectedChildProcess.h"
    "../../../JuceLibraryCode/modules/juce_events/interprocess/juce_InterprocessConnection.cpp"
    "../../../JuceLibraryCode/modules/juce_events/interprocess/juce_InterprocessConnection.h"
    "../../../JuceLibraryCode/modules/juce_events/interprocess/juce_InterprocessConnectionServer.cpp"
    "../../../JuceLibraryCode/modules/juce_events/interprocess/juce_InterprocessConnectionServer.h"
    "../../../JuceLibraryCode/modules/juce_events/interprocess/juce_NetworkServiceDiscovery.cpp"
    "../../../JuceLibraryCode/modules/juce_events/interprocess/juce_NetworkServiceDiscovery.h"
    "../../../JuceLibraryCode/modules/juce_events/messages/juce_ApplicationBase.cpp"
    "../../../JuceLibraryCode/modules/juce_events/messages/juce_ApplicationBase.h"
    "../../../JuceLibraryCode/modules/juce_events/messages/juce_CallbackMessage.h"
    "../../../JuceLibraryCode/modules/juce_events/messages/juce_DeletedAtShutdown.cpp"
    "../../../JuceLibraryCode/modules/juce_events/messages/juce_DeletedAtShutdown.h"
    "../../../JuceLibraryCode/modules/juce_events/messages/juce_Initialisation.h"
    "../../../JuceLibraryCode/modules/juce_events/messages/juce_Message.h"
    "../../../JuceLibraryCode/modules/juce_events/messages/juce_MessageListener.cpp"
    "../../../JuceLibraryCode/modules/juce_events/messages/juce_MessageListener.h"
    "../../../JuceLibraryCode/modules/juce_events/messages/juce_MessageManager.cpp"
    "../../../JuceLibraryCode/modules/juce_events/messages/juce_MessageManager.h"
    "../../../JuceLibraryCode/modules/juce_events/messages/juce_MountedVolumeListChangeDetector.h"
    "../../../JuceLibraryCode/modules/juce_events/messages/juce_NotificationType.h"
    "../../../JuceLibraryCode/modules/juce_events/native/juce_android_Messaging.cpp"
    "../../../JuceLibraryCode/modules/juce_events/native/juce_ios_MessageManager.mm"
    "../../../JuceLibraryCode/modules/juce_events/native/juce_linux_EventLoop.h"
    "../../../JuceLibraryCode/modules/juce_events/native/juce_linux_Messaging.cpp"
    "../../../JuceLibraryCode/modules/juce_events/native/juce_mac_MessageManager.mm"
    "../../../JuceLibraryCode/modules/juce_events/native/juce_osx_MessageQueue.h"
    "../../../JuceLibraryCode/modules/juce_events/native/juce_win32_HiddenMessageWindow.h"
    "../../../JuceLibraryCode/modules/juce_events/native/juce_win32_Messaging.cpp"
    "../../../JuceLibraryCode/modules/juce_events/native/juce_win32_WinRTWrapper.cpp"
    "../../../JuceLibraryCode/modules/juce_events/native/juce_win32_WinRTWrapper.h"
    "../../../JuceLibraryCode/modules/juce_events/timers/juce_MultiTimer.cpp"
    "../../../JuceLibraryCode/modules/juce_events/timers/juce_MultiTimer.h"
    "../../../JuceLibraryCode/modules/juce_events/timers/juce_Timer.cpp"
    "../../../JuceLibraryCode/modules/juce_events/timers/juce_Timer.h"
    "../../../JuceLibraryCode/modules/juce_events/juce_events.cpp"
    "../../../JuceLibraryCode/modules/juce_events/juce_events.mm"
    "../../../JuceLibraryCode/modules/juce_events/juce_events.h"
    "../../../JuceLibraryCode/modules/juce_graphics/colour/juce_Colour.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/colour/juce_Colour.h"
    "../../../JuceLibraryCode/modules/juce_graphics/colour/juce_ColourGradient.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/colour/juce_ColourGradient.h"
    "../../../JuceLibraryCode/modules/juce_graphics/colour/juce_Colours.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/colour/juce_Colours.h"
    "../../../JuceLibraryCode/modules/juce_graphics/colour/juce_FillType.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/colour/juce_FillType.h"
    "../../../JuceLibraryCode/modules/juce_graphics/colour/juce_PixelFormats.h"
    "../../../JuceLibraryCode/modules/juce_graphics/contexts/juce_GraphicsContext.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/contexts/juce_GraphicsContext.h"
    "../../../JuceLibraryCode/modules/juce_graphics/contexts/juce_LowLevelGraphicsContext.h"
    "../../../JuceLibraryCode/modules/juce_graphics/contexts/juce_LowLevelGraphicsPostScriptRenderer.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/contexts/juce_LowLevelGraphicsPostScriptRenderer.h"
    "../../../JuceLibraryCode/modules/juce_graphics/contexts/juce_LowLevelGraphicsSoftwareRenderer.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/contexts/juce_LowLevelGraphicsSoftwareRenderer.h"
    "../../../JuceLibraryCode/modules/juce_graphics/effects/juce_DropShadowEffect.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/effects/juce_DropShadowEffect.h"
    "../../../JuceLibraryCode/modules/juce_graphics/effects/juce_GlowEffect.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/effects/juce_GlowEffect.h"
    "../../../JuceLibraryCode/modules/juce_graphics/effects/juce_ImageEffectFilter.h"
    "../../../JuceLibraryCode/modules/juce_graphics/fonts/juce_AttributedString.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/fonts/juce_AttributedString.h"
    "../../../JuceLibraryCode/modules/juce_graphics/fonts/juce_CustomTypeface.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/fonts/juce_CustomTypeface.h"
    "../../../JuceLibraryCode/modules/juce_graphics/fonts/juce_Font.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/fonts/juce_Font.h"
    "../../../JuceLibraryCode/modules/juce_graphics/fonts/juce_GlyphArrangement.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/fonts/juce_GlyphArrangement.h"
    "../../../JuceLibraryCode/modules/juce_graphics/fonts/juce_TextLayout.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/fonts/juce_TextLayout.h"
    "../../../JuceLibraryCode/modules/juce_graphics/fonts/juce_Typeface.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/fonts/juce_Typeface.h"
    "../../../JuceLibraryCode/modules/juce_graphics/geometry/juce_AffineTransform.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/geometry/juce_AffineTransform.h"
    "../../../JuceLibraryCode/modules/juce_graphics/geometry/juce_BorderSize.h"
    "../../../JuceLibraryCode/modules/juce_graphics/geometry/juce_EdgeTable.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/geometry/juce_EdgeTable.h"
    "../../../JuceLibraryCode/modules/juce_graphics/geometry/juce_Line.h"
    "../../../JuceLibraryCode/modules/juce_graphics/geometry/juce_Parallelogram.h"
    "../../../JuceLibraryCode/modules/juce_graphics/geometry/juce_Path.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/geometry/juce_Path.h"
    "../../../JuceLibraryCode/modules/juce_graphics/geometry/juce_PathIterator.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/geometry/juce_PathIterator.h"
    "../../../JuceLibraryCode/modules/juce_graphics/geometry/juce_PathStrokeType.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/geometry/juce_PathStrokeType.h"
    "../../../JuceLibraryCode/modules/juce_graphics/geometry/juce_Point.h"
    "../../../JuceLibraryCode/modules/juce_graphics/geometry/juce_Rectangle.h"
    "../../../JuceLibraryCode/modules/juce_graphics/geometry/juce_RectangleList.h"
    "../../../JuceLibraryCode/modules/juce_graphics/image_formats/juce_GIFLoader.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/image_formats/juce_JPEGLoader.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/image_formats/juce_PNGLoader.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/images/juce_Image.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/images/juce_Image.h"
    "../../../JuceLibraryCode/modules/juce_graphics/images/juce_ImageCache.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/images/juce_ImageCache.h"
    "../../../JuceLibraryCode/modules/juce_graphics/images/juce_ImageConvolutionKernel.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/images/juce_ImageConvolutionKernel.h"
    "../../../JuceLibraryCode/modules/juce_graphics/images/juce_ImageFileFormat.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/images/juce_ImageFileFormat.h"
    "../../../JuceLibraryCode/modules/juce_graphics/native/juce_android_Fonts.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/native/juce_android_GraphicsContext.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/native/juce_android_IconHelpers.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/native/juce_freetype_Fonts.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/native/juce_linux_Fonts.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/native/juce_linux_IconHelpers.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/native/juce_mac_CoreGraphicsContext.h"
    "../../../JuceLibraryCode/modules/juce_graphics/native/juce_mac_CoreGraphicsContext.mm"
    "../../../JuceLibraryCode/modules/juce_graphics/native/juce_mac_CoreGraphicsHelpers.h"
    "../../../JuceLibraryCode/modules/juce_graphics/native/juce_mac_Fonts.mm"
    "../../../JuceLibraryCode/modules/juce_graphics/native/juce_mac_IconHelpers.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/native/juce_RenderingHelpers.h"
    "../../../JuceLibraryCode/modules/juce_graphics/native/juce_win32_Direct2DGraphicsContext.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/native/juce_win32_Direct2DGraphicsContext.h"
    "../../../JuceLibraryCode/modules/juce_graphics/native/juce_win32_DirectWriteTypeface.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/native/juce_win32_DirectWriteTypeLayout.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/native/juce_win32_Fonts.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/native/juce_win32_IconHelpers.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/placement/juce_Justification.h"
    "../../../JuceLibraryCode/modules/juce_graphics/placement/juce_RectanglePlacement.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/placement/juce_RectanglePlacement.h"
    "../../../JuceLibraryCode/modules/juce_graphics/juce_graphics.cpp"
    "../../../JuceLibraryCode/modules/juce_graphics/juce_graphics.mm"
    "../../../JuceLibraryCode/modules/juce_graphics/juce_graphics.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/application/juce_Application.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/application/juce_Application.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/buttons/juce_ArrowButton.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/buttons/juce_ArrowButton.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/buttons/juce_Button.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/buttons/juce_Button.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/buttons/juce_DrawableButton.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/buttons/juce_DrawableButton.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/buttons/juce_HyperlinkButton.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/buttons/juce_HyperlinkButton.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/buttons/juce_ImageButton.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/buttons/juce_ImageButton.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/buttons/juce_ShapeButton.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/buttons/juce_ShapeButton.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/buttons/juce_TextButton.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/buttons/juce_TextButton.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/buttons/juce_ToggleButton.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/buttons/juce_ToggleButton.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/buttons/juce_ToolbarButton.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/buttons/juce_ToolbarButton.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/commands/juce_ApplicationCommandID.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/commands/juce_ApplicationCommandInfo.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/commands/juce_ApplicationCommandInfo.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/commands/juce_ApplicationCommandManager.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/commands/juce_ApplicationCommandManager.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/commands/juce_ApplicationCommandTarget.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/commands/juce_ApplicationCommandTarget.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/commands/juce_KeyPressMappingSet.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/commands/juce_KeyPressMappingSet.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/components/juce_CachedComponentImage.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/components/juce_Component.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/components/juce_Component.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/components/juce_ComponentListener.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/components/juce_ComponentListener.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/components/juce_ModalComponentManager.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/components/juce_ModalComponentManager.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/desktop/juce_Desktop.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/desktop/juce_Desktop.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/desktop/juce_Displays.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/desktop/juce_Displays.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/drawables/juce_Drawable.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/drawables/juce_Drawable.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/drawables/juce_DrawableComposite.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/drawables/juce_DrawableComposite.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/drawables/juce_DrawableImage.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/drawables/juce_DrawableImage.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/drawables/juce_DrawablePath.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/drawables/juce_DrawablePath.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/drawables/juce_DrawableRectangle.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/drawables/juce_DrawableRectangle.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/drawables/juce_DrawableShape.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/drawables/juce_DrawableShape.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/drawables/juce_DrawableText.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/drawables/juce_DrawableText.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/drawables/juce_SVGParser.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_ContentSharer.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_ContentSharer.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_DirectoryContentsDisplayComponent.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_DirectoryContentsDisplayComponent.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_DirectoryContentsList.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_DirectoryContentsList.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_FileBrowserComponent.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_FileBrowserComponent.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_FileBrowserListener.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_FileChooser.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_FileChooser.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_FileChooserDialogBox.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_FileChooserDialogBox.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_FileListComponent.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_FileListComponent.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_FilenameComponent.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_FilenameComponent.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_FilePreviewComponent.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_FileSearchPathListComponent.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_FileSearchPathListComponent.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_FileTreeComponent.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_FileTreeComponent.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_ImagePreviewComponent.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_ImagePreviewComponent.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/keyboard/juce_CaretComponent.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/keyboard/juce_CaretComponent.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/keyboard/juce_KeyboardFocusTraverser.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/keyboard/juce_KeyboardFocusTraverser.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/keyboard/juce_KeyListener.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/keyboard/juce_KeyListener.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/keyboard/juce_KeyPress.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/keyboard/juce_KeyPress.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/keyboard/juce_ModifierKeys.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/keyboard/juce_ModifierKeys.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/keyboard/juce_SystemClipboard.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/keyboard/juce_TextEditorKeyMapper.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/keyboard/juce_TextInputTarget.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_AnimatedPosition.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_AnimatedPositionBehaviours.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_ComponentAnimator.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_ComponentAnimator.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_ComponentBoundsConstrainer.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_ComponentBoundsConstrainer.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_ComponentBuilder.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_ComponentBuilder.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_ComponentMovementWatcher.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_ComponentMovementWatcher.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_ConcertinaPanel.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_ConcertinaPanel.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_FlexBox.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_FlexBox.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_FlexItem.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_Grid.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_Grid.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_GridItem.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_GridItem.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_GroupComponent.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_GroupComponent.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_MultiDocumentPanel.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_MultiDocumentPanel.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_ResizableBorderComponent.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_ResizableBorderComponent.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_ResizableCornerComponent.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_ResizableCornerComponent.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_ResizableEdgeComponent.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_ResizableEdgeComponent.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_ScrollBar.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_ScrollBar.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_SidePanel.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_SidePanel.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_StretchableLayoutManager.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_StretchableLayoutManager.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_StretchableLayoutResizerBar.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_StretchableLayoutResizerBar.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_StretchableObjectResizer.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_StretchableObjectResizer.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_TabbedButtonBar.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_TabbedButtonBar.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_TabbedComponent.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_TabbedComponent.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_Viewport.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_Viewport.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V1.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V1.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V2.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V2.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V3.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V3.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V4.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V4.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/menus/juce_BurgerMenuComponent.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/menus/juce_BurgerMenuComponent.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/menus/juce_MenuBarComponent.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/menus/juce_MenuBarComponent.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/menus/juce_MenuBarModel.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/menus/juce_MenuBarModel.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/menus/juce_PopupMenu.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/menus/juce_PopupMenu.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/misc/juce_BubbleComponent.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/misc/juce_BubbleComponent.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/misc/juce_DropShadower.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/misc/juce_DropShadower.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/misc/juce_JUCESplashScreen.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/misc/juce_JUCESplashScreen.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_ComponentDragger.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_ComponentDragger.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_DragAndDropContainer.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_DragAndDropContainer.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_DragAndDropTarget.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_FileDragAndDropTarget.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_LassoComponent.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_MouseCursor.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_MouseCursor.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_MouseEvent.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_MouseEvent.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_MouseInactivityDetector.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_MouseInactivityDetector.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_MouseInputSource.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_MouseInputSource.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_MouseListener.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_MouseListener.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_SelectedItemSet.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_TextDragAndDropTarget.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_TooltipClient.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_android_ContentSharer.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_android_FileChooser.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_android_Windowing.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_common_MimeTypes.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_ios_ContentSharer.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_ios_FileChooser.mm"
    "../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_ios_UIViewComponentPeer.mm"
    "../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_ios_Windowing.mm"
    "../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_linux_FileChooser.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_linux_X11.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_linux_X11.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_linux_X11_Clipboard.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_linux_X11_Windowing.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_mac_FileChooser.mm"
    "../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_mac_MainMenu.mm"
    "../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_mac_MouseCursor.mm"
    "../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_mac_NSViewComponentPeer.mm"
    "../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_mac_Windowing.mm"
    "../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_MultiTouchMapper.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_win32_DragAndDrop.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_win32_FileChooser.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_win32_Windowing.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/positioning/juce_MarkerList.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/positioning/juce_MarkerList.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/positioning/juce_RelativeCoordinate.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/positioning/juce_RelativeCoordinate.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/positioning/juce_RelativeCoordinatePositioner.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/positioning/juce_RelativeCoordinatePositioner.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/positioning/juce_RelativeParallelogram.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/positioning/juce_RelativeParallelogram.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/positioning/juce_RelativePoint.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/positioning/juce_RelativePoint.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/positioning/juce_RelativePointPath.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/positioning/juce_RelativePointPath.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/positioning/juce_RelativeRectangle.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/positioning/juce_RelativeRectangle.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/properties/juce_BooleanPropertyComponent.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/properties/juce_BooleanPropertyComponent.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/properties/juce_ButtonPropertyComponent.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/properties/juce_ButtonPropertyComponent.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/properties/juce_ChoicePropertyComponent.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/properties/juce_ChoicePropertyComponent.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/properties/juce_MultiChoicePropertyComponent.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/properties/juce_MultiChoicePropertyComponent.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/properties/juce_PropertyComponent.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/properties/juce_PropertyComponent.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/properties/juce_PropertyPanel.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/properties/juce_PropertyPanel.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/properties/juce_SliderPropertyComponent.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/properties/juce_SliderPropertyComponent.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/properties/juce_TextPropertyComponent.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/properties/juce_TextPropertyComponent.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_ComboBox.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_ComboBox.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_ImageComponent.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_ImageComponent.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_Label.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_Label.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_ListBox.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_ListBox.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_ProgressBar.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_ProgressBar.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_Slider.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_Slider.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_TableHeaderComponent.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_TableHeaderComponent.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_TableListBox.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_TableListBox.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_TextEditor.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_TextEditor.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_Toolbar.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_Toolbar.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_ToolbarItemComponent.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_ToolbarItemComponent.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_ToolbarItemFactory.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_ToolbarItemPalette.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_ToolbarItemPalette.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_TreeView.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_TreeView.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_AlertWindow.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_AlertWindow.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_CallOutBox.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_CallOutBox.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_ComponentPeer.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_ComponentPeer.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_DialogWindow.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_DialogWindow.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_DocumentWindow.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_DocumentWindow.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_NativeMessageBox.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_ResizableWindow.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_ResizableWindow.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_ThreadWithProgressWindow.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_ThreadWithProgressWindow.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_TooltipWindow.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_TooltipWindow.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_TopLevelWindow.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_TopLevelWindow.h"
    "../../../JuceLibraryCode/modules/juce_gui_basics/juce_gui_basics.cpp"
    "../../../JuceLibraryCode/modules/juce_gui_basics/juce_gui_basics.mm"
    "../../../JuceLibraryCode/modules/juce_gui_basics/juce_gui_basics.h"
    "../../../JuceLibraryCode/AppConfig.h"
    "../../../JuceLibraryCode/BinaryData.cpp"
    "../../../JuceLibraryCode/BinaryData.h"
    "../../../JuceLibraryCode/include_juce_core.cpp"
    "../../../JuceLibraryCode/include_juce_data_structures.cpp"
    "../../../JuceLibraryCode/include_juce_events.cpp"
    "../../../JuceLibraryCode/include_juce_graphics.cpp"
    "../../../JuceLibraryCode/include_juce_gui_basics.cpp"
    "../../../JuceLibraryCode/JuceHeader.h"
)

set_source_files_properties("../../../Blobs/avcaster-logo-48.png" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Blobs/avcaster-logo-128.png" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Blobs/config-hover.png" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Blobs/config-pushed.png" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Blobs/config.png" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Constants/AppConstants.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Constants/ConfigConstants.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Constants/Constants.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Constants/GstConstants.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Constants/GuiConstants.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Constants/IrcConstants.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Controllers/AvCaster.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Controllers/Gstreamer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Controllers/IrcClient.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Models/AvCasterStore.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Models/Seeds.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Trace/Trace.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Trace/TraceAvCaster.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Trace/TraceAvCasterStore.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Trace/TraceChat.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Trace/TraceConfig.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Trace/TraceControls.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Trace/TraceGstreamer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Trace/TraceIrcClient.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Trace/TraceMain.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Views/Background.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Views/Chat.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Views/ChatList.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Views/ChatListItem.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Views/Config.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Views/ConfigAudio.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Views/ConfigCamera.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Views/ConfigChat.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Views/ConfigImage.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Views/ConfigOutput.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Views/ConfigScreen.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Views/ConfigText.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Views/Controls.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Views/MainContent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Views/Presets.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Views/Preview.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../Source/Views/Statusbar.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/containers/juce_AbstractFifo.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/containers/juce_AbstractFifo.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/containers/juce_Array.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/containers/juce_ArrayAllocationBase.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/containers/juce_ArrayBase.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/containers/juce_ArrayBase.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/containers/juce_DynamicObject.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/containers/juce_DynamicObject.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/containers/juce_ElementComparator.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/containers/juce_HashMap.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/containers/juce_HashMap_test.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/containers/juce_LinkedListPointer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/containers/juce_ListenerList.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/containers/juce_NamedValueSet.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/containers/juce_NamedValueSet.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/containers/juce_OwnedArray.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/containers/juce_OwnedArray.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/containers/juce_PropertySet.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/containers/juce_PropertySet.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/containers/juce_ReferenceCountedArray.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/containers/juce_ReferenceCountedArray.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/containers/juce_ScopedValueSetter.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/containers/juce_SortedSet.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/containers/juce_SparseSet.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/containers/juce_SparseSet.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/containers/juce_Variant.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/containers/juce_Variant.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/files/juce_DirectoryIterator.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/files/juce_DirectoryIterator.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/files/juce_File.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/files/juce_File.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/files/juce_FileFilter.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/files/juce_FileFilter.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/files/juce_FileInputStream.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/files/juce_FileInputStream.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/files/juce_FileOutputStream.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/files/juce_FileOutputStream.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/files/juce_FileSearchPath.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/files/juce_FileSearchPath.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/files/juce_MemoryMappedFile.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/files/juce_TemporaryFile.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/files/juce_TemporaryFile.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/files/juce_WildcardFileFilter.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/files/juce_WildcardFileFilter.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/javascript/juce_Javascript.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/javascript/juce_Javascript.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/javascript/juce_JSON.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/javascript/juce_JSON.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/logging/juce_FileLogger.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/logging/juce_FileLogger.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/logging/juce_Logger.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/logging/juce_Logger.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/maths/juce_BigInteger.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/maths/juce_BigInteger.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/maths/juce_Expression.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/maths/juce_Expression.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/maths/juce_MathsFunctions.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/maths/juce_NormalisableRange.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/maths/juce_Random.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/maths/juce_Random.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/maths/juce_Range.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/maths/juce_StatisticsAccumulator.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/memory/juce_Atomic.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/memory/juce_ByteOrder.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/memory/juce_ContainerDeletePolicy.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/memory/juce_HeapBlock.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/memory/juce_HeavyweightLeakedObjectDetector.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/memory/juce_LeakedObjectDetector.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/memory/juce_Memory.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/memory/juce_MemoryBlock.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/memory/juce_MemoryBlock.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/memory/juce_OptionalScopedPointer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/memory/juce_ReferenceCountedObject.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/memory/juce_ScopedPointer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/memory/juce_SharedResourcePointer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/memory/juce_Singleton.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/memory/juce_WeakReference.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/misc/juce_ConsoleApplication.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/misc/juce_ConsoleApplication.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/misc/juce_Result.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/misc/juce_Result.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/misc/juce_RuntimePermissions.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/misc/juce_RuntimePermissions.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/misc/juce_Uuid.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/misc/juce_Uuid.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/misc/juce_WindowsRegistry.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/native/java/README.txt" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/native/juce_android_Files.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/native/juce_android_JNIHelpers.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/native/juce_android_JNIHelpers.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/native/juce_android_Misc.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/native/juce_android_Network.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/native/juce_android_RuntimePermissions.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/native/juce_android_SystemStats.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/native/juce_android_Threads.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/native/juce_BasicNativeHeaders.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/native/juce_curl_Network.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/native/juce_linux_CommonFile.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/native/juce_linux_Files.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/native/juce_linux_Network.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/native/juce_linux_SystemStats.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/native/juce_linux_Threads.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/native/juce_mac_ClangBugWorkaround.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/native/juce_mac_Files.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/native/juce_mac_Network.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/native/juce_mac_Strings.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/native/juce_mac_SystemStats.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/native/juce_mac_Threads.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/native/juce_osx_ObjCHelpers.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/native/juce_posix_IPAddress.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/native/juce_posix_NamedPipe.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/native/juce_posix_SharedCode.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/native/juce_win32_ComSmartPtr.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/native/juce_win32_Files.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/native/juce_win32_Network.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/native/juce_win32_Registry.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/native/juce_win32_SystemStats.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/native/juce_win32_Threads.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/network/juce_IPAddress.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/network/juce_IPAddress.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/network/juce_MACAddress.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/network/juce_MACAddress.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/network/juce_NamedPipe.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/network/juce_NamedPipe.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/network/juce_Socket.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/network/juce_Socket.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/network/juce_URL.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/network/juce_URL.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/network/juce_WebInputStream.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/network/juce_WebInputStream.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/streams/juce_BufferedInputStream.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/streams/juce_BufferedInputStream.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/streams/juce_FileInputSource.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/streams/juce_FileInputSource.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/streams/juce_InputSource.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/streams/juce_InputStream.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/streams/juce_InputStream.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/streams/juce_MemoryInputStream.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/streams/juce_MemoryInputStream.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/streams/juce_MemoryOutputStream.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/streams/juce_MemoryOutputStream.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/streams/juce_OutputStream.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/streams/juce_OutputStream.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/streams/juce_SubregionStream.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/streams/juce_SubregionStream.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/streams/juce_URLInputSource.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/streams/juce_URLInputSource.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/system/juce_CompilerSupport.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/system/juce_PlatformDefs.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/system/juce_StandardHeader.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/system/juce_SystemStats.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/system/juce_SystemStats.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/system/juce_TargetPlatform.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/text/juce_Base64.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/text/juce_Base64.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/text/juce_CharacterFunctions.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/text/juce_CharacterFunctions.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/text/juce_CharPointer_ASCII.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/text/juce_CharPointer_UTF8.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/text/juce_CharPointer_UTF16.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/text/juce_CharPointer_UTF32.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/text/juce_Identifier.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/text/juce_Identifier.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/text/juce_LocalisedStrings.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/text/juce_LocalisedStrings.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/text/juce_NewLine.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/text/juce_String.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/text/juce_String.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/text/juce_StringArray.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/text/juce_StringArray.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/text/juce_StringPairArray.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/text/juce_StringPairArray.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/text/juce_StringPool.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/text/juce_StringPool.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/text/juce_StringRef.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/text/juce_TextDiff.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/text/juce_TextDiff.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/threads/juce_ChildProcess.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/threads/juce_ChildProcess.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/threads/juce_CriticalSection.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/threads/juce_DynamicLibrary.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/threads/juce_HighResolutionTimer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/threads/juce_HighResolutionTimer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/threads/juce_InterProcessLock.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/threads/juce_Process.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/threads/juce_ReadWriteLock.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/threads/juce_ReadWriteLock.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/threads/juce_ScopedLock.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/threads/juce_ScopedReadLock.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/threads/juce_ScopedWriteLock.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/threads/juce_SpinLock.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/threads/juce_Thread.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/threads/juce_Thread.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/threads/juce_ThreadLocalValue.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/threads/juce_ThreadPool.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/threads/juce_ThreadPool.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/threads/juce_TimeSliceThread.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/threads/juce_TimeSliceThread.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/threads/juce_WaitableEvent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/threads/juce_WaitableEvent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/time/juce_PerformanceCounter.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/time/juce_PerformanceCounter.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/time/juce_RelativeTime.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/time/juce_RelativeTime.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/time/juce_Time.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/time/juce_Time.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/unit_tests/juce_UnitTest.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/unit_tests/juce_UnitTest.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/unit_tests/juce_UnitTestCategories.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/xml/juce_XmlDocument.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/xml/juce_XmlDocument.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/xml/juce_XmlElement.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/xml/juce_XmlElement.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/zip/juce_GZIPCompressorOutputStream.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/zip/juce_GZIPCompressorOutputStream.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/zip/juce_GZIPDecompressorInputStream.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/zip/juce_GZIPDecompressorInputStream.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/zip/juce_ZipFile.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/zip/juce_ZipFile.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/juce_core.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/juce_core.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_core/juce_core.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_data_structures/app_properties/juce_ApplicationProperties.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_data_structures/app_properties/juce_ApplicationProperties.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_data_structures/app_properties/juce_PropertiesFile.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_data_structures/app_properties/juce_PropertiesFile.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_data_structures/undomanager/juce_UndoableAction.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_data_structures/undomanager/juce_UndoManager.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_data_structures/undomanager/juce_UndoManager.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_data_structures/values/juce_CachedValue.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_data_structures/values/juce_CachedValue.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_data_structures/values/juce_Value.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_data_structures/values/juce_Value.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_data_structures/values/juce_ValueTree.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_data_structures/values/juce_ValueTree.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_data_structures/values/juce_ValueTreeSynchroniser.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_data_structures/values/juce_ValueTreeSynchroniser.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_data_structures/values/juce_ValueWithDefault.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_data_structures/values/juce_ValueWithDefault.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_data_structures/juce_data_structures.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_data_structures/juce_data_structures.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_data_structures/juce_data_structures.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/broadcasters/juce_ActionBroadcaster.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/broadcasters/juce_ActionBroadcaster.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/broadcasters/juce_ActionListener.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/broadcasters/juce_AsyncUpdater.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/broadcasters/juce_AsyncUpdater.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/broadcasters/juce_ChangeBroadcaster.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/broadcasters/juce_ChangeBroadcaster.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/broadcasters/juce_ChangeListener.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/interprocess/juce_ConnectedChildProcess.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/interprocess/juce_ConnectedChildProcess.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/interprocess/juce_InterprocessConnection.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/interprocess/juce_InterprocessConnection.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/interprocess/juce_InterprocessConnectionServer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/interprocess/juce_InterprocessConnectionServer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/interprocess/juce_NetworkServiceDiscovery.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/interprocess/juce_NetworkServiceDiscovery.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/messages/juce_ApplicationBase.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/messages/juce_ApplicationBase.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/messages/juce_CallbackMessage.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/messages/juce_DeletedAtShutdown.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/messages/juce_DeletedAtShutdown.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/messages/juce_Initialisation.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/messages/juce_Message.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/messages/juce_MessageListener.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/messages/juce_MessageListener.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/messages/juce_MessageManager.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/messages/juce_MessageManager.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/messages/juce_MountedVolumeListChangeDetector.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/messages/juce_NotificationType.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/native/juce_android_Messaging.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/native/juce_ios_MessageManager.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/native/juce_linux_EventLoop.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/native/juce_linux_Messaging.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/native/juce_mac_MessageManager.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/native/juce_osx_MessageQueue.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/native/juce_win32_HiddenMessageWindow.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/native/juce_win32_Messaging.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/native/juce_win32_WinRTWrapper.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/native/juce_win32_WinRTWrapper.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/timers/juce_MultiTimer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/timers/juce_MultiTimer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/timers/juce_Timer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/timers/juce_Timer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/juce_events.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/juce_events.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_events/juce_events.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/colour/juce_Colour.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/colour/juce_Colour.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/colour/juce_ColourGradient.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/colour/juce_ColourGradient.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/colour/juce_Colours.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/colour/juce_Colours.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/colour/juce_FillType.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/colour/juce_FillType.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/colour/juce_PixelFormats.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/contexts/juce_GraphicsContext.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/contexts/juce_GraphicsContext.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/contexts/juce_LowLevelGraphicsContext.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/contexts/juce_LowLevelGraphicsPostScriptRenderer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/contexts/juce_LowLevelGraphicsPostScriptRenderer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/contexts/juce_LowLevelGraphicsSoftwareRenderer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/contexts/juce_LowLevelGraphicsSoftwareRenderer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/effects/juce_DropShadowEffect.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/effects/juce_DropShadowEffect.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/effects/juce_GlowEffect.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/effects/juce_GlowEffect.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/effects/juce_ImageEffectFilter.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/fonts/juce_AttributedString.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/fonts/juce_AttributedString.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/fonts/juce_CustomTypeface.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/fonts/juce_CustomTypeface.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/fonts/juce_Font.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/fonts/juce_Font.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/fonts/juce_GlyphArrangement.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/fonts/juce_GlyphArrangement.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/fonts/juce_TextLayout.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/fonts/juce_TextLayout.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/fonts/juce_Typeface.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/fonts/juce_Typeface.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/geometry/juce_AffineTransform.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/geometry/juce_AffineTransform.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/geometry/juce_BorderSize.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/geometry/juce_EdgeTable.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/geometry/juce_EdgeTable.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/geometry/juce_Line.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/geometry/juce_Parallelogram.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/geometry/juce_Path.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/geometry/juce_Path.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/geometry/juce_PathIterator.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/geometry/juce_PathIterator.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/geometry/juce_PathStrokeType.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/geometry/juce_PathStrokeType.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/geometry/juce_Point.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/geometry/juce_Rectangle.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/geometry/juce_RectangleList.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/image_formats/juce_GIFLoader.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/image_formats/juce_JPEGLoader.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/image_formats/juce_PNGLoader.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/images/juce_Image.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/images/juce_Image.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/images/juce_ImageCache.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/images/juce_ImageCache.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/images/juce_ImageConvolutionKernel.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/images/juce_ImageConvolutionKernel.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/images/juce_ImageFileFormat.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/images/juce_ImageFileFormat.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/native/juce_android_Fonts.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/native/juce_android_GraphicsContext.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/native/juce_android_IconHelpers.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/native/juce_freetype_Fonts.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/native/juce_linux_Fonts.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/native/juce_linux_IconHelpers.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/native/juce_mac_CoreGraphicsContext.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/native/juce_mac_CoreGraphicsContext.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/native/juce_mac_CoreGraphicsHelpers.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/native/juce_mac_Fonts.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/native/juce_mac_IconHelpers.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/native/juce_RenderingHelpers.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/native/juce_win32_Direct2DGraphicsContext.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/native/juce_win32_Direct2DGraphicsContext.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/native/juce_win32_DirectWriteTypeface.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/native/juce_win32_DirectWriteTypeLayout.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/native/juce_win32_Fonts.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/native/juce_win32_IconHelpers.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/placement/juce_Justification.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/placement/juce_RectanglePlacement.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/placement/juce_RectanglePlacement.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/juce_graphics.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/juce_graphics.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_graphics/juce_graphics.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/application/juce_Application.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/application/juce_Application.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/buttons/juce_ArrowButton.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/buttons/juce_ArrowButton.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/buttons/juce_Button.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/buttons/juce_Button.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/buttons/juce_DrawableButton.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/buttons/juce_DrawableButton.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/buttons/juce_HyperlinkButton.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/buttons/juce_HyperlinkButton.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/buttons/juce_ImageButton.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/buttons/juce_ImageButton.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/buttons/juce_ShapeButton.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/buttons/juce_ShapeButton.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/buttons/juce_TextButton.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/buttons/juce_TextButton.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/buttons/juce_ToggleButton.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/buttons/juce_ToggleButton.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/buttons/juce_ToolbarButton.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/buttons/juce_ToolbarButton.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/commands/juce_ApplicationCommandID.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/commands/juce_ApplicationCommandInfo.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/commands/juce_ApplicationCommandInfo.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/commands/juce_ApplicationCommandManager.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/commands/juce_ApplicationCommandManager.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/commands/juce_ApplicationCommandTarget.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/commands/juce_ApplicationCommandTarget.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/commands/juce_KeyPressMappingSet.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/commands/juce_KeyPressMappingSet.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/components/juce_CachedComponentImage.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/components/juce_Component.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/components/juce_Component.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/components/juce_ComponentListener.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/components/juce_ComponentListener.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/components/juce_ModalComponentManager.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/components/juce_ModalComponentManager.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/desktop/juce_Desktop.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/desktop/juce_Desktop.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/desktop/juce_Displays.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/desktop/juce_Displays.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/drawables/juce_Drawable.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/drawables/juce_Drawable.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/drawables/juce_DrawableComposite.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/drawables/juce_DrawableComposite.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/drawables/juce_DrawableImage.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/drawables/juce_DrawableImage.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/drawables/juce_DrawablePath.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/drawables/juce_DrawablePath.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/drawables/juce_DrawableRectangle.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/drawables/juce_DrawableRectangle.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/drawables/juce_DrawableShape.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/drawables/juce_DrawableShape.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/drawables/juce_DrawableText.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/drawables/juce_DrawableText.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/drawables/juce_SVGParser.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_ContentSharer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_ContentSharer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_DirectoryContentsDisplayComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_DirectoryContentsDisplayComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_DirectoryContentsList.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_DirectoryContentsList.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_FileBrowserComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_FileBrowserComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_FileBrowserListener.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_FileChooser.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_FileChooser.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_FileChooserDialogBox.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_FileChooserDialogBox.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_FileListComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_FileListComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_FilenameComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_FilenameComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_FilePreviewComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_FileSearchPathListComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_FileSearchPathListComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_FileTreeComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_FileTreeComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_ImagePreviewComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/filebrowser/juce_ImagePreviewComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/keyboard/juce_CaretComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/keyboard/juce_CaretComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/keyboard/juce_KeyboardFocusTraverser.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/keyboard/juce_KeyboardFocusTraverser.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/keyboard/juce_KeyListener.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/keyboard/juce_KeyListener.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/keyboard/juce_KeyPress.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/keyboard/juce_KeyPress.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/keyboard/juce_ModifierKeys.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/keyboard/juce_ModifierKeys.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/keyboard/juce_SystemClipboard.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/keyboard/juce_TextEditorKeyMapper.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/keyboard/juce_TextInputTarget.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_AnimatedPosition.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_AnimatedPositionBehaviours.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_ComponentAnimator.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_ComponentAnimator.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_ComponentBoundsConstrainer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_ComponentBoundsConstrainer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_ComponentBuilder.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_ComponentBuilder.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_ComponentMovementWatcher.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_ComponentMovementWatcher.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_ConcertinaPanel.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_ConcertinaPanel.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_FlexBox.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_FlexBox.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_FlexItem.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_Grid.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_Grid.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_GridItem.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_GridItem.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_GroupComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_GroupComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_MultiDocumentPanel.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_MultiDocumentPanel.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_ResizableBorderComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_ResizableBorderComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_ResizableCornerComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_ResizableCornerComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_ResizableEdgeComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_ResizableEdgeComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_ScrollBar.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_ScrollBar.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_SidePanel.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_SidePanel.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_StretchableLayoutManager.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_StretchableLayoutManager.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_StretchableLayoutResizerBar.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_StretchableLayoutResizerBar.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_StretchableObjectResizer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_StretchableObjectResizer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_TabbedButtonBar.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_TabbedButtonBar.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_TabbedComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_TabbedComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_Viewport.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/layout/juce_Viewport.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V1.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V1.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V2.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V2.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V3.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V3.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V4.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/lookandfeel/juce_LookAndFeel_V4.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/menus/juce_BurgerMenuComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/menus/juce_BurgerMenuComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/menus/juce_MenuBarComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/menus/juce_MenuBarComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/menus/juce_MenuBarModel.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/menus/juce_MenuBarModel.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/menus/juce_PopupMenu.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/menus/juce_PopupMenu.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/misc/juce_BubbleComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/misc/juce_BubbleComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/misc/juce_DropShadower.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/misc/juce_DropShadower.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/misc/juce_JUCESplashScreen.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/misc/juce_JUCESplashScreen.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_ComponentDragger.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_ComponentDragger.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_DragAndDropContainer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_DragAndDropContainer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_DragAndDropTarget.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_FileDragAndDropTarget.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_LassoComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_MouseCursor.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_MouseCursor.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_MouseEvent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_MouseEvent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_MouseInactivityDetector.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_MouseInactivityDetector.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_MouseInputSource.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_MouseInputSource.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_MouseListener.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_MouseListener.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_SelectedItemSet.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_TextDragAndDropTarget.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/mouse/juce_TooltipClient.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_android_ContentSharer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_android_FileChooser.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_android_Windowing.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_common_MimeTypes.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_ios_ContentSharer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_ios_FileChooser.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_ios_UIViewComponentPeer.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_ios_Windowing.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_linux_FileChooser.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_linux_X11.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_linux_X11.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_linux_X11_Clipboard.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_linux_X11_Windowing.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_mac_FileChooser.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_mac_MainMenu.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_mac_MouseCursor.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_mac_NSViewComponentPeer.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_mac_Windowing.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_MultiTouchMapper.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_win32_DragAndDrop.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_win32_FileChooser.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/native/juce_win32_Windowing.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/positioning/juce_MarkerList.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/positioning/juce_MarkerList.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/positioning/juce_RelativeCoordinate.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/positioning/juce_RelativeCoordinate.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/positioning/juce_RelativeCoordinatePositioner.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/positioning/juce_RelativeCoordinatePositioner.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/positioning/juce_RelativeParallelogram.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/positioning/juce_RelativeParallelogram.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/positioning/juce_RelativePoint.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/positioning/juce_RelativePoint.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/positioning/juce_RelativePointPath.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/positioning/juce_RelativePointPath.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/positioning/juce_RelativeRectangle.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/positioning/juce_RelativeRectangle.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/properties/juce_BooleanPropertyComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/properties/juce_BooleanPropertyComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/properties/juce_ButtonPropertyComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/properties/juce_ButtonPropertyComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/properties/juce_ChoicePropertyComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/properties/juce_ChoicePropertyComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/properties/juce_MultiChoicePropertyComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/properties/juce_MultiChoicePropertyComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/properties/juce_PropertyComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/properties/juce_PropertyComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/properties/juce_PropertyPanel.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/properties/juce_PropertyPanel.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/properties/juce_SliderPropertyComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/properties/juce_SliderPropertyComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/properties/juce_TextPropertyComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/properties/juce_TextPropertyComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_ComboBox.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_ComboBox.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_ImageComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_ImageComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_Label.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_Label.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_ListBox.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_ListBox.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_ProgressBar.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_ProgressBar.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_Slider.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_Slider.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_TableHeaderComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_TableHeaderComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_TableListBox.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_TableListBox.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_TextEditor.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_TextEditor.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_Toolbar.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_Toolbar.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_ToolbarItemComponent.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_ToolbarItemComponent.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_ToolbarItemFactory.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_ToolbarItemPalette.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_ToolbarItemPalette.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_TreeView.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/widgets/juce_TreeView.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_AlertWindow.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_AlertWindow.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_CallOutBox.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_CallOutBox.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_ComponentPeer.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_ComponentPeer.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_DialogWindow.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_DialogWindow.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_DocumentWindow.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_DocumentWindow.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_NativeMessageBox.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_ResizableWindow.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_ResizableWindow.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_ThreadWithProgressWindow.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_ThreadWithProgressWindow.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_TooltipWindow.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_TooltipWindow.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_TopLevelWindow.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/windows/juce_TopLevelWindow.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/juce_gui_basics.cpp" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/juce_gui_basics.mm" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/modules/juce_gui_basics/juce_gui_basics.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/AppConfig.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/BinaryData.h" PROPERTIES HEADER_FILE_ONLY TRUE)
set_source_files_properties("../../../JuceLibraryCode/JuceHeader.h" PROPERTIES HEADER_FILE_ONLY TRUE)

find_library(log "log")
find_library(android "android")
find_library(glesv2 "GLESv2")
find_library(egl "EGL")

target_link_libraries( ${BINARY_NAME}

    ${log}
    ${android}
    ${glesv2}
    ${egl}
    "cpufeatures"
)

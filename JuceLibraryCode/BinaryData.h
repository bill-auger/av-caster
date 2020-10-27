/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   avcasterlogo48_png;
    const int            avcasterlogo48_pngSize = 9439;

    extern const char*   avcasterlogo128_png;
    const int            avcasterlogo128_pngSize = 65933;

    extern const char*   confighover_png;
    const int            confighover_pngSize = 4254;

    extern const char*   configpushed_png;
    const int            configpushed_pngSize = 4254;

    extern const char*   config_png;
    const int            config_pngSize = 2129;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 5;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}

/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#ifndef BINARYDATA_H_6614346_INCLUDED
#define BINARYDATA_H_6614346_INCLUDED

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

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 5;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}

#endif

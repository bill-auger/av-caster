
The script files in the AvCaster Builds/Scripts/ directory are licensed under [version 3 of the GNU General Public License](COPYING_SCRIPTS).

---

the build helper scripts contained in this directory are intentionally non-executable and are intended to be run from the project root directory (the directory containing the Builds and Source directories)

firstly, run the setup-build-helpers script in this directory to copy these scripts to the project root - they will set to be executable from there

from this directory:
```
./setup-build-helpers
cd ../../
```
or from the project root directory:
```
Builds/Scripts/setup-build-helpers
```

then in the project root directory you will find the following helpers:

* ./cppcheck-filtered - run lint checks
* ./dbg               - runs make on the Debug build and then executes the binary under gdb
* ./mk CONFIG=Debug   - runs make on the Debug build and then executes the binary
* ./mk                - runs make on the Release build and then executes the binary
* ./mk-clean          - runs make clean on the Release build and then calls ./mk
* ./mk-reset          - deletes the av-caster persistence file and then calls ./mk

the Release build prints comprehensive traces to the console so this is the default build target

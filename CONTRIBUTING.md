### Disclaimer

AvCaster source code and assets are distributed under the terms of the GNU Lesser General Public License version 3.
As a contributor, you agree that all unlicensed contributions to the source tree, wiki, and issue tracker will automatically fall under the same licence as AvCaster.
In short, this means that you allow others to copy, distribute, and modify their copies or your work as long as they extend this priviledge to others and credit you as the original author if they distribute.
If you are not the original sole author of your contribution (i.e. it is a derivative work incorporating or based on someone else's work) , then all source works must be freely copyable and distributable under the terms of some GPL-compatible license (such as Creative Commonns) and you must clearly give attribution to the copyright holders with a hyperlinks to the original sources.
Any such contributions that are under the terms of a GPL-compatible license will retain their current license.
No other contributions will be accepted.


### Developers
You will find in the Builds/Scripts directory some helper scripts to aid in building and debugging this application. Simply run ```./Builds/Scripts/setup-build-helpers``` to install them. Note that we are currently locked at JUCE v3.1.1 until [an issue affecting scaled monitor resolutions](http://www.juce.com/forum/topic/juce-v320-and-v401-apps-window-not-visible-scaled-monitor-resolutions) is resolved. This is not relevant to most development tasks, but if you must use the Introjucer GUI builder for design or project maintenance, please compile it from [this branch](https://github.com/bill-auger/JUCE/tree/v3-1-1) and note that he av-caster and JUCE-3-1-1 directories should be siblings in order for the AvCaster.jucer project to locate the JUCE sources.


### Designers
```bash
### If you want to work with the AvCaster sources directly -
        first install the build dependencies above for your system
            as noted in the README.md
        then fork the AvCaster repo, clone the design branch,
            and compile as noted in the README.md
        then clone and compile the Introjucer GUI builder and project manager ###

### Clone the design branch locally ###
$ git clone -b design https://github.com/YOUR_GITHUB_NICK/av-caster
### then compile AvCaster as noted in the README.md ###

### Compile the Introjucer GUI builder and project manager ###
$ git clone -b v3-1-1 --depth 1 https://github.com/bill-auger/JUCE.git JUCE-3-1-1
### or ###
$ wget https://github.com/bill-auger/JUCE/archive/v3-1-1.tar.gz
$ tar xzf ./v3-1-1.tar.gz
### then ###
$ cd ./JUCE-3-1-1/extras/Introjucer/Builds/Linux/
$ make
$ ./build/Introjucer
### then select "Open" from the Introjucer "File" menu and browse to the AvCaster.jucer file in this project root directory. ###
```


### Pull requests
* Developers: please issue pull requests against the development branch.
* Designers: please issue pull requests against the design branch.

Note that branches other than 'master' tend to be rebased often so you may need to force pull those.  Please rebase all pull requests on/into the latest development HEAD.  Ideally, all branches should be a fast-foreward from master so re-sync should be simple. If you repo becomes out of sync with upstream, please re-sync or rebase before issuing a pull request. Also, please squash trivial commits but try to retain significant notable commits (see example below).


### commit messages

Please add commit messages of the following form:
```
short general description of feature in declarative tense (optional issue #)
<EMPTY LINE>
  * specific notable change
  * specific notable change
  * specific notable change
  * specific notable change

e.g.

add bar powers to the mighty foo (issue #42)

  * added Bar class
  * added height, width instance vars to Bar class
  * added Bar instance var to Foo class
  * added setBar(), getBar() accessors to Foo class
```


### Issue Tracker
Please do not hesitate to use the issue tracker for constructive notes related to that specific issue and significant progress updates that are not yet in a pull request; but use the gitter chat or other channels for new issues and lengthy discussions.

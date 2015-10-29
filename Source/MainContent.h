/*\
|*|  Copyright 2015 bill-auger <https://github.com/bill-auger/av-caster/issues>
|*|
|*|  This file is part of the AvCaster program.
|*|
|*|  AvCaster is free software: you can redistribute it and/or modify
|*|  it under the terms of the GNU Lesser General Public License version 3
|*|  as published by the Free Software Foundation.
|*|
|*|  AvCaster is distributed in the hope that it will be useful,
|*|  but WITHOUT ANY WARRANTY; without even the implied warranty of
|*|  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|*|  GNU Lesser General Public License for more details.
|*|
|*|  You should have received a copy of the GNU Lesser General Public License
|*|  along with AvCaster.  If not, see <http://www.gnu.org/licenses/>.
\*/


#ifndef MAINCONTENT_H_INCLUDED
#define MAINCONTENT_H_INCLUDED

#include "Background.h"
#include "Config.h"
#include "Controls.h"
#include "Statusbar.h"


/** MainContent is the main GUI container class for the AvCaster application. */
class MainContent : public Component
{
  friend class AvCaster ;


public:

  MainContent(DocumentWindow* main_window) ;
  ~MainContent();

  void paint(Graphics&) ;
  void resized() ;


private:

  DocumentWindow*           mainWindow ;
  ScopedPointer<Background> background ;
  ScopedPointer<Controls  > controls ;
  ScopedPointer<Config    > config ;
  ScopedPointer<Statusbar > statusbar ;

  void instantiate (ValueTree config_root  , ValueTree config_store ,
                    ValueTree camera_store , ValueTree audio_store  ) ;
  void setTitle    (String title_text) ;
  void warning     (String message_text) ;
  void error       (String message_text) ;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainContent)
} ;

#endif  // MAINCONTENT_H_INCLUDED

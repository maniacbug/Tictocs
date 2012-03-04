/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

// STL headers
// C headers
// Framework headers
// Library headers
#include <Tictocs.h>
#include <TictocTimer.h>
// Project headers

Tictocs::Timer timer(500);

//
// Application
//

void setup(void)
{
  // Preamble
  Serial.begin(57600);
  Serial.println(F(__FILE__));
}

void loop(void)
{
  timer.update();

  if ( timer.wasFired() )
    Serial.println(millis());
}

// vim:cin:ai:sts=2 sw=2 ft=cpp

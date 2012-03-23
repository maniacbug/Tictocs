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
#include <Button.h>
// Project headers

Button button(4);

//
// Application
//

void setup(void)
{
  // Preamble
  Serial.begin(57600);
  Serial.println(F(__FILE__));

  // Initialize objects
  button.begin();
}

void loop(void)
{
  button.update();

  if ( button.wasPressed() )
  {
    Serial.println(F("Button pressed"));
  }
}

// vim:cin:ai:sts=2 sw=2 ft=cpp

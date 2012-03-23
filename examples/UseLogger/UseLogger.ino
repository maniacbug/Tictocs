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
#include <PinControl.h>
#include <Connector.h>
#include <SimpleLogger.h>
// Project headers
#include "printf.h"

class ToggleTimer: public Connectable, public Tictocs::Timer
{
  uint8_t signal_off;
  uint8_t signal_on;
  bool state;
protected:
  virtual void onFired(void) 
  {
    state = !state;
    emit(state?signal_on:signal_off);
  }
public:
  ToggleTimer(Connector& conn,unsigned long interval,uint8_t _signal_off,uint8_t _signal_on): Connectable(conn), Timer(interval), signal_off(_signal_off), signal_on(_signal_on) 
  {
  }
};

const uint8_t signal_low = 1;
const uint8_t signal_high = 2;

Connector conn;
Updater up;

// Every 500ms the timer will alternately emit these signals 
ToggleTimer timer(conn,500,signal_low,signal_high);

// This controls the LED
PinControl led(conn,13,signal_low,signal_high);

// Monitor connection activity using the simple logger
SimpleLogger logger(/*objects*/ 5, /*signals*/ 5);

//
// Application
//

void setup(void)
{
  // Preamble
  Serial.begin(57600);
  Serial.println(F(__FILE__));
  
  // Logger uses printf, so prepare stdout for use
  printf_begin();

  led.begin(&timer);
  timer.begin(up);

  // Add logger symbols
  logger.setSymbol(signal_low,PSTR("signal_low"));
  logger.setSymbol(signal_high,PSTR("signal_high"));
  logger.setSymbol(&timer,PSTR("timer"));
  logger.setSymbol(&led,PSTR("led"));

  // Add logger to connector
  conn.setLogger(&logger);
}

void loop(void)
{
  up.update();
}

// vim:cin:ai:sts=2 sw=2 ft=cpp

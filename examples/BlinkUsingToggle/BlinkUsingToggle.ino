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
// Project headers

class SignalToggle: public Connectable
{
  uint8_t signal_listen;
  uint8_t signal_off;
  uint8_t signal_on;
  bool state;
protected:
  virtual void onNotify(const Connectable* ,uint8_t signal )
  {
    if (signal == signal_listen)
    {
      state = !state;
      emit(state?signal_on:signal_off);
    }
  }
public:
  SignalToggle(Connector& conn,uint8_t _signal_listen,uint8_t _signal_off,uint8_t _signal_on): Connectable(conn), signal_listen(_signal_listen), signal_off(_signal_off), signal_on(_signal_on) 
  {
  }
  void begin(Connectable* _whom)
  {
    listen(_whom,signal_listen);
  }
};

const uint8_t signal_timer = 1;
const uint8_t signal_low = 2;
const uint8_t signal_high = 3;

Connector conn;
Updater up;

// Every 500ms the timer will emit signal_timer 
Tictocs::EmitTimer timer(conn,500,signal_timer);

// The signal toggler will translate signal_timer into signal_low and signal_high
// alternately
SignalToggle toggle(conn,signal_timer,signal_low,signal_high);

// This controls the LED
PinControl led(conn,13,signal_low,signal_high);

//
// Application
//

void setup(void)
{
  // Preamble
  Serial.begin(57600);
  Serial.println(F(__FILE__));

  led.begin(&toggle);
  toggle.begin(&timer);
  timer.begin(up);
}

void loop(void)
{
  up.update();
}

// vim:cin:ai:sts=2 sw=2 ft=cpp

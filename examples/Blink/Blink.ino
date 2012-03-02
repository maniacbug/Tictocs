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

class EmitTimer: public Connectable, public Tictocs::Timer
{
  uint8_t signal_on_fired;
  bool auto_reset;
protected:
  virtual void onFired(void) { emit(signal_on_fired); if (auto_reset) reset(); }
public:
  EmitTimer(Connector& conn,unsigned long interval,uint8_t signal,bool _auto_reset=true): Connectable(conn), Timer(interval), signal_on_fired(signal), auto_reset(_auto_reset)
  {
  }
};

class PinToggle: public PinControl
{
  uint8_t signal_toggle;
protected:
  virtual void onNotify(const Connectable*, uint8_t signal)
  {
    if ( signal == signal_toggle )
      toggle();
  }
public:
  PinToggle(Connector& conn,uint8_t pin,uint8_t signal): PinControl(conn,pin,0,0), signal_toggle(signal)
  {
  }
  void begin(Connectable* whom)
  {
    PinControl::begin();
    Connectable::listen(whom,signal_toggle);
  }
};

const uint8_t signal_toggle = 1;

Connector conn;
Updater up;

// Every 500ms the timer will emit 'signal_toggle'
EmitTimer timer(conn,500,signal_toggle);

// Toggle pin 13 when hearing 'signal_toggle'
PinToggle led(conn,13,signal_toggle);

//
// Application
//

void setup(void)
{
  // Preamble
  Serial.begin(57600);
  Serial.println(F(__FILE__));

  led.begin(&timer);
  timer.begin(up);
}

void loop(void)
{
  up.update();
}

// vim:cin:ai:sts=2 sw=2 ft=cpp

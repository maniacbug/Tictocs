/*
 Copyright (C) 2012 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#ifndef __TICTOCS_TIMER_H__
#define __TICTOCS_TIMER_H__

// STL includes
// C includes
// Framework includes
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
// Library includes
// Project includes
#include <Updater.h>
#include <Connector.h>

namespace Tictocs
{

/**
 * Manage events which occur on a specified time interval
 */

class Timer: public Updatable
{
private:
  unsigned long interval; /**< How long to wait before firing */
  unsigned long last_updated; /**< When was the timer last updated */
  bool fired; /**< Has the timer fired since the user last checked? */
  bool enabled; /**< Is the timer enabled so it can run? */
protected:
  /**
   * Triggered when timer is fired.  Override to implement special behaviour
   */
   virtual void onFired(void) {}
public:
  /**
   * Constructor
   *
   * @param _interval How long to wait before firing
   */
  Timer(unsigned long _interval): interval(_interval), last_updated(millis()), fired(false), enabled(true) {}

  /**
   * Add to updater
   */
  void begin(Updater& up)
  {
    up.add(this);
  }
  using Updatable::begin;

  /**
   * Call regularly to update status of timer
   */
  void update(void) 
  {
    unsigned long now = millis();
    if ( enabled && now - last_updated >= interval )
    {
      last_updated += interval;
      fired = true;
      onFired();
    }
  }

  /**
   * Test whether the timer has fired since we last asked
   *
   * @retval true Timer fired since this method was last called
   */
  bool wasFired(void) { bool result = fired; fired = false; return result; }

  /**
   * Reset timer back to the start
   */
  void reset(void) { last_updated = millis(); enabled = true; }

  /**
   * Set new interval value (and reset)
   *
   * @param _interval New duration for the timer in ms
   */
  void setInterval(unsigned long _interval) { interval = _interval; reset(); }

  /**
   * Disables timer so it will never fire.  Call reset() to enable.
   */
  void disable(void) { enabled = false; }

  /**
   * Test whether the timer is enabled 
   */
  operator bool(void) const { return enabled; }
};

/**
 * Emit a signal on a regular interval
 */
class EmitTimer: public Connectable, public Timer
{
  uint8_t signal; /**< The signal to emit */
protected:
  /**
   * Triggered when timer is fired.
   */
  virtual void onFired(void) 
  {
    emit(signal);
  }
public:
  /**
   * Constructor
   *
   * @param conn Connector which we can attach to for communication
   * @param _interval How long to wait before firing
   * @param _signal Which signal to emit 
   */
  EmitTimer(Connector& conn,unsigned long _interval,uint8_t _signal): Connectable(conn), Timer(_interval), signal(_signal)
  {}
};

} // namespace Tictocs

#endif // __TIMER_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp

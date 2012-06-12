
/*
 Copyright (C) 2012 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#ifndef __RTCEVENT_H__
#define __RTCEVENT_H__

// STL includes
// C includes
// Library includes
// Project includes
#include <Connector.h>
#include <IUpdate.h>

namespace Tictocs
{

/**
 * Custom RTC interface.  This is used by the RTC Event to determine the
 * current time.  An interface is used to abstract away any particular
 * RTC implementation.
 */

class IRtc
{
public:
  /**
   * Whether the current time is after the given time
   *
   * @param _time to Compare against
   * @return Whether @p _time has passed
   */
  virtual bool is_after(uint32_t _time) const =0;
  
  /**
   * Set the current time
   *
   * @param _time New current time
   */
  virtual void adjust(uint32_t /*_time*/) {}
  
  /**
   * Get the current time
   *
   * @return The current time
   */
  virtual uint32_t now_unixtime(void) const { return 0; }
};

/**
 * Example for how classes should be declared
 */

class RtcEvent: public Connectable, public IUpdate
{
  uint32_t when; /**< When the signal should be emitted, in unix time */
  uint8_t signal_what; /**< What signal should be emitted */
  bool active; /**< Whether we are going to fire */
  static const IRtc* rtc; /**< The RTC where we get our time */
protected:
  /**
   * Checks whether it's time to fire
   */
  virtual void update(void);

  /**
   * Returns when the event will be fired
   *
   * @return When the event will be fired
   */
  uint32_t get_when(void) const { return when; }

  /**
   * Returns whether the event is actively watching the clock
   *
   * @return Whether the event is active
   */
  bool get_active(void) const { return active; }
public:
  /**
   * Fully-qualified constructor
   *
   * @param _conn Connector used to communicate with other objects
   * @param _when Time when to fire, in unix time
   * @param _signal_what What signal to fire when @p _when passes.
   */
  RtcEvent(Connector& _conn,uint32_t _when,uint8_t _signal_what);
  
  /**
   * Begin operation.  Call only once, after static init complete.
   */
  void begin(void);

  /**
   * Establish the RTC used to find the time
   *
   * @param rtc RTC used to find the time
   */
  static void setRtc(const IRtc* rtc);
};

} // namespace Tictocs

#endif // __RTCEVENT_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp

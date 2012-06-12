/*
 Copyright (C) 2012 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#ifndef __SEQUENCE_H__
#define __SEQUENCE_H__

// STL headers
// C headers
// Framework headers
// Library headers
// Project headers
#include <TictocTimer.h>

namespace Tictocs
{

/**
 * A sequence of signals which will be fired according to a timeline.
 *
 * It is a connectable timer that contains an array of delay/signal pairs.
 * The basic idea is to wait the delay for each, and then fire the signal.
 * Also, the sequence wakes up upon hearing its own wake-up signal.  It's
 * dormant until that.
 */

class Sequence: public Connectable, public Tictocs::Timer 
{
public:
  /**
   * A single step in the sequence.  Construct a sequence from an array
   * of these.
   */
  struct Entry
  {
    uint32_t delayms; /**< MS to wait before emitting */
    uint8_t signal; /**< Signal to emit */
  };
private:
  const Entry* entries; /**< Current list of static entries, in flash */
  const Entry* current; /**< Current entry we're waiting for */
  uint8_t signal_launch; /**< Signal we listen for */
protected:
  /**
   * Event triggered when timer fires
   */
  virtual void onFired(void);
  
  /**
   * Event triggered when receiving a signal we're listening for
   *
   * @param who Object which emitted the signal
   * @param signal Signal which was emitted
   */
  virtual void onNotify(const Connectable* who, uint8_t signal);

  /**
   * Whether this sequence has a valid current entry
   *
   * @return Whether the sequence has a valid current entry 
   */
  bool isValid(void) const;

  /**
   * Reset the interval and restart the timer, using the interval for the
   * current entry.
   */
  void resetInterval(void);
public:
  /**
   * Fully-qualified constructor
   *
   * @param conn Connector used to emit our signals
   * @param entries Array of entries, in flash memory.  Terminated with a {0,0}.
   * @param _signal_launch Signal which will start the sequence 
   */
  Sequence(Connector& conn,const Entry*,uint8_t _signal_launch); 

  /**
   * Begin operation
   *
   * Call this before the sequence will fully function
   *
   * @param updater Updater which will give this a time slice
   * @param whom Object to listen to, or NULL for listen to all
   */
  void begin(Updater& updater,Connectable* whom = NULL);

};

} // namespace Tictocs

#endif // __SEQUENCE_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp

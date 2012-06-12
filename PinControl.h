/*
 Copyright (C) 2012 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */


#ifndef __PINCONTROL_H__
#define __PINCONTROL_H__

// STL includes
// C includes
// Library includes
#include <Connector.h>
// Project includes

namespace Tictocs
{

/**
 * Control a single GPIO pin based purely on signals
 */

class PinControl: public Connectable
{
private:
  uint8_t pin; /**< The pin being controlled */
  uint8_t signal_low; /**< The signal which sets the pin LOW */
  uint8_t signal_high; /**< The signal which sets the pin HIGH */
protected:
  virtual void onNotify(const Connectable*, uint8_t signal);

  /**
   * Get the pin being controlled
   *
   * @return The pin being controlled
   */
  uint8_t get_pin(void) const { return pin; }
  
  /**
   * Toggle the current value of the pin
   */
  void toggle(void);
public:
  PinControl(Connector& _conn,int _pin,uint8_t _signal_low, uint8_t _signal_high): Connectable(_conn), pin(_pin), signal_low(_signal_low), signal_high(_signal_high) {}
  
  /**
   * Begin operation.  Call only once, after static init complete.
   */
  void begin(void);
  
  /**
   * Begin operation, and listen to a particular object
   *
   * @param _whom To whom we should listen, or NULL for listen to all
   */
  void begin(Connectable* _whom) { begin(); listen(_whom); }
  
  /**
   * Listen to a particular object.  When this object raises the signals
   * we're listening for, we'll act.
   *
   * @param _whom To whom we should listen, or NULL for listen to all
   */
  void listen(Connectable* _whom);
};

} // namespace Tictocs

#endif // __PINCONTROL_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp

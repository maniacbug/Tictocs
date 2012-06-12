/*
 Copyright (C) 2012 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#ifndef __BUTTON_H__
#define __BUTTON_H__

// STL includes
// C includes
// Library includes
// Project includes
#include <Updater.h>

namespace Tictocs
{

class Updater;

/**
 * Manages a single push button.  Button is connected to ground when closed, floating when open
 */

class Button: public Updatable 
{
private:
  uint8_t pin; /**< Which hardware pin this button is connected to. **/
  uint16_t interval; /**< How long the button must be pressed/released before the state change is accepted */
  uint32_t timer; /**< What time the button pin last changed state */ 
  uint32_t time_pressed; /**< What time the button was last pressed */
  uint8_t state:1; /**< Current accepted state of the button, LOW = pressed */
  uint8_t edge_pressed:1; /**< Has the button been pressed since the user last asked? */
  uint8_t edge_released:1; /**< Has the button been released since the user last asked? */
protected:
  /**
   * Called when button is pressed
   */
  virtual void onPressed(void) {}
  /**
   * Called when buttong is released
   *
   * @param duration How long the button was down
   */
  virtual void onReleased(unsigned long) {} 
public:
  /**
   * Constructor
   *
   * @param _pin Which pin the button is monitoring
   */
  Button(int _pin, unsigned long _interval = 20);

  /**
   * Prepare the button.  Sets the pin as output and engages the pull-up resistor
   */
  void begin(void);
  void begin(Updater&);

  /**
   * Update the state of the button.  Call this regularly.
   */
  void update(void);

  /**
   * Test whether the button has been pressed since we last asked
   *
   * @retval Pressed since this method was last called
   */
  bool wasPressed(void);

  /**
   * Test whether the button has been released since we last asked
   *
   * @return How long (ms) the button was held down, or 0 if was not recently released 
   */
  unsigned wasReleased(void);

  /**
   * Get current known state of the button
   *
   * @retval true Button is currently being pressed
   */
  bool isPressed(void) const;
}
__attribute__ ((packed));

} // namespace Tictocs

#endif // __BUTTON_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp

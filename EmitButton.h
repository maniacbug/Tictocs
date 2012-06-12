
/*
 Copyright (C) 2012 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#ifndef __EMITBUTTON_H__
#define __EMITBUTTON_H__

// STL includes
// C includes
// Library includes
// Project includes
#include <Button.h>
#include <Connector.h>

namespace Tictocs
{

/**
 * Manages a single push button which emits signals on press and release
 */

class EmitButton: public Connectable, public Button
{
  uint8_t signal_pressed; /**< The signal emitted when the button is pressed */
  uint8_t signal_released; /**< The signal emitted when the button is released */

protected:
  /**
   * Called by the underlying Button when pressed
   */
  void onPressed(void);
  
  /**
   * Called by the underlying Button when released
   *
   * @param pressed_for How long the button was pressed for (ms)
   */
  void onReleased(unsigned long pressed_for);
public:
  /**
   * Constructor
   *
   * @param _conn Connector used to communicate with other objects
   * @param _pin Which pin the button is monitoring
   * @param _signal_pressed The signal emitted when the button is pressed
   * @param _signal_released The signal emitted when the button is released
   * @param _interval How long the button must be pressed before the press is registered
   */
  EmitButton(Connector& _conn,int _pin, uint8_t _signal_pressed, uint8_t signal_released = 0, unsigned long _interval = 20 );
};

} // namespace Tictocs

#endif // __EMITBUTTON_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp

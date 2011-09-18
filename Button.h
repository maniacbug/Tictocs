#ifndef __BUTTON_H__
#define __BUTTON_H__

// STL includes
// C includes
// Library includes
// Project includes
#include <IUpdate.h>

/**
 * Manages a single push button.  Button is connected to ground when closed, floating when open
 */

class Button: public IUpdate
{
private:
  int pin; /**< Which hardware pin this button is connected to. **/
  unsigned long interval; /**< How long the button must be pressed/released before the state change is accepted */
  unsigned long timer; /**< How long the button has been in a new state but not yet accepted */
  int state; /**< Current accepted state of the button, LOW = pressed */
  bool edge_pressed; /**< Has the button been pressed since the user last asked? */
  bool edge_released; /**< Has the button been released since the user last asked? */
protected:
  virtual void onPressed(void) {}
  virtual void onReleased(void) {}
public:
  /**
   * Constructor
   *
   * @param _pin Which pin the button is monitoring
   */
  Button(int _pin, unsigned long _interval): pin(_pin), interval(_interval), timer(0), state(HIGH), edge_pressed(false), edge_released(false) {}

  /**
   * Prepare the button.  Sets the pin as output and engages the pull-up resistor
   */
  void begin(void) const;
  
  /**
   * Update the state of the button.  Call this regularly.
   */
  void update(void);

  /**
   * Test whether the button has been pressed since we last asked
   *
   * @retval true Pressed since this method was last called
   */
  bool wasPressed(void);

  /**
   * Test whether the button has been released since we last asked
   *
   * @retval true Released since this method was last called
   */
  bool wasReleased(void);

  /**
   * Get current known state of the button
   *
   * @retval true Button is currently being pressed
   */
  bool isPressed(void) const { return state == LOW; }
};

#endif // __BUTTON_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp

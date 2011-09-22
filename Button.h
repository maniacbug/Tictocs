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
  unsigned long time_pressed; /**< What time the button was last pressed */
  int state; /**< Current accepted state of the button, LOW = pressed */
  bool edge_pressed; /**< Has the button been pressed since the user last asked? */
  bool edge_released; /**< Has the button been released since the user last asked? */
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
  Button(int _pin, unsigned long _interval);

  /**
   * Prepare the button.  Sets the pin as output and engages the pull-up resistor
   */
  void begin(void);
  
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
  bool isPressed(void) const;
};

#endif // __BUTTON_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp

#ifndef __BUTTON_H__
#define __BUTTON_H__

// STL includes
// C includes
// Library includes
// Project includes

/**
 * Manages a single push button.  Button is connected to ground when closed, floating when open
 */

class Button
{
private:
  int pin;
protected:
public:
  /**
   * Constructor
   *
   * @param _pin Which pin the button is monitoring
   */
  Button(int _pin): pin(_pin) {}

  /**
   * Prepare the button.  Sets the pin as output and engages the pull-up resistor
   */
  void begin(void) const;
};

#endif // __BUTTON_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp

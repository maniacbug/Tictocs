#ifndef __EMITBUTTON_H__
#define __EMITBUTTON_H__

// STL includes
// C includes
// Library includes
// Project includes
#include <Button.h>

/**
 * Manages a single push button which emits signals on press and release
 */

class EmitButton: public Button
{
public:
  /**
   * Constructor
   *
   * @param _pin Which pin the button is monitoring
   */
  EmitButton(int _pin, unsigned long _interval, int /*_signal_pressed*/, int /*_signal_released*/): Button(_pin,_interval) {}
};
#endif // __EMITBUTTON_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp

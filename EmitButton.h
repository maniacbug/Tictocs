#ifndef __EMITBUTTON_H__
#define __EMITBUTTON_H__

// STL includes
// C includes
// Library includes
// Project includes
#include <Button.h>
#include <Connector.h>

/**
 * Manages a single push button which emits signals on press and release
 */

class EmitButton: public Connectable, public Button
{
  uint8_t signal_pressed;
  uint8_t signal_released;

protected:
  void onPressed(void);
  void onReleased(unsigned long);
public:
  /**
   * Constructor
   *
   * @param _pin Which pin the button is monitoring
   */
  EmitButton(Connector& _conn,int _pin, uint8_t _signal_pressed, uint8_t signal_released = 0, unsigned long _interval = 20 );
};
#endif // __EMITBUTTON_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp

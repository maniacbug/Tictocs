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
public:
  /**
   * Constructor
   *
   * @param _pin Which pin the button is monitoring
   */
  EmitButton(Connector& _conn,int _pin, unsigned long _interval, int /*_signal_pressed*/, int /*_signal_released*/ =0): Connectable(_conn), Button(_pin,_interval) {}
};
#endif // __EMITBUTTON_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp

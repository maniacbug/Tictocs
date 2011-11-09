#ifndef __PINCONTROL_H__
#define __PINCONTROL_H__

// STL includes
// C includes
// Library includes
#include <Connector.h>
// Project includes

/**
 * Example for how classes should be declared
 */

class PinControl: public Connectable
{
private:
  int pin;
  uint8_t signal_low;
  uint8_t signal_high;
protected:
  void onNotify(const Connectable*, uint8_t signal);
public:
  PinControl(Connector& _conn,int _pin,uint8_t _signal_low, uint8_t _signal_high): Connectable(_conn), pin(_pin), signal_low(_signal_low), signal_high(_signal_high) {}
  void begin(void);
  void listen(Connectable* _whom);
};

#endif // __PINCONTROL_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp

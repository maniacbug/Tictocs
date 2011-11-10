#ifndef __RTCEVENT_H__
#define __RTCEVENT_H__

// STL includes
// C includes
// Library includes
// Project includes
#include <Connector.h>
#include <IUpdate.h>

class IRtc
{
public:
  virtual bool is_after(uint32_t _time) const =0;
};

/**
 * Example for how classes should be declared
 */

class RtcEvent: public Connectable, public IUpdate
{
  uint32_t when;
  uint8_t signal_what;
  bool active;
  static const IRtc* rtc;
protected:
  void update(void);
public:
  RtcEvent(Connector& _conn,uint32_t _when,uint8_t _signal_what);
  void begin(void);

  static void setRtc(const IRtc*);

};

#endif // __RTCEVENT_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp

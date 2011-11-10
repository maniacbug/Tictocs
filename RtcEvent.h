#ifndef __RTCEVENT_H__
#define __RTCEVENT_H__

// STL includes
// C includes
// Library includes
// Project includes
#include <Connector.h>
#include <IUpdate.h>

class DateTime;
class RTC_native;

/**
 * Example for how classes should be declared
 */

class RtcEvent: public Connectable, public IUpdate
{
  uint32_t when;
  uint8_t signal_what;
  bool active;
protected:
  void update(void);
public:
  RtcEvent(Connector& _conn,const DateTime& _when,uint8_t _signal_what);
  void begin(void);

  static void setRtc(const RTC_native& /*_rtc*/);

};

#endif // __RTCEVENT_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp

// STL includes
// C includes
// Library includes
// Project includes
#include <RtcEvent.h>

#include <RTC_native.h>

const RTC_native* rtc = NULL;

/****************************************************************************/

void RtcEvent::update(void)
{
  if ( active && when <= const_cast<RTC_native*>(rtc)->now().unixtime() )
  {
    active = false;
    emit(signal_what);
  }
}

/****************************************************************************/
RtcEvent::RtcEvent(Connector& _conn,const DateTime& _when,uint8_t _signal_what):
	Connectable(_conn), when(_when.unixtime()), signal_what(_signal_what), active(false)
{
}

/****************************************************************************/

void RtcEvent::begin(void)
{
  if ( rtc )
    active = when > const_cast<RTC_native*>(rtc)->now().unixtime();
}

/****************************************************************************/

void RtcEvent::setRtc(const RTC_native& _rtc)
{
  rtc = &_rtc;
}

/****************************************************************************/

// vim:cin:ai:sts=2 sw=2 ft=cpp

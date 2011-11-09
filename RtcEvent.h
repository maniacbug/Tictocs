#ifndef __RTCEVENT_H__
#define __RTCEVENT_H__

// STL includes
// C includes
// Library includes
// Project includes
#include <Connector.h>

class DateTime;

/**
 * Example for how classes should be declared
 */

class RtcEvent: public Connectable
{
private:
protected:
public:
  RtcEvent(Connector& _conn,const DateTime& /*_when*/,uint8_t /*_signal_what*/): Connectable(_conn) {}

};

#endif // __RTCEVENT_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp

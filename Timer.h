#ifndef __TIMER_H__
#define __TIMER_H__

// STL includes
// C includes
// Library includes
// Project includes
#include <IUpdate.h>

/**
 * Manage events which occur on a specified time interval
 */

class Timer: public IUpdate
{
private:
  unsigned long interval; /**< How long to wait before firing */
  unsigned long last_updated;
  bool fired;
protected:
  /**
   * Call regularly to update status of timer
   */
   void update(void) 
   {
     unsigned long now = millis();
     if ( now - last_updated >= interval )
     {
       last_updated += interval;
       fired = true;
       // onFired();
     }
   }
public:
  /**
   * Constructor
   *
   * @param _interval How long to wait before firing
   */
  Timer(unsigned long _interval): interval(_interval), last_updated(0), fired(false) {}

  /**
   * Test whether the timer has fired since we last asked
   *
   * @retval true Timer fired since this method was last called
   */
  bool wasFired(void) { bool result = fired; fired = false; return result; }
};

#endif // __TIMER_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp

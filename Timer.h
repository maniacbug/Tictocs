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
  unsigned long last_updated; /**< When was the timer last updated */
  bool fired; /**< Has the timer fired since the user last checked? */
  bool enabled; /**< Is the timer enabled so it can run? */
protected:
  /**
   * Triggered when timer is fired.  Override to implement special behaviour
   */
   virtual void onFired(void) {}
public:
  /**
   * Constructor
   *
   * @param _interval How long to wait before firing
   */
  Timer(unsigned long _interval): interval(_interval), last_updated(0), fired(false), enabled(true) {}

  /**
   * Call regularly to update status of timer
   */
  void update(void) 
  {
    unsigned long now = millis();
    if ( enabled && now - last_updated >= interval )
    {
      last_updated += interval;
      fired = true;
      onFired();
    }
  }

  /**
   * Test whether the timer has fired since we last asked
   *
   * @retval true Timer fired since this method was last called
   */
  bool wasFired(void) { bool result = fired; fired = false; return result; }

  /**
   * Reset timer back to the start
   */
  void reset(void) { last_updated = millis(); enabled = true; }

  /**
   * Set new interval value (and reset)
   *
   * @param _interval New duration for the timer in ms
   */
  void setInterval(unsigned long _interval) { interval = _interval; reset(); }

  /**
   * Disables timer so it will never fire.  Call reset() to enable.
   */
  void disable(void) { enabled = false; }
};

#endif // __TIMER_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp

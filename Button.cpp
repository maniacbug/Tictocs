// STL includes
// C includes
// Framework includes
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
// Library includes
#include <Updater.h>
// Project includes
#include <Button.h>

using namespace Tictocs;

/****************************************************************************/

Button::Button(int _pin, unsigned long _interval): pin(_pin), interval(_interval), timer(0), time_pressed(0), state(HIGH), edge_pressed(false), edge_released(false) 
{
}

/****************************************************************************/

void Button::begin(void)
{
  pinMode(pin,INPUT);
  digitalWrite(pin,HIGH);

  Updatable::begin();
}

/****************************************************************************/

void Button::begin(Updater& up)
{
  begin();
  up.add(this);
}

/****************************************************************************/

void Button::update(void)
{
  uint32_t time_now = millis();
  uint8_t state_now = digitalRead(pin)?true:false;
  if ( state_now == state )
    timer = time_now;
  else if ( time_now - timer > interval )
  {
    state = state_now;
    timer = time_now;
    
    if (state)
    {
      edge_released = true;
      onReleased(time_now - time_pressed);
    }
    else
    {
      edge_pressed = true;
      time_pressed = time_now - interval;
      onPressed();
    }
  }
}

/****************************************************************************/

bool Button::isPressed(void) const 
{ 
  return state == LOW; 
}

/****************************************************************************/

bool Button::wasPressed(void) 
{ 
  bool result = edge_pressed; 
  edge_pressed = false; 
  return result; 
}

/****************************************************************************/

unsigned Button::wasReleased(void) 
{ 
  bool result = edge_released; 
  edge_released = false; 
  return result ? millis() - time_pressed : 0; 
}

/****************************************************************************/

// vim:cin:ai:sts=2 sw=2 ft=cpp

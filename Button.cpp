// STL includes
// C includes
// Library includes
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

// Project includes
#include <Button.h>

/****************************************************************************/

Button::Button(int _pin, unsigned long _interval): pin(_pin), interval(_interval), timer(0), time_pressed(0), state(HIGH), edge_pressed(false), edge_released(false) 
{
}

/****************************************************************************/

void Button::begin(void)
{
  pinMode(pin,INPUT);
  digitalWrite(pin,HIGH);
}

/****************************************************************************/

void Button::update(void)
{
  unsigned long time_now = millis();
  int state_now = digitalRead(pin);
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

bool Button::wasReleased(void) 
{ 
  bool result = edge_released; 
  edge_released = false; 
  return result; 
}

/****************************************************************************/

// vim:cin:ai:sts=2 sw=2 ft=cpp

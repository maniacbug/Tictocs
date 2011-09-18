// STL includes
// C includes
// Library includes
#include <WProgram.h>

// Project includes
#include <Button.h>

/****************************************************************************/

void Button::begin(void) const
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
      onReleased();
    }
    else
    {
      edge_pressed = true;
      onPressed();
    }
  }
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

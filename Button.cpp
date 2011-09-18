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

// vim:cin:ai:sts=2 sw=2 ft=cpp

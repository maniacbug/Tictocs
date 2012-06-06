// STL includes
// C includes
// Library includes
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

// Project includes
#include <EmitButton.h>

using namespace Tictocs;

/****************************************************************************/

EmitButton::EmitButton(Connector& _conn,int _pin, uint8_t _signal_pressed, uint8_t _signal_released, unsigned long _interval ): 
  Connectable(_conn), Button(_pin,_interval), signal_pressed(_signal_pressed), signal_released(_signal_released)
{
}

/****************************************************************************/

void EmitButton::onPressed(void)
{
  emit(signal_pressed);
}

/****************************************************************************/

void EmitButton::onReleased(unsigned long)
{
  if ( signal_released )
    emit ( signal_released );
}

/****************************************************************************/

// vim:cin:ai:sts=2 sw=2 ft=cpp

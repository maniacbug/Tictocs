/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

// STL headers
// C headers
// Framework headers
#include <Arduino.h>
#include <avr/pgmspace.h>
// Library headers
// Project headers
// This component's header
#include <Sequence.h>

using namespace Tictocs;

/****************************************************************************/

Sequence::Sequence(Connector& conn,const Entry* _entries,uint8_t _signal_launch): Connectable(conn), Tictocs::Timer(0), entries(_entries), current(_entries), signal_launch(_signal_launch)
{
  disable();
}

/****************************************************************************/

void Sequence::onFired(void)
{
  disable();
  if ( isValid() ) 
  {
    emit( pgm_read_byte(&(current->signal)) );
    ++current;
    resetInterval();
  }
}

/****************************************************************************/

void Sequence::onNotify(const Connectable* /*who*/, uint8_t signal)
{
  if ( signal == signal_launch )
  {
    // Restart!
    current = entries;
    resetInterval();
  }
}

/****************************************************************************/

bool Sequence::isValid(void) const
{
  return current && pgm_read_byte(&(current->signal));
}

/****************************************************************************/

void Sequence::resetInterval(void)
{
  if ( isValid() )
  {
    setInterval(pgm_read_dword(&(current->delayms)));
  }
}

/****************************************************************************/
void Sequence::begin(Updater& updater,Connectable* whom)
{
  Tictocs::Timer::begin(updater);
  listen(whom,signal_launch);
}
/****************************************************************************/

// vim:cin:ai:sts=2 sw=2 ft=cpp

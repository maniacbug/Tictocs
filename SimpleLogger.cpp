/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

// STL includes
// C includes
// Library includes
// Project includes
#include <SimpleLogger.h>

/****************************************************************************/

SimpleLogger::SimpleLogger(int _num_objects, int _num_signals):
  num_objects(_num_objects), next_object(0), num_signals(_num_signals),
  next_signal(0)
{
  signal_dictionary = reinterpret_cast<signal_entry*>(malloc(_num_signals * sizeof(signal_entry)));
}

/****************************************************************************/

prog_char* SimpleLogger::find_symbol(uint8_t signal)
{
  prog_char* result = NULL;

  int i = num_signals;
  while(i--)
  {
    signal_entry* current = signal_dictionary + i;
    if ( current->signal == signal )
      result = current->symbol; 
  }

  return result;
}

/****************************************************************************/

void SimpleLogger::log_emit(const Connectable* p, uint8_t signal)
{
  prog_char* signal_symbol = find_symbol(signal);
  if ( signal_symbol )
    printf_P(PSTR("EMIT %p %S\n\r"),p,signal_symbol);
  else
    printf_P(PSTR("EMIT %p %i\n\r"),p,signal);
}

/****************************************************************************/

void SimpleLogger::log_notify(const Connectable* p)
{
  printf_P(PSTR("NOTF %p\n\r"),p);
}

/****************************************************************************/

bool SimpleLogger::setSignalSymbol(uint8_t signal, prog_char* symbol)
{
  bool result = false;

  if ( next_signal < num_signals )
  {
    result = true;
    signal_dictionary[next_signal].symbol = symbol;
    signal_dictionary[next_signal].signal = signal;
  }
  return result;
}

/****************************************************************************/
// vim:cin:ai:sts=2 sw=2 ft=cpp

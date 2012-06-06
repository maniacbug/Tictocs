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

using namespace Tictocs;

/****************************************************************************/

SimpleLogger::SimpleLogger(uint8_t _num_objects, uint8_t _num_signals):
  num_objects(_num_objects), next_object(0), num_signals(_num_signals),
  next_signal(0)
{
  signal_dictionary = reinterpret_cast<signal_entry*>(malloc(_num_signals * sizeof(signal_entry)));
  object_dictionary = reinterpret_cast<object_entry*>(malloc(_num_objects * sizeof(object_entry)));
}

/****************************************************************************/

const char* SimpleLogger::find_symbol(uint8_t signal)
{
  const char* result = NULL;

  int i = next_signal;
  while(i--)
  {
    signal_entry* current = signal_dictionary + i;
    if ( current->signal == signal )
      result = current->symbol; 
  }

  return result;
}

/****************************************************************************/

const char* SimpleLogger::find_symbol(const Connectable* object)
{
  const char* result = NULL;

  int i = next_object;
  while(i--)
  {
    object_entry* current = object_dictionary + i;
    if ( current->object == object )
      result = current->symbol; 
  }

  return result;
}

/****************************************************************************/

int SimpleLogger::find_index(uint8_t signal)
{
  int result = -1;

  int i = next_signal;
  while(i--)
  {
    signal_entry* current = signal_dictionary + i;
    if ( current->signal == signal )
      result = i; 
  }

  return result;
}

/****************************************************************************/

int SimpleLogger::find_index(const Connectable* object)
{
  int result = -1;

  int i = next_object;
  while(i--)
  {
    object_entry* current = object_dictionary + i;
    if ( current->object == object )
      result = i;
  }

  return result;
}

/****************************************************************************/

const char* SimpleLogger::signal_at(uint8_t index) const
{
  const char* result = NULL;

  if ( index < next_signal )
    result = (signal_dictionary + index)->symbol;

  return result;
}

/****************************************************************************/

const char* SimpleLogger::object_at(uint8_t index) const
{
  const char* result = NULL;
  
  if ( index < next_object )
    result = (object_dictionary + index)->symbol;

  return result;
}

/****************************************************************************/

void SimpleLogger::log_emit(const Connectable* object, uint8_t signal)
{
  const char* signal_symbol = find_symbol(signal);
  const char* object_symbol = find_symbol(object);

  int state = (signal_symbol?1:0) + (object_symbol?2:0);

  switch (state)
  {
  case 0:
    printf_P(PSTR("EMIT %p %i\n\r"),object,signal);
    break;
  case 1:
    printf_P(PSTR("EMIT %p %S\n\r"),object,signal_symbol);
    break;
  case 2:
    printf_P(PSTR("EMIT %S %p\n\r"),object_symbol,signal);
    break;
  case 3:
    printf_P(PSTR("EMIT %S %S\n\r"),object_symbol,signal_symbol);
    break;
  }
}

/****************************************************************************/

void SimpleLogger::log_notify(const Connectable* object)
{
  const char* object_symbol = find_symbol(object);
  
  if ( object_symbol )
    printf_P(PSTR("NOTF %S\n\r"),object_symbol);
  else
    printf_P(PSTR("NOTF %p\n\r"),object);
}

/****************************************************************************/

bool SimpleLogger::setSymbol(uint8_t signal, const char* symbol)
{
  bool result = false;

  if ( next_signal < num_signals )
  {
    result = true;
    signal_dictionary[next_signal].symbol = symbol;
    signal_dictionary[next_signal].signal = signal;
    next_signal++;
  }
  return result;
}

/****************************************************************************/

bool SimpleLogger::setSymbol(const Connectable* object, const char* symbol)
{
  bool result = false;

  if ( next_object < num_objects )
  {
    result = true;
    object_dictionary[next_object].symbol = symbol;
    object_dictionary[next_object].object = object;
    next_object++;
  }
  return result;
}

/****************************************************************************/
// vim:cin:ai:sts=2 sw=2 ft=cpp

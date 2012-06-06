/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#ifndef __SIMPLELOGGER_H__
#define __SIMPLELOGGER_H__

// STL includes
// C includes
// Library includes
#include <avr/pgmspace.h>
// Project includes
#include <Connector.h>

namespace Tictocs
{

/**
 * Simple logging for connector signals.
 *
 * Prints emits/notify's to screen and provides a dictionary to map values
 * to symbolic names.
 */

class SimpleLogger: public Connector::ILogger
{
protected:
  struct signal_entry
  {
    uint8_t signal;
    const char* symbol;
  };
  struct object_entry
  {
    const Connectable* object;
    const char* symbol;
  };
private:
  uint8_t num_objects;
  uint8_t next_object;
  uint8_t num_signals;
  uint8_t next_signal;

  signal_entry* signal_dictionary;
  object_entry* object_dictionary;
protected:
  virtual void log_emit(const Connectable*, uint8_t);
  virtual void log_notify(const Connectable*);
  int find_index(uint8_t signal);
  int find_index(const Connectable* object);
  const char* signal_at(uint8_t index) const;
  const char* object_at(uint8_t index) const;
public:
  // Send in number of objects & signals to make room for in the
  // dictionary
  SimpleLogger(uint8_t _num_objects, uint8_t _num_signals);
  bool setSymbol(uint8_t, const char*);
  bool setSymbol(const Connectable*, const char*);
  const char* find_symbol(uint8_t signal);
  const char* find_symbol(const Connectable* object);
};

} // namespace Tictocs

#endif // __SIMPLELOGGER_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp

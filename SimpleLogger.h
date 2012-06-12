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
 * to symbolic names.  This provides a simple and universal debugging
 * mechanism.  If all your app logic is contained in signals, this will log
 * everything that's going on.
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
  uint8_t num_objects; /**< Maximum number of objects which can be stored */
  uint8_t next_object; /**< Index of the next object to be stored */
  uint8_t num_signals; /**< Maximum number of signals which can be stored */
  uint8_t next_signal; /**< Index of the next signal to be stored */

  signal_entry* signal_dictionary; /**< Dictionary of symbols to signals */
  object_entry* object_dictionary; /**< Dictionary of symbols to objects */
protected:
  /**
   * Log that a signal has been emitted
   *
   * @param who Who emitted the signal
   * @param what What signal was emitted
   */
  virtual void log_emit(const Connectable* who, uint8_t what);
  
  /**
   * Log that an object has been notified of a signal
   *
   * @param whom Which object was notified
   */
  virtual void log_notify(const Connectable* whom);
  
  /**
   * Given a signal, find its position in the dictionary
   *
   * @param signal The signal to look for
   * @return The 0-based index within the signal dictionary, or -1 if not found
   */
  int find_index(uint8_t signal);
  
  /**
   * Given an object, find its position in the dictionary
   *
   * @param signal The signal to look for
   * @return The 0-based index within the object dictionary, or -1 if not found
   */
  int find_index(const Connectable* object);
  const char* signal_at(uint8_t index) const;
  const char* object_at(uint8_t index) const;
public:
  /**
   * Constructor
   *
   * Allocates memory for the specified number of objects and signals
   *
   * @param _num_objects Maximum number of objects which can be stored.
   * @param _num_signals Maximum number of signals which can be stored.
   */
  SimpleLogger(uint8_t _num_objects, uint8_t _num_signals);
  
  /**
   * Add a signal symbol to the dictionary
   *
   * @param what The signal ID being referred to
   * @param symbol The human-readable signal.
   * @return Whether the symbol was successfully added
   */
  bool setSymbol(uint8_t what, const char* symbol);
  
  /**
   * Add a signal symbol to the object dictionary
   *
   * @param what The object being referred to
   * @param symbol The human-readable signal.
   * @return Whether the symbol was successfully added
   */
  bool setSymbol(const Connectable* what, const char* symbol);
  const char* find_symbol(uint8_t signal);
  const char* find_symbol(const Connectable* object);
};

} // namespace Tictocs

#endif // __SIMPLELOGGER_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp

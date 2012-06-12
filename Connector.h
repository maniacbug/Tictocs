/*
 Copyright (C) 2012 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#ifndef __CONNECTOR_H__
#define __CONNECTOR_H__

// STL includes
// C includes
// Library includes
#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
// Project includes

namespace Tictocs
{

/**
 * An object which can be connected to another object
 */

class Connector;

class Connectable
{
private:
  Connector& conn;
protected:
  void emit(uint8_t signal);
  virtual void onNotify(const Connectable* ,uint8_t ) {}
  Connectable(Connector& _conn): conn(_conn) {}
  friend class Connector;
public:
  void listen(const Connectable* emitter,uint8_t signal);
  void unListen(const Connectable* emitter,uint8_t signal = 0);
  Connector& connector(void) { return conn; }
  Connector& connector(void) const { return const_cast<Connectable*>(this)->conn; }
};

/**
 * A single connection
 */

struct Connection
{
  const Connectable* emitter;
  uint8_t signal;
  Connectable* listener;
  Connection(void): emitter(NULL), signal(0), listener(NULL) {}
  Connection(const Connectable* _emitter, uint8_t _signal, Connectable* _listener);
};

/**
 * Master table of connections
 */

class Connector
{
public:
  static const int default_max_connections = 25; /**< Max # of connections we can handle */
  struct ILogger
  {
    virtual void log_emit(const Connectable*, uint8_t) =0;
    virtual void log_notify(const Connectable*) =0;
  };
private:
  Connection* connections; /**< Set of known connections */
  Connection* end_connections; /**< Pointer just past the last known connection */
  ILogger* logger;
  uint16_t max_connections;
protected:
  void log_emit(const Connectable*, uint8_t);
  void log_notify(const Connectable*);
public:
  Connector(uint16_t _max_connections = default_max_connections);
  void add(const Connection& connection);
  void remove(const Connection& connection);
  void emit(const Connectable* emitter, uint8_t signal);
  uint16_t size(void) const { return end_connections - connections; }
  void setLogger(ILogger* _logger) { logger = _logger; }
};

} // namespace Tictocs

#endif // __CONNECTOR_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp

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
  Connector& connector(void) { return conn; }
};

/**
 * A single connection
 */

struct Connection
{
  const Connectable* emitter;
  uint8_t signal;
  Connectable* listener;
  Connection(void) {}
  Connection(const Connectable* _emitter, uint8_t _signal, Connectable* _listener);
};

/**
 * Master table of connections
 */

class Connector
{
public:
  static const int max_connections = 25; /**< Max # of connections we can handle */
  struct ILogger
  {
    virtual void log_emit(const Connectable*, uint8_t) =0;
    virtual void log_notify(const Connectable*) =0;
  };
private:
  Connection connections[max_connections]; /**< Set of known connections */
  Connection* end_connections; /**< Pointer just past the last known connection */
  ILogger* logger;
protected:
  void log_emit(const Connectable*, uint8_t);
  void log_notify(const Connectable*);
public:
  Connector(void): end_connections(connections), logger(NULL) {}
  void add(const Connection& connection);
  void emit(const Connectable* emitter, uint8_t signal);
  int size(void) const { return end_connections - connections; }
  void setLogger(ILogger* _logger) { logger = _logger; }
};

#endif // __CONNECTOR_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp

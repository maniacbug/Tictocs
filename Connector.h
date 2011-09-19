#ifndef __CONNECTOR_H__
#define __CONNECTOR_H__

// STL includes
// C includes
// Library includes
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
  void notify(const char* subject);
  virtual void onNotify(const Connectable* ,const char* ) {}
  Connectable(Connector& _conn): conn(_conn) {}
  friend class Connector;
public:
  void listen(const Connectable* sender,const char* subject);
};

/**
 * A single connection
 */

struct Connection
{
  const Connectable* from;
  char subject[20];
  Connectable* to;
  Connection(void) {}
  Connection(const Connectable* _from, const char *_subject, Connectable* _to);
};

/**
 * Master table of connections
 */

class Connector
{
public:
  static const int max_connections = 20; /**< Max # of connections we can handle */
private:
  Connection connections[max_connections]; /**< Set of known connections */
  Connection* end_connections; /**< Pointer just past the last known connection */
protected:
public:
  Connector(void): end_connections(connections) {}
  void add(Connection& connection);
  void notify(const Connectable* sender, const char* subject);
  int size(void) const { return end_connections - connections; }
};

#endif // __CONNECTOR_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp

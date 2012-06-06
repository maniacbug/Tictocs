// STL includes
// C includes
#include <string.h>
// Library includes
// Project includes
#include <Connector.h>

using namespace Tictocs;

/****************************************************************************/

void Connectable::emit(uint8_t signal)
{
  conn.emit(this,signal);
}

/****************************************************************************/

void Connectable::listen(const Connectable* emitter,uint8_t signal) 
{
  // Filter out 0 which is an invalid signal
  if (signal)
    conn.add(Connection(emitter, signal, this));
}

/****************************************************************************/

void Connectable::unListen(const Connectable* emitter,uint8_t signal)
{
  // signal == 0 is OK in this case, it means unlisten to ALL from this
  // emitter.

  conn.remove(Connection(emitter, signal, this));
}

/****************************************************************************/

Connection::Connection(const Connectable* _emitter, uint8_t _signal, Connectable* _listener):
  emitter(_emitter), signal(_signal), listener(_listener)
{
}

/****************************************************************************/

Connector::Connector(uint16_t _max_connections): 
  logger(NULL), max_connections(_max_connections)
{
  connections = reinterpret_cast<Connection*>( malloc( sizeof(Connection) 
	* _max_connections ) );
  end_connections = connections;
}


/****************************************************************************/

void Connector::add(const Connection& connection)
{
  // First, look for an unused slot
  bool done = false;
  Connection *current = end_connections;
  while (current-- != connections && !done)
  {
    // An empty slot will have a NULL listener
    if ( ! current->listener ) 
    {
      // Replace this with the given connection 
      *current = connection;
      done = true;
    }
  }

  // No unused slots? Add one to the end
  if ( !done && size() < max_connections )
    *end_connections++ = connection;
}

/****************************************************************************/

void Connector::remove(const Connection& connection)
{
  // Search for a matching connection in our list
  Connection *current = end_connections;
  while (current-- != connections)
  {
    bool emitter_match = ( connection.emitter == NULL || current->emitter == connection.emitter ) ;
    bool signal_match = ( connection.signal == 0 || current->signal == connection.signal );
    bool listener_match = ( current->listener == connection.listener );
    if ( emitter_match && signal_match && listener_match )
    {
      // Replace this with an empty connection
      *current = Connection();
    }
  }
}

/****************************************************************************/

void Connector::emit(const Connectable* emitter, uint8_t signal)
{
  // Filter out 0 which is an invalid signal
  if (!signal)
    return;

  log_emit(emitter,signal);

  Connection *current = end_connections;
  while (current-- != connections)
  {
    bool emitter_match = ( current->emitter == NULL || current->emitter == emitter ) ;
    bool signal_match = ( current->signal == signal );
    if ( emitter_match && signal_match && current->listener )
    {
      log_notify(current->listener);
      current->listener->onNotify(emitter,signal);
    }
  }
}

/****************************************************************************/

void Connector::log_emit(const Connectable* p, uint8_t signal)
{
  if ( logger )
    logger->log_emit(p,signal);
}

/****************************************************************************/

void Connector::log_notify(const Connectable* p)
{
  if ( logger )
    logger->log_notify(p);
}

/****************************************************************************/

// vim:cin:ai:sts=2 sw=2 ft=cpp

// STL includes
// C includes
#include <string.h>
// Library includes
// Project includes
#include <Connector.h>

void Connectable::emit(uint8_t signal)
{
  conn.emit(this,signal);
}

/****************************************************************************/

void Connectable::listen(const Connectable* emitter,uint8_t signal) 
{
  conn.add(Connection(emitter, signal, this));
}

/****************************************************************************/

Connection::Connection(const Connectable* _emitter, uint8_t _signal, Connectable* _listener):
  emitter(_emitter), signal(_signal), listener(_listener)
{
}

/****************************************************************************/

void Connector::add(const Connection& connection)
{
  if ( size() < max_connections )
    *end_connections++ = connection;
}

/****************************************************************************/

void Connector::emit(const Connectable* emitter, uint8_t signal)
{
  Connection *current = end_connections;
  while (current-- != connections)
  {
    bool emitter_match = ( current->emitter == NULL || current->emitter == emitter ) ;
    bool signal_match = ( current->signal == signal );
    if ( emitter_match && signal_match )
      current->listener->onNotify(emitter,signal);
  }
}

/****************************************************************************/

// vim:cin:ai:sts=2 sw=2 ft=cpp

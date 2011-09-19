// STL includes
// C includes
#include <string.h>
// Library includes
// Project includes
#include <Connector.h>

void Connectable::emit(const char* signal)
{
  conn.emit(this,signal);
}

/****************************************************************************/

void Connectable::listen(const Connectable* emitter,const char* signal) 
{
  conn.add(Connection(emitter, signal, this));
}

/****************************************************************************/

Connection::Connection(const Connectable* _emitter, const char *_signal, Connectable* _listener):
  emitter(_emitter), listener(_listener)
{
  strncpy(signal,_signal,sizeof(signal));
}

/****************************************************************************/

void Connector::add(const Connection& connection)
{
  if ( size() < max_connections )
    *end_connections++ = connection;
}

/****************************************************************************/

void Connector::emit(const Connectable* emitter, const char* signal)
{
  Connection *current = end_connections;
  while (current-- != connections)
  {
    if ( current->emitter == emitter && !strcmp(current->signal,signal))
      current->listener->onNotify(emitter,signal);
  }
}

/****************************************************************************/

// vim:cin:ai:sts=2 sw=2 ft=cpp

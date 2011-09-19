// STL includes
// C includes
#include <string.h>
// Library includes
// Project includes
#include <Connector.h>

void Connectable::notify(const char* subject)
{
  conn.notify(this,subject);
}

/****************************************************************************/

void Connectable::listen(const Connectable* sender,const char* subject) 
{
  Connection c(sender, subject, this);
  conn.add(c);
}

/****************************************************************************/

Connection::Connection(const Connectable* _from, const char *_subject, Connectable* _to):
  from(_from), to(_to)
{
  strncpy(subject,_subject,sizeof(subject));
}

/****************************************************************************/

void Connector::add(Connection& connection)
{
  if ( size() < max_connections )
    *end_connections++ = connection;
}

/****************************************************************************/

void Connector::notify(const Connectable* sender, const char* subject)
{
  Connection *current = end_connections;
  while (current-- != connections)
  {
    if ( current->from == sender && !strcmp(current->subject,subject))
      current->to->onNotify(sender,subject);
  }
}

/****************************************************************************/

// vim:cin:ai:sts=2 sw=2 ft=cpp

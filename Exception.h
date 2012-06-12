
/*
 Copyright (C) 2012 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

// STL includes
// C includes
// Library includes
// Project includes
#include <Connector.h>

namespace Tictocs
{

/**
 * Exception, created by Tictacs when a runtime error occurs.
 */

const uint8_t signal_exception = 0xff;

class Exception: public Connectable
{
private:
  char buffer[200];
  const Connectable* who_threw;
protected:
public:
  Exception(Connectable*, const char* _message, ...);
  const char* what(void) const { return buffer; }
  const Connectable* who(void) const { return who_threw; }
};

} // namespace Tictocs

#endif // __EXCEPTION_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp

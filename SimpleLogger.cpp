/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

// STL includes
// C includes
// Library includes
// Project includes
#include <SimpleLogger.h>

/****************************************************************************/

void SimpleLogger::log_emit(const Connectable* p, uint8_t signal)
{
  printf_P(PSTR("EMIT %p %i\n\r"),p,signal);
}

/****************************************************************************/

void SimpleLogger::log_notify(const Connectable* p)
{
  printf_P(PSTR("NOTF %p\n\r"),p);
}
/****************************************************************************/
// vim:cin:ai:sts=2 sw=2 ft=cpp


/*
 Copyright (C) 2012 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#ifndef __IUPDATE_H__
#define __IUPDATE_H__

// STL includes
// C includes
// Library includes
// Project includes

namespace Tictocs
{

/**
 * Interface for an object which can be updated
 */

class IUpdate
{
private:
protected:
public:
  /**
   * Update the object.  Perform any needed per-loop operation.
   */
  virtual void update(void) = 0;
};

} // namespace Tictocs

#endif // __IUPDATE_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp

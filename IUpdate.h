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
  virtual void update(void) = 0;
};

} // namespace Tictocs

#endif // __IUPDATE_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp

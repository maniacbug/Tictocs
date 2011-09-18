// STL includes
// C includes
// Library includes
// Project includes
#include <Updater.h>

/****************************************************************************/

Updater::Updater(void): end_objects(objects) 
{
}

/****************************************************************************/

void Updater::add(IUpdate* object) 
{
  if ( size() < max_objects )
    *end_objects++ = object;
}

/****************************************************************************/

// vim:cin:ai:sts=2 sw=2 ft=cpp

// STL includes
// C includes
// Library includes
// Project includes
#include <Updater.h>
#include <IUpdate.h>

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

void Updater::update(void)
{
  IUpdate** current = end_objects;
  while ( current-- != objects )
    (*current)->update();
}

/****************************************************************************/

// vim:cin:ai:sts=2 sw=2 ft=cpp

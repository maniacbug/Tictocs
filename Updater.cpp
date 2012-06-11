// STL includes
// C includes
#include <stdlib.h>
// Library includes
// Project includes
#include <Updater.h>
#include <IUpdate.h>

using namespace Tictocs;

/****************************************************************************/

Updater Tictocs::theUpdater;

/****************************************************************************/

void Updatable::begin()
{
  theUpdater.add(this);
}

/****************************************************************************/

Updater::Updater(uint16_t _max_objects): max_objects(_max_objects)
{
  objects = reinterpret_cast<IUpdate**>( malloc( sizeof(IUpdate*) * max_objects) ); 
  end_objects = objects;
}
  
Updater::~Updater()
{
  if ( objects )
    delete objects;
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

/*
 Copyright (C) 2012 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#ifndef __UPDATER_H__
#define __UPDATER_H__

// STL includes
// C includes
#include <stdint.h>
// Library includes
// Project includes
#include <IUpdate.h>

namespace Tictocs
{

/**
 * An object which is automatically managed by theUpdater.
 */
class Updatable: public IUpdate
{
public:
  void begin();
};

/**
 * Manages a set of IUpdate objects.  The basic idea behind this class is that
 * you add all of your objects to the Updater, and then you only have to call
 * Updater::update() once in loop().
 */

class Updater
{
private:
  static const int default_max_objects = 50; /**< By default, max # of objects we can handle */
  IUpdate** objects; /**< Set of known objects */
  IUpdate** end_objects; /**< Pointer just past the last known object */
  uint16_t max_objects;  /**< Max # of objects we can handle */
protected:
public:
  /**
   * Create a new object updater
   *
   * @param max_objects Maximum number of objects that will be able to be 
   * tracked
   */
  Updater(uint16_t max_objects = default_max_objects);
  
  /**
   * Destructor 
   */
  ~Updater();

  /**
   * Add an object to be updated
   *
   * @param object Object which will be updated
   */
  void add(IUpdate* object);

  /**
   * Update all known objects
   */
  void update(void);

  /**
   * Determine the number of objects currently known t the system
   *
   * @return Number of objects being updated
   */
  uint16_t size(void) const { return end_objects - objects; }
  
  /**
   * Determine how many objects max can be contained
   *
   * @return Max number of objects which can be contained in this object
   */
  uint16_t getMax(void) const { return max_objects; }

};

/**
 * The master updater which handles Updatable objects
 *
 * @todo This does eat up a lot of static memory if never used :(
 */
extern Updater theUpdater;

} // namespace Tictocs

#endif // __UPDATER_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp

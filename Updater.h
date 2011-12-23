#ifndef __UPDATER_H__
#define __UPDATER_H__

// STL includes
// C includes
#include <stdint.h>
// Library includes
// Project includes

class IUpdate;

/**
 * Manages a set of IUpdate objects
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
};

#endif // __UPDATER_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp

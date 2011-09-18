#ifndef __UPDATER_H__
#define __UPDATER_H__

// STL includes
// C includes
// Library includes
// Project includes

class IUpdate;

/**
 * Manages a set of IUpdate objects
 */

class Updater
{
public:
  static const int max_objects = 10; /**< Max # of objects we can handle */
private:
  IUpdate* objects[max_objects]; /**< Set of known objects */
  IUpdate** end_objects; /**< Pointer just past the last known object */
protected:
public:
  /**
   * Create a new object updater
   */
  Updater(void);

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
  int size(void) const { return end_objects - objects; }
};

#endif // __UPDATER_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp

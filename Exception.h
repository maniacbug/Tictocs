#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

// STL includes
// C includes
// Library includes
// Project includes

class Connectable;

/**
 * Exception, created by Tictacs when a runtime error occurs.
 */

class Exception
{
private:
  char buffer[200];
protected:
public:
  Exception(const Connectable*, const char* _message, ...);
  const char* what(void) const { return buffer; }
};

#endif // __EXCEPTION_H__
// vim:cin:ai:sts=2 sw=2 ft=cpp

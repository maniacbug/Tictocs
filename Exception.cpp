// STL includes
// C includes
#include <stdio.h>
#include <stdarg.h>
// Library includes
// Project includes
#include <Exception.h>

/****************************************************************************/

Exception::Exception(Connectable* pca, const char* format, ...): Connectable(pca->connector())
{
  va_list ap;
  va_start(ap,format);
  vsnprintf(buffer,sizeof(buffer),format,ap);
  va_end(ap);

  emit("exception");
}

/****************************************************************************/

// vim:cin:ai:sts=2 sw=2 ft=cpp

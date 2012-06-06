// STL includes
// C includes
#include <stdio.h>
#include <stdarg.h>
// Library includes
// Project includes
#include <Exception.h>

using namespace Tictocs;

/****************************************************************************/

Exception::Exception(Connectable* pca, const char* format, ...): 
  Connectable(pca->connector()), who_threw(pca)
{
  va_list ap;
  va_start(ap,format);
  vsnprintf(buffer,sizeof(buffer),format,ap);
  va_end(ap);

  emit(signal_exception);
}

/****************************************************************************/

// vim:cin:ai:sts=2 sw=2 ft=cpp

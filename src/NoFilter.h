
#ifndef NO_FILTER_H
#define NO_FILTER_H

#include "Filter.h"

class NoFilter : public Filter
{
  public:
    NoFilter()
    {
      
    }

    float filter(float raw, float dt)
    {
      return raw;
    }
};

#endif /* NO_FILTER_H */

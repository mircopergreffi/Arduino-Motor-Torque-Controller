
#ifndef CURRENT_SENSE_H
#define CURRENT_SENSE_H

#include "Filter.h"

class CurrentSense
{
  private:
    float mCurrentScale;
    int mPinRIS, mPinLIS;
    Filter * mFilter = NULL;

  public:
    CurrentSense(int pin_ris, int pin_lis)
    {
      mPinRIS = pin_ris;
      mPinLIS = pin_lis;
      mCurrentScale = 1;
    }

    CurrentSense(int pin_ris, int pin_lis, Filter * filter) :
      CurrentSense(pin_ris, pin_lis)
    {
      mFilter = filter;
    }

    void setCurrentScale(float currentScale)
    {
      mCurrentScale = currentScale;
    }

    float getCurrentScale()
    {
      return mCurrentScale;
    }

    int readRaw()
    {
      return analogRead(mPinLIS) - analogRead(mPinRIS);
    }

    float readValue()
    {
      return mFilter->filter(readRaw()) / mCurrentScale;
    }
};

#endif /* CURRENT_SENSE_H */

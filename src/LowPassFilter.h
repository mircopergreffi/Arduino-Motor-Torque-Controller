
#ifndef LOW_PASS_FILTER
#define LOW_PASS_FILTER

#include "Filter.h"

class LowPassFilter : public Filter
{
  private:
    float mCutFreq;
  
    int mTimeNew, mTimeLast, mTimeDiff;
    float mLowPass;

  public:
    LowPassFilter(float cutFreq)
    {
      mCutFreq = cutFreq;
      mTimeLast = 0;
      mLowPass = 0;
    }

    float filter(float raw)
    {
      mTimeNew = micros();
      mTimeDiff = mTimeNew - mTimeLast;
      mTimeLast = mTimeNew;
      
      mLowPass += (raw - mLowPass)*mCutFreq/mTimeDiff;
      return mLowPass;
    }
};

#endif /* LOW_PASS_FILTER */

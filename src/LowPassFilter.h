
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
      mLowPass = 0;
    }

    float filter(float raw, float dt)
    {
      mLowPass += (raw - mLowPass)*mCutFreq*dt;
      return mLowPass;
    }
};

#endif /* LOW_PASS_FILTER */
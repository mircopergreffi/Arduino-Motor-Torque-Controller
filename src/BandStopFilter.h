
// Second Order Band Stop Filter

#ifndef BAND_STOP_FILTER
#define BAND_STOP_FILTER

#include "Filter.h"

class BandStopFilter : public Filter
{
  private:
    float mLowCut, mHighCut;
  
    int mTimeNew, mTimeLast, mTimeDiff;
    float mLowPass, mHighPass;
    float mLowPass2, mHighPass2;
    float mBandStop;

  public:
    BandStopFilter(float freq, float radius)
    {
      mLowCut = freq - radius;
      mHighCut = freq + radius;

      mTimeLast = 0;
      
      mLowPass = 0;
      mHighPass = 0;
      mLowPass2 = 0;
      mHighPass2 = 0;
    }

    float filter(float raw)
    {
      mTimeNew = micros();
      mTimeDiff = mTimeNew - mTimeLast;
      mTimeLast = mTimeNew;
      
      mLowPass += (raw - mLowPass)*mLowCut/mTimeDiff;
      mLowPass2 += (mLowPass - mLowPass2)*mLowCut/mTimeDiff;
      mHighPass = (raw - mHighPass)/mHighCut/mTimeDiff;
      mHighPass2 = (mHighPass - mHighPass2)/mHighCut/mTimeDiff;
      
      mBandStop = mLowPass2 + mHighPass2;
      return mBandStop;
    }
};

#endif /* BAND_STOP_FILTER */

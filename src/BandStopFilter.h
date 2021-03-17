
// Second Order Band Stop Filter

#ifndef BAND_STOP_FILTER
#define BAND_STOP_FILTER

#include "Filter.h"

class BandStopFilter : public Filter
{
  private:
    float mLowCut, mHighCut;

    float mLastRaw;
    float mLowPass, mHighPass;
    float mBandStop;

  public:
    BandStopFilter(float freq, float radius)
    {
      mLowCut = freq - radius;
      mHighCut = freq + radius;
      
      mLastRaw = 0;
      mLowPass = 0;
      mHighPass = 0;
    }

    float filter(float raw, float dt)
    {      
      mLowPass += (raw - mLowPass)*mLowCut*dt;
      mHighPass += (raw - mLastRaw) - mHighPass*mHighCut*dt;      
      mBandStop = mLowPass + mHighPass;
      mLastRaw = raw;
      return mBandStop;
    }
};

#endif /* BAND_STOP_FILTER */
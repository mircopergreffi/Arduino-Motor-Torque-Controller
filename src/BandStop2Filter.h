
// Second Order Band Stop Filter

#ifndef BAND_STOP_2_FILTER_H
#define BAND_STOP_2_FILTER_H

#include "Filter.h"

class BandStop2Filter : public Filter
{
  private:
    float mLowCut, mHighCut;
    
    float mLowPass, mHighPass;
    float mLowPass2, mHighPass2;
    float mBandStop;

  public:
    BandStop2Filter(float freq, float radius)
    {
      mLowCut = freq - radius;
      mHighCut = freq + radius;
  
      mLowPass = 0;
      mHighPass = 0;
      mLowPass2 = 0;
      mHighPass2 = 0;
    }

    float filter(float raw, float dt)
    {      
      mLowPass += (raw - mLowPass)*mLowCut*dt;
      mLowPass2 += (mLowPass - mLowPass2)*mLowCut*dt;
      mHighPass += (raw - mHighPass)/mHighCut/dt;
      mHighPass2 += (mHighPass - mHighPass2)/mHighCut/dt;
      
      mBandStop = mLowPass + mHighPass;
      return mBandStop;
    }
};

#endif /* BAND_STOP_2_FILTER */
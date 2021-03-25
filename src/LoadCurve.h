
#ifndef LOAD_CURVE_H
#define LOAD_CURVE_H

/*          
 * O        |
 * u  Omax  |------------------+
 * t        |                   \
 * p        |                    \
 * u        |                     \
 * t        |                      \
 *          |                       \
 *          +------------------------+----->
 *                           Imin   Imax
 *                 I n p u t
 * 
 *  Output -> Voltage
 *  Input  -> Current
 * 
 */

#include "Controller.h"

class LoadCurve : public Controller
{
  private:
    float mMaxInput, mMinInput, mMaxOutput;
    float mSlope, mIntercept, mOutput;
    
  public:
    LoadCurve(float maxInput, float minInput, float maxOutput)
    {
      setParameters(maxInput, minInput, maxOutput);
    }

    void setParameters(float maxInput, float minInput, float maxOutput)
    {
      mMaxInput = maxInput;
      mMinInput = minInput;
      mMaxOutput = maxOutput;
      mSlope = maxOutput / (minInput - maxInput);
      mIntercept = - mSlope * maxInput;
    }

    float getMaxInput()
    {
      return mMaxInput;
    }

    float getMinInput()
    {
      return mMinInput;
    }
  
    float getMaxOutput()
    {
      return mMaxOutput;
    }

    void setSetPoint(float setPoint)
    {
      
    }

    float compute(float in)
    {
      mOutput = mSlope * in + mIntercept;
      if (mOutput > mMaxOutput)
        mOutput = mMaxOutput;
      return mOutput;
    }
};

#endif /* LOAD_CURVE_H */

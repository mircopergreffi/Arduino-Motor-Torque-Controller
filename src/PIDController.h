
#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include "Controller.h"

class PIDController : public Controller
{
  private:
    bool mEnabled;
    bool mUseIntegralMemoryLimits;
    
    float Kp, Ki, Kd;
    float mSetPoint;
    float mMaxIntegralMemory, mMinIntegralMemory;
    float mMaxOutputLimit, mMinOutputLimit;
    
    int mTimeLast, mTimeNew, mTimeDiff;
    float mError, mErrorLast;
    float mOutputLast, mOutputNew, mOutputDiff;
    float mIntegralMemory;

  public:
    PIDController(float kp, float ki, float kd)
    {
      setParameters(kp, ki, kd);
      setSetPoint(0);
      useIntegralMemoryLimits(false);
      setOutputLimits(255, -255);
      mIntegralMemory = 0;
      mTimeLast = 0;
      mErrorLast = 0;
      mOutputLast = 0;
    }

    PIDController() :
      PIDController(0, 0, 0)
    {
    }

    void setParameters(float kp, float ki, float kd)
    {
      Kp = kp;
      Ki = ki;
      Kd = kd;
    }

    float getKp()
    {
      return Kp;
    }

    float getKi()
    {
      return Ki;
    }

    float getKd()
    {
      return Kd;
    }

    void setSetPoint(float setPoint)
    {
      mSetPoint = setPoint;
    }

    float getSetPoint()
    {
      return mSetPoint;
    }

    void setIntegralMemoryLimits(float maxIntegralMemory, float minIntegralMemory)
    {
      mMaxIntegralMemory = maxIntegralMemory;
      mMinIntegralMemory = minIntegralMemory;
      useIntegralMemoryLimits(true);
    }

    void setIntegralMemoryLimit(float integralMemoryLimit)
    {
      setIntegralMemoryLimits(integralMemoryLimit, -integralMemoryLimit);
    }

    float getMaxIntegralMemory()
    {
      return mMaxIntegralMemory;
    }

    float getMinIntegralMemory()
    {
      return mMinIntegralMemory;
    }

    void useIntegralMemoryLimits(bool use)
    {
      mUseIntegralMemoryLimits = use;
    }

    void setOutputLimits(float maxOutputLimit, float minOutputLimit)
    {
      mMaxOutputLimit = maxOutputLimit;
      mMinOutputLimit = minOutputLimit;
    }

    float compute(float in)
    {
      mTimeNew = micros();
      mTimeDiff = mTimeNew - mTimeLast;

      mError = mSetPoint - in;

      mIntegralMemory += Ki * mError * mTimeDiff;
      if (mUseIntegralMemoryLimits)
        if (mIntegralMemory > mMaxIntegralMemory)
          mIntegralMemory = mMaxIntegralMemory;
        else if (mIntegralMemory < mMinIntegralMemory)
          mIntegralMemory = mMinIntegralMemory;

      mOutputNew = Kp * mError + mIntegralMemory + Kd * (mError - mErrorLast) / mTimeDiff;
      if (mOutputNew > mMaxOutputLimit)
        mOutputNew = mMaxOutputLimit;
      else if (mOutputNew < mMinOutputLimit)
        mOutputNew = mMinOutputLimit;

      mTimeLast = mTimeNew;
      mErrorLast = mError;
      mOutputLast = mOutputNew;

      return mOutputNew;
    }
    
};

#endif /* PID_CONTROLLER_H */

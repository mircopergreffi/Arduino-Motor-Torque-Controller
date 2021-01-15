
#ifndef TORQUE_CONTROLLER_H
#define TORQUE_CONTROLLER_H

#include "FullBridge.h"
#include "CurrentSense.h"
#include "Controller.h"

class Motor
{
  private:
    bool mEnabled;
    float mTorqueConstant;
    float mSetPoint, mCurrent, mVoltage;
    FullBridge * mFullBridge;
    CurrentSense * mCurrentSense;
    Controller * mController;

  public:
    Motor(FullBridge * fullBridge, CurrentSense * currentSense, Controller * controller)
    {
      mFullBridge = fullBridge;
      mCurrentSense = currentSense;
      mController = controller;
      mSetPoint = 0;
      mCurrent = 0;
      setEnable(false);
    }

    bool isEnabled()
    {
      return mEnabled;
    }

    void setEnable(bool enable)
    {
      mEnabled = enable;
      mFullBridge->setEnable(enable);
    }

    void setTorqueConstant(float torqueConstant)
    {
      mTorqueConstant = torqueConstant;
    }

    float getTorqueConstant()
    {
      return mTorqueConstant;
    }

    void setTorqueRequest(float torque)
    {
      setCurrentRequest(torque * mTorqueConstant);
    }

    void getTorqueRequest()
    {
      return getCurrentRequest() / mTorqueConstant;
    }

    void setCurrentRequest(float current)
    {
      mSetPoint = current;
      mController->setSetPoint(current);
    }

    float getCurrentRequest()
    {
      return mSetPoint;
    }

    float getCurrent()
    {
      return mCurrent;
    }

    float getVoltage()
    {
      return mVoltage;
    }

    void run()
    {
      mCurrent = mCurrentSense->readValue();
      mVoltage = mController->compute(mCurrent);
      mFullBridge->setVoltage(mVoltage);
    }
};

#endif /* TORQUE_CONTROLLER_H */

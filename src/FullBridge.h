
#ifndef FULL_BRIDGE_H
#define FULL_BRIDGE_H

class FullBridge
{
  private:
    bool mEnabled;
    int mPinRPWM, mPinREN;
    int mPinLPWM, mPinLEN;
    int mMaxPWM;

  public:  
    FullBridge(int pin_rpwm, int pin_lpwm, int pin_ren, int pin_len)
    {
      mPinRPWM = pin_rpwm;
      mPinLPWM = pin_lpwm;
      mPinREN = pin_ren;
      mPinLEN = pin_len;
      mMaxPWM = 255;
      pinMode(mPinRPWM, OUTPUT);
      pinMode(mPinLPWM, OUTPUT);
      pinMode(mPinREN, OUTPUT);
      if (mPinLEN > -1)
        pinMode(mPinLEN, OUTPUT);
      setEnable(false);
      setVoltage(0);
    }
    
    FullBridge(int pin_rpwm, int pin_lpwm, int pin_en)
      : FullBridge(pin_rpwm, pin_lpwm, pin_en, -1)
    {
    }

    void setMaxPWM(int maxPWM)
    {
      mMaxPWM = maxPWM;
    }
    
    bool isEnabled()
    {
      return mEnabled;
    }

    void setEnable(bool enable)
    {
      digitalWrite(mPinREN, enable ? HIGH : LOW);
      if (mPinLEN > -1)
        digitalWrite(mPinLEN, enable ? HIGH : LOW);
      mEnabled = enable;
    }

    void setVoltage(int voltage)
    {
      if (mEnabled)
        if (voltage == 0)
        {
          digitalWrite(mPinRPWM, LOW);
          digitalWrite(mPinLPWM, LOW);
        }
        else if (voltage > 0)
        {
          digitalWrite(mPinLPWM, HIGH);
          analogWrite(mPinRPWM, max(0, mMaxPWM - voltage));
        }
        else 
        {
          digitalWrite(mPinRPWM, HIGH);
          analogWrite(mPinLPWM, max(0, mMaxPWM + voltage));
        }
    }
};

#endif /* FULL_BRIDGE_H */

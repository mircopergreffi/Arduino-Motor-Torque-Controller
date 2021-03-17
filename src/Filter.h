
#ifndef FILTER_H
#define FILTER_H

#define MICROS 1000000.0

class Filter
{
  private:
    int mTimeNew, mTimeLast, mTimeDiff;
    
  public:
    Filter()
    {
      mTimeLast = 0;
    }
    
    float filter(float raw)
    {
      mTimeNew = micros();
      mTimeDiff = mTimeNew - mTimeLast;
      mTimeLast = mTimeNew;
      return filter(raw, mTimeDiff/MICROS);
    }
    
    virtual float filter(float raw, float dt);
};

#endif /* FILTER_H */
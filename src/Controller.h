
#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller
{
  public:
    virtual void setSetPoint(float setPoint);
    virtual float compute(float in);
};

#endif /* CONTROLLER_H */

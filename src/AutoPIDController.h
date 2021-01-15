
#ifndef AUTO_PID_CONTROLLER_H
#define AUTO_PID_CONTROLLER_H

#include "PIDController.h"

class AutoPIDController : public PIDController
{
  public:
    AutoPIDController(float kp, float ki, float kd) :
      PIDController(kp, ki, kd)
    {
      
    }
};

#endif /* AUTO_PID_CONTROLLER_H */

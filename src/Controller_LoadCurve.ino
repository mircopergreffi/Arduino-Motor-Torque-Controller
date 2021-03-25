
#include "BandStopFilter.h"
#include "CurrentSense.h"
#include "FullBridge.h"
//#include "AutoPIDController.h"
#include "LoadCurve.h"
#include "Motor.h"

#define PIN_RPWM  9
#define PIN_LPWM  10
#define PIN_REN   7
#define PIN_LEN   8
#define PIN_RIS   A0
#define PIN_LIS   A1

#define FILTER_FREQ   100.0
#define FILTER_RADIUS  10.0

// #define PID_KP    5.0
// #define PID_KI    0.0001
// #define PID_KD    0.0

#define CURRENT_SCALE   f // Ratio between ADC-reading and motor current
#define TORQUE_CONSTANT 1      // Motor torque constant (torque over current)

BandStopFilter mBandStopFilter(FILTER_FREQ, FILTER_RADIUS);
CurrentSense mCurrentSense(PIN_RIS, PIN_LIS, &mBandStopFilter);
FullBridge mFullBridge(PIN_RPWM, PIN_LPWM, PIN_REN, PIN_LEN);

//AutoPIDController mAutoPID(PID_KP, PID_KI, PID_KD);
//Motor mMotor(&mFullBridge, &mCurrentSense, &mAutoPID);

LoadCurve mLoadCurve(1.0, 1.2, 255);
Motor mMotor(&mFullBridge, &mCurrentSense, &mLoadCurve);

String mCommand = "";
char mBuffer;

void onCommand(String command)
{
  mLoadCurve.setParameters(1.0, 1.2, command.toInt());
}

void setup() {

  // Logging
  Serial.begin(1000000);
  Serial.println("SetPoint Current Voltage");

  // Set pin 9 and 10 PWM Frequency to 3921.16 Hz
  // (timer=1 base_clock=31372.55Hz divider=8)
  TCCR1B = TCCR1B & B11111000 | B00000010;

  mCurrentSense.setCurrentScale(CURRENT_SCALE);
//  mAutoPID.setIntegralMemoryLimits(64);
  
  mMotor = mMotor;
  mMotor.setTorqueConstant(TORQUE_CONSTANT);
  mMotor.setEnable(true);
  mMotor.setCurrentRequest(3);
}

int now, lasttime = 0;

void loop() {

  if (Serial.available() > 0)
  {
    mBuffer = Serial.read();
    if (mBuffer == '\n')
    {
      onCommand(mCommand);
      mCommand = "";
    }
    else
    {
      mCommand += mBuffer;
    }
  }
  

  mMotor.run();

  // Logging
  now = millis();
  if (now - lasttime > 1)
  {
    lasttime = now;
    Serial.print(mMotor.getCurrentRequest());
    Serial.print(" ");
    Serial.print(mMotor.getCurrent());
    Serial.print(" ");
    Serial.println(mMotor.getVoltage()/21.25);
  }
}

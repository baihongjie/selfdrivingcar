#include <vector>
#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
  pre_cte = 0.0f;
  err = 0.0f;
  count = 0;
  this->Kp = Kp;
  this->Ki = Ki;
  this->Kd = Kd;
}

double PID::GetSteeringValueAndUpdateError(double cte) {
  total_cte += cte;
  double diff_cte = cte - pre_cte;
  double steer = -Kp * cte - Kd * diff_cte - Ki * total_cte;
  pre_cte = cte;
  err += cte * cte;
  count += 1;
  return steer;
}

double PID::AvgError() {
  return err / count;
}

int PID::GetCount() {
  return count;
}

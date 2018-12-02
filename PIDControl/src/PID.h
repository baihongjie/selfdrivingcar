#ifndef PID_H
#define PID_H

#include <vector>

class PID {
public:
  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;
  double err;
  int count;

  /**/
  double pre_cte;
  double total_cte;

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Get steering value and update the PID error variables given cross track error.
  */
  double GetSteeringValueAndUpdateError(double cte);

  /*
  * Calculate the average PID error.
  */
  double AvgError();
  int GetCount();
};

#endif /* PID_H */

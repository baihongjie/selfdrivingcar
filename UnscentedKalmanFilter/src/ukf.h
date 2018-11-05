#ifndef UKF_H
#define UKF_H

#include "measurement_package.h"
#include "Eigen/Dense"
#include <vector>
#include <string>
#include <fstream>

using Eigen::MatrixXd;
using Eigen::VectorXd;

class UKF {
public:

  ///* initially set to false, set to true in first call of ProcessMeasurement
  bool is_initialized_;

  ///* if this is false, laser measurements will be ignored (except for init)
  bool use_laser_;

  ///* if this is false, radar measurements will be ignored (except for init)
  bool use_radar_;

  ///* state vector: [pos1 pos2 vel_abs yaw_angle yaw_rate] in SI units and rad
  VectorXd x_;

  MatrixXd P_;

  ///* predicted sigma points matrix
  //MatrixXd Xsig_pred_;

  ///* Process noise standard deviation longitudinal acceleration in m/s^2
  double std_a_;

  ///* Process noise standard deviation yaw acceleration in rad/s^2
  double std_yawdd_;

  ///* Laser measurement noise standard deviation position1 in m
  double std_laspx_;

  ///* Laser measurement noise standard deviation position2 in m
  double std_laspy_;

  ///* Radar measurement noise standard deviation radius in m
  double std_radr_;

  ///* Radar measurement noise standard deviation angle in rad
  double std_radphi_;

  ///* Radar measurement noise standard deviation radius change in m/s
  double std_radrd_ ;

  ///* Weights of sigma points
  VectorXd weights_;

  ///* State dimension
  int n_x_;

  ///* Augmented state dimension
  int n_aug_;
	
  int n_z_;

  ///* Sigma point spreading parameter
  double lambda_;

  // Previous timestamp used to compute delta_t.
  double previous_timestamp_;

  // If true, print debug message.
  bool debug_;

  /**
   * Constructor
   */
  UKF();

  /**
   * Destructor
   */
  virtual ~UKF();

  /**
   * ProcessMeasurement
   * @param meas_package The latest measurement data of either radar or laser
   */
  void ProcessMeasurement(MeasurementPackage meas_package);

  /**
   * Predict sigmal point.
   */
  void PredictSigmalPoint(const MatrixXd& Xsig_aug, double delta_t, MatrixXd* Xsig_pred_out);

  /**
   * Prediction mean state, and the state covariance
   */
  void PredictMeanCov(
    double delta_t,
    MeasurementPackage::SensorType sensor,
    const MatrixXd& Xsig_aug,
    const MatrixXd& Xsig_pred,
    VectorXd* z_out,
    MatrixXd* Zsig,
    MatrixXd* S_out,
    VectorXd* x,
    MatrixXd* P_out);

  /**
   * Updates the state and the state covariance matrix using a radar/lidar measurement
   */
  void Update(
    MeasurementPackage::SensorType sensor,
    const VectorXd& z,
    const MatrixXd& Xsig_pred,
    const MatrixXd& S,
    const MatrixXd& Zsig,
    const VectorXd& z_pred,
    VectorXd* x,
    MatrixXd* P);

  /**
   * Augment sigma points.
   */
  void AugmentedSigmaPoints(const VectorXd& x, const MatrixXd& P, MatrixXd* Xsig_out);
};

#endif /* UKF_H */

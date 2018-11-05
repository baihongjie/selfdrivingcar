#include "ukf.h"
#include "Eigen/Dense"
#include <iostream>

using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXd;
using std::vector;

int a = 0;
/**
 * Initializes Unscented Kalman filter
 */
UKF::UKF() {
  debug_ = false;

  is_initialized_ = false;
  // if this is false, laser measurements will be ignored (except during init)
  use_laser_ = true;

  // if this is false, radar measurements will be ignored (except during init)
  use_radar_ = true;

  n_x_ = 5;
  n_aug_ = 7;
  n_z_ = 3;
  lambda_ = 3 - n_aug_; 
  // initial state vector
  x_ = VectorXd(5);

  // initial covariance matrix
  P_ = MatrixXd(5, 5);
  P_ <<   1.0, 0.0, 0.0, 0.0, 0.0,
          0.0, 1.0, 0.0, 0.0, 0.0,
          0.0, 0.0, 1.0, 0.0, 0.0,
          0.0, 0.0, 0.0, 1.0, 0.0,
          0.0, 0.0, 0.0, 0.0, 1.0;
  //P_ *= 0.15;

  // Initialize weights.
  weights_ = VectorXd(2 * n_aug_ + 1);
  for (int i = 0; i < 2 * n_aug_ + 1; ++i) {
    if (i == 0) {
      weights_(i) = lambda_ / (lambda_ + n_aug_);
    } else {
      weights_(i) = 0.5 / (lambda_ + n_aug_);
    }
  }

  // Process noise standard deviation longitudinal acceleration in m/s^2
  std_a_ = 3;  // std_a_ = 30;
  // Process noise standard deviation yaw acceleration in rad/s^2
  std_yawdd_ = 0.5;  // std_yawdd_ = 30;

  // Laser measurement noise standard deviation position1 in m
  std_laspx_ = 0.15;

  // Laser measurement noise standard deviation position2 in m
  std_laspy_ = 0.15;

  // Radar measurement noise standard deviation radius in m
  std_radr_ = 0.3;

  // Radar measurement noise standard deviation angle in rad
  std_radphi_ = 0.03;  // std_radphi_ = 0.03;

  // Radar measurement noise standard deviation radius change in m/s
  std_radrd_ = 0.3;  // std_radrd_ = 0.3;
}

UKF::~UKF() {}

/**
 * @param {MeasurementPackage} meas_package The latest measurement data of
 * either radar or laser.
 */
void UKF::ProcessMeasurement(MeasurementPackage meas_package) {
  if (!is_initialized_) {
    is_initialized_ = true;
    if (meas_package.sensor_type_ == MeasurementPackage::RADAR) {
      float rho = meas_package.raw_measurements_[0]; 
      float phi = meas_package.raw_measurements_[1];
      float rho_dot = meas_package.raw_measurements_[2];
      float px = rho * cos(phi); 
      float py = rho * sin(phi);
      float vx = rho_dot * cos(phi);
      float vy = rho_dot * sin(phi);
      float v  = sqrt(vx * vx + vy * vy);
      x_ << px, py, v, 0, 0;
    } else if (meas_package.sensor_type_ == MeasurementPackage::LASER) {
      x_ << meas_package.raw_measurements_[0], meas_package.raw_measurements_[1], 0, 0, 0;
    }
    previous_timestamp_ = meas_package.timestamp_;
    return;
  }
  if ((use_laser_ && meas_package.sensor_type_ == MeasurementPackage::LASER) || 
      (use_radar_ && meas_package.sensor_type_ == MeasurementPackage::RADAR)) { 
    VectorXd z = meas_package.raw_measurements_;
    float delta_t = (meas_package.timestamp_ - previous_timestamp_) / 1000000.0;
    previous_timestamp_ = meas_package.timestamp_;

    MatrixXd Xsig_aug;
    if (debug_) {
      std::cout << "AugmentedSigmaPoints" << std::endl; 
    }
    AugmentedSigmaPoints(x_, P_, &Xsig_aug);
    MatrixXd Xsig_pred;
    if (debug_) {
      std::cout << "PredictSigmalPoint" << std::endl; 
    }
    PredictSigmalPoint(Xsig_aug, delta_t, &Xsig_pred);
    VectorXd z_pred;
    MatrixXd S;
    MatrixXd Zsig;
    if (debug_) {
      std::cout << "Prediction" << std::endl; 
    }
    PredictMeanCov(delta_t, meas_package.sensor_type_, Xsig_aug, Xsig_pred, &z_pred, &Zsig, &S, &x_, &P_);
    VectorXd x_out;
    if (debug_) {
      std::cout << "Update" << std::endl; 
    }
    Update(
        meas_package.sensor_type_,
        z,
        Xsig_pred,
        S,
        Zsig,
        z_pred,
        &x_,
        &P_);
  }
}

void UKF::PredictSigmalPoint(const MatrixXd& Xsig_aug, double delta_t, MatrixXd* Xsig_pred_out) {
  MatrixXd Xsig_pred(n_x_, 2 * n_aug_ + 1);

  //predict sigma points
  for (int i = 0; i < 2 * n_aug_ + 1; ++i) {
    double p_x = Xsig_aug(0, i);
    double p_y = Xsig_aug(1, i);
    double v = Xsig_aug(2, i);
    double yaw = Xsig_aug(3,i);
    double yawd = Xsig_aug(4,i);
    double nu_a = Xsig_aug(5,i);
    double nu_yawdd = Xsig_aug(6,i);
    //predicted state values
    double px_p, py_p;
    if (fabs(yawd) > 0.001) {
        px_p = p_x + v/yawd * ( sin (yaw + yawd*delta_t) - sin(yaw));
        py_p = p_y + v/yawd * ( cos(yaw) - cos(yaw+yawd*delta_t) );
    }
    else {
        px_p = p_x + v*delta_t*cos(yaw);
        py_p = p_y + v*delta_t*sin(yaw);
    }
    double v_p = v;
    double yaw_p = yaw + yawd*delta_t;
    double yawd_p = yawd;

    //add noise
    px_p = px_p + 0.5*nu_a*delta_t*delta_t * cos(yaw);
    py_p = py_p + 0.5*nu_a*delta_t*delta_t * sin(yaw);
    v_p = v_p + nu_a*delta_t;

    yaw_p = yaw_p + 0.5*nu_yawdd*delta_t*delta_t;
    yawd_p = yawd_p + nu_yawdd*delta_t;

    //write predicted sigma point into right column
    Xsig_pred(0,i) = px_p;
    Xsig_pred(1,i) = py_p;
    Xsig_pred(2,i) = v_p;
    Xsig_pred(3,i) = yaw_p;
    Xsig_pred(4,i) = yawd_p;
  }
  if (debug_) {
    std::cout << "Xsig_pred = " << std::endl << Xsig_pred << std::endl;
  }
  *Xsig_pred_out = Xsig_pred;
}

/**
 * Predicts sigma points, the state, and the state covariance matrix.
 * @param {double} delta_t the change in time (in seconds) between the last
 * measurement and this one.
 */
void UKF::PredictMeanCov(
    double delta_t,
    MeasurementPackage::SensorType sensor,
    const MatrixXd& Xsig_aug,
    const MatrixXd& Xsig_pred,
    VectorXd* z_out,
    MatrixXd* Zsig,
    MatrixXd* S_out,
    VectorXd* x,
    MatrixXd* P) {
  //create vector for predicted state
  x->fill(0.0);
  P->fill(0.0);
  //predict state mean
  for (int i = 0; i < 2 * n_aug_ + 1; ++i) {
    *x = *x + weights_(i) * Xsig_pred.col(i);
  }
  //predict state covariance matrix
  for (int i = 0; i < 2 * n_aug_ + 1; ++i) {
    VectorXd x_diff = Xsig_pred.col(i) - *x;
    //angle normalization
    while (x_diff(3)> M_PI) x_diff(3)-=2.*M_PI;
    while (x_diff(3)<-M_PI) x_diff(3)+=2.*M_PI;
    *P = *P + weights_(i) * x_diff * x_diff.transpose() ;
  }

  //////////PREDCICT MEASUREMENT
  //set measurement dimension, radar can measure r, phi, and r_dot
  //create matrix for sigma points in measurement space
  if (sensor == MeasurementPackage::RADAR) { 
    n_z_ = 3;
    *Zsig = MatrixXd::Zero(n_z_, 2 * n_aug_ + 1);
    //transform sigma points into measurement space
    for (int i = 0; i < 2 * n_aug_ + 1; i++) {  //2n+1 simga points

      // extract values for better readibility
      double p_x = Xsig_pred(0,i);
      double p_y = Xsig_pred(1,i);
      double v  = Xsig_pred(2,i);
      double yaw = Xsig_pred(3,i);

      double v1 = cos(yaw)*v;
      double v2 = sin(yaw)*v;

      // measurement model
      (*Zsig)(0,i) = sqrt(p_x*p_x + p_y*p_y);                        //r
      (*Zsig)(1,i) = atan2(p_y,p_x);                                 //phi
      (*Zsig)(2,i) = (p_x*v1 + p_y*v2 ) / sqrt(p_x*p_x + p_y*p_y);   //r_dot
    }
  } else {
    n_z_ = 2;
    *Zsig = Xsig_pred.block(0, 0, n_z_, 2*n_aug_+1);
  }

  //mean predicted measurement
  VectorXd z_pred = VectorXd(n_z_);
  z_pred.fill(0.0);
  for (int i = 0; i < 2 * n_aug_ + 1; i++) {
    z_pred = z_pred + weights_(i) * Zsig->col(i);
  }

  //innovation covariance matrix S
  MatrixXd S = MatrixXd(n_z_,n_z_);
  S.fill(0.0);
  for (int i = 0; i < 2 * n_aug_ + 1; i++) {  //2n+1 simga points
    //residual
    VectorXd z_diff = Zsig->col(i) - z_pred;

    //angle normalization
    while (z_diff(1)> M_PI) z_diff(1)-=2.*M_PI;
    while (z_diff(1)<-M_PI) z_diff(1)+=2.*M_PI;

    S = S + weights_(i) * z_diff * z_diff.transpose();
  }

  //add measurement noise covariance matrix
  MatrixXd R = MatrixXd(n_z_,n_z_);
  if (sensor == MeasurementPackage::RADAR) { 
    R << std_radr_*std_radr_, 0, 0,
         0, std_radphi_*std_radphi_, 0,
         0, 0,std_radrd_*std_radrd_;
  } else {
    R << std_laspx_*std_laspx_, 0,
         0, std_laspy_*std_laspy_;
  }
  S = S + R;

  /*******************************************************************************
   * Student part end
   ******************************************************************************/

  //print result
  if (debug_) {
    std::cout << "z_pred: " << std::endl << z_pred << std::endl;
    std::cout << "S: " << std::endl << S << std::endl;
    std::cout << "P_: " << std::endl << P_ << std::endl;
    std::cout << "Zsig: " << std::endl << *Zsig << std::endl;
  }

  //write result
  *z_out = z_pred;
  *S_out = S;
}

/**
 * Updates the state and the state covariance matrix using a radar/laser measurement.
 */
void UKF::Update(
    MeasurementPackage::SensorType sensor,
    const VectorXd& z,
    const MatrixXd& Xsig_pred,
    const MatrixXd& S,
    const MatrixXd& Zsig,
    const VectorXd& z_pred,
    VectorXd* x,
    MatrixXd* P) {
  //create matrix for cross correlation Tc
  MatrixXd Tc = MatrixXd(n_x_, n_z_);
  Tc.fill(0.0);

  //calculate cross correlation matrix
  for (int i = 0; i < 2 * n_aug_ + 1; i++) {
    //residual
    VectorXd z_diff = Zsig.col(i) - z_pred;
    //angle normalization
    while (z_diff(1)> M_PI) z_diff(1)-=2.*M_PI;
    while (z_diff(1)<-M_PI) z_diff(1)+=2.*M_PI;

    // state difference
    VectorXd x_diff = Xsig_pred.col(i) - *x;
    //angle normalization
    while (x_diff(3)> M_PI) x_diff(3)-=2.*M_PI;
    while (x_diff(3)<-M_PI) x_diff(3)+=2.*M_PI;

    Tc = Tc + weights_(i) * x_diff * z_diff.transpose();
  }
  //Kalman gain K;
  MatrixXd K = Tc * S.inverse();
  //residual
  VectorXd z_diff = z - z_pred;
  //angle normalization
  while (z_diff(1)> M_PI) z_diff(1)-=2.*M_PI;
  while (z_diff(1)<-M_PI) z_diff(1)+=2.*M_PI;
  if (debug_) {
    std::cout << "Tc: " << std::endl << Tc << std::endl;
    std::cout << "K: " << std::endl << K << std::endl;
    std::cout << "z_diff: " << std::endl << z_diff << std::endl;
    std::cout << "x: " << std::endl << *x<< std::endl;
  }

  //update state mean and covariance matrix
  *x = *x + K * z_diff;
  *P = *P - K*S*K.transpose();
  VectorXd NIS = z_diff.transpose() * S.inverse() * z_diff;
  //print result
  if (debug_) {
    std::cout << "Updated state x: " << *x << std::endl;
    std::cout << "Updated state covariance P: " << std::endl << *P << std::endl;
    if (sensor == MeasurementPackage::RADAR) {
      std::cout << "NIS RADAR: " << NIS << std::endl;
    } else {
      std::cout << "NIS LASER: " << NIS << std::endl;
    }
  }
}

void UKF::AugmentedSigmaPoints(const VectorXd& x, const MatrixXd& P, MatrixXd* Xsig_out) {
  //create augmented mean vector
  VectorXd x_aug = VectorXd(n_aug_);

  //create augmented state covariance
  MatrixXd P_aug = MatrixXd(n_aug_, n_aug_);

  //create sigma point matrix
  MatrixXd Xsig_aug = MatrixXd(n_aug_, 2 * n_aug_ + 1);

  //create augmented mean state
  x_aug.head(5) = x;
  x_aug(5) = 0;
  x_aug(6) = 0;
  //create augmented covariance matrix
  P_aug.fill(0.0);
  P_aug.topLeftCorner(5, 5) = P;
  P_aug(5, 5) = std_a_ * std_a_;
  P_aug(6, 6) = std_yawdd_ * std_yawdd_;

  //create square root matrix
  MatrixXd A_aug = P_aug.llt().matrixL();
  //create augmented sigma points
  Xsig_aug.col(0) = x_aug;
  for (int i = 0; i < n_aug_; ++i) {
      Xsig_aug.col(i+1) = x_aug + sqrt(lambda_ + n_aug_) * A_aug.col(i);
      Xsig_aug.col(i+1 + n_aug_) = x_aug - sqrt(lambda_ + n_aug_) * A_aug.col(i);
  }
  if (debug_) {
    std::cout << "Xsig_aug = " << std::endl << Xsig_aug << std::endl;
  }

  //write result
  *Xsig_out = Xsig_aug;
}

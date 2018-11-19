/*
 * particle_filter.cpp
 *
 *  Created on: Dec 12, 2016
 *      Author: Tiffany Huang
 */

#include <random>
#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <math.h> 
#include <iostream>
#include <sstream>
#include <string>
#include <iterator>

#include "particle_filter.h"

using namespace std;

void ParticleFilter::init(double x, double y, double theta, double std[]) {
  // Add random Gaussian noise to each particle.
  // NOTE: Consult particle_filter.h for more information about this method (and others in this file).
  if (is_initialized) return;

  num_particles = 200;

  normal_distribution<double> dist_x(x, std[0]);
  normal_distribution<double> dist_y(y, std[1]);
  normal_distribution<double> dist_theta(theta, std[2]);

  for (int i = 0; i < num_particles; ++i) {
    Particle p;
    p.x = dist_x(gen);
    p.y = dist_y(gen);
    p.theta = dist_theta(gen);
    p.weight = 1.0 / num_particles;
    particles.push_back(p);
  }
  is_initialized = true;
}

void ParticleFilter::prediction(double delta_t, double std[], double velocity, double yaw_rate) {
  // NOTE: When adding noise you may find std::normal_distribution and std::default_random_engine useful.
  //  http://en.cppreference.com/w/cpp/numeric/random/normal_distribution
  //  http://www.cplusplus.com/reference/random/default_random_engine/
  normal_distribution<double> dist_x(0, std[0]);
  normal_distribution<double> dist_y(0, std[1]);
  normal_distribution<double> dist_theta(0, std[2]);
  for (Particle& p : particles) {
    if (fabs(yaw_rate) > 0.001) {
      p.x += velocity / yaw_rate * (sin(p.theta + yaw_rate * delta_t) - sin(p.theta));
      p.y += velocity / yaw_rate * (cos(p.theta) - cos(p.theta + yaw_rate * delta_t));
      p.theta += yaw_rate * delta_t;
    } else {
      p.x += velocity * delta_t * cos(p.theta);
      p.y += velocity * delta_t * sin(p.theta);
    }
    std::normal_distribution<double> dist_x(p.x, std[0]);
    std::normal_distribution<double> dist_y(p.y, std[1]);
    std::normal_distribution<double> dist_theta(p.theta, std[2]);
    p.x = dist_x(gen);
    p.y = dist_y(gen);
    p.theta = dist_theta(gen);
  }

}

std::vector<LandmarkObs> ParticleFilter::dataAssociation(
    std::vector<LandmarkObs> predicted, std::vector<LandmarkObs>& observations) {
  // NOTE: this method will NOT be called by the grading code. But you will probably find it useful to 
  //   implement this method and use it as a helper during the updateWeights phase.
  vector<LandmarkObs> results;
  for (auto& obs: observations) {
    double minvalue = std::numeric_limits<double>::max();
    LandmarkObs min_landmark;
    for (const auto& pred: predicted) {
      double distance = dist(obs.x, obs.y, pred.x, pred.y);
      if (distance < minvalue) {
        minvalue = distance;
        min_landmark = pred;
      }
    }
    results.push_back(min_landmark);
  }
  return results;
}

void ParticleFilter::updateWeights(double sensor_range, double std_landmark[], 
    const std::vector<LandmarkObs> &observations, const Map &map_landmarks) {
  // NOTE: The observations are given in the VEHICLE'S coordinate system. Your particles are located
  //   according to the MAP'S coordinate system. You will need to transform between the two systems.
  //   Keep in mind that this transformation requires both rotation AND translation (but no scaling).
  //   The following is a good resource for the theory:
  //   https://www.willamette.edu/~gorr/classes/GeneralGraphics/Transforms/transforms2d.htm
  //   and the following is a good resource for the actual equation to implement (look at equation 
  //   3.33
  //   http://planning.cs.uiuc.edu/node99.html
  for(auto& p : particles) {
    // Transfrom to map space.
    std::vector<LandmarkObs> transformed_obs;
    for (const auto& observation: observations){
      LandmarkObs landmark;
      landmark.x = p.x + observation.x * cos(p.theta) - observation.y * sin(p.theta);
      landmark.y = p.y + observation.x * sin(p.theta) + observation.y * cos(p.theta);
      transformed_obs.push_back(landmark);
    }

    vector<LandmarkObs> predicted;
    for (const auto& l: map_landmarks.landmark_list){
      double distance = dist(p.x, p.y, l.x_f, l.y_f);
      if (distance < sensor_range) {
        LandmarkObs landmark;
        landmark.id = l.id_i;
        landmark.x = l.x_f;
        landmark.y = l.y_f;
        predicted.push_back(landmark);
      }
    }

    // Associate nearest nearest landmark.
    vector<LandmarkObs> associated_landmarks =
      dataAssociation(predicted, transformed_obs);

    // Compute probability and use it as weight.
    double probability = 1.0;
    for (int i = 0; i < associated_landmarks.size(); ++i){
      double dx = transformed_obs[i].x - associated_landmarks[i].x;
      double dy = transformed_obs[i].y - associated_landmarks[i].y;
      double sigma_x = std_landmark[0];
      double sigma_y = std_landmark[1];
      probability *= 1.0 / (2 * M_PI * sigma_x * sigma_y) * exp(-dx * dx / (2 * sigma_x * sigma_x)) * exp(-dy * dy / (2 * sigma_y * sigma_y));			
    }
    p.weight = probability;
  }
}

void ParticleFilter::resample() {
  // NOTE: You may find std::discrete_distribution helpful here.
  //   http://en.cppreference.com/w/cpp/numeric/random/discrete_distribution
  vector<float> weights;
  for (const auto& p : particles) {
    weights.push_back(p.weight);
  }
  std::discrete_distribution<float> d(weights.begin(), weights.end());
  vector<Particle> v;
  for(int n = 0; n < num_particles; ++n) {
    v.push_back(particles[d(gen)]);
  }
  particles = v;
}

Particle ParticleFilter::SetAssociations(Particle& particle, const std::vector<int>& associations, 
    const std::vector<double>& sense_x, const std::vector<double>& sense_y) {
  //particle: the particle to assign each listed association, and association's (x,y) world coordinates mapping to
  // associations: The landmark id that goes along with each listed association
  // sense_x: the associations x mapping already converted to world coordinates
  // sense_y: the associations y mapping already converted to world coordinates

  particle.associations= associations;
  particle.sense_x = sense_x;
  particle.sense_y = sense_y;
  return particle;
}

string ParticleFilter::getAssociations(Particle best) {
  vector<int> v = best.associations;
  stringstream ss;
  copy( v.begin(), v.end(), ostream_iterator<int>(ss, " "));
  string s = ss.str();
  s = s.substr(0, s.length()-1);  // get rid of the trailing space
  return s;
}

string ParticleFilter::getSenseX(Particle best) {
  vector<double> v = best.sense_x;
  stringstream ss;
  copy( v.begin(), v.end(), ostream_iterator<float>(ss, " "));
  string s = ss.str();
  s = s.substr(0, s.length()-1);  // get rid of the trailing space
  return s;
}

string ParticleFilter::getSenseY(Particle best) {
  vector<double> v = best.sense_y;
  stringstream ss;
  copy( v.begin(), v.end(), ostream_iterator<float>(ss, " "));
  string s = ss.str();
  s = s.substr(0, s.length()-1);  // get rid of the trailing space
  return s;
}

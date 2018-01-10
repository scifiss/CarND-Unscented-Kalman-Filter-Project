#include <iostream>
#include "tools.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {
  /**
  TODO:
    * Calculate the RMSE here.
  */
   VectorXd rmse(4);
  rmse << 0,0,0,0;  // for px, py, vx, vy components, should be at least < [.09, .10, .40, .30]

  //each component c has 1...n estimations,
  // a(i) = est(i) - truth(i)
  // rmse(c) = sqrt(  sum( a(1)^2+a(2)^2+...+a(n)^2 )/n  )

  // check the validation of inputs
  if (estimations.size() == 0
      || estimations.size() != ground_truth.size() )
  {

      cout << "Sizes of estimation and ground truth don't match or is zero." << endl;
      return rmse;
  }
  // squared sum of residuals for each of the n estimations
  for (unsigned int i=0; i< estimations.size(); i++)
  {
      // the ith data points, each has px, py, vx, vy components
      VectorXd residual = estimations[i] - ground_truth[i];
      // each estimation, ground truth, and residual
      residual = residual.array() * residual.array();
      rmse += residual;

  }
  // mean squared sum
  rmse = rmse/estimations.size();
  // root of each component
  rmse = rmse.array().sqrt();

  return rmse;
}

#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;

/*
A code demo that demonstrates how to perform quadratic
interpolation using Eigen library in C++. The code cons
tructs a Vandermonde matrix and solves for the coeffici
ents of the quadratic polynomial.
*/

int main() {
  // Given coordinates (x, y)
  std::vector<double> x = {1.0, 2.0, 3.0};
  std::vector<double> y = {3.0, 6.0, 5.0};

  int n = x.size(); // Number of data points

  // Construct the Vandermonde matrix
  MatrixXd A(n, 3);
  for (int i = 0; i < n; ++i) {
    A(i, 0) = x[i] * x[i];
    A(i, 1) = x[i];
    A(i, 2) = 1.0;
  }

  // Create a vector for the y-values
  VectorXd b(n);
  for (int i = 0; i < n; ++i) {
    b(i) = y[i];
  }

  // Solve the linear system for the coefficients
  Vector3d coeffs = A.colPivHouseholderQr().solve(b); 

  // Display the quadratic polynomial coefficients
  std::cout << "Quadratic Polynomial Coefficients: " << std::endl;
  std::cout << "a: " << coeffs(0) << ", b: " << coeffs(1) << ", c: " << coeffs(2) << std::endl;

  return 0;
} 
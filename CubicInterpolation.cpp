#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;

/*
Code demo that demonstrates how to perform cubic interp
olation using Eigen library in C++. The code constructs
 a Vandermonde matrix, solves for the coefficients of t
he cubic polynomial, and then utilizes those coefficien
ts to create an interpolating function to obtain interp
olated values. 
*/

double interpolateCubic(const Vector4d& coeffs, double x) {
  double result = coeffs(0) * x * x * x + coeffs(1) * x * x + coeffs(2) * x + coeffs(3);
  return result;
}

int main() {
  // Given coordinates (x, y)
  std::vector<double> x = {1.0, 2.0, 3.0, 4.0};
  std::vector<double> y = {3.0, 6.0, 5.0, 2.0};

  int n = x.size(); // Number of data points

  // Construct the Vandermonde matrix
  MatrixXd A(n, 4);
  for (int i = 0; i < n; ++i) {
    A(i, 0) = x[i] * x[i] * x[i];
    A(i, 1) = x[i] * x[i];
    A(i, 2) = x[i];
    A(i, 3) = 1.0;
  }

  // Create a vector for the y-values
  VectorXd b(n);
  for (int i = 0; i < n; ++i) {
    b(i) = y[i];
  }

  // Solve the linear system for the coefficients
  Vector4d coeffs = A.colPivHouseholderQr().solve(b);

  // Display the cubic polynomial coefficients
  std::cout << "Cubic Polynomial Coefficients: " << std::endl;
  std::cout << "a: " << coeffs(0) << ", b: " << coeffs(1) << ", c: " 
        << coeffs(2) << ", d: " << coeffs(3) << std::endl; 

  // Interpolate using the obtained coefficients
  double interpolatedValue = interpolateCubic(coeffs, 2.5);

  // Display the interpolated value
  std::cout << "Interpolated value at x = 2.5: " << interpolatedValue << std::endl;

  return 0;
} 
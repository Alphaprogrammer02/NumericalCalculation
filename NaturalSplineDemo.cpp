#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;

/*
A basic implementation of the Natural Spline algorithm
using the Eigen library for linear algebra operations.

NaturalSplineInterpolation function takes two VectorXd
objects x and y as inputs, representing the x and y coo
rdinates of the sample points, respectively. The functi
on calculates the coefficients (a, b, c, and d) for eac
h spline segment and prints them.
*/ 

void NaturalSplineInterpolation(const VectorXd& x, const VectorXd& y)
{
    int n = x.size();
    VectorXd h = x.segment(1, n - 1) - x.segment(0, n - 1);
    VectorXd alpha(n - 2), l(n - 2), mu(n - 2), z(n - 2);
    MatrixXd A(n - 2, n - 2);

    for (int i = 0; i < n - 2; ++i) {
        alpha(i) = 3.0 * (y(i + 2) - y(i + 1)) / h(i + 1) - 3.0 * (y(i + 1) - y(i)) / h(i);
    }

    l(0) = 1.0;
    mu(0) = 0.0;
    z(0) = 0.0;

    for (int i = 1; i < n - 2; ++i) {
        l(i) = 2.0 * (x(i + 1) - x(i - 1)) - h(i - 1) * mu(i - 1);
        mu(i) = h(i) / l(i);
        z(i) = (alpha(i - 1) - h(i - 1) * z(i - 1)) / l(i);
    }

    VectorXd c(n);
    c(0) = 0.0;
    c(n - 1) = 0.0;

    for (int j = n - 3; j >= 0; --j) {
        c(j + 1) = z(j) - mu(j) * c(j + 2);
    }

    VectorXd b(n - 1), d(n - 1);

    for (int k = 0; k < n - 1; ++k) {
        b(k) = (y(k + 1) - y(k)) / h(k) - h(k) * (c(k + 1) + 2.0 * c(k)) / 3.0;
        d(k) = (c(k + 1) - c(k)) / (3.0 * h(k));
    }

    std::cout << "Natural Spline Interpolation Coefficients:\n";
    for (int i = 0; i < n - 1; ++i) {
        std::cout << "Segment " << i + 1 << ": ";
        std::cout << "a = " << y(i) << ", b = " << b(i) << ", c = " << c(i) << ", d = " << d(i) << "\n";
    }
}

int main()
{
    // Test data
    VectorXd x(10);
    VectorXd y(10);

    // Populate test data (x and y coordinates)
    x << 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0;
    y << 0.0, 2.0, 1.0, 4.0, 3.0, 6.0, 5.0, 8.0, 7.0, 10.0;

    // Perform Natural Spline Interpolation
    NaturalSplineInterpolation(x, y);

    return 0;
} 
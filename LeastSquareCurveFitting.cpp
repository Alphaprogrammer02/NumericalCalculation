#include <iostream>
#include <vector>
#include <cmath>
#include <Eigen/Dense>

using namespace Eigen;

/*
Illuminated by:     "Curve fitting using least square" by Shiliang Xu 
Book:               collection of commonly used algorithmic programs  
Publisher:          Tsinghua University Press 
Version:            6th
Publication Date:   May 2019
Date:               Sep. 24 2023 
*/

/*
Implementation of a least square fitting algorithm that
 fits a user-specified cubic polynomial function to a s
et of input samples. 

In this code, a user-specified cubic polynomial functio
n f(x) = ax^3 + bx^2 + c*x + d is used for the least sq
uare fitting. The leastSquareFitting function takes the
 number of samples (n), the order of the polynomial (m)
, and the x and y coordinates of the input samples as a
rguments.

The function constructs the matrices A and b, where A r
epresents the Vandermonde matrix and b represents the v
ector of y-coordinates. It then solves the least square
 problem by performing QR decomposition and obtaining t
he coefficients of the fitted polynomial. Finally, the 
resulting coefficients are printed. 
*/ 

// Function to perform least square fitting
void leastSquareFitting(int n, int m, const std::vector<double>& x, const std::vector<double>& y) {
    // Check if the number of samples and polynomial order are valid
    if (n <= m || m < 0) {
        std::cout << "Invalid input: n should be greater than m and m should be non-negative." << std::endl;
        return;
    }

    // Create the matrices A and b for the least square problem
    MatrixXd A(n, m + 1);
    VectorXd b(n);
    
    // Populate the matrices A and b
    for (int i = 0; i < n; i++) {
        double xi = x[i];
        double yi = y[i];
        for (int j = 0; j <= m; j++) {
            A(i, j) = std::pow(xi, j);
        }
        b(i) = yi;
    }

    // Solve the least square problem using QR decomposition
    VectorXd coefficients = A.householderQr().solve(b);

    // Print the resulting coefficients
    std::cout << "Coefficients of the fitted polynomial: ";
    for (int j = m; j >= 0; j--) {
        std::cout << coefficients(j);
        if (j > 0) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

int main() {
    int n = 5; // Number of samples
    int m = 3; // Polynomial order
    
    std::vector<double> x = {1.0, 2.0, 3.0, 4.0, 5.0}; // x-coordinates of input samples
    std::vector<double> y = {5.0, 12.0, 25.0, 42.0, 65.0}; // y-coordinates of input samples

    leastSquareFitting(n, m, x, y);

    return 0;
} 
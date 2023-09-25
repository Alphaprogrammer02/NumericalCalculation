#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;

/*
Example script that uses the Eigen library to apply the
 Cholesky decomposition for solving a least square fitt
ing problem. The script also includes an evaluation of
the fitting performance using the mean squared error (M
SE). 

By utilizing the Cholesky decomposition, we can efficie
ntly solve the normal equations in the least square fit
ting problem, leading to an optimal solution for the pa
rameter vector x.

This approach avoids the direct computation of the inve
rse of A^T A and provides a numerically stable solution
. It is particularly beneficial when dealing with large
 systems of equations or when solving the least square
problem iteratively. 
*/ 

int main() {
    // Define the observed data points
    VectorXd b(10);
    b << 1.2, 2.1, 3.3, 4.0, 5.2, 6.1, 7.5, 8.0, 9.1, 10.2;

    // Define the matrix of coefficients
    MatrixXd A(10, 2);
    A << 1.0, 1.0,
         1.0, 2.0,
         1.0, 3.0,
         1.0, 4.0,
         1.0, 5.0,
         1.0, 6.0,
         1.0, 7.0,
         1.0, 8.0,
         1.0, 9.0,
         1.0, 10.0;

    // Compute the Cholesky decomposition of A^T A
    MatrixXd ATA = A.transpose() * A;
    LLT<MatrixXd> llt(ATA);

    // Check if decomposition is successful
    if (llt.info() != Success) {
        std::cout << "Cholesky decomposition failed!" << std::endl;
        return 1;
    }

    // Solve the linear system A^T A x = A^T b using Cholesky decomposition
    VectorXd x = llt.solve(A.transpose() * b);

    // Compute the fitted values
    VectorXd fitted = A * x;

    // Compute the mean squared error
    double mse = (b - fitted).squaredNorm() / b.size();

    // Print the results
    std::cout << "Fitted parameters (x):" << std::endl;
    std::cout << x << std::endl;
    std::cout << "Mean Squared Error (MSE): " << mse << std::endl;

    return 0;
} 
#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;

/*
Illuminated by:     "Multi-variable linear regression analysis" by Shiliang Xu 
Book:               collection of commonly used algorithmic programs  
Publisher:          Tsinghua University Press
Version:            6th
Publication Date:   May 2019
Date:               Sep. 05 2023
*/ 
/*
An improved version that can solve a multi-variate line
ar regression problem with x having a shape of (m, 4).
The evaluation of the fitting performance is also inclu
ded, using the mean squared error (MSE). 
*/

int main() {
    // Define the observed data points
    VectorXd b(5);
    b << 10.1, 10.2, 10.0, 10.1, 10.0; 

    // Define the matrix of coefficients
    MatrixXd A(5, 4); 
    A << 0.0, 1.1, 2.0, 3.2,
         1.0, 1.0, 3.0, 3.2, 
         2.0, 1.2, 1.8, 3.0, 
         3.0, 1.1, 1.9, 2.9, 
         4.0, 0.0, 2.1, 2.9; 
         

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
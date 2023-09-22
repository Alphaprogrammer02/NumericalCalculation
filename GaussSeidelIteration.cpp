#include <iostream>
#include <Eigen/Dense>

/*
Illuminated by:     "Solving systems of linear equations by Gauss-Seidel 
                     iteration" by Shiliang Xu 
Book:               A collection of commonly used algorithmic programs 
Publisher:          Tsinghua University Press 
Version:            6th 
Publication Date:   May 2019
Date:               Sep. 21 2023  
*/ 
/*
The Gauss-Seidel iteration method has several advantage
s:

- It can converge faster than the Jacobi iteration meth
od for certain types of systems.
- It can be used for both diagonally dominant and non-d
iagonally dominant systems.
- It can handle systems with a mix of positive and nega
tive coefficients.

However, there are also some limitations:

- It may not converge for some systems, especially if t
he matrix A is not diagonally dominant.
- It may converge slowly or oscillate for systems with 
eigenvalues close to 0 or with ill-conditioned matrices
.

The Gauss-Seidel iteration method is commonly used in n
umerical methods, scientific computing, and engineering
 applications where solving systems of linear equations
 is required. It provides an iterative approach to find
 approximate solutions to these systems, even for large
 and complex systems.

It's important to note that there are other methods ava
ilable for solving linear systems, such as Gaussian eli
mination, LU decomposition, and conjugate gradient meth
od. 
*/


int main() 
{
    Eigen::MatrixXd A(4, 4); // Square matrix A
    Eigen::VectorXd b(4);    // Vector b

    // Initialize matrix A and vector b with appropriate values
    A << 7,  2,  1, -2, 
         9,  15, 3, -2,
         -2, -2, 11, 5,
         1,  3,  2, 13; 

    b << 4, 7, -1, 0; 

    Eigen::VectorXd x(4); // Vector x (unknowns)

    // Gauss-Seidel iteration
    int maxIterations = 100;
    double tolerance = 1e-6;
    int iterations = 0;
    double error = tolerance + 1;

    while (error > tolerance && iterations < maxIterations) {
        Eigen::VectorXd x_new = x; 
        for (int i = 0; i < A.rows(); ++i) {
            double sum = 0.0;

            for (int j = 0; j < A.cols(); ++j) {
                if (j != i) {
                    sum += A(i, j) * x(j);
                }
            }
            x_new(i) = (b(i) - sum) / A(i, i);
        } 
        error = (x_new - x).norm();
        x = x_new;
        iterations++;
    }

    // Print the solution
    std::cout << "Solution:\n";
    std::cout << x << "\n";

    return 0;
} 
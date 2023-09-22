#include <iostream>
#include <Eigen/Dense>

/*
Illuminated by:     "Solve pathological or ill-conditioned systems of equations" 
                     by Shiliang Xu 
Book:               collection of commonly used algorithmic programs  
Publisher:          Tsinghua University Press
Version:            6th
Publication Date:   May 2019
Date:               Sep. 22 2023
*/

/*
The expression A.colPivHouseholderQr().solve(b) in Eige
n allows us to solve a system of equations, even when t
he system is pathological or ill-conditioned. Let's bre
ak down the steps and understand how it works:

1. A.colPivHouseholderQr(): This performs a QR decompos
ition of matrix A using the column-pivoting variant of 
the Householder QR factorization. The QR decomposition 
decomposes matrix A into the product of an orthogonal m
atrix Q and an upper triangular matrix R, such that A =
 QR. The column pivoting ensures stability and reliabil
ity, especially in the presence of highly correlated or
 nearly dependent columns in matrix A.

2. .solve(b): This method solves the system of equation
s using the QR decomposition computed in the previous s
tep. It takes the right-hand side vector b and efficien
tly computes the solution vector x that satisfies the e
quation Ax = b.

Eigen's QR decomposition with the column-pivoting varia
nt is particularly useful for solving pathological or i
ll-conditioned systems of equations. A system is consid
ered pathological when it exhibits one or more of the f
ollowing characteristics:

- Highly correlated or nearly dependent columns in the 
coefficient matrix A.
- Small or zero eigenvalues, which can cause numerical 
instability.
- Large condition number, indicating sensitivity to sma
ll changes in the input.

The column pivoting technique helps in handling these s
ituations by rearranging the columns of matrix A during
 the decomposition to ensure stability and accurate sol
utions, even when the system is pathological.

By using A.colPivHouseholderQr().solve(b), Eigen's QR d
ecomposition with column pivoting is applied to solve t
he system of equations in a robust and efficient manner
, providing reliable solutions even in challenging scen
arios.

It's important to note that while column pivoting can i
mprove stability, it cannot overcome fundamental issues
 like rank deficiency or singularities in the system. I
n such cases, additional considerations or techniques m
ay be required to handle the specific problems associat
ed with the system.
*/
/*
The expression residual.lpNorm<Eigen::Infinity>() calcu
lates the maximum norm (also known as the L-infinity no
rm or the supremum norm) of the residual vector.

The L-infinity norm of a vector is defined as the maxim
um absolute value among its elements. It represents the
 magnitude of the largest component in the vector. Math
ematically, for a vector v with elements v1, v2, ..., v
n, the L-infinity norm is given by:

||v||<sub>∞</sub> = max(|v1|, |v2|, ..., |vn|) 

By obtaining the L-infinity norm, you can assess the ma
ximum error between the predicted values (obtained by m
ultiplying matrix A with the solution vector x) and the
 actual right-hand side values in the system of equatio
ns.
*/


void evaluateSolutionError(const Eigen::MatrixXd& A, const Eigen::VectorXd& x, const Eigen::VectorXd& b) {
    // Calculate the residual vector
    Eigen::VectorXd residual = A * x - b;

    // Calculate the error norms
    double l2Norm = residual.norm();     // L2 norm
    double maxNorm = residual.lpNorm<Eigen::Infinity>();   // Maximum norm

    // Print the error norms
    std::cout << "Error Norms:\n";
    std::cout << "L2 Norm: " << l2Norm << std::endl;
    std::cout << "Maximum Norm: " << maxNorm << std::endl;
} 


int main() {
    // Define the matrix A and vector b of the system of equations
    Eigen::MatrixXd A(5, 5);
    Eigen::VectorXd b(5);

    // Assign values to matrix A and vector b
    A << 1.0, 0.5, 0.33333, 0.25, 0.2, 
         0.5, 0.33333, 0.25, 0.20, 0.16667, 
         0.33333, 0.25, 0.20, 0.16667, 0.14286, 
         0.25, 0.20, 0.16667, 0.14286, 0.125, 
         0.20, 0.16667, 0.142857, 0.125, 0.11111; 
    b << 1, 0, 0, 0, 1; 

    // Solve the system of equations
    Eigen::VectorXd x = A.colPivHouseholderQr().solve(b);

    // Print the solution
    std::cout << "Solution x:\n" << x << std::endl;

    // Evaluate the solution error 
    evaluateSolutionError(A, x, b); 

    return 0;
} 
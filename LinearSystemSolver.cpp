#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;

/*
Illuminated by:     "Solve a system of linear equations of order n " by Shiliang Xu 
Book:               A collection of commonly used algorithmic programs 
Publisher:          Tsinghua University Press 
Version:            6th 
Publication Date:   May 2019
Date:               Sep. 04 2023  
*/

/*
The function definition VectorXd solveLinearSystem(cons
t MatrixXd& A, const VectorXd& b) allows you to pass da
ta entries of int, float, and double types into the fun
ction. In the Eigen library, the MatrixXd class represe
nts a matrix of arbitrary dimension with entries of typ
e double. Similarly, the VectorXd class represents a ve
ctor of arbitrary dimension with entries of type double
.
*/
/*
Keep in mind that the Eigen library provides a wide ran
ge of functionality for linear algebra operations. Some
 commonly used member functions for matrices include tr
anspose(), inverse(), determinant(), and various matrix
 decompositions such as lu(), qr(), and svd(). For vect
ors, common member functions include norm(), dot(), and
 cross(). Consulting the documentation or using code co
mpletion in your IDE/editor will provide you with detai
led information about the available member functions an
d data members specific to the Eigen library. 
*/


// Function to solve the system of linear equations Ax = b
VectorXd solveLinearSystem(const MatrixXd& A, const VectorXd& b) {
    // Check if the matrix A is invertible
    if (A.determinant() == 0) {
        std::cerr << "Error: Matrix A is not invertible. Unable to solve the system." << std::endl;
        return VectorXd();
    }
    
    // Solve the linear system Ax = b using LU decomposition
    VectorXd x = A.lu().solve(b);
    return x;
}

int main() {
    // Example usage
    MatrixXd A(3, 3);  // Define the coefficient matrix A
    VectorXd b(3);    // Define the constant vector b

    // Assign values to the coefficient matrix A
    A <<  2,  1, -1,
         -3, -1,  2,
         -2,  1,  2;

    // Assign values to the constant vector b
    b << 8, -11, -3;

    // Solve the linear system Ax = b
    VectorXd x = solveLinearSystem(A, b);

    // Print the solution
    std::cout << "Solution: x = \n" << x << std::endl;

    MatrixXd B(4, 4);  // Define the coefficient matrix A
    VectorXd b2(4);    // Define the constant vector b

    // Assign values to the coefficient matrix A
    B <<  0.2368,  0.2471,  0.2568,  1.2671,
          0.1968,  0.2071,  1.2168,  0.2271,
          0.1581,  1.1675,  0.1768,  0.1871,
          1.1161,  0.1254,  0.1397,  0.1490;

    // Assign values to the constant vector b
    b2 << 1.8471, 1.7471, 1.6471, 1.5471; 

    // Solve the linear system Ax = b
    VectorXd x2 = solveLinearSystem(B, b2);

    // Print the solution
    std::cout << "Solution: x = \n" << x2 << std::endl; 

    return 0;
} 
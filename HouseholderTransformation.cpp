#include <iostream>
#include <Eigen/Core>
#include <Eigen/QR> 

using namespace Eigen; 

/*
Illuminated by:     "Householder Transformation" by Shiliang Xu 
Book:               A collection of commonly used algorithmic programs 
Publisher:          Tsinghua University Press 
Version:            6th 
Publication Date:   May 2019
Date:               Sep. 03 2023  
*/

void applyHouseholderTransformation(const VectorXd& x, const VectorXd& v, VectorXd& y)
{
    HouseholderQR<MatrixXd> qr(x.size(), v.size());
    // Set Q to identity 
    MatrixXd Q = MatrixXd::Identity(x.size(), x.size());
  
    Q.applyOnTheLeft(v);

    y = Q * x.asDiagonal();  
}

int main()
{
    // Define the vector x and the Householder vector v
    VectorXd x(4);
    x << 1, 2, 3, 4; 

    VectorXd v(4);
    v << 1, 1, 1, 1;

    HouseholderQR<MatrixXd> qr(x.size(), v.size());
  
    MatrixXd Q = MatrixXd::Identity(x.size(), x.size());

    // Calculate the reflected vector y
    VectorXd y;
    applyHouseholderTransformation(x, v, y);

    // Print the results
    std::cout << "x: " << x.transpose() << std::endl;
    std::cout << "v: " << v.transpose() << std::endl;
    std::cout << "H:\n" << Q << std::endl; 
    std::cout << "y: " << y.transpose() << std::endl;

    return 0;
} 
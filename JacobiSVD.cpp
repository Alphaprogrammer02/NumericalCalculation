#include <iostream>
#include <Eigen/Dense>

/*
Illuminated by:     "SVD of a square matrix" by Shiliang Xu 
Book:               collection of commonly used algorithmic programs  
Publisher:          Tsinghua University Press
Version:            6th
Publication Date:   May 2019
Date:               Sep. 02 2023
*/

void setSmallValuesToZero(Eigen::MatrixXd& matrix, double epsilon) {
  for (int i = 0; i < matrix.rows(); ++i) {
    for (int j = 0; j < matrix.cols(); ++j) {
      if (std::abs(matrix(i, j)) < epsilon) {
        matrix(i, j) = 0.0;
      }
    }
  }
}

int main() {

  // Input matrix
  int numRows = 3;
  int numCols = 3;
  Eigen::MatrixXf inputMatrix(numRows, numCols);
  inputMatrix << 58, 35, 83, 
                 89, 13, 18,
                 58, 32, 52; 

  std::cout << "Input Matrix:\n" << inputMatrix << std::endl;

  // SVD decomposition
  // Decompose input matrix into U, singular values, V
  Eigen::JacobiSVD<Eigen::MatrixXf> svd(inputMatrix, Eigen::ComputeThinU | Eigen::ComputeThinV);
  Eigen::MatrixXf Umatrix = svd.matrixU();
  Eigen::MatrixXf Vmatrix = svd.matrixV();
  Eigen::VectorXf singularValuesVector = svd.singularValues();

  std::cout << "U Matrix:\n" << Umatrix << std::endl;
  std::cout << "Singular Values:\n" << singularValuesVector << std::endl;
  std::cout << "V Matrix:\n" << Vmatrix << std::endl;

  // Verify orthogonality of U and V
  // U^T * U and V^T * V should be identity matrices
  double epsilon = 0.000001;
  Eigen::MatrixXd U_double = Umatrix.cast<double>();  
  Eigen::MatrixXd UUt = U_double * U_double.transpose();
  setSmallValuesToZero(UUt, epsilon);
  std::cout << "U * U^T:\n" << UUt << std::endl;
    
  Eigen::MatrixXd V_double = Vmatrix.cast<double>();  
  Eigen::MatrixXd VVt = V_double * V_double.transpose();
  setSmallValuesToZero(VVt, epsilon); 
  std::cout << "V * V^T:\n" << VVt << std::endl;

  // Reconstruct input matrix
  // A = U * Σ * V^T
  Eigen::MatrixXf reconstructedA = Umatrix * singularValuesVector.asDiagonal() * Vmatrix.transpose();
  std::cout << "Reconstructed A:\n" << reconstructedA << std::endl;

  return 0;
} 
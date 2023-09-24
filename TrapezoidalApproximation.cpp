#include <iostream>
#include <functional>
#include <cmath>

/*
Perform the trapezoidal rule to approximate the integra
l of the given function.
*/ 

// Function to perform trapezoidal approximation for numerical integration
double trapezoidalApproximation(std::function<double(double)> f, double a, double b, double tol = 0.00001) {
    double h = b - a;
    double integral = (f(a) + f(b)) / 2.0;
    double previousIntegral = integral;
    double n = 1.0;
    
    do {
        previousIntegral = integral;
        integral = 0.0;
        
        for (double i = 0.0; i < n; i++) {
            double x = a + i * h;
            integral += f(x);
        }
        
        integral *= h;
        
        n *= 2.0;
        h /= 2.0;
        
    } while (std::abs(integral - previousIntegral) > tol);
    
    return integral;
}

int main() {
    // Example usage: integrating the function f(x) = sin(x) + exp(x) from 0 to 1
    double integral = trapezoidalApproximation([](double x) { return std::sin(x) + std::exp(x); }, 0.0, 1.0);

    std::cout << "Approximated integral: " << integral << std::endl;

    return 0;
}  
#include <iostream>
#include <gsl/gsl_interp.h>
#include <gsl/gsl_spline.h>

/*
The code demonstrates the principle of Hermite interpol
ation using the GSL (GNU Scientific Library) in C++. He
rmite interpolation is a method for estimating function
 values and derivatives between given data points. The
code provides a step-by-step implementation of Hermite
interpolation using the GSL library.

It can be customized by modifying the data points, func
tion values, derivatives, and evaluation point accordin
g to specific requirements.
*/ 

/*
compilation command: 
g++ -std=c++17 HemiteInterpolation.cpp -o HemiteInterpolation -L/usr/local/lib/libgsl.so.27 -lgsl -lgslcblas -lm 
*/ 

int main() {
    // Define the data points and their corresponding function values
    double x[] = {0.0, 1.0, 2.0, 3.0, 4.0};
    double y[] = {1.0, 2.0, 1.0, 0.0, 1.0};

    // Define the derivatives at the data points
    double dy[] = {0.0, 1.0, -1.0, 0.0, 0.0};

    // Number of data points
    size_t n = sizeof(x) / sizeof(x[0]);

    // Allocate memory for the interpolation
    gsl_interp_accel *accelerator = gsl_interp_accel_alloc();
    gsl_spline *spline = gsl_spline_alloc(gsl_interp_cspline, n);

    // Initialize the interpolation
    gsl_spline_init(spline, x, y, n);

    // Evaluate the interpolated function at desired points
    double xi = 1.5; // Example evaluation point
    double yi = gsl_spline_eval(spline, xi, accelerator);

    std::cout << "Interpolated value at x = " << xi << " is y = " << yi << std::endl;

    // Evaluate the derivative of the interpolated function at desired points
    double dyi = gsl_spline_eval_deriv(spline, xi, accelerator);

    std::cout << "Derivative at x = " << xi << " is dy/dx = " << dyi << std::endl;

    // Free allocated memory
    gsl_spline_free(spline);
    gsl_interp_accel_free(accelerator);

    return 0;
} 
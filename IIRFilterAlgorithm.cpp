#include <iostream>
#include <fstream>
#include <vector> 

/*
Illuminated by:     "FIR and IIR Filter" by Robert Johanssan  
Book:               Numerical Python: Scientific Computing and Data Science 
Publisher:          Tsinghua University Press
Version:            2nd 
Publication Date:   June 2020  
Date:               Sep. 07 2023 
*/ 
/*
Demonstrate the implementation of a low-pass Infinite I
mpulse Response (IIR) filter. The IIR filter is designe
d to allow frequencies up to 100 Hz to pass through whi
le filtering out higher frequencies.

The algorithm follows these steps:

- The IIR filter coefficients (b0, b1, a1) are defined
as constants.
- The applyIIRFilter function takes an input signal as
a vector and applies the IIR filter to it.
- Inside applyIIRFilter, the filter's difference equati
on is implemented using a loop, where each input sample
 is processed to calculate the corresponding output sam
ple.
- The filtered output signal is stored in a vector and
returned.
- In the main function, the input signal is read from a
 file named "signals.txt".
- The applyIIRFilter function is called to filter the i
nput signal and obtain the filtered output signal.
- The filtered output signal is written to a file named
 "filtered_signals.txt".

The algorithm can be customized by modifying the filter
 coefficients (b0, b1, a1) to achieve different filter
characteristics or cutoff frequencies. Additionally, th
e input signal can be provided through the "signals.txt
" file, and the filtered output signal will be written
to the "filtered_signals.txt" file.
*/ 

// IIR Filter Coefficients
const double b0 = 0.000585;  // Coefficient for current input sample
const double b1 = 0.001169;  // Coefficient for previous input sample
const double a1 = -1.734725; // Coefficient for previous output sample

// Function to apply the IIR filter to input signal
std::vector<double> applyIIRFilter(const std::vector<double>& inputSignal) {
    std::vector<double> outputSignal;
    double prevInput = 0.0;
    double prevOutput = 0.0;

    for (const auto& input : inputSignal) {
        // Apply IIR filter difference equation
        double output = b0 * input + b1 * prevInput - a1 * prevOutput;

        // Store the filtered output
        outputSignal.push_back(output);

        // Update previous input and output samples
        prevInput = input;
        prevOutput = output;
    }

    return outputSignal;
}

int main() {
    std::ifstream inputFile("./data/signals.txt");
    std::ofstream outputFile("./data/filtered_signals.txt");

    if (!inputFile) {
        std::cout << "Failed to open input file." << std::endl;
        return 1;
    }

    if (!outputFile) {
        std::cout << "Failed to open output file." << std::endl;
        return 1;
    }

    std::vector<double> inputSignal;
    double sample;

    // Read input signal from file
    while (inputFile >> sample) {
        inputSignal.push_back(sample);
    }

    // Apply the IIR filter to the input signal
    std::vector<double> filteredSignal = applyIIRFilter(inputSignal);

    // Write the filtered signal to the output file
    for (const auto& sample : filteredSignal) {
        outputFile << sample << std::endl;
    }

    std::cout << "Filtering completed. Filtered signal written to filtered_signals.txt" << std::endl;

    return 0;
}
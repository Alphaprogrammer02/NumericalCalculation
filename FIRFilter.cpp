#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <Eigen/Dense> 

using namespace Eigen;

/*
Illuminated by:     "FIR and IIR Filter" by Robert Johanssan  
Book:               Numerical Python: Scientific Computing and Data Science 
Publisher:          Tsinghua University Press
Version:            2nd 
Publication Date:   June 2020  
Date:               Sep. 05 2023
*/  
/*
The script enables the processing of a discrete signal
stored in a CSV file through a Finite Impulse Response
(FIR) algorithm. The script offers the flexibility for
users to adjust the parameters and achieve a low-pass f
iltering effect. By default, the cutoff frequency is se
t to 10Hz, allowing frequencies equal to or below 10Hz
to pass through the filter while filtering out frequenc
ies above this threshold. The script reads the input da
ta from a CSV file, applies the FIR low-pass filter to
the data, and writes the filtered signal to another CSV
 file. This allows users to transform the original sign
al, effectively reducing high-frequency noise and focus
ing on the desired low-frequency components. The result
ing filtered data can be further analyzed or visualized
 for subsequent signal processing or analysis tasks.
*/

// Function to read data from a CSV file
std::vector<double> readCSV(const std::string& filename) {
    std::vector<double> data;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file: " << filename << std::endl;
        return data;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        while (std::getline(ss, cell, ',')) {
            data.push_back(std::stod(cell));
        }
    }

    file.close();
    return data;
}

// Function to write data to a CSV file
void writeCSV(const std::string& filename, const std::vector<double>& data) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file: " << filename << std::endl;
        return;
    }

    for (const auto& value : data) {
        file << value << std::endl;
    }

    file.close();
}

// Function to apply an FIR low-pass filter
std::vector<double> applyFIRLowPassFilter(const std::vector<double>& data, double cutoffFrequency, double samplingRate) {
    int numSamples = data.size();
    std::vector<double> filteredData(numSamples);

    // Compute the filter coefficients
    int filterOrder = static_cast<int>(std::ceil(0.45 * samplingRate / cutoffFrequency));
    std::vector<double> filterCoefficients(filterOrder + 1, 1.0 / (filterOrder + 1));

    // Apply the filter
    for (int i = 0; i < numSamples; ++i) {
        for (int j = 0; j <= filterOrder; ++j) {
            if (i - j >= 0) {
                filteredData[i] += filterCoefficients[j] * data[i - j];
            }
        }
    }

    return filteredData;
}

int main() {
    std::string inputFilename = "./data/signals.csv";
    std::string outputFilename = "./data/output.csv"; 
    double cutoffFrequency = 10.0;  // Default cutoff frequency in Hz
    double samplingRate = 1000.0;   // Default sampling rate in Hz

    // Read data from the input CSV file
    std::vector<double> inputData = readCSV(inputFilename);
    if (inputData.empty()) {
        return 1;
    }

    // Apply the FIR low-pass filter
    std::vector<double> filteredData = applyFIRLowPassFilter(inputData, cutoffFrequency, samplingRate);

    // Write the filtered data to the output CSV file
    writeCSV(outputFilename, filteredData);

    std::cout << "Filtering completed successfully!" << std::endl;

    return 0;
} 
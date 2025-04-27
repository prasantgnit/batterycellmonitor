#include <iostream>
#include <memory>
#include "Cell/cell.hpp"
#include "Logger/logger.hpp"

int main() {
    // Create a logger instance using std::make_shared for dependency injection
    auto logger = std::make_shared<Logger>(LogLevel::INFO, "cell_log.txt");

    // Create a Cell object with a logger and a cell ID (e.g., cell ID 1)
    Cell cell(logger, 1);

    // Initialize the cell communication (Socket)
    cell.init();

    // Simulate injecting different voltage and current values
    // First data set
    float voltage_1 = 3.7f;
    uint16_t current_1 = 150; // Example current value

    // Process data for first set
    std::cout << "Processing first data set..." << std::endl;
    cell.processData(voltage_1, current_1);

    // Second data set
    float voltage_2 = 4.2f;
    uint16_t current_2 = 200; // Example current value

    // Process data for second set
    std::cout << "Processing second data set..." << std::endl;
    cell.processData(voltage_2, current_2);

    // Third data set
    float voltage_3 = 3.4f;
    uint16_t current_3 = 180; // Example current value

    // Process data for third set
    std::cout << "Processing third data set..." << std::endl;
    cell.processData(voltage_3, current_3);

    return 0;
}

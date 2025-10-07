/*********************
 * File : util.cpp
 * Author : Sinan Demir
 * Date   : 09/24/2025
 * Purpose: Source file for util.cpp contains utility function definitions. (csv output)
 *********************/
 
#include "util.h"

void write_csv(const std::string& filename, const std::vector<std::string>& headers, const std::vector<std::vector<std::string>>& rows) {
    /******************************
     * Write data to a CSV file
     * @param filename Name of the output CSV file
     * @param headers Vector of column headers
     * @param rows Vector of vectors containing data rows
     * @exception std::runtime_error if file cannot be opened for writing
     * @return None
     * @note
     *****************************/
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for writing.");
    }
    for (const auto& header : headers) {
        file << header << ",";
    }
    file << "\n";
    for (const auto& row : rows) {
        for (const auto& value : row) {
            file << value << ",";
        }
        file << "\n";
    }
    file.close();
}  // end write_csv 
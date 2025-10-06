/*********************
 * File : util.cpp
 * Author : Sinan Demir
 * Date   : 09/24/2025
 * Purpose: Source file for util.cpp contains utility function definitions. (csv output)
 *********************/
 
#include "util.h"

void write_csv(const std::string& filename, const std::vector<std::string>& headers, const std::vector<std::vector<std::string>>& rows) {
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

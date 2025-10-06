/***********************
 * file : util.h
 * author : Sinan Demir
 * date : 09/24/2025
 * purpose : Header file for util.cpp contains utility functions. (csv output)
 ***********************/


#ifndef UTIL_H
#define UTIL_H

#include <fstream>
#include <string>
#include <vector>


// Write a CSV file given headers and rows.
// headers = {"n", "Trap Lifetime", "Simp Lifetime"}
// rows    = vector of rows, each row is a vector of values as strings
void write_csv(const std::string& filename,
               const std::vector<std::string>& headers,
               const std::vector<std::vector<std::string>>& rows);

#endif // UTIL_H

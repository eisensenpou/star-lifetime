# Utilities Module

**Module Overview for Utility Functions**

---

## 📋 Module Overview

The utilities module provides essential helper functions for data export and file I/O operations. While simple in scope, this module is crucial for enabling external analysis, result visualization, and data persistence in the Star Lifetime project.

### 🎯 **Purpose**
- Provide CSV file generation capabilities
- Support data export for external analysis tools
- Enable result sharing and visualization
- Facilitate scientific data management

### 📁 **Files**
- **Header**: `include/util.h`
- **Implementation**: `src/util.cpp`

---

## 📄 CSV Export Functionality

### **`write_csv()` Function**

#### **Purpose**
The `write_csv()` function provides a flexible interface for exporting tabular data to CSV (Comma-Separated Values) format, which is widely supported by data analysis tools, spreadsheets, and visualization software.

#### **Function Signature**
```cpp
void write_csv(const std::string& filename,
               const std::vector<std::string>& headers,
               const std::vector<std::vector<std::string>>& rows);
```

#### **Parameters**

| Parameter | Type | Description |
|-----------|------|-------------|
| `filename` | `const std::string&` | Path to output CSV file |
| `headers` | `const std::vector<std::string>&` | Column headers/field names |
| `rows` | `const std::vector<std::vector<std::string>>&` | Data rows as vector of string vectors |

#### **Exception Handling**
- **Throws**: `std::runtime_error` if file cannot be opened for writing
- **Causes**: File permission issues, invalid path, disk full, etc.

#### **File Format**
- **Delimiter**: Comma (`,`)
- **Line Ending**: System default newline
- **Encoding**: Plain text (ASCII/UTF-8 compatible)
- **Structure**: Header row followed by data rows

#### **Return Value**
- **Type**: `void`
- **Behavior**: Creates/overwrites file with CSV data

---

## 💡 Usage Examples

### **Basic CSV Generation**
```cpp
#include "util.h"
#include <vector>
#include <string>

int main() {
    // Define column headers
    std::vector<std::string> headers = {
        "Mass_Solar", "Luminosity_Solar", "Lifetime_Years", "Temperature_K"
    };
    
    // Define data rows
    std::vector<std::vector<std::string>> data = {
        {"0.5", "0.03", "200000000000", "3500"},
        {"1.0", "1.0", "10000000000", "5800"},
        {"2.0", "11.3", "1000000000", "10000"},
        {"5.0", "177.8", "100000000", "20000"}
    };
    
    // Write to CSV file
    try {
        write_csv("stellar_data.csv", headers, data);
        std::cout << "CSV file created successfully.\n";
    } catch (const std::runtime_error& e) {
        std::cerr << "Error creating CSV: " << e.what() << "\n";
    }
    
    return 0;
}
```

### **Stellar Physics Data Export**
```cpp
#include "util.h"
#include "physics/star_physics.h"
#include <vector>
#include <string>
#include <sstream>

void export_stellar_table() {
    using namespace physics::stellar;
    
    // Prepare headers
    std::vector<std::string> headers = {
        "Mass_Msun", "Mass_kg", "Luminosity_Lsun", "Luminosity_W", "Lifetime_Years"
    };
    
    // Generate data for various stellar masses
    std::vector<std::vector<std::string>> data;
    std::vector<double> masses = {0.5, 1.0, 1.5, 2.0, 3.0, 5.0, 10.0};
    
    for (double mass_solar : masses) {
        double mass_kg = mass_solar * M_SUN;
        double luminosity = luminosity(mass_kg);
        double luminosity_solar = luminosity / L_SUN;
        double lifetime = lifetime(mass_kg);
        
        // Convert values to strings
        std::vector<std::string> row;
        row.push_back(std::to_string(mass_solar));
        row.push_back(std::to_string(mass_kg));
        row.push_back(std::to_string(luminosity_solar));
        row.push_back(std::to_string(luminosity));
        row.push_back(std::to_string(lifetime));
        
        data.push_back(row);
    }
    
    // Export to CSV
    write_csv("stellar_properties.csv", headers, data);
}
```

### **Numerical Analysis Results Export**
```cpp
#include "util.h"
#include "num_analysis/integration.h"
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>

void export_convergence_study() {
    using namespace num_analysis::integration;
    
    // Test function: f(x) = exp(-x²) from 0 to 2
    auto test_func = [](double x) { return std::exp(-x * x); };
    double a = 0.0, b = 2.0;
    
    // Headers
    std::vector<std::string> headers = {
        "n_points", "trapezoidal_result", "simpson_result", 
        "trapezoidal_error", "simpson_error"
    };
    
    // Convergence study data
    std::vector<std::vector<std::string>> data;
    std::vector<int> n_values = {10, 20, 50, 100, 200, 500, 1000};
    
    for (int n : n_values) {
        double trap_result = trapezoid_rule(test_func, a, b, n);
        double simp_result = simpsons_rule(test_func, a, b, n);
        
        // Use high-resolution as reference
        double reference = simpsons_rule(test_func, a, b, 10000);
        
        double trap_error = std::abs(trap_result - reference);
        double simp_error = std::abs(simp_result - reference);
        
        // Format numbers with appropriate precision
        auto format_double = [](double value, int precision = 8) {
            std::stringstream ss;
            ss << std::scientific << std::setprecision(precision) << value;
            return ss.str();
        };
        
        std::vector<std::string> row = {
            std::to_string(n),
            format_double(trap_result),
            format_double(simp_result),
            format_double(trap_error),
            format_double(simp_error)
        };
        
        data.push_back(row);
    }
    
    write_csv("integration_convergence.csv", headers, data);
}
```

### **Error Analysis Export**
```cpp
#include "util.h"
#include "num_analysis/errors.h"
#include <vector>
#include <string>
#include <cmath>

void export_error_analysis() {
    using namespace num_analysis::errors;
    
    // Headers
    std::vector<std::string> headers = {
        "method", "n_points", "exact_value", "approximate_value", 
        "absolute_error", "relative_error"
    };
    
    // Data
    std::vector<std::vector<std::string>> data;
    
    // Test case: ∫₀^π sin(x) dx = 2
    auto sine_func = [](double x) { return std::sin(x); };
    double exact = 2.0;
    
    std::vector<int> n_values = {10, 50, 100, 500, 1000};
    
    for (int n : n_values) {
        // Trapezoidal rule
        double trap_approx = num_analysis::integration::trapezoid_rule(sine_func, 0, M_PI, n);
        double trap_abs_err = absolute_error(exact, trap_approx);
        double trap_rel_err = relative_error(exact, trap_approx);
        
        std::vector<std::string> trap_row = {
            "trapezoidal",
            std::to_string(n),
            std::to_string(exact),
            std::to_string(trap_approx),
            std::to_string(trap_abs_err),
            std::to_string(trap_rel_err)
        };
        data.push_back(trap_row);
        
        // Simpson's rule
        double simp_approx = num_analysis::integration::simpsons_rule(sine_func, 0, M_PI, n);
        double simp_abs_err = absolute_error(exact, simp_approx);
        double simp_rel_err = relative_error(exact, simp_approx);
        
        std::vector<std::string> simp_row = {
            "simpson",
            std::to_string(n),
            std::to_string(exact),
            std::to_string(simp_approx),
            std::to_string(simp_abs_err),
            std::to_string(simp_rel_err)
        };
        data.push_back(simp_row);
    }
    
    write_csv("error_analysis.csv", headers, data);
}
```

---

## 🔧 Implementation Details

### **File I/O Operations**
```cpp
// Core implementation from util.cpp
void write_csv(const std::string& filename,
               const std::vector<std::string>& headers,
               const std::vector<std::vector<std::string>>& rows) {
    
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for writing.");
    }
    
    // Write headers
    for (const auto& header : headers) {
        file << header << ",";
    }
    file << "\n";
    
    // Write data rows
    for (const auto& row : rows) {
        for (const auto& value : row) {
            file << value << ",";
        }
        file << "\n";
    }
    
    file.close();
}
```

### **Error Handling Strategy**
- **File Creation**: Checks if file opens successfully
- **Write Operations**: Relies on ofstream's internal error handling
- **Resource Management**: Automatic file closure on scope exit
- **Exception Safety**: RAII pattern for file handle management

### **Memory Management**
- **String Storage**: Uses standard library containers with automatic memory management
- **Large Datasets**: Streams data directly to file to minimize memory usage
- **No Dynamic Allocation**: Uses stack-allocated objects where possible

---

## 📊 Data Format Considerations

### **CSV Specification Compliance**
- **Field Delimiter**: Comma (`,`)
- **Line Delimiter**: System-dependent newline
- **Quoting**: Not implemented (assumes simple data)
- **Escaping**: Not implemented (assumes clean data)

### **Limitations and Considerations**
1. **No Automatic Quoting**: Values containing commas will break format
2. **No Data Validation**: Assumes all data is string-compatible
3. **No Type Conversion**: All data treated as strings
4. **File Overwriting**: Existing files are overwritten without warning

### **Recommended Enhancements**
```cpp
// Enhanced version with better CSV compliance
void write_csv_enhanced(const std::string& filename,
                       const std::vector<std::string>& headers,
                       const std::vector<std::vector<std::string>>& rows) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for writing.");
    }
    
    // Helper function to escape CSV values
    auto escape_csv = [](const std::string& value) {
        if (value.find(',') != std::string::npos || 
            value.find('"') != std::string::npos ||
            value.find('\n') != std::string::npos) {
            std::string escaped = "\"";
            for (char c : value) {
                if (c == '"') escaped += "\"\"";
                else escaped += c;
            }
            escaped += "\"";
            return escaped;
        }
        return value;
    };
    
    // Write headers
    for (size_t i = 0; i < headers.size(); ++i) {
        file << escape_csv(headers[i]);
        if (i < headers.size() - 1) file << ",";
    }
    file << "\n";
    
    // Write data rows
    for (const auto& row : rows) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << escape_csv(row[i]);
            if (i < row.size() - 1) file << ",";
        }
        file << "\n";
    }
}
```

---

## 🔗 Integration with Project

### **Current Usage**
- **[`generate_csv.cpp`](../../src/generate_csv.cpp)**: Standalone stellar data generator
- **[`physics::stellar`](physics_stellar.md)**: `generate_lifetime_table()` function
- **Testing**: Data export for result validation

### **Data Export Patterns**
1. **Stellar Properties**: Mass, luminosity, lifetime calculations
2. **Numerical Analysis**: Convergence studies, error analysis
3. **Comparative Studies**: Method comparisons, performance metrics

### **File Organization**
```
project/
├── results/              # Generated data files
│   ├── lifetime_table.csv
│   ├── stellar_data.csv
│   └── error_analysis.csv
├── src/                  # Source code
│   └── generate_csv.cpp  # Standalone data generator
└── docs/                 # Documentation
```

---

## 🎯 Best Practices

### **Data Organization**
```cpp
// Organize data logically
struct StellarData {
    double mass_solar;
    double luminosity_solar;
    double lifetime_years;
    double temperature_kelvin;
};

std::vector<StellarData> stellar_catalog;
// ... populate catalog ...

// Convert to CSV format
std::vector<std::vector<std::string>> csv_data;
for (const auto& star : stellar_catalog) {
    csv_data.push_back({
        std::to_string(star.mass_solar),
        std::to_string(star.luminosity_solar),
        std::to_string(star.lifetime_years),
        std::to_string(star.temperature_kelvin)
    });
}
```

### **File Naming Conventions**
```cpp
// Use descriptive names
std::string create_output_filename(const std::string& prefix, 
                                   const std::string& suffix) {
    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);
    
    std::ostringstream oss;
    oss << prefix << "_" << std::put_time(&tm, "%Y%m%d_%H%M%S") << "_" << suffix << ".csv";
    return oss.str();
}

// Usage: "stellar_data_20241025_143022_analysis.csv"
```

### **Error Handling**
```cpp
void safe_csv_export(const std::string& filename,
                    const std::vector<std::string>& headers,
                    const std::vector<std::vector<std::string>>& rows) {
    try {
        write_csv(filename, headers, rows);
        std::cout << "Successfully exported " << rows.size() 
                  << " rows to " << filename << "\n";
    } catch (const std::runtime_error& e) {
        std::cerr << "Failed to export data: " << e.what() << "\n";
        // Consider fallback strategies
    }
}
```

---

## 📖 Related Documentation

### **Connected Modules**
- **[`physics::stellar`](physics_stellar.md)** - Uses CSV export for lifetime tables
- **[`num_analysis::integration`](num_analysis_integration.md)** - Exports convergence studies
- **[`num_analysis::errors`](num_analysis_errors.md)** - Exports error analysis results

### **External Tools**
- **Spreadsheet Software**: Excel, LibreOffice Calc
- **Data Analysis**: Python pandas, R dataframes
- **Visualization**: Matplotlib, gnuplot, Tableau

---

## 🚀 Quick Reference

### **Function Signature**
```cpp
void write_csv(const std::string& filename,
               const std::vector<std::string>& headers,
               const std::vector<std::vector<std::string>>& rows);
```

### **Basic Usage**
```cpp
#include "util.h"

std::vector<std::string> headers = {"Column1", "Column2", "Column3"};
std::vector<std::vector<std::string>> data = {
    {"1", "2", "3"},
    {"4", "5", "6"}
};

write_csv("output.csv", headers, data);
```

### **Error Handling**
```cpp
try {
    write_csv(filename, headers, data);
} catch (const std::runtime_error& e) {
    std::cerr << "Error: " << e.what() << std::endl;
}
```

---

*Data export bridges computational results with external analysis tools.* 📊
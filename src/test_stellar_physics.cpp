/************************
 * File   : test_stellar_physics.cpp
 * Author : Sinan Demir
 * Date   : 10/10/2025
 * Purpose: Testing and validation script for the physics::stellar namespace,
 *          including the Star class and numerical stellar lifetime models.
 ************************/



#include "physics/star_physics.h"
#include "num_analysis/integration.h"
#include "num_analysis/differentiation.h"
#include "num_analysis/errors.h"

using namespace physics::constants;
using namespace physics::stellar;

void test_basic_star_properties() {
    /*
    * Test 1: Basic Star Property Accessors
    */
    std::cout << "\n=== Test 1: Basic Star Property Accessors ===\n";
    Star sun("Sun", 1.0, 1.0, 4.6e9);

    assert(sun.getName() == "Sun");
    assert(std::abs(sun.getMass() - 1.0) < 1e-12);
    assert(std::abs(sun.getLuminosity() - 1.0) < 1e-12);
    assert(std::abs(sun.getAge() - 4.6e9) < 1e-3);

    std::cout << "PASS: Star accessors and constructor verified.\n";
}

void test_lifetime_estimates() {
    /* Test 2: Analytical Lifetime Comparison */
    std::cout << "\n=== Test 2: Analytical Lifetime Comparison ===\n";

    double M = M_SUN;
    double expected_life = lifetime(M);  // years
    double fuel = fuel_stock(M);
    double lum  = luminosity(M);

    double numeric_life = (fuel / lum) / SECONDS_PER_YEAR;
    double rel_error = num_analysis::errors::relative_error(expected_life, numeric_life);

    std::cout << "Analytic lifetime: " << expected_life << " years\n";
    std::cout << "Numeric lifetime : " << numeric_life << " years\n";
    std::cout << "Relative error    : " << rel_error << "\n";

    assert(rel_error < 1e-10);
    std::cout << "PASS: Analytical lifetime model consistent with numeric result.\n";
}

void test_integration_methods() {
    /* Test 3: Numerical Integration Consistency */
    std::cout << "\n=== Test 3: Numerical Integration Consistency ===\n";

    auto f = [](double x) { return std::sin(x); };
    double exact = 2.0; // ∫₀^π sin(x) dx = 2
    double trap = num_analysis::integration::trapezoid_rule(f, 0, M_PI, 1000);
    double simp = num_analysis::integration::simpsons_rule(f, 0, M_PI, 1000);

    std::cout << "Trapezoid: " << trap << "\n";
    std::cout << "Simpson  : " << simp << "\n";

    double err_t = num_analysis::errors::relative_error(exact, trap);
    double err_s = num_analysis::errors::relative_error(exact, simp);

    std::cout << "Rel error (Trapezoid): " << err_t << "\n";
    std::cout << "Rel error (Simpson)  : " << err_s << "\n";

    assert(err_s < err_t);
    std::cout << "PASS: Simpson’s rule more accurate than trapezoid.\n";
}

void test_stellar_models() {
    /* Test 4: Stellar Lifetime Model Validation */
    std::cout << "\n=== Test 4: Stellar Lifetime Model Validation ===\n";

    double S0 = fuel_stock(M_SUN);
    double T_guess = 1e10; // initial guess (years)
    int n = 1000;

    // Use a decaying luminosity toy model
    auto L = L_exp_decay;

    double lifetime_est = estimate_lifetime(S0, L, T_guess, n, true);
    std::cout << "Estimated lifetime (Simpson) : " << lifetime_est << " years\n";

    assert(lifetime_est > 0);
    std::cout << "PASS: Numerical stellar lifetime integration executed successfully.\n";
}

void test_star_comparisons() { 
    /* Test 5: Star Comparison Methods */
    std::cout << "\n=== Test 5: Star Comparison Methods ===\n";
    Star sun("Sun", 1.0, 1.0, 4.6e9);
    Star sirius("Sirius A", 2.1, 25.0, 2.4e8);
    Star proxima("Proxima Centauri", 0.12, 0.0017, 4.85e9);

    assert(sirius.isMoreMassiveThan(sun));
    assert(sun.isOlderThan(sirius));
    assert(sirius.isBrighterThan(proxima));

    std::cout << "PASS: Star comparison logic validated.\n";
}

void run_all_tests() {
    /* Run all tests */
    std::cout << std::scientific << std::setprecision(6);
    std::cout << "=============================================\n";
    std::cout << "     Running Stellar Physics Test Suite\n";
    std::cout << "=============================================\n";

    test_basic_star_properties();
    test_lifetime_estimates();
    test_integration_methods();
    test_stellar_models();
    test_star_comparisons();

    std::cout << "\nAll tests completed successfully.\n";
    std::cout << "=============================================\n";
}

int main() {
    try {
        run_all_tests();
    } catch (const std::exception& e) {
        std::cerr << "\n[ERROR] Exception caught: " << e.what() << "\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

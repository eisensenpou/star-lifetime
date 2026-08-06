/**
 * @file module.cpp
 * @author Sinan Demir
 * @brief pybind11 bindings for the stellar physics module.
 * @version 0.1
 * @date 2026-01-28
 *
 * @copyright Copyright (c) 2026
 */



#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "num_analysis/differentiation_public.h"
#include "num_analysis/errors_public.h"
#include "num_analysis/integration_public.h"
#include "physics/star_physics_public.h"

// --------------------------------------------

namespace py = pybind11;

PYBIND11_MODULE(star_lifetime_py, m) {
    m.doc() = "Python bindings for stellar lifetime calculations";

    /**
     * @brief NumericalError exception binding
     * 
     * @see include/num_analysis/errors_public.h
     */
    py::register_exception<num_analysis::public_api::NumericalError>(
        m,
        "NumericalError"
    );


    /**
     * @brief compute_fuel_lifetime function binding, it does not 
     * need a Star object to be used in Python.
     * @param mass Mass of the star in solar mass units
     * @return Fuel lifetime in years
     * @throws std::invalid_argument if mass is negative
     * @throws std::runtime_error on numerical failure
     * @note Reuses tested function lifetime(M_kg)
     */
    m.def(
        "compute_fuel_lifetime",
        &physics::public_api::lifetime,
        "Compute stellar fuel lifetime from stellar mass (in solar mass units)",
        py::arg("mass")
    );

    /**
     * @brief derivative function binding
     * @param x Sample points (must be strictly monotonic)
     * @param y Function values at sample points
     * @param method Differentiation scheme: "forward", "backward", "central
     * (default)" 
     * @return Vector of derivative values (same size as input)
     * 
     * @throws std::invalid_argument on invalid input
     * @throws std::runtime_error on numerical failure
     */
    m.def(
        "derivative",
        &num_analysis::public_api::derivative,
        "Compute the numerical derivative of a function at a given point using Central Difference Method",
        py::arg("x"), 
        py::arg("y"), 
        py::arg("method") = "central"
    );

    m.def(
        "integrate_scalar",
        &num_analysis::public_api::integrate_scalar,
        "Integrate a scalar quantity over a closed interval",
        py::arg("a"),
        py::arg("b")
    );


}

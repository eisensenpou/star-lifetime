

#include "num_analysis/integration_public.h"
#include "num_analysis/detail/integration.h"
#include "num_analysis/errors_public.h"

#include <cmath>
#include <stdexcept>

namespace num_analysis::public_api {

double integrate_scalar(double a, double b) {
  if (!(a < b)) {
    throw std::invalid_argument("Integration bounds must satisfy a < b.");
  }

  /*
   * This lambda is INTERNAL ONLY.
   * It never crosses the public boundary and is not exposed to Python.
   */
  auto internal_quantity = [](double x) -> double {
    // Example placeholder:
    // In real usage, this would call frozen physics/core logic.
    return x;
  };

  /*
   * Fixed numerical contract.
   * Tolerance is not user-configurable and part of the API guarantee.
   */
  constexpr double ABS_TOL = 1e-10;
  constexpr int MAX_DOUBLINGS = 20;

  /*
   * Adaptive refinement: double the subinterval count until successive
   * Simpson's-rule estimates agree within ABS_TOL, per the documented
   * "internal adaptive integrator" contract.
   */
  int n = 2;
  double estimate =
      num_analysis::integration::simpsons_rule(internal_quantity, a, b, n);

  for (int i = 0; i < MAX_DOUBLINGS; ++i) {
    n *= 2;
    double refined =
        num_analysis::integration::simpsons_rule(internal_quantity, a, b, n);
    if (std::abs(refined - estimate) < ABS_TOL) {
      return refined;
    }
    estimate = refined;
  }

  throw NumericalError(
      NumericalErrorKind::NonConvergence,
      "integrate_scalar failed to converge within the fixed accuracy contract");
}

} // namespace num_analysis::public_api

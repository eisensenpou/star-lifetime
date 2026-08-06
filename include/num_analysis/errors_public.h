/**
 * @file errors_public.h
 * @author Sinan Demir
 * @brief Declaration of PUBLIC API for numerical analysis errors
 * @version 0.1
 * @date 2026-01-31
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include <stdexcept>
#include <string>

namespace num_analysis::public_api {

/**
 * @brief Enumerates numerical failure categories.
 *
 * This list is closed and part of the public API contract.
 */
enum class NumericalErrorKind {
  NonConvergence,
  LossOfPrecision,
  Overflow,
  Underflow,
  ErrorBoundViolation,
  UnsupportedRegime
};

/**
 * @brief Base class for numerical computation errors.
 *
 * Indicates that a computation failed due to numerical limitations,
 * despite physically valid input.
 */
class NumericalError : public std::runtime_error {
public:
  NumericalError(NumericalErrorKind kind, const std::string &message);

  NumericalErrorKind kind() const noexcept;

private:
  NumericalErrorKind kind_;
};

} // namespace num_analysis::public_api
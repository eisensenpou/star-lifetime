/**
 * @file errors_public.cpp
 * @author Sinan Demir
 * @brief Implementation file of PUBLIC API for numerical analysis errors
 * @version 0.1
 * @date 2026-01-31
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "num_analysis/errors_public.h"

namespace num_analysis::public_api {

NumericalError::NumericalError(NumericalErrorKind kind,
                               const std::string &message)
    : std::runtime_error(message), kind_(kind) {}

NumericalErrorKind NumericalError::kind() const noexcept { return kind_; }

} // namespace num_analysis::public_api

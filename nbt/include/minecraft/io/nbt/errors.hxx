// ============================================================================
// Project: SOLISMC_IO
//
// Common NBT errors
//
// Author    Meltwin (github@meltwin.fr)
// Date      12/10/2026 (created 10/10/2026)
// Version   1.0.0
// ----------------------------------------------------------------------------
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#pragma once

#include <format>

#include <solis/utils/errors.hpp>

#include "minecraft/io/nbt/tags.hxx"

namespace minecraft::nbt::errors {

// ============================================================================

/**
 * @brief Bad cast from std::any
 */
struct BasAnyCastError : solis::SolisError {

  static constexpr auto BASE_MSG{"Bad cast from std::any"};

  explicit BasAnyCastError(std::string_view function)
      : solis::SolisError(
            std::format("{:s} from function {:s}", BASE_MSG, function)) {}

  explicit BasAnyCastError(Tags tag, std::string_view function)
      : solis::SolisError(
            std::format("{:s} of value type {:s} from function {:s}", BASE_MSG,
                        to_string(tag), function)) {}
};

// ============================================================================

/**
 * @brief Field could not be found in map
 */
struct FieldNotFoundError : solis::SolisError {
  explicit FieldNotFoundError(std::string_view name)
      : solis::SolisError(std::format("Field {:s} could not be found!", name)) {
  }
};

// ============================================================================

/**
 * @brief Expected and processed tags does not matched
 */
struct MismatchedTag : solis::SolisError {

  explicit MismatchedTag(Tags expected, Tags processed,
                         std::string_view function)
      : solis::SolisError(std::format(
            "Mismatched tag expected={:s} != processed={:s} in function {:s}",
            to_string(expected), to_string(processed), function)) {}
};

// ============================================================================

/**
 * @brief Calling to a function with an unsupported tag
 */
struct UnsupportedTag : solis::SolisError {

  explicit UnsupportedTag(Tags tag, std::string_view function)
      : solis::SolisError(std::format("Unsupported tag {:s} in function {:s}",
                                      to_string(tag), function)) {}
};

} // namespace minecraft::nbt::errors
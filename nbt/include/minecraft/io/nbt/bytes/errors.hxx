// ============================================================================
// Project: SOLISMC_IO
//
// Error collection for the NBT byte parsing utilities
//
// Author    Meltwin (github@meltwin.fr)
// Date      28/09/2026 (created 28/09/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#pragma once

#include <format>
#include <solis/utils/errors.hpp>

#include "minecraft/io/nbt/tags.hxx"

namespace minecraft::nbt::byte::errors {

// ============================================================================

/**
 * @brief Initialized a parser from a toolbox without selecting it beforehand
 */
struct AnyParseError : solis::SolisError {

  explicit AnyParseError(const char *msg)
      : solis::SolisError(std::format("Could not parse std::any : {:s}", msg)) {
  }
};

// ============================================================================

/**
 * @brief Initialized a parser from a toolbox without selecting it beforehand
 */
struct UninitializedParser : solis::SolisError {

  explicit UninitializedParser()
      : solis::SolisError("Parser was not previously initialized") {}
};

// ============================================================================

/**
 * @brief Initialized a parser from a toolbox without selecting it beforehand
 */
struct UninitializedWriter : solis::SolisError {

  explicit UninitializedWriter()
      : solis::SolisError("Writer was not previously initialized") {}
};

// ============================================================================

/**
 * @brief Calling to a function with an unsupported tag
 */
struct UnsupportedTag : solis::SolisError {

  explicit UnsupportedTag(Tags tag)
      : solis::SolisError(std::format("Unsupported tag {:s}", to_str(tag))) {}
};

} // namespace minecraft::nbt::byte::errors
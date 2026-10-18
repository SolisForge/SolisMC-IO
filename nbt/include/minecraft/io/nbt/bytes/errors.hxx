// ============================================================================
// Project: SOLISMC_IO
//
// Error collection for the NBT byte parsing utilities
//
// Author    Meltwin (github@meltwin.fr)
// Date      10/10/2026 (created 28/09/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#pragma once

#include "minecraft/io/nbt/errors.hxx"

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

} // namespace minecraft::nbt::byte::errors
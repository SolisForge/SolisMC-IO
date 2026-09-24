// ============================================================================
// Project: SOLISMC_IO
//
// Common array-like structure parsing
//
// Author    Meltwin (github@meltwin.fr)
// Date      14/09/2026 (created 14/09/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#pragma once

#include "minecraft/io/nbt/bytes/base/common.hxx"
#include "minecraft/io/nbt/bytes/base/integral.hxx"

namespace minecraft::nbt::byte {

// ============================================================================
// Base implementation
// ============================================================================

/**
 * @brief State of read/write operation on array
 *
 */
struct ArrayRWState {
  // Size
  IntRWState size_counter{};
  uint32_t size{0};

  // Contents
  RWState<uint32_t> content_state{};
};

} // namespace minecraft::nbt::byte
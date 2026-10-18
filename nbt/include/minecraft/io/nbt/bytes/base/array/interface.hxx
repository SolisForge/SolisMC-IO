// ============================================================================
// Project: SOLISMC_IO
//
// Common array-like structure parsing
//
// Author    Meltwin (github@meltwin.fr)
// Date      13/10/2026 (created 14/09/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#pragma once

#include "minecraft/io/nbt/bytes/base/common.hxx"
#include "minecraft/io/nbt/bytes/base/integral.hxx"
#include "minecraft/io/nbt/tags.hxx"

namespace minecraft::nbt::byte {

// ============================================================================
// Base implementation
// ============================================================================

/**
 * @brief State of read/write operation on array
 *
 */
struct ArrayRWState {
  /**
   * @brief Actual representation is int32_t, but store
   * here in unsigned to prevent negative sizes
   */
  using ArraySize_t = uint32_t;

  // Size
  IntRWState size_state{};
  ArraySize_t size{0};

  // Contents
  RWState<ArraySize_t> content_state{};

  // Tag
  Tags tag;
  bool is_tag_processed{false};

  void reset() {
    size_state.reset();
    content_state.reset();
    size = 0;
    tag = Tags::END;
    is_tag_processed = false;
  }
};

} // namespace minecraft::nbt::byte
// ============================================================================
// Project: SOLISMC_IO
//
// Stateful parser for floating point types implementation
//
// Author    Meltwin (github@meltwin.fr)
// Created   24/09/2026
// ============================================================================

// ============================================================================
// Version   1.0.0
// Modified  23/10/2026
// Copyright Solis Forge | 2026 - 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#include "minecraft/io/nbt/bytes/base/float.hxx"
#include "minecraft/io/nbt/bytes/base/common.hxx"
#include "minecraft/io/nbt/bytes/stateful/float.hxx"

#include "helper.hxx"

namespace minecraft::nbt::byte {
#define FLOAT_TEMPLATE template <std::floating_point T, GameVersion GV>
#define FP read_float<T, GV>

FLOAT_TEMPLATE
DEFINE_COMMON_PARSER(FP, T);

// ============================================================================
// Implementation of parser
// ============================================================================
FLOAT_TEMPLATE
void Parser<T, GV>::reset() {
  state_.processed = 0;
  value_ = 0;
}

// ============================================================================
// Implementation of writer
// ============================================================================
template<std::floating_point T, GameVersion GV>
DumpResult Writer<T, GV>::dump(Stream &strm) {
  using enum DumpResult;
  // If no value is bound to this writer
  if (!bound_)
    return UNBOUND;
  // Reset state if needed
  if (is_done())
    reset();
  if (auto ret = write_float<T, GV>(strm, state_, value_); ret != ENDED)
    return ret;
  bound_ = false;
  return ENDED;
}

// ============================================================================

template<std::floating_point T, GameVersion GV>
void Writer<T, GV>::reset() {
  state_.processed = 0;
}
} // namespace minecraft::nbt::byte

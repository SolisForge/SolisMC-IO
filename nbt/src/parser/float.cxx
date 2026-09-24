// ============================================================================
// Project: SOLISMC_IO
//
// Stateful parser for floating point types implementation
//
// Author    Meltwin (github@meltwin.fr)
// Date      24/09/2026 (created 24/09/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#include "minecraft/io/nbt/bytes/base/float.hxx"
#include "minecraft/io/nbt/bytes/base/common.hxx"
#include "minecraft/io/nbt/bytes/parser/float.hxx"

namespace minecraft::nbt::byte {

// ============================================================================
// Implementation
// ============================================================================

template <std::floating_point T, GameVersion GV>
ParseResult FloatParser<T, GV>::parse(Stream &strm) {
  // Reset state if needed
  if (state_.left(sizeof(T)) == 0)
    reset();

  // Parse value
  return read_float<T, GV>(strm, state_, value_);
}

// ============================================================================

template <std::floating_point T, GameVersion GV>
void FloatParser<T, GV>::reset() {
  state_.processed = 0;
  value_ = 0;
}

// ============================================================================
// Export
// ============================================================================
#define EXPORT(type)                                                           \
  template struct FloatParser<type, GameVersion::JAVA>;                        \
  template struct FloatParser<type, GameVersion::BEDROCK>;

EXPORT(float)
EXPORT(double)

#undef EXPORT

} // namespace minecraft::nbt::byte
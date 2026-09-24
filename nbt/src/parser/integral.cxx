// ============================================================================
// Project: SOLISMC_IO
//
// Stateful parser for integral types implementation
//
// Author    Meltwin (github@meltwin.fr)
// Date      24/09/2026 (created 24/09/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#include "minecraft/io/nbt/bytes/parser/integral.hxx"
#include "minecraft/io/nbt/bytes/base/common.hxx"
#include "minecraft/io/nbt/bytes/base/integral.hxx"

namespace minecraft::nbt::byte {

// ============================================================================
// Implementation
// ============================================================================

template <std::integral T, GameVersion GV>
ParseResult IntegralParser<T, GV>::parse(Stream &strm) {
  // Reset state if needed
  if (state_.left(sizeof(T)) == 0)
    reset();

  // Parse value
  return read_int<T, GV>(strm, state_, value_);
}

// ============================================================================

template <std::integral T, GameVersion GV> void IntegralParser<T, GV>::reset() {
  state_.processed = 0;
  value_ = 0.0;
}

// ============================================================================
// Export
// ============================================================================
#define EXPORT(type)                                                           \
  template struct IntegralParser<type, GameVersion::JAVA>;                     \
  template struct IntegralParser<type, GameVersion::BEDROCK>;

EXPORT(int8_t)
EXPORT(int16_t)
EXPORT(int32_t)
EXPORT(int64_t)

#undef EXPORT

} // namespace minecraft::nbt::byte
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
#include "minecraft/io/nbt/bytes/stateful/integral.hxx"
#include "minecraft/game_info.hxx"
#include "minecraft/io/nbt/bytes/base/common.hxx"
#include "minecraft/io/nbt/bytes/base/integral.hxx"

namespace minecraft::nbt::byte {

// ============================================================================
// Implementation of parser
// ============================================================================

template <std::integral T, GameVersion GV>
ParseResult IntegralParser<T, GV>::parse(Stream &strm) {
  // Reset state if needed
  if (is_done())
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
// Implementation of writer
// ============================================================================
template <std::integral T, GameVersion GV>
DumpResult IntegralWriter<T, GV>::dump(Stream &strm) {
  using enum DumpResult;
  // If no value is bound to this writer
  if (!bound_)
    return UNBOUND;
  // Reset state if needed
  if (is_done())
    reset();
  if (auto ret = write_int<T, GV>(strm, state_, value_); ret != ENDED)
    return ret;
  bound_ = false;
  return ENDED;
}

// ============================================================================

template <std::integral T, GameVersion GV> void IntegralWriter<T, GV>::reset() {
  state_.processed = 0;
}

// ============================================================================
// Export
// ============================================================================
#define EXPORT(type)                                                           \
  template struct IntegralParser<type, GameVersion::JAVA>;                     \
  template struct IntegralParser<type, GameVersion::BEDROCK>;                  \
  template struct IntegralWriter<type, GameVersion::JAVA>;                     \
  template struct IntegralWriter<type, GameVersion::BEDROCK>;

EXPORT(int8_t)
EXPORT(int16_t)
EXPORT(int32_t)
EXPORT(int64_t)

#undef EXPORT

} // namespace minecraft::nbt::byte
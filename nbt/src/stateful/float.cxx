// ============================================================================
// Project: SOLISMC_IO
//
// Stateful parser for floating point types implementation
//
// Author    Meltwin (github@meltwin.fr)
// Date      10/10/2026 (created 24/09/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#include "minecraft/io/nbt/bytes/base/float.hxx"
#include "minecraft/io/nbt/bytes/base/common.hxx"
#include "minecraft/io/nbt/bytes/stateful/float.hxx"

namespace minecraft::nbt::byte {

// ============================================================================
// Implementation of parser
// ============================================================================

template <std::floating_point T, GameVersion GV>
ParseResult Parser<T, GV>::parse(Stream &strm) {
  // Reset state if needed
  if (is_done())
    reset();

  // Parse value
  return read_float<T, GV>(strm, state_, value_);
}

// ============================================================================

template <std::floating_point T, GameVersion GV> void Parser<T, GV>::reset() {
  state_.processed = 0;
  value_ = 0;
}

// ============================================================================
// Implementation of writer
// ============================================================================
template <std::floating_point T, GameVersion GV>
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

template <std::floating_point T, GameVersion GV> void Writer<T, GV>::reset() {
  state_.processed = 0;
}

// ============================================================================
// Export
// ============================================================================
#define EXPORT(type)                                                           \
  template struct Parser<type, GameVersion::JAVA>;                             \
  template struct Parser<type, GameVersion::BEDROCK>;                          \
  template struct Writer<type, GameVersion::JAVA>;                             \
  template struct Writer<type, GameVersion::BEDROCK>;

EXPORT(float)
EXPORT(double)

#undef EXPORT

} // namespace minecraft::nbt::byte
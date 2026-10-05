// ============================================================================
// Project: SOLISMC_IO
//
// Stateful parser for strings implementation
//
// Author    Meltwin (github@meltwin.fr)
// Date      25/09/2026 (created 25/09/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#include "minecraft/io/nbt/bytes/stateful/string.hxx"

namespace minecraft::nbt::byte {

// ============================================================================
template <GameVersion GV> ParseResult StringParser<GV>::parse(Stream &strm) {
  // Reset state if needed
  if (is_done())
    reset();

  // Parse value
  return read_string<GV>(strm, state_, value_);
}

// ============================================================================

template <GameVersion GV> void StringParser<GV>::reset() {
  state_.size_state.processed = 0;
  state_.data_state.processed = 0;
  value_.resize(0);
}

// ============================================================================
// Implementation of writer
// ============================================================================
template <GameVersion GV> DumpResult StringWriter<GV>::dump(Stream &strm) {
  using enum DumpResult;
  // If no value is bound to this writer
  if (!bound_)
    return UNBOUND;
  // Reset state if needed
  if (is_done())
    reset();
  if (auto ret = write_string<GV>(strm, state_, *value_); ret != ENDED)
    return ret;
  bound_ = false;
  return ENDED;
}

// ============================================================================

template <GameVersion GV> void StringWriter<GV>::reset() {
  state_.size_state.processed = 0;
  state_.data_state.processed = 0;
}

// ============================================================================
// Export
// ============================================================================
template struct StringParser<GameVersion::JAVA>;
template struct StringParser<GameVersion::BEDROCK>;
template struct StringWriter<GameVersion::JAVA>;
template struct StringWriter<GameVersion::BEDROCK>;

} // namespace minecraft::nbt::byte
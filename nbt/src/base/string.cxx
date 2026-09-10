// ============================================================================
// Project: SOLISMC_IO
//
// Implementation of base functions for string type byte parsing
//
// Author    Meltwin (github@meltwin.fr)
// Date      10/09/2026 (created 10/09/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#include "minecraft/io/nbt/bytes/base/string.hxx"
#include "byte_helper.hxx"
#include "minecraft/io/nbt/bytes/base/common.hxx"
#include <bit>

namespace minecraft::nbt::byte {

#define R_ARGS Stream &strm, StringRWState &state, std::string &value
#define W_ARGS Stream &strm, StringRWState &state, std::string const &value

// ============================================================================
// Implementations
// ============================================================================
namespace base {
template <std::endian endianess> ParseResult read_string(R_ARGS) {
  using enum minecraft::nbt::byte::ParseResult;
  // Parse size
  if (state.size_state.left(sizeof(uint16_t)) != 0) {
    if (auto ret = read_integral<endianess>(
            strm, state.size_state, sizeof(uint16_t), (char *)(&state.size));
        ret != ENDED)
      return ret;
    value.resize(state.size);
  }

  // Parse value
  state.data_state.processed += helper::read_bytes<std::endian::native>(
      strm, value.data(), state.size, state.data_state.processed);
  return (state.data_state.left(state.size) == 0) ? ENDED : UNFINISHED;
}

// ============================================================================
template <std::endian endianess> DumpResult write_string(W_ARGS) {
  using enum minecraft::nbt::byte::DumpResult;
  auto string_size = static_cast<uint16_t>(value.size() - 1);

  // Write size
  if (state.size_state.left(sizeof(uint16_t)) != 0) {
    if (auto ret = write_integral<endianess>(
            strm, state.size_state, sizeof(uint16_t), (char *)(&string_size));
        ret != ENDED)
      return ret;
  }
  // Write value
  state.data_state.processed += helper::write_bytes<std::endian::native>(
      strm, value.c_str(), string_size, state.data_state.processed);
  return (state.data_state.left(string_size) == 0) ? ENDED : UNFINISHED;
}

} // namespace base

// ============================================================================
// Versions bindings
// ============================================================================
#define ARGS_FWD strm, state, value

namespace java {

ParseResult read_string(R_ARGS) {
  return base::read_string<std::endian::big>(ARGS_FWD);
}

DumpResult write_string(W_ARGS) {
  return base::write_string<std::endian::big>(ARGS_FWD);
}

} // namespace java

namespace bedrock {

ParseResult read_string(R_ARGS) {
  return base::read_string<std::endian::little>(ARGS_FWD);
}

DumpResult write_string(W_ARGS) {
  return base::write_string<std::endian::little>(ARGS_FWD);
}

} // namespace bedrock

// ============================================================================
// Export
// ============================================================================

template ParseResult read_string<GameVersion::JAVA>(R_ARGS);
template ParseResult read_string<GameVersion::BEDROCK>(R_ARGS);
template DumpResult write_string<GameVersion::JAVA>(W_ARGS);
template DumpResult write_string<GameVersion::BEDROCK>(W_ARGS);

} // namespace minecraft::nbt::byte
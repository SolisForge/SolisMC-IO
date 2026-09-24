// ============================================================================
// Project: SOLISMC_IO
//
// NBT List (std::vector<std::any>) structure parsing implementation
//
// Author    Meltwin (github@meltwin.fr)
// Date      14/09/2026 (created 14/09/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#include "minecraft/io/nbt/bytes/base/array/list.hxx"
#include "minecraft/game_info.hxx"
#include "minecraft/io/nbt/bytes/base/common.hxx"
#include "minecraft/io/nbt/bytes/base/integral.hxx"

namespace minecraft::nbt::byte {

#define R_ARGS Stream &strm, ListRWState &state, List &value
#define W_ARGS Stream &strm, ListRWState &state, List const &value
#define ARGS_FWD strm, state, value

// ============================================================================
// Base implementation
// ============================================================================
namespace base {

template <std::endian endianness> ParseResult read_list(R_ARGS) {
  // Parse tag
  if (!state.is_tag_parsed) {
    if (strm.n == 0)
      return ParseResult::UNFINISHED;
    state.tag = Tags(strm.data[0]);
    strm.inc();
    state.is_tag_parsed = true;
  }

  // Parse size
  if (state.size_counter.left(sizeof(uint8_t)) > 0) {
    if (auto ret = read_integral<endianness>(
            strm, state.size_counter, sizeof(uint8_t), (char *)(&state.size));
        ret != ParseResult::ENDED)
      return ret;
    value.reserve(state.size);
  }

  // Parse contents

  return ParseResult::UNFINISHED;
}

template <std::endian endianness> DumpResult write_list(W_ARGS) {
  return DumpResult::UNFINISHED;
}

} // namespace base

// ============================================================================
// Versions bindings
// ============================================================================

namespace java {

ParseResult read_list(R_ARGS) {
  return base::read_list<std::endian::big>(ARGS_FWD);
}

DumpResult write_list(W_ARGS) {
  return base::write_list<std::endian::big>(ARGS_FWD);
}

} // namespace java

namespace bedrock {

ParseResult read_list(R_ARGS) {
  return base::read_list<std::endian::little>(ARGS_FWD);
}

DumpResult write_list(W_ARGS) {
  return base::write_list<std::endian::little>(ARGS_FWD);
}

} // namespace bedrock

} // namespace minecraft::nbt::byte
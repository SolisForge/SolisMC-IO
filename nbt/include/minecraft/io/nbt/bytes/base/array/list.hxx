// ============================================================================
// Project: SOLISMC_IO
//
// NBT List (std::vector<std::any>) structure parsing definition
//
// Author    Meltwin (github@meltwin.fr)
// Date      14/09/2026 (created 14/09/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#pragma once

#include "minecraft/io/nbt/bytes/base/array/interface.hxx"
#include "minecraft/io/nbt/bytes/base/common.hxx"
#include "minecraft/io/nbt/list.hxx"
#include "minecraft/io/nbt/tags.hxx"

namespace minecraft::nbt::byte {

// ============================================================================
// Common resources
// ============================================================================

/**
 * @brief State implementation for NBT lists
 *
 */
struct ListRWState : ArrayRWState {
  Tags tag{Tags::END};
  bool is_tag_parsed{false};
};

#define R_ARGS Stream &strm, ListRWState &state, List &value
#define W_ARGS Stream &strm, ListRWState &state, List const &value

// ============================================================================
// Bindings
// ============================================================================

// Java implementation
// ----------------------------------------------------------------------------
namespace java {

/**
 * @brief Parse a list from the stream
 *
 * @param strm stream to read from
 * @param state parsing state
 * @param value list to fill
 * @return result of the parsing
 */
ParseResult read_list(R_ARGS);

/**
 * @brief Dump a list to the stream
 *
 * @param strm stream to write to
 * @param state dump state
 * @param value list to read
 * @return state of the dumping
 */
DumpResult write_list(W_ARGS);

} // namespace java

// Bedrock implementation
// ----------------------------------------------------------------------------
namespace bedrock {

/**
 * @brief Parse a list from the stream
 *
 * @param strm stream to read from
 * @param state parsing state
 * @param value list to fill
 * @return result of the parsing
 */
ParseResult read_list(R_ARGS);

/**
 * @brief Dump a list to the stream
 *
 * @param strm stream to write to
 * @param state dump state
 * @param value list to read
 * @return state of the dumping
 */
DumpResult write_list(W_ARGS);

} // namespace bedrock

// General-purpose implementation
// ----------------------------------------------------------------------------
#define ARGS_FWD strm, state, value

/**
 * @brief Parse a list from the stream
 *
 * @tparam GV targeted game version
 * @param strm stream to read from
 * @param state parsing state
 * @param value list to fill
 * @return result of the parsing
 */
template <GameVersion GV = GameVersion::JAVA> ParseResult read_list(R_ARGS) {
  if constexpr (GV == GameVersion::JAVA)
    return java::read_list(ARGS_FWD);
  return bedrock::read_list(ARGS_FWD);
}

/**
 * @brief Dump a list to the stream
 *
 * @tparam GV targeted game version
 * @param strm stream to write to
 * @param state dump state
 * @param value list to read
 * @return state of the dumping
 */
template <GameVersion GV = GameVersion::JAVA> DumpResult write_list(W_ARGS) {
  if constexpr (GV == GameVersion::JAVA)
    return java::write_list(ARGS_FWD);
  return bedrock::write_list(ARGS_FWD);
}

#undef ARGS_FWD

#undef R_ARGS
#undef W_ARGS

} // namespace minecraft::nbt::byte
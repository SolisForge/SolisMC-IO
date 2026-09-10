// ============================================================================
// Project: SOLISMC_IO
//
// Definition of base functions for string byte parsing
//
// The NBT representation of strings is a frame of:
//     - uint16 (2 bytes) size
//     - char[] data (not null terminated)
//
// Author    Meltwin (github@meltwin.fr)
// Date      10/09/2026 (created 10/09/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#pragma once

#include "minecraft/game_info.hxx"
#include "minecraft/io/nbt/bytes/base/integral.hxx"
#include <string>

namespace minecraft::nbt::byte {

// ============================================================================
// Base implementation
// ============================================================================
struct StringRWState {
  IntRWState size_state;        //< State for the size processing
  RWState<uint16_t> data_state; //< State for the content processing
  uint16_t size{0};             //< Size of the string value
};

// ============================================================================
// Bindings
// ============================================================================
#define R_ARGS Stream &strm, StringRWState &state, std::string &value
#define W_ARGS Stream &strm, StringRWState &state, std::string const &value

// Java implementation
// ----------------------------------------------------------------------------
namespace java {

/**
 * @brief Parse a string value from the stream
 *
 * @param strm stream to read from
 * @param state parsing state
 * @param value string to fill
 * @return result of the parsing
 */
ParseResult read_string(R_ARGS);

/**
 * @brief Dump a string value to the stream
 *
 * @param strm stream to write to
 * @param state dump state
 * @param value string to read
 * @return state of the dumping
 */
DumpResult write_string(W_ARGS);

} // namespace java

// Bedrock implementation
// ----------------------------------------------------------------------------
namespace bedrock {

/**
 * @brief Parse a string value from the stream
 *
 * @param strm stream to read from
 * @param state parsing state
 * @param value string to fill
 * @return result of the parsing
 */
inline ParseResult read_string(R_ARGS);

/**
 * @brief Dump a string value to the stream
 *
 * @param strm stream to write to
 * @param state dump state
 * @param value string to read
 * @return state of the dumping
 */
inline DumpResult write_string(W_ARGS);

} // namespace bedrock

// General-purpose implementation
// ----------------------------------------------------------------------------
#define ARGS_FWD strm, state, value

/**
 * @brief Parse a string value from the stream
 *
 * @tparam GV targeted game version
 * @param strm stream to read from
 * @param state parsing state
 * @param value string to fill
 * @return result of the parsing
 */
template <GameVersion GV = GameVersion::JAVA> ParseResult read_string(R_ARGS) {
  if constexpr (GV == GameVersion::JAVA)
    return java::read_string(ARGS_FWD);
  return bedrock::read_string(ARGS_FWD);
}

/**
 * @brief Dump a string value to the stream
 *
 * @tparam GV targeted game version
 * @param strm stream to write to
 * @param state dump state
 * @param value string to read
 * @return state of the dumping
 */
template <GameVersion GV = GameVersion::JAVA> DumpResult write_string(W_ARGS) {
  if constexpr (GV == GameVersion::JAVA)
    return java::write_string(ARGS_FWD);
  return bedrock::write_string(ARGS_FWD);
}

#undef ARGS_FWD

// ============================================================================
// Exports
// ============================================================================

extern template ParseResult read_string<GameVersion::JAVA>(R_ARGS);
extern template ParseResult read_string<GameVersion::BEDROCK>(R_ARGS);
extern template DumpResult write_string<GameVersion::JAVA>(W_ARGS);
extern template DumpResult write_string<GameVersion::BEDROCK>(W_ARGS);

#undef R_ARGS
#undef W_ARGS

} // namespace minecraft::nbt::byte
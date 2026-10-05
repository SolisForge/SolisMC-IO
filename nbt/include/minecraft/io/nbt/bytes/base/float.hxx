// ============================================================================
// Project: SOLISMC_IO
//
// Definition of base functions for floating-point type byte parsing
//
// Author    Meltwin (github@meltwin.fr)
// Date      30/08/2026 (created 30/08/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#pragma once

#include "minecraft/game_info.hxx"
#include "minecraft/io/nbt/bytes/base/common.hxx"
#include <bit>
#include <concepts>

namespace minecraft::nbt::byte {

// ============================================================================
// Base implementation
// ============================================================================
using FloatRWState = RWState<uint8_t>; // Integral types are 8 bytes long at max

// ============================================================================

namespace base {
#define ARGS_IMPL_READ                                                         \
  Stream &strm, FloatRWState &state, const uint8_t tlen, char *value
#define ARGS_IMPL_WRITE                                                        \
  Stream &strm, FloatRWState &state, const uint8_t tlen, const char *value

/**
 * @brief Parse a floating-point type from bytes
 *
 * @param strm stream to read from
 * @param state parsing state
 * @param tlen length of the integral type to parse
 * @param value pointer to the value to set
 * @return result of the parsing
 */
template <std::endian data_endianness>
ParseResult read_floating(ARGS_IMPL_READ);

/**
 * @brief Dump a floating-point type to bytes
 *
 * @param strm stream to write to
 * @param state dump state
 * @param tlen length of the integral type to write
 * @param value pointer to the value to read
 * @return result of the dump
 */
template <std::endian data_endianness>
DumpResult write_floating(ARGS_IMPL_WRITE);

// Specializations
template <> ParseResult read_floating<std::endian::little>(ARGS_IMPL_READ);
template <> ParseResult read_floating<std::endian::big>(ARGS_IMPL_READ);
template <> DumpResult write_floating<std::endian::little>(ARGS_IMPL_WRITE);
template <> DumpResult write_floating<std::endian::big>(ARGS_IMPL_WRITE);

#undef ARGS_IMPL_READ
#undef ARGS_IMPL_WRITE
} // namespace base

// ============================================================================
// Bindings
// ============================================================================
#define ARGS_READ(T) Stream &strm, FloatRWState &state, T &value
#define ARGS_WRITE(T) Stream &strm, FloatRWState &state, T const &value

// Java implementation
// ----------------------------------------------------------------------------
namespace java {

/**
 * @brief Parse a floating-point value from the stream
 *
 * @tparam T floating-point type to parse
 * @param strm stream to read from
 * @param state parsing state
 * @param value value object to fill
 * @return result of the parsing
 */
template <std::floating_point T> inline ParseResult read_float(ARGS_READ(T)) {
  return base::read_floating<std::endian::big>(strm, state, sizeof(T),
                                               (char *)(&value));
}

/**
 * @brief Dump a floating-point value to the stream
 *
 * @tparam T floating-point type to dump
 * @param strm stream to write to
 * @param state dumping state
 * @param value value object to read
 * @return result of the dump
 */
template <std::floating_point T> inline DumpResult write_float(ARGS_WRITE(T)) {
  return base::write_floating<std::endian::big>(strm, state, sizeof(T),
                                                (char *)(&value));
}

} // namespace java

// Bedrock implementation
// ----------------------------------------------------------------------------
namespace bedrock {

/**
 * @brief Parse a floating-point value from the stream
 *
 * @tparam T floating-point type to parse
 * @param strm stream to read from
 * @param state parsing state
 * @param value value object to fill
 * @return result of the parsing
 */
template <std::floating_point T> inline ParseResult read_float(ARGS_READ(T)) {
  return base::read_floating<std::endian::little>(strm, state, sizeof(T),
                                                  (char *)(&value));
}

/**
 * @brief Dump a floating-point value to the stream
 *
 * @tparam T floating-point type to dump
 * @param strm stream to write to
 * @param state dumping state
 * @param value value object to read
 * @return result of the dump
 */
template <std::floating_point T> inline DumpResult write_float(ARGS_WRITE(T)) {
  return base::write_floating<std::endian::big>(strm, state, sizeof(T),
                                                (char *)(&value));
}

} // namespace bedrock

// General-purpose implementation
// ----------------------------------------------------------------------------
#define ARGS_FWD strm, state, value

/**
 * @brief Parse an integral value from the stream
 *
 * @tparam T integral type to parse
 * @tparam GV targeted game version
 * @param strm stream to read from
 * @param state parsing state
 * @param value value object to fill
 * @return result of the parsing
 */
template <std::floating_point T, GameVersion GV = GameVersion::JAVA>
ParseResult read_float(ARGS_READ(T)) {
  if constexpr (GV == GameVersion::JAVA)
    return java::read_float(ARGS_FWD);
  return bedrock::read_float(ARGS_FWD);
}

/**
 * @tparam GV targeted game version
 * @brief Dump a floating-point value to the stream
 *
 * @tparam T floating-point type to dump
 * @tparam GV targeted game version
 * @param strm stream to write to
 * @param state dumping state
 * @param value value object to read
 * @return result of the dump
 */
template <std::floating_point T, GameVersion GV = GameVersion::JAVA>
inline DumpResult write_float(ARGS_WRITE(T)) {
  if constexpr (GV == GameVersion::JAVA)
    return java::write_float(ARGS_FWD);
  return bedrock::write_float(ARGS_FWD);
}

#undef ARGS_FWD

// ============================================================================
// Exports
// ============================================================================
#define EXPORT(type)                                                           \
  extern template ParseResult read_float<type, GameVersion::JAVA>(             \
      ARGS_READ(type));                                                        \
  extern template ParseResult read_float<type, GameVersion::BEDROCK>(          \
      ARGS_READ(type));                                                        \
  extern template DumpResult write_float<type, GameVersion::JAVA>(             \
      ARGS_WRITE(type));                                                       \
  extern template DumpResult write_float<type, GameVersion::BEDROCK>(          \
      ARGS_WRITE(type));

EXPORT(float)
EXPORT(double)

#undef EXPORT
#undef ARGS_READ
#undef ARGS_WRITE

} // namespace minecraft::nbt::byte
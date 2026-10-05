// ============================================================================
// Project: SOLISMC-IO
//
// Implementation of base functions for integral type byte parsing
//
// Author    Meltwin (github@meltwin.fr)
// Date      10/08/2026 (created 10/08/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#include "minecraft/io/nbt/bytes/base/integral.hxx"
#include <cstdint>

#include "byte_helper.hxx"
#include "minecraft/io/nbt/bytes/base/common.hxx"

namespace minecraft::nbt::byte::base {

// ============================================================================
// Implementations
// ============================================================================
#define ARGS_READ                                                              \
  Stream &strm, IntRWState &state, const uint8_t tlen, char *value
#define ARGS_WRITE                                                             \
  Stream &strm, IntRWState &state, const uint8_t tlen, const char *value
#define FWD strm, state, tlen, value

template <std::endian endianess>
inline ParseResult parse_int_from_bytes(ARGS_READ) {
  state.processed +=
      helper::read_bytes<endianess>(strm, value, tlen, state.processed);
  return (state.left(tlen) == 0) ? ParseResult::ENDED : ParseResult::UNFINISHED;
}

template <std::endian endianess>
inline DumpResult write_int_from_bytes(ARGS_WRITE) {
  state.processed +=
      helper::write_bytes<endianess>(strm, value, tlen, state.processed);
  return (state.left(tlen) == 0) ? DumpResult::ENDED : DumpResult::UNFINISHED;
}

// ============================================================================
// Endianess bindings
// ============================================================================

#define BIND(endianess)                                                        \
  template <> ParseResult read_integral<endianess>(ARGS_READ) {                \
    return parse_int_from_bytes<endianess>(FWD);                               \
  }                                                                            \
  template <> DumpResult write_integral<endianess>(ARGS_WRITE) {               \
    return write_int_from_bytes<endianess>(FWD);                               \
  }

BIND(std::endian::little)
BIND(std::endian::big)

} // namespace minecraft::nbt::byte::base

#undef ARGS_READ
#undef ARGS_WRITE

// ============================================================================
// Export
// ============================================================================
namespace minecraft::nbt::byte {

#define ARGS_READ(T) Stream &strm, IntRWState &state, T &value
#define ARGS_WRITE(T) Stream &strm, IntRWState &state, T const &value
#define EXPORT(type)                                                           \
  template ParseResult read_int<type, GameVersion::JAVA>(ARGS_READ(type));     \
  template ParseResult read_int<type, GameVersion::BEDROCK>(ARGS_READ(type));  \
  template DumpResult write_int<type, GameVersion::JAVA>(ARGS_WRITE(type));    \
  template DumpResult write_int<type, GameVersion::BEDROCK>(ARGS_WRITE(type));

EXPORT(int8_t);
EXPORT(int16_t);
EXPORT(int32_t);
EXPORT(int64_t);

} // namespace minecraft::nbt::byte
// ============================================================================
// Project: SOLISMC_IO
//
// Implementation of base functions for floating-point type byte parsing
//
// Author    Meltwin (github@meltwin.fr)
// Date      30/08/2026 (created 30/08/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#include "minecraft/io/nbt/bytes/base/float.hxx"

#include "byte_helper.hxx"
#include "minecraft/io/nbt/bytes/base/common.hxx"

namespace minecraft::nbt::byte::base {

// ============================================================================
// Implementations
// ============================================================================
#define ARGS Stream &strm, FloatRWState &state, const uint8_t tlen, char *value
#define FWD strm, state, tlen, value

template <std::endian endianess>
inline ParseResult parse_float_from_bytes(ARGS) {
  state.processed +=
      helper::read_bytes<endianess>(strm, value, tlen, state.processed);
  ;
  return (state.left(tlen) == 0) ? ParseResult::ENDED : ParseResult::UNFINISHED;
}

template <std::endian endianess>
inline DumpResult write_float_from_bytes(ARGS) {
  state.processed +=
      helper::write_bytes<endianess>(strm, value, tlen, state.processed);
  return (state.left(tlen) == 0) ? DumpResult::ENDED : DumpResult::UNFINISHED;
}

// ============================================================================
// Endianess bindings
// ============================================================================

#define BIND(endianess)                                                        \
  template <> ParseResult read_floating<endianess>(ARGS) {                     \
    return parse_float_from_bytes<endianess>(FWD);                             \
  }                                                                            \
  template <> DumpResult write_floating<endianess>(ARGS) {                     \
    return write_float_from_bytes<endianess>(FWD);                             \
  }

BIND(std::endian::little)
BIND(std::endian::big)

} // namespace minecraft::nbt::byte::base

#undef ARGS

// ============================================================================
// Export
// ============================================================================
namespace minecraft::nbt::byte {

#define ARGS(T) Stream &strm, FloatRWState &state, T &value
#define EXPORT(type)                                                           \
  template ParseResult read_float<type, GameVersion::JAVA>(ARGS(type));        \
  template ParseResult read_float<type, GameVersion::BEDROCK>(ARGS(type));     \
  template DumpResult write_float<type, GameVersion::JAVA>(ARGS(type));        \
  template DumpResult write_float<type, GameVersion::BEDROCK>(ARGS(type));

EXPORT(float);
EXPORT(double);

} // namespace minecraft::nbt::byte
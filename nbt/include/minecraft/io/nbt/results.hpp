// ============================================================================
// Project: SOLISMC-FILEIO
//
// Definition of result values
//
// Author    Meltwin (github@meltwin.fr)
// Date      13/06/2026 (created 13/06/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#ifndef SOLISMC_IO_NBT_COMMON_RESULTS
#define SOLISMC_IO_NBT_COMMON_RESULTS

#include <cstdint>

namespace minecraft::nbt {

// ============================================================================
// Results
// ============================================================================

enum class ParseResult : uint8_t {
  ENDED = 0,      //< The parsing ended successfully with 0 or more bytes left
  UNFINISHED = 1, //< The parsing has not ended yet
};

constexpr const char *to_string(const ParseResult R) {
  if (R == ParseResult::ENDED) {
    return "ENDED";
  }
  return "UNFINISHED";
}

enum class WriteResult : uint8_t {
  ENDED = 0,      //< The writing ended successfully with 0 or more bytes left
  UNFINISHED = 1, //< The writing has not ended yet
};

constexpr const char *to_string(const WriteResult R) {
  if (R == WriteResult::ENDED) {
    return "ENDED";
  }
  return "UNFINISHED";
}

} // namespace minecraft::nbt

#endif
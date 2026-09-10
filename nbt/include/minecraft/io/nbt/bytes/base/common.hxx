// ============================================================================
// Project: SOLISMC-IO
//
// Common resources for byte IO
//
// Author    Meltwin (github@meltwin.fr)
// Date      10/08/2026 (created 10/08/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#pragma once

#include <algorithm>
#include <concepts>
#include <cstddef>
#include <cstdint>

namespace minecraft::nbt::byte {

// ============================================================================
// Parse / dump results
// ============================================================================

/**
 * @brief Result of the byte parsing
 */
enum class ParseResult : uint8_t {
  UNFINISHED, //< Parsing is not finished yet
  ENDED       //< Parsing has ended
};

/**
 * @brief Result of the byte parsing
 */
enum class DumpResult : uint8_t {
  UNFINISHED, //< Dump is not finished yet
  ENDED       //< Dump has ended
};

// ============================================================================
// Stream container
// ============================================================================

/**
 * @brief Stream container
 */
struct Stream {
  char *data = std::nullptr_t{};
  std::size_t n{0};

  /**
   * @brief Increase the stream iterator
   */
  inline void inc(std::size_t const i = 1) {
    if (n < i)
      return;
    auto to_add = std::min(i, n);
    data += to_add;
    n -= to_add;
  }
};

// ============================================================================
// Generic parsing/dumping state
// ============================================================================
template <std::unsigned_integral T> struct RWState {
  T processed{0};

  inline auto left(T size) const {
    return static_cast<std::size_t>(size - processed);
  }
};

} // namespace minecraft::nbt::byte
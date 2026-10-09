#pragma once
// ============================================================================
// Project: SOLISMC_IO
//
// Tags <-> string methods
//
// Author    Meltwin (github@meltwin.fr)
// Date      07/10/2026 (created 07/10/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#include "minecraft/io/nbt/tags.hxx"

#include <algorithm>
#include <iterator>
#include <string>
#include <string_view>

namespace minecraft::nbt::app {

// ============================================================================

/**
 * @brief Convert a string value to a Tags enumeration
 *
 * @param tag tag string representation
 */
constexpr Tags from_string(std::string_view const &tag) {
  using enum Tags;

  std::string lowered{};
  std::ranges::transform(tag, std::back_inserter(lowered),
                         [](unsigned char c) { return std::toupper(c); });

#define X(T, _)                                                                \
  if (lowered.compare(#T) == 0)                                                \
    return T;
#include "minecraft/io/nbt/.xmacros/tags.x"
#undef X
  return COMPOUND;
}

// ============================================================================

/**
 * @brief Convert a tag to a string value
 *
 * @param tag
 * @return constexpr Tags
 */
constexpr const char *to_string(Tags tag) { return to_str(tag); }

} // namespace minecraft::nbt::app
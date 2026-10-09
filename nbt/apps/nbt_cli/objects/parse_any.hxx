// ============================================================================
// Project: SOLISMC_IO
//
// Parse from any tag
//
// Author    Meltwin (github@meltwin.fr)
// Date      09/10/2026 (created 09/10/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#pragma once

#include <any>
#include <cstdint>
#include <string_view>

#include "minecraft/io/nbt/bytes/errors.hxx"
#include "minecraft/io/nbt/tags.hxx"

namespace minecraft::nbt::app {

// ============================================================================
// Content parsing
// ============================================================================
inline std::any parse_from_tag(std::string_view str, Tags tag) {
  using enum Tags;

  switch (tag) {
    // Integral types
  case BYTE:
    return (int8_t)std::strtol(str.data(), nullptr, 16);
  case SHORT:
    return (int16_t)std::strtol(str.data(), nullptr, 10);
  case INT:
    return (int32_t)std::strtol(str.data(), nullptr, 10);
  case LONG:
    return std::strtol(str.data(), nullptr, 10);
  // Floating point type
  case FLOAT:
    return (float)std::strtod(str.data(), nullptr);
  case DOUBLE:
    return std::strtod(str.data(), nullptr);

  // Default: raise an exception
  default:
    throw byte::errors::UnsupportedTag(tag, "app::parse_from_tag");
  }
}

} // namespace minecraft::nbt::app

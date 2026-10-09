#pragma once
// ============================================================================
// Project: SOLISMC_IO
//
// Value formatting utilities
//
// Author    Meltwin (github@meltwin.fr)
// Date      07/10/2026 (created 07/10/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#include <cstdint>
#include <format>

#include "objects/list.hxx"

namespace minecraft::nbt::app {

/**
 * @brief Format any value to ostream compatible objects
 */
template <typename T> inline auto fmt_value(T value) { return value; }

/**
 * @brief Format byte value
 */
template <> inline auto fmt_value<>(int8_t value) {
  return std::format("{:X}", static_cast<uint8_t>(value));
}

template <> inline auto fmt_value(List value) { return list_export(value); }

} // namespace minecraft::nbt::app

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

#include "objects/compound.hxx"
#include "objects/list.hxx"

namespace minecraft::nbt::app {

template <class T>
concept Printable = requires(std::ostream &os, T a) { os << a; };

/**
 * @brief Format any value to ostream compatible objects
 */
template <typename T> inline void fmt_value(std::ostream &os, T const &value) {
  os << value;
}

/**
 * @brief Format byte value
 */
template <> inline void fmt_value<>(std::ostream &os, int8_t const &value) {
  os << std::format("{:X}", static_cast<uint8_t>(value));
}

template <> inline void fmt_value(std::ostream &os, List const &value) {
  os << list_export(value);
}

template <> inline void fmt_value(std::ostream &os, Compound const &value) {
  os << compound_export(value);
}

} // namespace minecraft::nbt::app

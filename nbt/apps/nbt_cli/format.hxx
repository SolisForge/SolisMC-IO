#pragma once
// ================================================================================================
// Project: SOLISMC_IO
//
// Value formatting utilities
//
// Author    Meltwin (github@meltwin.fr)
// Date      13/10/2026 (created 07/10/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ================================================================================================
#include <cstdint>
#include <format>
#include <ostream>

#include "minecraft/io/nbt/objects/list.hxx"
#include "objects/compound.hxx"
#include "objects/list.hxx"

namespace minecraft::nbt::app {
// ================================================================================================
// General format function
// ================================================================================================

template<typename T>
concept Printable = requires(std::ostream &os, T const &a) { os << a; };
template<typename T>
concept Exportable =
        Printable<T> ||
        requires(std::ostream &os, T const &value) { fmt_value(os, value); };

/**
 * @brief Format any value to ostream compatible objects
 */
template<typename T>
inline void fmt_value(std::ostream &os, T const &value) {
    os << value;
}

// ================================================================================================
// Specialized formats
// ================================================================================================

/**
 * @brief Format byte value
 */
template<>
inline void fmt_value<>(std::ostream &os, int8_t const &value) {
    os << std::format("{:X}", static_cast<uint8_t>(value));
}

template<>
inline void fmt_value<>(std::ostream &os, List const &value) {
    fmt_list(os, value);
}

template<>
inline void fmt_value<>(std::ostream &os, Compound const &value) {
    os << compound_export(value);
}

template<IsVector E>
inline void fmt_value(std::ostream &os, E const &value) {
    // Display values
    std::size_t i{0};
    os << "[";
    for (auto const &item: value) {
        fmt_value<typename VecElem < E>::E_t > (os, item);
        if (i++ < value.size() - 1)
            os << ",";
    }
    os << "]";
}
} // namespace minecraft::nbt::app
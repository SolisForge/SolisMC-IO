// ================================================================================================
// Project: SOLISMC_IO
//
// NBT byte IO errors
//
// Author    Meltwin (github@meltwin.fr)
// Created   18/10/2026
// ================================================================================================

// ============================================================================
// Version   1.0.0
// Modified  23/10/2026
// Copyright Solis Forge | 2026 - 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#pragma once

#include <fmt/format.h>

#include "minecraft/io/nbt/errors.hxx"

namespace minecraft::nbt::byte::errors {
// ================================================================================================

/**
 * @brief Initialized a parser from a toolbox without selecting it beforehand
 */
struct NBT_EXPORT AnyParseError final : solis::SolisError {
    explicit AnyParseError(const std::string_view msg) :
        solis::SolisError(fmt::format("Could not parse std::any : {:s}", msg)) {}
};

// ================================================================================================

/**
 * @brief No parser could be selected for this field
 */
struct NBT_EXPORT UnknownFieldParserError final : solis::SolisError {
    explicit UnknownFieldParserError(const std::string_view field_name, const Tags tag) :
        SolisError(fmt::format("Could not select parser for field {:s} [{:s}]", field_name,
                               to_string(tag))) {}
};

// ================================================================================================

/**
 * @brief Initialized a parser from a toolbox without selecting it beforehand
 */
struct NBT_EXPORT UninitializedParser final : solis::SolisError {
    explicit UninitializedParser() : solis::SolisError("Parser was not previously initialized") {}
};

// ================================================================================================

/**
 * @brief Initialized a parser from a toolbox without selecting it beforehand
 */
struct NBT_EXPORT UninitializedWriter final : solis::SolisError {
    explicit UninitializedWriter() : solis::SolisError("Writer was not previously initialized") {}
};
} // namespace minecraft::nbt::byte::errors

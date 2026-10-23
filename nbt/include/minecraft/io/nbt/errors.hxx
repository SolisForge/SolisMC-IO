// ================================================================================================
// Project: SOLISMC_IO
//
// Common NBT errors
//
// Author    Meltwin (github@meltwin.fr)
// Created   10/10/2026
// ================================================================================================

// ============================================================================
// Version   1.0.0
// Modified  23/10/2026
// Copyright Solis Forge | 2026 - 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#pragma once

#include <format>

#include <solis/utils/errors.hpp>

#include "minecraft/io/nbt/lib_export.hxx"
#include "minecraft/io/nbt/tags.hxx"

namespace minecraft::nbt::errors {
// ================================================================================================

/**
 * @brief Bad cast from std::any
 */
struct NBT_EXPORT BadAnyCastError final : solis::SolisError {
    static constexpr std::string_view BASE_MSG{"Bad cast from std::any"};

    explicit BadAnyCastError(const std::string_view function) :
        solis::SolisError(std::format("{} from function {:s}", BASE_MSG, function)) {}

    explicit BadAnyCastError(const Tags tag, const std::string_view function) :
        solis::SolisError(std::format("{:s} of value type {:s} from function {:s}", BASE_MSG,
                                      to_string(tag), function)) {}
};

// ================================================================================================

/**
 * @brief Field could not be found in map
 */
struct NBT_EXPORT FieldNotFoundError final : solis::SolisError {
    explicit FieldNotFoundError(std::string_view name) :
        solis::SolisError(std::format("Field {:s} could not be found!", name)) {}
};

// ================================================================================================

/**
 * @brief Expected and processed tags does not match
 */
struct NBT_EXPORT MismatchedTag final : solis::SolisError {
    explicit MismatchedTag(const Tags expected, const Tags processed,
                           const std::string_view function) :
        solis::SolisError(
                std::format("Mismatched tag expected={:s} != processed={:s} in function {:s}",
                            to_string(expected), to_string(processed), function)) {}
};

// ================================================================================================

/**
 * @brief Calling to a function with an unsupported tag
 */
struct NBT_EXPORT UnsupportedTag final : solis::SolisError {
    explicit UnsupportedTag(const Tags tag, const std::string_view function) :
        solis::SolisError(
                std::format("Unsupported tag {:s} in function {:s}", to_string(tag), function)) {}
};
} // namespace minecraft::nbt::errors

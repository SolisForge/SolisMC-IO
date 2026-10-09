// ============================================================================
// Project: SOLISMC_IO
//
// Compound encoding / decoding for the nbt utility app
//
// Author    Meltwin (github@meltwin.fr)
// Date      09/10/2026 (created 09/10/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#pragma once

#include <string>
#include <string_view>

#include "minecraft/io/nbt/compound.hxx"

namespace minecraft::nbt::app {
/**
 * @brief Export a compound to a string representation
 */
std::string compound_export(Compound const &);

/**
 * @brief Import a compound from a string representation
 */
Compound compound_import(std::string_view);

} // namespace minecraft::nbt::app
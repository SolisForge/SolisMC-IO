#pragma once
// ============================================================================
// Project: SOLISMC_IO
//
// List encoding / decoding for the nbt utility app
//
// Author    Meltwin (github@meltwin.fr)
// Date      13/10/2026 (created 07/10/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#include "minecraft/io/nbt/objects/list.hxx"

namespace minecraft::nbt::app {

// ============================================================================
// List import / export
// ============================================================================

/**
 * @brief Import a list from a string representation
 */
List list_import(std::string_view);

/**
 * @brief Export a list to a string representation
 */
void fmt_list(std::ostream &, List const &);

} // namespace minecraft::nbt::app
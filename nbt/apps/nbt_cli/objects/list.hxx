#pragma once
// ============================================================================
// Project: SOLISMC_IO
//
// List encoding / decoding for the nbt utility app
//
// Author    Meltwin (github@meltwin.fr)
// Date      07/10/2026 (created 07/10/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#include "minecraft/io/nbt/list.hxx"

#include <any>
#include <string>

namespace minecraft::nbt::app {

/**
 * @brief Parse any value from its tag
 *
 * @return std::any
 */
std::any parse_from_tag(std::string_view, Tags);

/**
 * @brief Import a list from a string representation
 */
List list_import(std::string_view);

/**
 * @brief Import a list from a string representation
 */
std::string list_export(List const &);

} // namespace minecraft::nbt::app
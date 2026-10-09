// ============================================================================
// Project: SOLISMC_IO
//
// Implementation of compound encoding / decoding for the nbt utility app
//
// Author    Meltwin (github@meltwin.fr)
// Date      09/10/2026 (created 09/10/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#include "compound.hxx"
#include "minecraft/io/nbt/compound.hxx"

namespace minecraft::nbt::app {

// ============================================================================

Compound compound_import(std::string_view str) { return Compound{}; }

// ============================================================================

std::string compound_export(Compound const &c) { return std::string{}; }

} // namespace minecraft::nbt::app
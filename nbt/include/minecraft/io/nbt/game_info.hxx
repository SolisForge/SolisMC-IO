// ================================================================================================
// Project: SOLISMC-IO
//
// Game information enumerations
//
// Author    Meltwin (github@meltwin.fr)
// Created   10/08/2026
// ================================================================================================

// ============================================================================
// Version   1.0.0
// Modified  23/10/2026
// Copyright Solis Forge | 2026 - 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#pragma once

#include <cstdint>

#include "minecraft/io/nbt/lib_export.hxx"


namespace minecraft {
/**
 * @brief Game released versions type
 */
enum class NBT_EXPORT GameVersion : uint8_t { JAVA, BEDROCK };
} // namespace minecraft

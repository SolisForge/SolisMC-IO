// ============================================================================
// Project: SOLISMC_IO
//
// Parse any NBT value
//
// Author    Meltwin (github@meltwin.fr)
// Date      14/09/2026 (created 14/09/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#pragma once
#include "minecraft/io/nbt/bytes/base/common.hxx"
#include "minecraft/io/nbt/tags.hxx"
#include <any>

using minecraft::nbt::Tags;
using minecraft::nbt::byte::Stream;

std::any parse_any(Stream &strm, Tags elem_type) {}

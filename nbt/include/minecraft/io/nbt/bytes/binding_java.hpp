// ============================================================================
// Project: SOLISMC-FILEIO
//
// Java bindings for NBT byte parsing
//
// Author    Meltwin (github@meltwin.fr)
// Date      13/06/2026 (created 13/06/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#ifndef SOLISMC_IO_NBT_BYTE_JAVA
#define SOLISMC_IO_NBT_BYTE_JAVA

#include "minecraft/io/nbt/bytes/float.hpp"
#include "minecraft/io/nbt/bytes/integral.hpp"
#include "minecraft/io/nbt/bytes/interface.hpp"

#define GAME_VERSION GameVersion::JAVA

namespace minecraft::nbt {

// ============================================================================
// Java specific parsers
// ============================================================================
namespace java {

template <typename T>
using ByteParser = minecraft::nbt::byte::base::ByteParser<T, GAME_VERSION>;
template <typename T>
using ByteWriter = minecraft::nbt::byte::base::ByteWriter<T, GAME_VERSION>;
} // namespace java

namespace byte::base {

// ============================================================================
// Parser/writter specialization registration
// ============================================================================
template <std::integral T>
REGISTER_TEMPLATED_BYTE_PARSER(T, GAME_VERSION, IntegralByteParser);
template <std::integral T>
REGISTER_TEMPLATED_BYTE_WRITER(T, GAME_VERSION, IntegralByteWriter);
template <std::floating_point T>
REGISTER_TEMPLATED_BYTE_PARSER(T, GAME_VERSION, FloatByteParser);
template <std::floating_point T>
REGISTER_TEMPLATED_BYTE_WRITER(T, GAME_VERSION, FloatByteWriter);

// ============================================================================
// Common type declaration
// ============================================================================
DECLARE_COMMON_NBT_PARSER(GAME_VERSION, int8_t, int16_t, int32_t, int64_t);
DECLARE_COMMON_NBT_PARSER(GAME_VERSION, uint8_t, uint16_t, uint32_t, uint64_t);
DECLARE_COMMON_NBT_PARSER(GAME_VERSION, float, double);
} // namespace byte::base

} // namespace minecraft::nbt

#undef GAME_VERSION

#endif
// ============================================================================
// Project: SOLISMC-FILEIO
//
//
//
// Author    Meltwin (github@meltwin.fr)
// Date      04/06/2026 (created 04/06/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#ifndef SOLISMC_IO_NBT_BYTE_PARSING
#define SOLISMC_IO_NBT_BYTE_PARSING

#include "minecraft/io/nbt/bytes/base.hpp"     // IWYU pragma: keep
#include "minecraft/io/nbt/bytes/integral.hpp" // IWYU pragma: keep
#include "minecraft/io/nbt/bytes/interface.hpp"

namespace minecraft::nbt {

using ParseResult = NBT_NAMESPACE(NBT_VARIANT)::ParseResult;

template <typename T>
using ByteParser = NBT_NAMESPACE(NBT_VARIANT)::ByteParser<T>;
template <typename T>
using ByteWriter = NBT_NAMESPACE(NBT_VARIANT)::ByteWriter<T>;

} // namespace minecraft::nbt

#endif
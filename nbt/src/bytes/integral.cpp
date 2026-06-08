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
#include "minecraft/io/nbt/bytes/integral.hpp"
#include <concepts>

namespace minecraft::nbt::byte {

template <std::integral T> void IntegralByteParser<T>::foo(int a) const {
  std::cout << a + 20 << std::endl;
}

// Force definition of these ByteParser in this library
EXPORT_COMMON_NBT_PARSER(int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t,
                         int64_t, uint64_t)

} // namespace minecraft::nbt::byte

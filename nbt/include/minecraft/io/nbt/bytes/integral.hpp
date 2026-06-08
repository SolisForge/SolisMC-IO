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
#ifndef SOLISMC_IO_NBT_BYTE_PARSING_INTEGRAL
#define SOLISMC_IO_NBT_BYTE_PARSING_INTEGRAL

#include "minecraft/io/nbt/bytes/base.hpp"
#include <concepts>
#include <cstdint>

namespace minecraft::nbt::byte {

template <std::integral T>
struct IntegralByteParser : public ByteParserInterface {

  /**
   * @brief Integral parser
   *
   * @param a
   */
  void foo(int a) const override;
};

// ============================================================================
// Specialization registration
// ============================================================================
template <std::integral T> REGISTER_BYTE_PARSER(T, IntegralByteParser);

DECLARE_COMMON_NBT_PARSER(int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t,
                          int64_t, uint64_t)

} // namespace minecraft::nbt::byte

#endif
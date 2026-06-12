// ============================================================================
// Project: SOLISMC-FILEIO
//
// Integral-types NBT parser & writer declaration
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
#include "minecraft/io/nbt/bytes/interface.hpp"
#include <concepts>
#include <cstdint>

namespace NBT_NAMESPACE(NBT_VARIANT) {

// ============================================================================

/**
 * @brief Implementation of the byte parser for the integral types (int, short,
 * ...)
 */
template <std::integral T>
struct IntegralByteParser : public ByteParserInterface {

  static constexpr uint8_t TYPE_LENGTH = sizeof(T);

  ParseResult parse(Stream &strm, Size &n) override;

  inline bool is_done() override { return read_bytes == TYPE_LENGTH; }

  void reset() override;

  /**
   * @brief Get the read value if the parser is done, else 0
   */
  inline T get() { return (is_done()) ? value : 0; }

private:
  T value{0};
  uint8_t read_bytes{0};
};

// ============================================================================

/**
 * @brief Implementation of the byte writer for the integral types (int, short,
 * ...)
 */
template <std::integral T>
struct IntegralByteWriter : public ByteWriterInterface {};

// ============================================================================
// Common specialization registration
// ============================================================================
template <std::integral T>
REGISTER_TEMPLATED_BYTE_PARSER(T, IntegralByteParser);
template <std::integral T>
REGISTER_TEMPLATED_BYTE_WRITER(T, IntegralByteWriter);

DECLARE_COMMON_NBT_PARSER(int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t,
                          int64_t, uint64_t)

DECLARE_COMMON_NBT_WRITER(int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t,
                          int64_t, uint64_t)

} // namespace NBT_NAMESPACE(NBT_VARIANT)

#endif
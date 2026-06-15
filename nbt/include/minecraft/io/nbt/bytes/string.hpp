// ============================================================================
// Project: SOLISMC-FILEIO
//
// String-types NBT parser & writer declaration
//
// Author    Meltwin (github@meltwin.fr)
// Date      13/06/2026 (created 13/06/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#ifndef SOLISMC_IO_NBT_BYTE_PARSING_STRING
#define SOLISMC_IO_NBT_BYTE_PARSING_STRING

#include "minecraft/io/nbt/bytes/integral.hpp" // IWYU pragma: keep
#include <cstdint>
#include <string>

namespace minecraft::nbt::byte::base {

/**
 * @brief Implementation of the byte parser for the string types
 */
template <GameVersion GV> struct StringByteParser : public ByteParserInterface {

  ParseResult parse(Stream &strm, Size &n) override;

  bool is_done() const override;

  /**
   * @brief Reset the parser internal state.
   */
  void reset() override;

  /**
   * @brief Get the read value if the parser is done, else an empty string
   */
  inline std::string get() {
    return (is_done()) ? std::move(value) : std::string{};
  }

private:
  IntegralByteParser<int32_t, GV> int_parser;
  std::string value{};
  uint8_t read_bytes{0};
};

// ============================================================================

/**
 * @brief Implementation of the byte writer for the integral types (int, short,
 * ...)
 */
template <GameVersion GV>
struct StringByteWriter : public ByteWriterInterface {};

// ============================================================================
// Common specialization registration
// ============================================================================

// DECLARE_COMMON_NBT_PARSER(float, double)

// DECLARE_COMMON_NBT_WRITER(float, double)

} // namespace minecraft::nbt::byte::base

#endif
// ============================================================================
// Project: SOLISMC-FILEIO
//
// NBT lists parser & writer declaration
//
// Author    Meltwin (github@meltwin.fr)
// Date      04/06/2026 (created 04/06/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#ifndef SOLISMC_IO_NBT_BYTE_PARSING_LIST
#define SOLISMC_IO_NBT_BYTE_PARSING_LIST

#include "minecraft/io/nbt/bytes/integral.hpp" // IWYU pragma: keep
#include <vector>

namespace minecraft::nbt::byte::base {

// ============================================================================

/**
 * @brief Implementation of the byte parser for the integral types (int, short,
 * ...)
 */
template <typename T, GameVersion GV>
struct ListByteParser : public ByteParserInterface {

  ParseResult parse(Stream &strm, Size &n) override;

  bool is_done() const override;

  void reset() override;

  /**
   * @brief Get the read value if the parser is done, else 0
   */
  inline std::vector<T> get() {
    return (is_done()) ? std::move(value) : std::vector<T>{};
  }

private:
  IntegralByteParser<uint32_t, GV> size_parser;
  ByteParser<T, GV> value_parser;
  std::vector<T> value{};
  uint32_t read_elements{0};
};

// ============================================================================

/**
 * @brief Implementation of the byte writer for the integral types (int, short,
 * ...)
 */
template <typename T, GameVersion GV>
struct ListByteWriter : public ByteWriterInterface {};

// ============================================================================
// Register common parser implementation
// ============================================================================
template <typename T>
struct ByteParser<std::vector<T>, GameVersion::JAVA>
    : ByteParserValidator<ListByteParser<T, GameVersion::JAVA>> {};
template <typename T>
struct ByteParser<std::vector<T>, GameVersion::BEDROCK>
    : ByteParserValidator<ListByteParser<T, GameVersion::BEDROCK>> {};

// Declare common NBT implementations
DECLARE_COMMON_NBT_PARSER(GameVersion::JAVA, std::vector<int8_t>,
                          std::vector<int32_t>, std::vector<int64_t>);
DECLARE_COMMON_NBT_PARSER(GameVersion::BEDROCK, std::vector<int8_t>,
                          std::vector<int32_t>, std::vector<int64_t>);

} // namespace minecraft::nbt::byte::base

#endif
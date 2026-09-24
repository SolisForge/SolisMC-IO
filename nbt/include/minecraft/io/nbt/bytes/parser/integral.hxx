// ============================================================================
// Project: SOLISMC_IO
//
// Stateful parser for integral types
//
// Author    Meltwin (github@meltwin.fr)
// Date      24/09/2026 (created 24/09/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#pragma once

#include "minecraft/game_info.hxx"
#include "minecraft/io/nbt/bytes/base/integral.hxx"
#include "minecraft/io/nbt/bytes/parser/interface.hxx"

namespace minecraft::nbt::byte {

// ============================================================================
// Parser defintion
// ============================================================================

/**
 * @brief Stateful parser for integral types
 */
template <std::integral T, GameVersion GV>
struct IntegralParser : public ByteParser {

  /**
   * @brief Parse an integral type value from a stream
   *
   * @param strm stream to parse the integral value from
   * @return result of the parsing
   */
  ParseResult parse(Stream &strm) override;

  /**
   * @brief Reset the internal state of the parser
   */
  void reset() override;

  // ------------------------------------------------------
  // Getters
  // ------------------------------------------------------

  T get() const { return value_; }

  std::any any_get() const override { return get(); }

private:
  IntRWState state_; //< Parsing state
  T value_;          //< Parsed value
};

// ============================================================================
// Export
// ============================================================================
#define EXPORT(type)                                                           \
  extern template struct IntegralParser<type, GameVersion::JAVA>;              \
  extern template struct IntegralParser<type, GameVersion::BEDROCK>;

EXPORT(int8_t)
EXPORT(int16_t)
EXPORT(int32_t)
EXPORT(int64_t)

#undef EXPORT

} // namespace minecraft::nbt::byte

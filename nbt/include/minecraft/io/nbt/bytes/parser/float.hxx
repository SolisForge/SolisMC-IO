// ============================================================================
// Project: SOLISMC_IO
//
// Stateful parser for floating-point types
//
// Author    Meltwin (github@meltwin.fr)
// Date      24/09/2026 (created 24/09/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#pragma once

#include "minecraft/game_info.hxx"
#include "minecraft/io/nbt/bytes/base/float.hxx"
#include "minecraft/io/nbt/bytes/parser/interface.hxx"

namespace minecraft::nbt::byte {

// ============================================================================
// Parser defintion
// ============================================================================

/**
 * @brief Stateful parser for floating point types
 */
template <std::floating_point T, GameVersion GV>
struct FloatParser : public ByteParser {

  /**
   * @brief Parse an float type value from a stream
   *
   * @param strm stream to parse the float value from
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
  FloatRWState state_; //< Parsing state
  T value_;            //< Parsed value
};

// ============================================================================
// Export
// ============================================================================
#define EXPORT(type)                                                           \
  extern template struct FloatParser<type, GameVersion::JAVA>;                 \
  extern template struct FloatParser<type, GameVersion::BEDROCK>;

EXPORT(float)
EXPORT(double)

#undef EXPORT

} // namespace minecraft::nbt::byte

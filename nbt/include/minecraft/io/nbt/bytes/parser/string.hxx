// ============================================================================
// Project: SOLISMC_IO
//
// Stateful parser for string types
//
// Author    Meltwin (github@meltwin.fr)
// Date      25/09/2026 (created 25/09/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#pragma once

#include "minecraft/game_info.hxx"
#include "minecraft/io/nbt/bytes/base/string.hxx"
#include "minecraft/io/nbt/bytes/parser/interface.hxx"

namespace minecraft::nbt::byte {

/**
 * @brief Stateful parser for integral types
 */
template <GameVersion GV> struct StringParser : public ByteParser {

  /**
   * @brief Parse a string value from a stream
   *
   * @param strm stream to parse the string from
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

  bool is_done() const override {
    return state_.size_state.left(sizeof(uint16_t)) == 0 &&
           state_.data_state.left(state_.size) == 0;
  }

  std::string get() { return std::move(value_); }

  std::any any_get() override { return get(); }

private:
  StringRWState state_; //< Parsing state
  std::string value_;   //< Parsed value
};

// ============================================================================
// Export
// ============================================================================
extern template struct StringParser<GameVersion::JAVA>;
extern template struct StringParser<GameVersion::BEDROCK>;

} // namespace minecraft::nbt::byte

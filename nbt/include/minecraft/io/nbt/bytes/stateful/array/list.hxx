// ============================================================================
// Project: SOLISMC_IO
//
// Stateful parser for NBT::List std::vector<std::any>) types
//
// Author    Meltwin (github@meltwin.fr)
// Date      28/09/2026 (created 28/09/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#pragma once
#include "minecraft/game_info.hxx"
#include "minecraft/io/nbt/bytes/base/array/list.hxx"
#include "minecraft/io/nbt/bytes/stateful/interface.hxx"
#include "minecraft/io/nbt/bytes/tool_box.hxx"

namespace minecraft::nbt::byte {

// ============================================================================

/**
 * @brief Parse for the NBT::List object
 */
template <GameVersion GV> struct ListParser : ByteParser {

  explicit ListParser<GV>(ToolBoxInterface::SharedPtr);

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

  bool is_done() const override;

  inline List get() const { return value_; }

  inline std::any any_get() override { return get(); }

private:
  ToolBoxInterface::SharedPtr toolbox_; //< Toolbox for any parsing
  ListRWState state_;                   //< Parsing state
  List value_;                          //< Parsed value
};

// ============================================================================
// Export
// ============================================================================
extern template struct ListParser<GameVersion::JAVA>;
extern template struct ListParser<GameVersion::BEDROCK>;

} // namespace minecraft::nbt::byte
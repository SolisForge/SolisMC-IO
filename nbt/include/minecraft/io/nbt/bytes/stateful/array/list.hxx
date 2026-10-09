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
#include <cstddef>

namespace minecraft::nbt::byte {

// ============================================================================
// Parser definition
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
// Writer definition
// ============================================================================

/**
 * @brief Stateful dumper for integral values
 */
template <GameVersion GV> struct ListWriter : public ByteDumper {

  explicit ListWriter<GV>(ToolBoxInterface::SharedPtr);

  /**
   * @brief Bind a new value to write
   *
   * @param value the value to write in the stream
   */
  inline void bind(std::any const &v) override { bind(std::any_cast<List>(v)); }

  /**
   * @brief Bind a new value to write
   *
   * @param value the value to write in the stream
   */
  inline void bind(List const &v) {
    value_ = &v;
    bound_ = true;
  }

  /**
   * @brief Has writer parser completed its work ?
   */
  bool is_done() const override;

  /**
   * @brief Dump the value into the stream
   *
   * @param strm byte stream to write into
   * @return result of the dump
   */
  DumpResult dump(Stream &strm) override;

  /**
   * @brief Reset the internal state of the writer
   */
  void reset() override;

private:
  ToolBoxInterface::SharedPtr toolbox_; //< Toolbox for any parsing
  ListRWState state_{};
  const List *value_ = std::nullptr_t{};
  bool bound_ = false;
};

// ============================================================================
// Export
// ============================================================================
extern template struct ListParser<GameVersion::JAVA>;
extern template struct ListParser<GameVersion::BEDROCK>;
extern template struct ListWriter<GameVersion::JAVA>;
extern template struct ListWriter<GameVersion::BEDROCK>;

} // namespace minecraft::nbt::byte
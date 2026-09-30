// ============================================================================
// Project: SOLISMC_IO
//
// Parse any NBT value
//
// Author    Meltwin (github@meltwin.fr)
// Date      14/09/2026 (created 14/09/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#pragma once
#include "minecraft/io/nbt/bytes/base/common.hxx"
#include "minecraft/io/nbt/bytes/parser/interface.hxx"
#include "minecraft/io/nbt/bytes/tool_box.hxx"
#include "minecraft/io/nbt/tags.hxx"
#include <any>
#include <cstddef>

using minecraft::nbt::Tags;
using minecraft::nbt::byte::ParserToolBoxInterface;
using minecraft::nbt::byte::Stream;

namespace minecraft::nbt::byte {

// ============================================================================
struct AnyParser : ByteParser {

  explicit AnyParser(ParserToolBoxInterface::SharedPtr toolbox)
      : ByteParser(), toolbox_(toolbox) {}

  /**
   * @brief Has the parser completed its work ?
   */
  bool is_done() const override;

  /**
   * @brief Parse a value from a stream
   *
   * @param strm stream to parse the value from
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
  std::any any_get() override;

private:
  ParserToolBoxInterface::SharedPtr toolbox_;       //< Parser toolbox
  ByteParser::SharedPtr parser_ = std::nullptr_t{}; //< Current parser
  Tags tag_ = Tags::END;                            //< Tag of the type to parse
  std::any value_;                                  //< Parsed value
};

} // namespace minecraft::nbt::byte

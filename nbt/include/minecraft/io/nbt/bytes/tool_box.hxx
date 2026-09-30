// ============================================================================
// Project: SOLISMC_IO
//
// Parser initializing structure definition
//
// This object is usefull for parsing generic types as List or Compound that
// depends on a Tags byte representation at runtime.
//
// Author    Meltwin (github@meltwin.fr)
// Date      28/09/2026 (created 28/09/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#pragma once

#include "minecraft/game_info.hxx"
#include "minecraft/io/nbt/bytes/parser/interface.hxx"
#include "minecraft/io/nbt/tags.hxx"
#include <cstddef>
#include <string>

namespace minecraft::nbt::byte {

// ============================================================================

/**
 * @brief Toolbox interface for the NBT byte parsing functions
 */
struct ParserToolBoxInterface {

  using SharedPtr = std::shared_ptr<ParserToolBoxInterface>;

  virtual ~ParserToolBoxInterface() = default;

  /**
   * @brief Select a parser for the corresponding field
   *
   * @param name name of the object field
   * @param tag NBT tag for this type
   * @param to_parse set to true if we are going to fetch a parser for this
   * field
   */
  virtual bool select(std::string const &name, Tags tag, bool to_parse) = 0;

  /**
   * @brief Get the parser for the selected field
   *
   * @return a unique pointer for the selected parser
   */
  virtual ByteParser::SharedPtr get_parser() = 0;
};

// ============================================================================
template <GameVersion> struct DefaultParserToolBox : ParserToolBoxInterface {

  /**
   * @brief Select a parser for the corresponding field
   *
   * @param name name of the object field
   * @param tag NBT tag for this type
   * @param to_parse set to true if we are going to fetch a parser for this
   * field
   */
  bool select(std::string const &name, Tags tag, bool to_parse) override;

  /**
   * @brief Get the parser for the selected field
   *
   * @return a unique pointer for the selected parser
   */
  ByteParser::SharedPtr get_parser() override;

protected:
  /**
   * @brief Get the default perser for this type
   *
   * @return ByteParser::SharedPtr
   */
  ByteParser::SharedPtr get_default_parser(Tags tag) const;

private:
  // Generic parser
  ByteParser::SharedPtr parser_ = std::nullptr_t{};
  Tags parser_tag_ = Tags::END;
};

// ============================================================================
// Export
// ============================================================================
#define EXPORT(type)                                                           \
  extern template struct DefaultParserToolBox<GameVersion::JAVA>;              \
  extern template struct DefaultParserToolBox<GameVersion::BEDROCK>;

EXPORT(float)
EXPORT(double)

#undef EXPORT

} // namespace minecraft::nbt::byte

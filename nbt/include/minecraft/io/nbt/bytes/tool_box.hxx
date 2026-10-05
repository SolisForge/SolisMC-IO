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
#include "minecraft/io/nbt/bytes/stateful/interface.hxx"
#include "minecraft/io/nbt/tags.hxx"
#include <cstddef>
#include <string>

namespace minecraft::nbt::byte {

// ============================================================================

/**
 * @brief Toolbox interface for the NBT byte parsing functions
 */
struct ToolBoxInterface {

  using SharedPtr = std::shared_ptr<ToolBoxInterface>;

  virtual ~ToolBoxInterface() = default;

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

  /**
   * @brief Get the writer for the selected field
   *
   * @return a point for the selected writer
   */
  virtual ByteDumper::SharedPtr get_writer() = 0;
};

// ============================================================================
template <GameVersion> struct DefaultToolBox : ToolBoxInterface {

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

  /**
   * @brief Get the writer for the selected field
   *
   * @return a point for the selected writer
   */
  ByteDumper::SharedPtr get_writer() override;

protected:
  /**
   * @brief Get the default parser for this type
   *
   * @return ByteParser::SharedPtr
   */
  ByteParser::SharedPtr get_default_parser(Tags tag) const;

  /**
   * @brief Get the default writer for this type
   *
   * @return ByteParser::SharedPtr
   */
  ByteDumper::SharedPtr get_default_writer(Tags tag) const;

private:
  // Generic parser
  ByteParser::SharedPtr parser_ = std::nullptr_t{};
  ByteDumper::SharedPtr writer_ = std::nullptr_t{};
  Tags selected_tag_ = Tags::END;
};

// ============================================================================
// Export
// ============================================================================
#define EXPORT(type)                                                           \
  extern template struct DefaultToolBox<GameVersion::JAVA>;                    \
  extern template struct DefaultToolBox<GameVersion::BEDROCK>;

EXPORT(float)
EXPORT(double)

#undef EXPORT

} // namespace minecraft::nbt::byte

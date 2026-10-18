// ============================================================================
// Project: SOLISMC_IO
//
// Parser initializing structure definition
//
// This object is usefull for parsing generic types as List or Compound that
// depends on a Tags byte representation at runtime.
//
// Author    Meltwin (github@meltwin.fr)
// Date      13/10/2026 (created 28/09/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#pragma once

#include "minecraft/io/nbt/bytes/stateful/interface.hxx"
#include "minecraft/io/nbt/nbt.hxx" // IWYU pragma: keep
#include <memory>
#include <string_view>

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
  virtual bool select(std::string_view name, Tags tag, bool to_parse) = 0;

  virtual bool select(Tags tag, bool to_parse) {
    return select(std::string_view{}, tag, to_parse);
  }

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
  virtual ByteWriter::SharedPtr get_writer() = 0;

  // ------------------------------------------------------
  // Easy select
  // ------------------------------------------------------

  template <typename T> inline ByteParser::SharedPtr get_parser_for() {
    select(get_tag<T>(), true);
    return get_parser();
  }

  template <typename T> inline ByteWriter::SharedPtr get_writer_for() {
    select(get_tag<T>(), false);
    return get_writer();
  }
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
  bool select(std::string_view name, Tags tag, bool to_parse) override;

  /**
   * @brief Select a parser for the corresponding field
   *
   * @param tag NBT tag for this type
   * @param to_parse set to true if we are going to fetch a parser for this
   * field
   */
  bool select(Tags tag, bool to_parser) final {
    return select(std::string_view{}, tag, to_parser);
  }

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
  ByteWriter::SharedPtr get_writer() override;

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
  ByteWriter::SharedPtr get_default_writer(Tags tag) const;

private:
  // Generic parser
  ByteParser::SharedPtr parser_ = std::nullptr_t{};
  ByteWriter::SharedPtr writer_ = std::nullptr_t{};
  Tags selected_tag_ = Tags::END;
};

// ============================================================================
// Concepts
// ============================================================================
template <typename T>
concept ParserWithToolbox =
    ParserImpl<T> && requires(ToolBoxInterface::SharedPtr p) { T(p); };

template <typename T>
concept WriterWithToolbox =
    WriterImpl<T> && requires(ToolBoxInterface::SharedPtr p) { T(p); };

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

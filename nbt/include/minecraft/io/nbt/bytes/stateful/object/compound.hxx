// ============================================================================
// Project: SOLISMC_IO
//
// Stateful parser for NBT::Compound type
//
// Author    Meltwin (github@meltwin.fr)
// Date      13/10/2026 (created 13/10/2026)
// Version   1.0.0
// ----------------------------------------------------------------------------
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#pragma once

#include "minecraft/io/nbt/bytes/stateful/interface.hxx"
#include "minecraft/io/nbt/bytes/tool_box.hxx"
#include "minecraft/io/nbt/objects/compound.hxx"
#include <cstddef>

namespace minecraft::nbt::byte {

// ============================================================================
// Parser definition
// ============================================================================

/**
 * @brief Parse for the NBT::List object
 */
template <GameVersion GV> struct Parser<Compound, GV> : ByteParser {

  explicit Parser<Compound, GV>(ToolBoxInterface::SharedPtr);

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

  inline Compound get() const { return value_; }

  inline std::any any_get() override { return get(); }

private:
  ToolBoxInterface::SharedPtr toolbox_; //< Toolbox for any parsing
  // ArrayRWState state_;                  //< Parsing state
  Compound value_; //< Parsed value
};

// ============================================================================
// Writer definition
// ============================================================================

/**
 * @brief Stateful dumper for integral values
 */
template <GameVersion GV> struct Writer<Compound, GV> : public ByteWriter {

  explicit Writer<Compound, GV>(ToolBoxInterface::SharedPtr);

  /**
   * @brief Bind a new value to write
   *
   * @param value the value to write in the stream
   */
  inline void bind(std::any const &v) override {
    bind(std::any_cast<Compound>(v));
  }

  /**
   * @brief Bind a new value to write
   *
   * @param value the value to write in the stream
   */
  inline void bind(Compound const &v) {
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
  // ArrayRWState state_{};
  const Compound *value_ = std::nullptr_t{};
  bool bound_ = false;
};

// ============================================================================
// Export
// ============================================================================
extern template struct Parser<Compound, GameVersion::JAVA>;
extern template struct Parser<Compound, GameVersion::BEDROCK>;
extern template struct Writer<Compound, GameVersion::JAVA>;
extern template struct Writer<Compound, GameVersion::BEDROCK>;

} // namespace minecraft::nbt::byte
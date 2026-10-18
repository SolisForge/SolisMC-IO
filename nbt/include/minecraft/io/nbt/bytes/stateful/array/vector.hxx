// ============================================================================
// Project: SOLISMC_IO
//
// Stateful parser for NBT::*_ARRAY (std::vector) types
//
// Author    Meltwin (github@meltwin.fr)
// Date      18/10/2026 (created 12/10/2026)
// Version   1.0.0
// ----------------------------------------------------------------------------
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#pragma once

#include <cstddef>
#include <vector>

#include "minecraft/io/nbt/bytes/base/array/vector.hxx"
#include "minecraft/io/nbt/bytes/base/common.hxx"
#include "minecraft/io/nbt/bytes/stateful/interface.hxx"
#include "minecraft/io/nbt/bytes/tool_box.hxx"
#include "minecraft/io/nbt/tags.hxx"

namespace minecraft::nbt::byte {

// ============================================================================

/**
 * @brief Return the NBT tag associated with this vector type if any, else
 * return LIST
 */
template <typename T> constexpr Tags get_type_tag() {
  const auto t = get_tag<std::vector<T>>();
  return (t == Tags::COMPOUND) ? Tags::LIST : t;
}

// ============================================================================
// Parser definition
// ============================================================================
template <typename T, GameVersion GV>
struct Parser<std::vector<T>, GV> : ByteParser {
  static constexpr auto TAG{get_type_tag<T>()}; //< Tag for this parser

  /**
   * @brief Construct a new byte parser for a vector type
   *
   * @param tb
   */
  explicit Parser<std::vector<T>, GV>(ToolBoxInterface::SharedPtr tb)
      : ByteParser() {
    tb->select(std::string{}, TAG, true);
    item_parser_ = tb->get_parser();
  }

  /**
   * @brief Parse the content of the stream
   *
   * @param strm byte stream to read from
   * @return result state of the parsing
   */
  ParseResult parse(Stream &strm) override {
    if (is_done())
      reset();
    return read_vector<T, GV>(strm, state_, value_, item_parser_);
  }

  // ------------------------------------------------------
  // Getters
  // ------------------------------------------------------

  /**
   * @brief Get the parsed vector as std::any
   */
  std::any any_get() override { return value_; }

  /**
   * @brief Get the parsed vector
   */
  decltype(auto) get() {
    auto v = std::move(value_);
    value_.resize(0);
    return v;
  }

  // ------------------------------------------------------
  // State functions
  // ------------------------------------------------------
  /**
   * @brief Has the parser completed its work ?
   */
  bool is_done() const override {
    return
        // Tag is processed1
        (TAG != Tags::LIST || state_.is_tag_processed)
        // Size is processed
        && state_.size_state.left(sizeof(ArrayRWState::ArraySize_t)) == 0
        // Payload is processed
        && state_.content_state.left(state_.size) == 0;
  };

  /**
   * @brief Reset the internal state of the parser
   */
  void reset() override {
    item_parser_->reset();
    state_.reset();
    value_.reserve(0);
  }

private:
  ByteParser::SharedPtr item_parser_; //< Parser for each item
  ArrayRWState state_;                //< Parsing state
  std::vector<T> value_;              //< Parsed value
};

// ============================================================================
// Writer definition
// ============================================================================
template <typename T, GameVersion GV>
struct Writer<std::vector<T>, GV> : ByteWriter {
  static constexpr auto TAG{get_type_tag<T>()}; //< Tag for this writer

  /**
   * @brief Construct a new byte parser for a vector type
   *
   * @param tb
   */
  explicit Writer<std::vector<T>, GV>(ToolBoxInterface::SharedPtr tb)
      : ByteWriter() {
    tb->select(std::string{}, TAG, true);
    item_writer_ = tb->get_writer();
  }

  // ------------------------------------------------------
  // Bind methods
  // ------------------------------------------------------

  /**
   * @brief Bind a new value to write
   *
   * @param value the value to write in the stream
   */
  inline void bind(std::any const &v) override {
    bind(std::any_cast<std::vector<T>>(v));
  }

  /**
   * @brief Bind a new value to write
   *
   * @param value the value to write in the stream
   */
  inline void bind(std::vector<T> const &v) {
    value_ = &v;
    bound_ = true;
  }

  // ------------------------------------------------------
  // State functions
  // ------------------------------------------------------

  /**
   * @brief Has the parser completed its work ?
   */
  bool is_done() const override {
    return
        // Tag is processed1
        (TAG != Tags::LIST || state_.is_tag_processed)
        // Size is processed
        && state_.size_state.left(sizeof(ArrayRWState::ArraySize_t)) == 0
        // Payload is processed
        && state_.content_state.left(state_.size) == 0;
  }

  /**
   * @brief Reset the internal state of the writer
   */
  void reset() override {
    item_writer_->reset();
    state_.reset();
    bound_ = false;
  }

  // ------------------------------------------------------
  // Bytes writing
  // ------------------------------------------------------

  /**
   * @brief Dump the value into the stream
   *
   * @param strm byte stream to write into
   * @return result of the dump
   */
  DumpResult dump(Stream &strm) override {
    if (is_done())
      reset();
    return write_vector<T, GV>(strm, state_, *value_, item_writer_);
  }

private:
  ByteWriter::SharedPtr item_writer_;              //< Parser for each item
  ArrayRWState state_;                             //< Dump state
  std::vector<T> const *value_ = std::nullptr_t{}; //< Dumped value
  bool bound_ = false;                             //< Was the value bound
};

// ============================================================================
// Export
// ============================================================================
#define EXPORT(T)                                                              \
  extern template struct Parser<std::vector<T>, GameVersion::JAVA>;            \
  extern template struct Parser<std::vector<T>, GameVersion::BEDROCK>;         \
  extern template struct Writer<std::vector<T>, GameVersion::JAVA>;            \
  extern template struct Writer<std::vector<T>, GameVersion::BEDROCK>;

EXPORT(int8_t)  // Tags::BYTE_ARRAY
EXPORT(int32_t) // Tags::INT_ARRAY
EXPORT(int64_t) // Tags::LONG_ARRAY

#undef EXPORT

} // namespace minecraft::nbt::byte
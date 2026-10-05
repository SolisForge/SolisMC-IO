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
#include "minecraft/io/nbt/bytes/stateful/interface.hxx"

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

  bool is_done() const override { return state_.left(sizeof(T)) == 0; }

  T get() const { return value_; }

  std::any any_get() override { return get(); }

private:
  FloatRWState state_; //< Parsing state
  T value_;            //< Parsed value
};

// ============================================================================
// Writer defintion
// ============================================================================

/**
 * @brief Stateful dumper for float values
 */
template <std::floating_point T, GameVersion GV>
struct FloatWriter : public ByteDumper {

  /**
   * @brief Bind a new value to write
   *
   * @param value the value to write in the stream
   */
  inline void bind(std::any const &v) override { bind(std::any_cast<T>(v)); }

  /**
   * @brief Bind a new value to write
   *
   * @param value the value to write in the stream
   */
  inline void bind(T const &v) {
    value_ = v;
    bound_ = true;
  }

  /**
   * @brief Has writer parser completed its work ?
   */
  inline bool is_done() const override { return state_.left(sizeof(T)) == 0; }

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
  FloatRWState state_{};
  T value_{0};
  bool bound_ = false;
};

// ============================================================================
// Export
// ============================================================================
#define EXPORT(type)                                                           \
  extern template struct FloatParser<type, GameVersion::JAVA>;                 \
  extern template struct FloatParser<type, GameVersion::BEDROCK>;              \
  extern template struct FloatWriter<type, GameVersion::JAVA>;                 \
  extern template struct FloatWriter<type, GameVersion::BEDROCK>;

EXPORT(float)
EXPORT(double)

#undef EXPORT

} // namespace minecraft::nbt::byte

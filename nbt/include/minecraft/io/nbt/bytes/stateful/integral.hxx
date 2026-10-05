// ============================================================================
// Project: SOLISMC_IO
//
// Stateful parser for integral types
//
// Author    Meltwin (github@meltwin.fr)
// Date      24/09/2026 (created 24/09/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#pragma once

#include "minecraft/game_info.hxx"
#include "minecraft/io/nbt/bytes/base/integral.hxx"
#include "minecraft/io/nbt/bytes/stateful/interface.hxx"
#include <any>

namespace minecraft::nbt::byte {

// ============================================================================
// Parser defintion
// ============================================================================

/**
 * @brief Stateful parser for integral types
 */
template <std::integral T, GameVersion GV>
struct IntegralParser : public ByteParser {

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

  bool is_done() const override { return state_.left(sizeof(T)) == 0; }

  T get() const { return value_; }

  std::any any_get() override { return get(); }

private:
  IntRWState state_; //< Parsing state
  T value_;          //< Parsed value
};

// ============================================================================
// Writer defintion
// ============================================================================

/**
 * @brief Stateful dumper for integral values
 */
template <std::integral T, GameVersion GV>
struct IntegralWriter : public ByteDumper {

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
  IntRWState state_{};
  T value_{0};
  bool bound_ = false;
};

// ============================================================================
// Export
// ============================================================================
#define EXPORT(type)                                                           \
  extern template struct IntegralParser<type, GameVersion::JAVA>;              \
  extern template struct IntegralParser<type, GameVersion::BEDROCK>;           \
  extern template struct IntegralWriter<type, GameVersion::JAVA>;              \
  extern template struct IntegralWriter<type, GameVersion::BEDROCK>;

EXPORT(int8_t)
EXPORT(int16_t)
EXPORT(int32_t)
EXPORT(int64_t)

#undef EXPORT

} // namespace minecraft::nbt::byte

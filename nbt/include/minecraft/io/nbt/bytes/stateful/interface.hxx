// ============================================================================
// Project: SOLISMC_IO
//
// Interface for the parsers objects
//
// Author    Meltwin (github@meltwin.fr)
// Date      21/09/2026 (created 21/09/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#pragma once

#include "minecraft/io/nbt/bytes/base/common.hxx"

#include <any>
#include <memory>

namespace minecraft::nbt::byte {

// ============================================================================
// Byte parsing
// ============================================================================

/**
 * @brief Interface for a byte parsing object
 */
struct ByteParser {

  using SharedPtr = std::shared_ptr<ByteParser>;

  virtual ~ByteParser() = default;

  // ------------------------------------------------------
  // Parsing-related methods
  // ------------------------------------------------------

  /**
   * @brief Has the parser completed its work ?
   */
  virtual bool is_done() const = 0;

  /**
   * @brief Parse the content of the stream
   *
   * @param strm byte stream to read from
   * @return result of the parsing
   */
  virtual ParseResult parse(Stream &strm) = 0;

  /**
   * @brief Reset the internal state of the parser
   */
  virtual void reset() = 0;

  // ------------------------------------------------------
  // Getters
  // ------------------------------------------------------

  /**
   * @brief Get the parsed value as an std::any object
   *
   * Required for generic types (e.g. List, Compound)
   */
  virtual std::any any_get() = 0;
};

// ============================================================================
// Byte dumping
// ============================================================================

/**
 * @brief Interface for a byte parsing object
 */
struct ByteDumper {
  using SharedPtr = std::shared_ptr<ByteDumper>;

  virtual ~ByteDumper() = default;

  /**
   * @brief Bind a new value to write
   *
   * @param value the value to write in the stream
   */
  virtual void bind(std::any const &value) = 0;

  /**
   * @brief Has writer parser completed its work ?
   */
  virtual bool is_done() const = 0;

  /**
   * @brief Dump the value into the stream
   *
   * @param strm byte stream to write into
   * @return result of the dump
   */
  virtual DumpResult dump(Stream &strm) = 0;

  /**
   * @brief Reset the internal state of the parser
   */
  virtual void reset() = 0;
};

} // namespace minecraft::nbt::byte
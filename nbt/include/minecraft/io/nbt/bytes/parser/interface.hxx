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

namespace minecraft::nbt::byte {

// ============================================================================
// Byte parsing
// ============================================================================

/**
 * @brief Interface for a byte parsing object
 */
struct ByteParser {

  virtual ~ByteParser() = default;

  // ------------------------------------------------------
  // Parsing-related methods
  // ------------------------------------------------------

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
  virtual std::any any_get() const = 0;
};

// ============================================================================
// Byte dumping
// ============================================================================

/**
 * @brief Interface for a byte parsing object
 */
struct ByteDumper {

  virtual ~ByteDumper() = default;

  /**
   * @brief Dump the value into the stream
   *
   * @param strm byte stream to write into
   * @return result of the dump
   */
  virtual DumpResult dump(Stream &strm) = 0;
};

} // namespace minecraft::nbt::byte
// ============================================================================
// Project: SOLISMC-FILEIO
//
// Base interface for buffered byte-operations classes
//
// Author    Meltwin (github@meltwin.fr)
// Date      09/06/2026 (created 09/06/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#ifndef SOLISMC_IO_NBT_BYTE_PARSING_INTERFACE
#define SOLISMC_IO_NBT_BYTE_PARSING_INTERFACE

#include <cstdint>
#include <type_traits>

namespace minecraft::nbt::byte {

// ============================================================================
// Results
// ============================================================================
enum class ParseResult : uint8_t {
  ENDED = 0,      //< The parsing ended successfully with 0 or more bytes left
  UNFINISHED = 1, //< The parsing has not ended yet
  NOT_ENOUGH = 2  //< Not enough bytes in the stream
};

enum class WriteResult : uint8_t {
  ENDED = 0,      //< The writing ended successfully with 0 or more bytes left
  UNFINISHED = 1, //< The writing has not ended yet
};

// ============================================================================
// Common types
// ============================================================================
using Stream = const char *;
using Size = std::size_t;

// ============================================================================
// Interfaces
// ============================================================================

/**
 * @brief Interface for the NBT byte parser implementations
 */
struct ByteParserInterface {

  virtual ~ByteParserInterface() = default;

  /**
   * @brief Parse the object from the given byte stream
   *
   * @param strm the byte stream to read from
   * @param n the number of bytes left in the stream
   * @return the state of the parsing
   */
  virtual ParseResult parse(Stream *strm, Size &n) = 0;
};

// ============================================================================

/**
 * @brief Interface for the NBT byte writer implementations
 */
struct ByteWriterInterface {

  virtual ~ByteWriterInterface() = default;

  /**
   * @brief Write the object in the given byte stream
   *
   * @param strm the byte stream to write to
   * @param n the number of bytes available for writing in the stream
   * @return the state of the writing operation
   */
  virtual ParseResult write(Stream *strm, Size &n) = 0;
};

// ============================================================================
// Concepts
// ============================================================================

template <class T>
concept IsParserImplementation = std::is_base_of_v<ByteParserInterface, T>;
template <class T>
concept IsWriterImplementation = std::is_base_of_v<ByteWriterInterface, T>;

} // namespace minecraft::nbt::byte
#endif
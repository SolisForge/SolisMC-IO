// ============================================================================
// Project: SOLISMC-FILEIO
//
// Base object of the NBT byte parsing objects
//
// Author    Meltwin (github@meltwin.fr)
// Date      04/06/2026 (created 04/06/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#ifndef SOLISMC_IO_NBT_BYTE_PARSING_BASE
#define SOLISMC_IO_NBT_BYTE_PARSING_BASE

#include "minecraft/io/nbt/bytes/interface.hpp"
#include <solis/utils/macros.hpp>

namespace minecraft::nbt::byte {

// ============================================================================
// Parser & writer selector
// ============================================================================

/**
 * @brief Selector for NBT byte parser.
 * This struct helps to validate the parser implementation.
 *
 * @tparam T object to construct from the bytes
 * @tparam _Impl implementation to use to parse this object
 */
template <typename T, IsParserImplementation _Impl>
struct ByteParserSelector : public _Impl {};
/**
 * @brief Byte parser for the given object
 *
 * @tparam T object to construct from the bytes
 */
template <typename T> struct ByteParser;

/**
 * @brief Selector for NBT byte writer.
 * This struct helps to validate the writer implementation.
 *
 * @tparam T type of the object to write as bytes
 */
template <typename T, IsWriterImplementation _Impl>
struct ByteWriterSelector : public _Impl {};
/**
 * @brief Byte writer for the given object
 *
 * @tparam T object to construct from the bytes
 */
template <typename T> struct ByteWriter;

// ============================================================================
// Helper macros
// ============================================================================
/**
 * @brief Register the byte parser implementation
 */
#define REGISTER_TEMPLATED_BYTE_PARSER(MetaVar, Impl)                          \
  struct ByteParser<MetaVar> : ByteParserSelector<MetaVar, Impl<MetaVar>> {};

/**
 * @brief Register the byte parser implementation
 */
#define REGISTER_BYTE_PARSER(MetaVar, Impl)                                    \
  struct ByteParser<MetaVar> : ByteParserSelector<MetaVar, Impl> {};

/**
 * @brief Register the byte writer implementation
 */
#define REGISTER_TEMPLATED_BYTE_WRITER(MetaVar, Impl)                          \
  struct ByteWriter<MetaVar> : ByteWriterSelector<MetaVar, Impl<MetaVar>> {};
/**
 * @brief Register the byte writer implementation
 */
#define REGISTER_BYTE_WRITER(MetaVar, Impl)                                    \
  struct ByteWriter<MetaVar> : ByteWriterSelector<MetaVar, Impl> {};

// ================================ IN HEADER =================================

/**
 * @brief Register a common parser implementation in headers
 */
#define __DECLARE_COMMON_NBT_PARSER__IMPL(T)                                   \
  extern template struct ByteParser<T>;

#define DECLARE_COMMON_NBT_PARSER(...)                                         \
  FOR_EACH(__DECLARE_COMMON_NBT_PARSER__IMPL, __VA_ARGS__)

/**
 * @brief Register a common writer implementation in headers
 */
#define __DECLARE_COMMON_NBT_WRITER__IMPL(T)                                   \
  extern template struct ByteWriter<T>;

#define DECLARE_COMMON_NBT_WRITER(...)                                         \
  FOR_EACH(__DECLARE_COMMON_NBT_WRITER__IMPL, __VA_ARGS__)

// ================================ IN SOURCE =================================

/**
 * @brief Export a common parser implementation in source
 */
#define __EXPORT_COMMON_NBT_PARSER__IMPL(T) template struct ByteParser<T>;

#define EXPORT_COMMON_NBT_PARSER(...)                                          \
  FOR_EACH(__EXPORT_COMMON_NBT_PARSER__IMPL, __VA_ARGS__)

/**
 * @brief Export a common writer implementation in source
 */
#define __EXPORT_COMMON_NBT_WRITER__IMPL(T) template struct ByteWriter<T>;

#define EXPORT_COMMON_NBT_WRITER(...)                                          \
  FOR_EACH(__EXPORT_COMMON_NBT_WRITER__IMPL, __VA_ARGS__)

// ============================================================================
// Default parser registration
// ============================================================================

} // namespace minecraft::nbt::byte

#endif
// ============================================================================
// Project: SOLISMC-FILEIO
//
// Base interface of the NBT byte parsing objects
//
// Author    Meltwin (github@meltwin.fr)
// Date      04/06/2026 (created 04/06/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#ifndef SOLISMC_IO_NBT_BYTE_PARSING_BASE
#define SOLISMC_IO_NBT_BYTE_PARSING_BASE

#include <iostream>
#include <solis/utils/macros.hpp>
#include <type_traits>

namespace minecraft::nbt::byte {

/**
 * @brief Interface for the NBT byte parser implementations
 *
 */
struct ByteParserInterface {

  virtual ~ByteParserInterface() = default;

  virtual void foo(int a) const = 0;
};

template <class T>
concept _ByteParserImpl = std::is_base_of_v<ByteParserInterface, T>;

struct DefaultParser : public ByteParserInterface {

  void foo(int a) const override { std::cout << a << std::endl; }
};

/**
 * @brief Main
 *
 * @tparam T
 */
template <typename T, _ByteParserImpl _Impl = DefaultParser>
struct ByteParser : public _Impl {};

// ============================================================================
// Helper macros
// ============================================================================
/**
 * @brief Register the byte parser implementation
 */
#define REGISTER_BYTE_PARSER(MetaVar, Impl)                                    \
  struct ByteParser<MetaVar> : ByteParser<MetaVar, Impl<MetaVar>> {};

/**
 * @brief Register a common parser implementation in headers
 */
#define __DECLARE_COMMON_NBT_PARSER__IMPL(T)                                   \
  extern template struct ByteParser<T>;

#define DECLARE_COMMON_NBT_PARSER(...)                                         \
  FOR_EACH(__DECLARE_COMMON_NBT_PARSER__IMPL, __VA_ARGS__)
/**
 * @brief Register a common parser implementation in headers
 */
#define __EXPORT_COMMON_NBT_PARSER__IMPL(T) template struct ByteParser<T>;

#define EXPORT_COMMON_NBT_PARSER(...)                                          \
  FOR_EACH(__EXPORT_COMMON_NBT_PARSER__IMPL, __VA_ARGS__)

} // namespace minecraft::nbt::byte

#endif
// ============================================================================
// Project: SOLISMC_IO
//
// NTB data type tags definition
//
// Author    Meltwin (github@meltwin.fr)
// Date      30/08/2026 (created 30/08/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#pragma once

#include <cstdint>
#include <format>
#include <string>
#include <vector>

#include <solis/utils/errors.hpp>

namespace minecraft::nbt {

using NBTTagError = solis::SolisError;

// ============================================================================
// Tags definitions
// ============================================================================

enum class Tags : uint8_t {
  END = 0,    //< End of COMPOUND object
  BYTE,       //< 8 bits signed integer
  SHORT,      //< 16 bits signed integer
  INT,        //< 32 bits signed integer
  LONG,       //< 64 bits signed integer
  FLOAT,      //< 32 bits signed floating point (IEEE 754-2008, binary32)
  DOUBLE,     //< 64 bits signed floating point (IEEE 754-2008, binary64)
  BYTE_ARRAY, // unsigned INT size + size BYTE
  STRING,     // unsigned SHORT size + size UTF-8 BYTEs (not null terminated)
  LIST,       // TAG + unsigned INT size + size items
  COMPOUND,   // [TAG + unsigned SHORT size + STRING[size] + payload] + TAG.END
  INT_ARRAY,  // unsigned INT size + size INT
  LONG_ARRAY, // unsigned INT size + size LONG
};

// ============================================================================
// Tag <-> String
// ============================================================================

/**
 * @brief Return the string representation of the given tag
 *
 * @param tag NBT tag
 * @return string representation
 */
constexpr const char *to_str(Tags const tag) {
  using enum Tags;

  switch (tag) {
    // Define x macro
#define X(tag_name)                                                            \
  case tag_name:                                                               \
    return #tag_name;

    // Generate all cases
    X(END)
#include "minecraft/io/nbt/.xmacros/tags.x"

  default:
    throw NBTTagError(std::format("Unknown tag {:d} for to_str(Tags)",
                                  static_cast<int>(tag)));
  }
}

// ============================================================================

constexpr Tags from_string(std::string_view str) {
  using enum Tags;

  // Define x macro
#define X(tag)                                                                 \
  if (str.compare(#tag) == 0)                                                  \
    return tag;

  // Generate all cases
  X(END)
#include "minecraft/io/nbt/.xmacros/tags.x"
  throw NBTTagError(std::format("Unknow tag name {:s}", str));
}

// ============================================================================
// Byte <-> Tags
// ============================================================================

/**
 * @brief Initialize a byte from its char representation
 */
constexpr Tags from_byte(char c) { return static_cast<Tags>(c); }

/**
 * @brief Get the byte representation of the tag
 *
 * @param t
 * @return constexpr char
 */
constexpr char to_byte(Tags t) { return static_cast<char>(t); }

// ============================================================================
// Type <-> Tags
// ============================================================================
// Forward declaration of NBT types
struct List;
struct Compound;

namespace details {

// Mapping objects

template <Tags E> struct get_type_obj {
  using T = Compound;
};
template <typename T> constexpr auto get_tag() { return Tags::COMPOUND; };

#define X(tag, type)                                                           \
  template <> struct get_type_obj<Tags::tag> {                                 \
    using T = type;                                                            \
  };                                                                           \
  template <> constexpr auto get_tag<type>() { return Tags::tag; }

// Mapping listing

X(END, void)
X(BYTE, int8_t)
X(SHORT, int16_t)
X(INT, int32_t)
X(LONG, int64_t)
X(FLOAT, float)
X(DOUBLE, double)
X(STRING, std::string)
X(BYTE_ARRAY, std::vector<int8_t>)
X(LIST, List)
X(COMPOUND, Compound)
X(INT_ARRAY, std::vector<int32_t>)
X(LONG_ARRAY, std::vector<int64_t>)

#undef X

} // namespace details

// ============================================================================

/**
 * @brief Get the C++ type for the given NBT tag
 */
template <Tags E> using get_type = details::get_type_obj<E>::T;

/**
 * @brief Get the tag associated to this type
 */
template <typename T> constexpr Tags get_tag() { return details::get_tag<T>(); }

} // namespace minecraft::nbt
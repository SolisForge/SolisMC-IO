// ============================================================================
// Project: SOLISMC_IO
//
// Bytes decoder implementation
//
// Author    Meltwin (github@meltwin.fr)
// Date      30/08/2026 (created 30/08/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#include "minecraft/game_info.hxx"
#include "minecraft/io/nbt/bytes/errors.hxx"
#include "minecraft/io/nbt/bytes/tool_box.hxx"
#include "minecraft/io/nbt/tags.hxx"
#include "processing.hxx"
#include <concepts>
#include <cstdlib>
#include <iostream>
#include <ostream>

#include "minecraft/io/nbt/bytes/stateful/array/list.hxx"
#include "minecraft/io/nbt/bytes/stateful/float.hxx"
#include "minecraft/io/nbt/bytes/stateful/integral.hxx"
#include "minecraft/io/nbt/bytes/stateful/string.hxx"

using namespace minecraft::nbt::byte;

// ============================================================================
// Value formatter
// ============================================================================
template <typename T> inline auto fmt_value(T value) { return value; }
template <> inline auto fmt_value<>(int8_t value) {
  return std::format("{:X}", static_cast<uint8_t>(value));
}

// ============================================================================
// Simple types functions
// ============================================================================
template <typename T>
int display_value(T const &value, ParseResult const &result) {
  if (result == ParseResult::ENDED)
    std::cout << fmt_value(value);
  else
    std::cerr << "UNFINISHED" << std::endl;
  return (int)(result);
}

// ============================================================================
template <std::signed_integral T> int decode_integral(Stream &strm) {
  IntegralParser<T, minecraft::GameVersion::JAVA> parser;
  auto ret = parser.parse(strm);
  return display_value(parser.get(), ret);
}

// ============================================================================
template <std::floating_point T> int decode_float(Stream &strm) {
  FloatParser<T, minecraft::GameVersion::JAVA> parser;
  auto ret = parser.parse(strm);
  return display_value(parser.get(), ret);
}

// ============================================================================
int decode_string(Stream &strm) {
  StringParser<minecraft::GameVersion::JAVA> parser;
  auto ret = parser.parse(strm);
  return display_value(parser.get(), ret);
}

// ============================================================================
// List functions
// ============================================================================
template <typename T> void display_vector(std::vector<T> const &value) {
  // Display values
  std::size_t i{0};
  std::cout << "[";
  for (auto const &item : value)
    std::cout << fmt_value(item) << ((i++ < value.size() - 1) ? "," : "");
  std::cout << "]";
}

template <typename T>
int display_casted_list(minecraft::nbt::List const &value,
                        ParseResult const &result) {
  if (result == ParseResult::UNFINISHED) {
    std::cerr << "UNFINISHED" << std::endl;
    return (int)(result);
  }

  // Display values
  std::cout << to_str(value.tag());
  display_vector(value.copy_cast<T>());
  return (int)(result);
}

template <>
int display_value<>(minecraft::nbt::List const &value,
                    ParseResult const &result) {
  switch (value.tag()) {
    using enum minecraft::nbt::Tags;
  case BYTE:
    return display_casted_list<int8_t>(value, result);
  case SHORT:
    return display_casted_list<int16_t>(value, result);
  case INT:
    return display_casted_list<int32_t>(value, result);
  case LONG:
    return display_casted_list<int64_t>(value, result);
  case FLOAT:
    return display_casted_list<float>(value, result);
  case DOUBLE:
    return display_casted_list<double>(value, result);
  default:
    throw errors::UnsupportedTag{value.tag()};
  }
  return (int)(result);
}

// ============================================================================
int decode_list(Stream &strm) {
  auto toolbox =
      std::make_shared<DefaultToolBox<minecraft::GameVersion::JAVA>>();
  ListParser<minecraft::GameVersion::JAVA> parser{toolbox};
  auto ret = parser.parse(strm);
  return display_value(parser.get(), ret);
}

// ============================================================================
// Main function
// ============================================================================
int decode_bytes(std::string &bytes, const Tags tag) {
  Stream strm{bytes.data(), bytes.length()};
  switch (tag) {
    using enum minecraft::nbt::Tags;

    // Integral type
  case BYTE:
    return decode_integral<int8_t>(strm);
  case SHORT:
    return decode_integral<int16_t>(strm);
  case INT:
    return decode_integral<int32_t>(strm);
  case LONG:
    return decode_integral<int64_t>(strm);

  // Floating point type
  case FLOAT:
    return decode_float<float>(strm);
  case DOUBLE:
    return decode_float<double>(strm);

  // STRING
  case STRING:
    return decode_string(strm);

  case LIST:
    return decode_list(strm);

  default:
    throw DecodingNotImplemented(tag);
  }
}

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
#include "minecraft/io/nbt/bytes/base/common.hxx"
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

#include "format.hxx"

namespace minecraft::nbt::app {

using ParseResult = byte::ParseResult;
using Stream = byte::Stream;

// ============================================================================
// Simple types functions
// ============================================================================
template <typename T>
int display_value(T const &value, ParseResult const &result) {
  if (result == ParseResult::ENDED)
    std::cout << fmt_value<T>(value);
  else
    std::cerr << "UNFINISHED" << std::endl;
  return (int)(result);
}

// ============================================================================
template <std::signed_integral T> int decode_integral(Stream &strm) {
  byte::IntegralParser<T, minecraft::GameVersion::JAVA> parser;
  auto ret = parser.parse(strm);
  return display_value(parser.get(), ret);
}

// ============================================================================
template <std::floating_point T> int decode_float(Stream &strm) {
  byte::FloatParser<T, minecraft::GameVersion::JAVA> parser;
  auto ret = parser.parse(strm);
  return display_value(parser.get(), ret);
}

// ============================================================================
int decode_string(Stream &strm) {
  byte::StringParser<minecraft::GameVersion::JAVA> parser;
  auto ret = parser.parse(strm);
  return display_value(parser.get(), ret);
}

// ============================================================================
// List functions
// ============================================================================
int decode_list(Stream &strm) {
  auto toolbox =
      std::make_shared<byte::DefaultToolBox<minecraft::GameVersion::JAVA>>();
  byte::ListParser<minecraft::GameVersion::JAVA> parser{toolbox};
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

} // namespace minecraft::nbt::app

// ============================================================================
// Project: SOLISMC_IO
//
// Bytes encoder implementation
//
// Author    Meltwin (github@meltwin.fr)
// Date      30/08/2026 (created 30/08/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#include "minecraft/game_info.hxx"
#include "minecraft/io/nbt/bytes/base/common.hxx"
#include "minecraft/io/nbt/tags.hxx"
#include "processing.hxx"
#include <concepts>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <ostream>

#include "minecraft/io/nbt/bytes/stateful/float.hxx"
#include "minecraft/io/nbt/bytes/stateful/integral.hxx"
#include "minecraft/io/nbt/bytes/stateful/string.hxx"

using namespace minecraft::nbt::byte;
using minecraft::GameVersion;

// ============================================================================
// Helper functions
// ============================================================================
int display_value(std::string const &encoded_data, DumpResult const &result,
                  std::size_t const &tlen) {
  if (result == DumpResult::ENDED) {
    for (std::size_t i = 0; i < tlen; i++) {
      std::cout << encoded_data[i];
    }
  } else
    std::cerr << "UNFINISHED" << std::endl;
  return (int)(result);
}

// ============================================================================
template <std::signed_integral T>
int encode_integral(std::string const &value_str) {
  auto value =
      static_cast<T>(std::strtoll(value_str.c_str(), std::nullptr_t{}, 10));
  IntegralWriter<T, GameVersion::JAVA> writer{};

  // Setup the stream
  std::string out_str;
  out_str.resize(sizeof(T));
  Stream strm{out_str.data(), out_str.size()};

  // Dump value
  writer.bind(value);
  auto ret = writer.dump(strm);
  return display_value(out_str, ret, out_str.size());
}

// ============================================================================
template <std::floating_point T>
int encode_float(std::string const &value_str) {
  auto value = static_cast<T>(std::strtod(value_str.c_str(), std::nullptr_t{}));
  FloatWriter<T, GameVersion::JAVA> writer{};

  // Setup the string
  std::string out_str;
  out_str.resize(sizeof(T));
  Stream strm{out_str.data(), out_str.size()};

  // Dump value
  writer.bind(value);
  auto ret = writer.dump(strm);
  return display_value(out_str, ret, out_str.size());
}

// ============================================================================
int encode_string(std::string const &value) {
  StringWriter<GameVersion::JAVA> writer{};

  // Setup the string
  std::string out_str;
  // Size == string size - 1 to remove white spaces
  out_str.resize(sizeof(uint16_t) + value.size());
  Stream strm{out_str.data(), out_str.size()};

  // Dump value
  writer.bind(value);
  auto ret = writer.dump(strm);
  return display_value(out_str, ret, out_str.size() - 1);
}

// ============================================================================
// Main function
// ============================================================================
int encode_bytes(std::string const &value, const Tags tag) {
  switch (tag) {
    using enum minecraft::nbt::Tags;

    // Integral type
  case BYTE:
    return encode_integral<int8_t>(value);
  case SHORT:
    return encode_integral<int16_t>(value);
  case INT:
    return encode_integral<int32_t>(value);
  case LONG:
    return encode_integral<int64_t>(value);

  // Floating point type
  case FLOAT:
    return encode_float<float>(value);
  case DOUBLE:
    return encode_float<double>(value);

  // STRING
  case STRING:
    return encode_string(value);

  default:
    throw DecodingNotImplemented(tag);
  }
}

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
#include "minecraft/io/nbt/bytes/base/common.hxx"
#include "minecraft/io/nbt/tags.hxx"
#include "processing.hxx"
#include <concepts>
#include <cstdlib>
#include <iostream>
#include <ostream>

#include "minecraft/io/nbt/bytes/base/float.hxx"
#include "minecraft/io/nbt/bytes/base/integral.hxx"
#include "minecraft/io/nbt/bytes/base/string.hxx"

// ============================================================================
// Helper functions
// ============================================================================
int display_value(std::string const &encoded_data,
                  minecraft::nbt::byte::DumpResult const &result,
                  std::size_t const &tlen) {
  if (result == minecraft::nbt::byte::DumpResult::ENDED) {
    for (std::size_t i = 0; i < tlen; i++) {
      std::cout << encoded_data[i];
    }
    std::flush(std::cout);
    std::cerr << std::endl;
  } else
    std::cout << "UNFINISHED" << std::endl;
  return (int)(result);
}

// ============================================================================
template <std::signed_integral T>
int encode_integral(std::string const &value_str) {
  minecraft::nbt::byte::IntRWState state;

  // Setup the string
  std::string out_str;
  out_str.resize(sizeof(T));
  minecraft::nbt::byte::Stream strm{out_str.data(), out_str.size()};

  // Dump value
  auto value = (T)std::strtol(value_str.c_str(), nullptr, 10);
  auto ret = minecraft::nbt::byte::java::write_int<T>(strm, state, value);
  return display_value(out_str, ret, out_str.size());
}

// ============================================================================
template <std::floating_point T>
int encode_float(std::string const &value_str) {
  minecraft::nbt::byte::FloatRWState state;

  // Setup the string
  std::string out_str;
  out_str.resize(sizeof(T));
  minecraft::nbt::byte::Stream strm{out_str.data(), out_str.size()};

  // Dump value
  auto value = (T)std::strtod(value_str.c_str(), nullptr);
  auto ret = minecraft::nbt::byte::java::write_float<T>(strm, state, value);
  return display_value(out_str, ret, out_str.size());
}

// ============================================================================
int encode_string(std::string const &value) {
  minecraft::nbt::byte::StringRWState state{};

  // Setup the string
  std::string out_str;
  // Size == string size - 1 to remove white spaces
  out_str.resize(sizeof(uint16_t) + value.size());
  minecraft::nbt::byte::Stream strm{out_str.data(), out_str.size()};

  // Dump value
  auto ret = minecraft::nbt::byte::java::write_string(strm, state, value);
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

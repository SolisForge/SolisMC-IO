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
#include "minecraft/io/nbt/bytes/tool_box.hxx"
#include "minecraft/io/nbt/tags.hxx"
#include "processing.hxx"
#include <concepts>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string_view>

#include "minecraft/io/nbt/bytes/stateful/array/list.hxx"
#include "minecraft/io/nbt/bytes/stateful/float.hxx"
#include "minecraft/io/nbt/bytes/stateful/integral.hxx"
#include "minecraft/io/nbt/bytes/stateful/string.hxx"

#include "objects/list.hxx"

namespace minecraft::nbt::app {

using byte::DumpResult;
using byte::Stream;

// ============================================================================
// Helper functions
// ============================================================================
int display_value(std::string_view encoded_data, DumpResult const &result,
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
  byte::IntegralWriter<T, GameVersion::JAVA> writer{};

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
  byte::FloatWriter<T, GameVersion::JAVA> writer{};

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
  byte::StringWriter<GameVersion::JAVA> writer{};

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
int encode_list(std::string const &value) {
  // Import list
  auto list = list_import(value);

  // Setup the stream
  std::string out_str{};
  out_str.resize(sizeof(uint16_t) + list.size());
  Stream strm{out_str.data(), out_str.size()};

  // Dump value
  auto toolbox = std::make_shared<byte::DefaultToolBox<GameVersion::JAVA>>();
  byte::ListWriter<GameVersion::JAVA> writer{toolbox};
  writer.bind(list);

  // Unknown output size: encode by block
  DumpResult ret;
  constexpr auto BLOCK_SIZE{1 << 10};
  std::size_t curr_size = 0;
  std::size_t processed = 0;
  do {
    // Resize output string
    curr_size += BLOCK_SIZE;
    out_str.resize(curr_size);
    strm.data = out_str.data() + processed;
    strm.n = BLOCK_SIZE;

    // Encode more data
    ret = writer.dump(strm);
    processed += BLOCK_SIZE - strm.n;
  } while (ret == DumpResult::UNFINISHED);

  return display_value(std::string_view(out_str).substr(0, processed), ret,
                       processed);
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

  case LIST:
    return encode_list(value);

  default:
    throw EncodingNotImplemented(tag);
  }
}

} // namespace minecraft::nbt::app

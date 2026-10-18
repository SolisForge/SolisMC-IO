// ============================================================================
// Project: SOLISMC_IO
//
// Bytes decoder implementation
//
// Author    Meltwin (github@meltwin.fr)
// Date      13/10/2026 (created 30/08/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#include "minecraft/io/nbt/bytes/base/common.hxx"
#include "minecraft/io/nbt/bytes/tool_box.hxx"
#include "minecraft/io/nbt/nbt.hxx" // IWYU pragma: keep
#include "processing.hxx"
#include <cstdlib>
#include <iostream>
#include <ostream>

#include "format.hxx"

namespace minecraft::nbt::app {

static const byte::DefaultToolBox<GameVersion::JAVA>::SharedPtr NBT_TOOLBOX = {
    std::make_shared<byte::DefaultToolBox<GameVersion::JAVA>>()};

using ParseResult = byte::ParseResult;
using Stream = byte::Stream;

// ============================================================================
// Simple types functions
// ============================================================================
auto display_value(auto const &value, ParseResult const &result) {
  if (result == ParseResult::ENDED)
    fmt_value(std::cout, value);
  else
    std::cerr << "UNFINISHED" << std::endl;
  return (int)(result);
}

// ============================================================================
template <typename T> auto decode_any(Stream &strm) {
  auto parser = NBT_TOOLBOX->get_parser_for<T>();
  auto ret = parser->parse(strm);
  return display_value(std::any_cast<T>(parser->any_get()), ret);
}

// ============================================================================
// Main function
// ============================================================================
int decode_bytes(std::string &bytes, const Tags tag) {
  Stream strm{bytes.data(), bytes.length()};
  switch (tag) {
    using enum minecraft::nbt::Tags;

#define X(tag)                                                                 \
  case tag:                                                                    \
    return decode_any<get_type<tag>>(strm);
#include "minecraft/io/nbt/.xmacros/tags.x"

  default:
    throw DecodingNotImplemented(tag);
  }
}

} // namespace minecraft::nbt::app

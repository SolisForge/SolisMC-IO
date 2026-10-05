// ============================================================================
// Project: SOLISMC_IO
//
// Parser initializing structure implementation
//
// Author    Meltwin (github@meltwin.fr)
// Date      28/09/2026 (created 28/09/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#include "minecraft/io/nbt/bytes/tool_box.hxx"
#include "minecraft/game_info.hxx"
#include "minecraft/io/nbt/bytes/errors.hxx"

#include "minecraft/io/nbt/bytes/stateful/float.hxx"
#include "minecraft/io/nbt/bytes/stateful/integral.hxx"
#include "minecraft/io/nbt/bytes/stateful/interface.hxx"
#include "minecraft/io/nbt/bytes/stateful/string.hxx"

#include <cstddef>

namespace minecraft::nbt::byte {

// ============================================================================
template <GameVersion GV>
bool DefaultToolBox<GV>::select([[maybe_unused]] std::string const &name,
                                Tags tag, bool to_parse) {
  // Selecting parser
  if (to_parse && tag != selected_tag_) {
    writer_ = std::nullptr_t{};
    parser_ = get_default_parser(tag);
  }
  // Selecting writer
  else if (!to_parse && tag != selected_tag_) {
    parser_ = std::nullptr_t{};
    writer_ = get_default_writer(tag);
  }
  selected_tag_ = tag;
  return true;
}

// ============================================================================
template <GameVersion GV>
ByteParser::SharedPtr DefaultToolBox<GV>::get_default_parser(Tags tag) const {
  switch (tag) {
    using enum minecraft::nbt::Tags;
    // Integral types
  case BYTE:
    return std::make_shared<IntegralParser<int8_t, GV>>();
  case SHORT:
    return std::make_shared<IntegralParser<int16_t, GV>>();
  case INT:
    return std::make_shared<IntegralParser<int32_t, GV>>();
  case LONG:
    return std::make_shared<IntegralParser<int64_t, GV>>();
  // Float types
  case FLOAT:
    return std::make_shared<FloatParser<float, GV>>();
  case DOUBLE:
    return std::make_shared<FloatParser<double, GV>>();
  // String
  case STRING:
    return std::make_shared<StringParser<GV>>();

  default:
    throw errors::UnsupportedTag(tag);
  }
}

// ============================================================================
template <GameVersion GV>
ByteDumper::SharedPtr DefaultToolBox<GV>::get_default_writer(Tags tag) const {
  switch (tag) {
    using enum minecraft::nbt::Tags;
    // Integral types
  case BYTE:
    return std::make_shared<IntegralWriter<int8_t, GV>>();
  case SHORT:
    return std::make_shared<IntegralWriter<int16_t, GV>>();
  case INT:
    return std::make_shared<IntegralWriter<int32_t, GV>>();
  case LONG:
    return std::make_shared<IntegralWriter<int64_t, GV>>();
  // Float types
  case FLOAT:
    return std::make_shared<FloatWriter<float, GV>>();
  case DOUBLE:
    return std::make_shared<FloatWriter<double, GV>>();
    // // String
    // case STRING:
    //   return std::make_shared<StringParser<GV>>();

  default:
    throw errors::UnsupportedTag(tag);
  }
}

// ============================================================================
// Getters
// ============================================================================
template <GameVersion GV>
ByteParser::SharedPtr DefaultToolBox<GV>::get_parser() {
  if (parser_ == std::nullptr_t{})
    throw errors::UninitializedParser{};
  return parser_;
}
// ============================================================================
template <GameVersion GV>
ByteDumper::SharedPtr DefaultToolBox<GV>::get_writer() {
  if (writer_ == std::nullptr_t{})
    throw errors::UninitializedWriter{};
  return writer_;
}

// ============================================================================
// Export
// ============================================================================
#define X(GV) template struct DefaultToolBox<GV>;
#include "minecraft/io/nbt/.xmacros/game_version.x"
#undef X

} // namespace minecraft::nbt::byte
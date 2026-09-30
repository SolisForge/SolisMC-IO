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
#include "minecraft/io/nbt/bytes/parser/interface.hxx"

#include "minecraft/io/nbt/bytes/parser/float.hxx"
#include "minecraft/io/nbt/bytes/parser/integral.hxx"
#include "minecraft/io/nbt/bytes/parser/string.hxx"

namespace minecraft::nbt::byte {

// ============================================================================
template <GameVersion GV>
bool DefaultParserToolBox<GV>::select([[maybe_unused]] std::string const &name,
                                      Tags tag, bool to_parse) {
  if (to_parse && tag != parser_tag_) {
    parser_ = get_default_parser(tag);
    parser_tag_ = tag;
  }

  return true;
}

// ============================================================================
template <GameVersion GV>
ByteParser::SharedPtr
DefaultParserToolBox<GV>::get_default_parser(Tags tag) const {
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
ByteParser::SharedPtr DefaultParserToolBox<GV>::get_parser() {
  if (parser_ == std::nullptr_t{})
    throw errors::UninitializedParser{};
  return parser_;
}

// ============================================================================
// Export
// ============================================================================
template struct DefaultParserToolBox<GameVersion::JAVA>;
template struct DefaultParserToolBox<GameVersion::BEDROCK>;

} // namespace minecraft::nbt::byte
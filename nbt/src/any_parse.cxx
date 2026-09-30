// ============================================================================
// Project: SOLISMC_IO
//
// Parse any NBT value
//
// Author    Meltwin (github@meltwin.fr)
// Date      28/09/2026 (created 28/09/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#include "any_parse.hxx"
#include "minecraft/io/nbt/bytes/errors.hxx"
#include "minecraft/io/nbt/tags.hxx"

namespace minecraft::nbt::byte {

// ============================================================================
std::any AnyParser::any_get() {
  if (parser_ == nullptr)
    throw errors::UninitializedParser();
  return parser_->any_get();
}

// ============================================================================
bool AnyParser::is_done() const {
  return tag_ != Tags::END && parser_ != nullptr && parser_->is_done();
}

// ============================================================================
ParseResult AnyParser::parse(Stream &strm) {
  // If done, reset the parser
  if (is_done())
    reset();

  // Read tag
  if (tag_ == Tags::END) {
    tag_ = from_byte(strm.data[0]);
    strm.inc();

    // Setup parser
    if (!toolbox_->select(std::string{}, tag_, true))
      throw errors::AnyParseError("field selection failed");
    parser_ = toolbox_->get_parser();
    if (parser_ == nullptr)
      throw errors::AnyParseError("parser is null");
  }

  // Parse value
  return parser_->parse(strm);
}

// ============================================================================
void AnyParser::reset() {
  tag_ = Tags::END;
  parser_ = std::nullptr_t{};
}

} // namespace minecraft::nbt::byte
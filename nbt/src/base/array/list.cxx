// ============================================================================
// Project: SOLISMC_IO
//
// NBT List (std::vector<std::any>) structure parsing implementation
//
// Author    Meltwin (github@meltwin.fr)
// Date      14/09/2026 (created 14/09/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#include "minecraft/io/nbt/bytes/base/array/list.hxx"
#include "minecraft/io/nbt/bytes/base/common.hxx"
#include "minecraft/io/nbt/bytes/base/integral.hxx"
#include "minecraft/io/nbt/tags.hxx"

namespace minecraft::nbt::byte {

#define R_ARGS                                                                 \
  Stream &strm, ListRWState &state, List &value,                               \
      ParserToolBoxInterface::SharedPtr &tool_box
#define W_ARGS                                                                 \
  [[maybe_unused]] Stream &strm, [[maybe_unused]] ListRWState &state,          \
      [[maybe_unused]] List const &value,                                      \
      [[maybe_unused]] ParserToolBoxInterface::SharedPtr &tool_box
#define ARGS_FWD strm, state, value, tool_box

// ============================================================================
// Base implementation
// ============================================================================
namespace base {

template <std::endian endianness> ParseResult read_list(R_ARGS) {
  // Parse tag
  if (!state.is_tag_parsed) {
    if (strm.n == 0)
      return ParseResult::UNFINISHED;
    value.set_tag(from_byte(strm.data[0]));
    strm.inc();
    state.is_tag_parsed = true;
  }

  // Parse size
  if (state.size_state.left(sizeof(uint16_t)) > 0) {
    if (auto ret = read_integral<endianness>(
            strm, state.size_state, sizeof(uint16_t), (char *)(&state.size));
        ret != ParseResult::ENDED)
      return ret;
    value.reserve(state.size);

    // Select parser
    tool_box->select(std::string{}, value.tag(), true);
  }

  // Parse contents
  auto parser = tool_box->get_parser();
  while (state.content_state.processed < state.size) {
    if (auto ret = parser->parse(strm); ret != ParseResult::ENDED)
      return ret;
    state.content_state.processed++;
    value.push_back(parser->any_get());
  }

  return ParseResult::ENDED;
}

template <std::endian endianness> DumpResult write_list(W_ARGS) {
  return DumpResult::UNFINISHED;
}

} // namespace base

// ============================================================================
// Versions bindings
// ============================================================================

namespace java {

ParseResult read_list(R_ARGS) {
  return base::read_list<std::endian::big>(ARGS_FWD);
}

DumpResult write_list(W_ARGS) {
  return base::write_list<std::endian::big>(ARGS_FWD);
}

} // namespace java

namespace bedrock {

ParseResult read_list(R_ARGS) {
  return base::read_list<std::endian::little>(ARGS_FWD);
}

DumpResult write_list(W_ARGS) {
  return base::write_list<std::endian::little>(ARGS_FWD);
}

} // namespace bedrock

} // namespace minecraft::nbt::byte
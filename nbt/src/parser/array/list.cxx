// ============================================================================
// Project: SOLISMC_IO
//
// Stateful parser for NBT::List std::vector<std::any>) types
//
// Author    Meltwin (github@meltwin.fr)
// Date      28/09/2026 (created 28/09/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#include "minecraft/io/nbt/bytes/parser/array/list.hxx"
#include "minecraft/io/nbt/bytes/base/array/list.hxx"

namespace minecraft::nbt::byte {

// ============================================================================
template <GameVersion GV>
ListParser<GV>::ListParser(ParserToolBoxInterface::SharedPtr toolbox)
    : ByteParser(), toolbox_(toolbox) {}

// ============================================================================
template <GameVersion GV> bool ListParser<GV>::is_done() const {
  return state_.size_state.left(sizeof(uint32_t)) &&
         state_.content_state.left(state_.size) == 0;
}

// ============================================================================
template <GameVersion GV> void ListParser<GV>::reset() {
  state_ = ListRWState{};
  value_.reserve(0);
}

// ============================================================================
template <GameVersion GV> ParseResult ListParser<GV>::parse(Stream &strm) {
  if (is_done())
    reset();
  return read_list<GV>(strm, state_, value_, toolbox_);
}

// ============================================================================
// Export
// ============================================================================
template struct ListParser<GameVersion::JAVA>;
template struct ListParser<GameVersion::BEDROCK>;

} // namespace minecraft::nbt::byte
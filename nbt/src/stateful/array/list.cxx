// ============================================================================
// Project: SOLISMC_IO
//
// Stateful parser for NBT::List std::vector<std::any>) types
//
// Author    Meltwin (github@meltwin.fr)
// Created   28/09/2026
// ============================================================================

// ============================================================================
// Version   1.0.0
// Modified  23/10/2026
// Copyright Solis Forge | 2026 - 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#include "minecraft/io/nbt/bytes/stateful/array/list.hxx"
#include "minecraft/io/nbt/bytes/base/array/list.hxx"
#include "minecraft/io/nbt/bytes/stateful/interface.hxx"

namespace minecraft::nbt::byte {
// ============================================================================
// Parser implementation
// ============================================================================
template<GameVersion GV>
Parser<List, GV>::Parser(ToolBoxInterface::SharedPtr toolbox)
  : ByteParser(), toolbox_(toolbox) {
}

// ============================================================================
template<GameVersion GV>
bool Parser<List, GV>::is_done() const {
  return state_.size_state.left(sizeof(uint32_t)) &&
         state_.content_state.left(state_.size) == 0;
}

// ============================================================================
template<GameVersion GV>
void Parser<List, GV>::reset() {
  state_.reset();
  value_.reserve(0);
}

// ============================================================================
template<GameVersion GV>
ParseResult Parser<List, GV>::parse(Stream &strm) {
  if (is_done())
    reset();
  return read_list<GV>(strm, state_, value_, toolbox_);
}

// ============================================================================
// Writer implementation
// ============================================================================
template<GameVersion GV>
Writer<List, GV>::Writer(ToolBoxInterface::SharedPtr toolbox)
  : ByteWriter(), toolbox_(toolbox) {
}

// ============================================================================
template<GameVersion GV>
bool Writer<List, GV>::is_done() const {
  return state_.is_tag_processed &&
         state_.size_state.left(sizeof(List::SizeField_t)) == 0 &&
         value_ != std::nullptr_t{} &&
         state_.content_state.left(
           static_cast<List::SizeField_t>(value_->size())) == 0;
}

// ============================================================================
template<GameVersion GV>
void Writer<List, GV>::reset() {
  state_.reset();
  bound_ = false;
}

// ============================================================================
template<GameVersion GV>
DumpResult Writer<List, GV>::dump(Stream &strm) {
  if (is_done())
    reset();
  return write_list<GV>(strm, state_, *value_, toolbox_);
}
} // namespace minecraft::nbt::byte

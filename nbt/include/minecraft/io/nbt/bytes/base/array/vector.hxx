// ================================================================================================
// Project: SOLISMC_IO
//
// NBT List (std::vector<T>) structure parsing definition
//
// Author    Meltwin (github@meltwin.fr)
// Created   12/10/2026
// ================================================================================================

// ================================================================================================
// Version   1.0.0
// Modified  23/10/2026
// Copyright Solis Forge | 2026 - 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ================================================================================================
#pragma once

#include <any>
#include <vector>

#include "minecraft/io/nbt/bytes/base/array/interface.hxx"
#include "minecraft/io/nbt/bytes/base/common.hxx"
#include "minecraft/io/nbt/bytes/base/integral.hxx"
#include "minecraft/io/nbt/bytes/stateful/interface.hxx"
#include "minecraft/io/nbt/errors.hxx"
#include "minecraft/io/nbt/game_info.hxx"

namespace nbterrors = minecraft::nbt::errors;

namespace minecraft::nbt::byte {
// ================================================================================================
// Common resources
// ================================================================================================
#define R_ARGS(T)                                                              \
  Stream &strm, ArrayRWState &state, std::vector<T> &value,                    \
      ByteParser::SharedPtr &item_processor
#define W_ARGS(T)                                                              \
  Stream &strm, ArrayRWState &state, std::vector<T> const &value,              \
      ByteWriter::SharedPtr &item_processor

#define ARGS_FWD strm, state, value, item_processor

// ================================================================================================
// Base implementation
// ================================================================================================
namespace _impl {
/**
 * @brief Return the NBT tag associated with this vector type if any, else
 * return LIST
 */
template<typename T>
constexpr Tags get_vector_type_tag() {
  const auto t = get_tag<std::vector<T> >();
  return (t == Tags::COMPOUND) ? Tags::LIST : t;
}

// ================================================================================================

/**
 * @brief Generic vector reading from stream
 */
template<typename T, GameVersion GV>
ParseResult read_vector(R_ARGS(T)) {
  // Parse tag
  // ------------------------------------------------------
  // If frame should have a item tag
  if constexpr (const auto TAG = get_vector_type_tag<T>(); TAG == Tags::LIST) {
    if (!state.is_tag_processed) {
      if (strm.n == 0)
        return ParseResult::UNFINISHED;
      state.tag = from_byte(strm.data[0]);
      strm.inc();

      // Check if expected and parsed tags matches
      if (TAG != state.tag)
        throw nbterrors::MismatchedTag(TAG, state.tag, "read_vector");
      state.is_tag_processed = true;
    }
  } else {
    state.is_tag_processed = true;
  }

  // Parse size
  // ------------------------------------------------------
  if (state.size_state.left(sizeof(ArrayRWState::ArraySize_t)) != 0) {
    if (auto ret = read_int<ArrayRWState::ArraySize_t, GV>(
        strm,
        state.size_state,
        state.size);
      ret != ParseResult::ENDED)
      return ret;
    value.resize(state.size);
  }

  // Parse content
  // ------------------------------------------------------
  while (state.content_state.left(state.size) != 0) {
    if (auto ret = item_processor->parse(strm); ret != ParseResult::ENDED)
      return ret;
    value.push_back(std::any_cast<T>(item_processor->any_get()));
    item_processor->reset();
    state.content_state.processed++;
  }

  return ParseResult::ENDED;
}

// ================================================================================================

/**
 * @brief Generic vector writing to stream
 */
template<typename T, GameVersion GV>
DumpResult write_vector(W_ARGS(T)) {
  // Dump tag if needed
  // ------------------------------------------------------
  if constexpr (const auto TAG = get_vector_type_tag<T>(); TAG != Tags::LIST) {
    state.is_tag_processed = true;
  }
  // If frame should have a item tag
  else {
    if (!state.is_tag_processed) {
      if (strm.n == 0)
        return DumpResult::UNFINISHED;
      strm.data[0] = to_byte(TAG);
      strm.inc();

      state.is_tag_processed = true;
    }
  }

  // Dump size
  // ------------------------------------------------------
  if (state.size_state.left(sizeof(ArrayRWState::ArraySize_t)) != 0) {
    if (auto ret = write_int<ArrayRWState::ArraySize_t, GV>(
        strm,
        state.size_state,
        state.size);
      ret != DumpResult::ENDED)
      return ret;
  }

  // Parse content
  // ------------------------------------------------------
  while (state.content_state.left(state.size) != 0) {
    item_processor->bind(value[state.content_state.processed]);
    if (auto ret = item_processor->dump(strm); ret != DumpResult::ENDED)
      return ret;
    item_processor->reset();
    state.content_state.processed++;
  }

  return DumpResult::ENDED;
}
} // namespace _impl

// ================================================================================================
// Bindings
// ================================================================================================

// Java implementation
// ----------------------------------------------------------------------------
namespace java {
/**
 * @brief Parse a vector from the stream
 *
 * @param strm stream to read from
 * @param state parsing state
 * @param value vector to fill
 * @return result of the parsing
 */
template<typename T>
inline ParseResult read_vector(R_ARGS(T)) {
  return _impl::read_vector<T, GameVersion::JAVA>(ARGS_FWD);
}

/**
 * @brief Dump a vector to the stream
 *
 * @param strm stream to write to
 * @param state dump state
 * @param value vector to read from
 * @return state of the dumping
 */
template<typename T>
inline DumpResult write_vector(W_ARGS(T)) {
  return _impl::write_vector<T, GameVersion::JAVA>(ARGS_FWD);
}
} // namespace java

// Bedrock implementation
// ----------------------------------------------------------------------------
namespace bedrock {
/**
 * @brief Parse a vector from the stream
 *
 * @param strm stream to read from
 * @param state parsing state
 * @param value vector to fill
 * @return result of the parsing
 */
template<typename T>
ParseResult read_vector(R_ARGS(T)) {
  return _impl::read_vector<T, GameVersion::JAVA>(ARGS_FWD);
}

/**
 * @brief Dump a vector to the stream
 *
 * @param strm stream to write to
 * @param state dump state
 * @param value vector to read from
 * @return state of the dumping
 */
template<typename T>
DumpResult write_vector(W_ARGS(T)) {
  return _impl::write_vector<T, GameVersion::JAVA>(ARGS_FWD);
}
} // namespace bedrock

// General-purpose implementation
// ----------------------------------------------------------------------------

/**
 * @brief Parse a vector from the stream
 *
 * @tparam GV targeted game version
 * @param strm stream to read from
 * @param state parsing state
 * @param value vector to fill
 * @return result of the parsing
 */
template<typename T, GameVersion GV = GameVersion::JAVA>
inline ParseResult read_vector(R_ARGS(T)) {
  if constexpr (GV == GameVersion::JAVA)
    return java::read_vector(ARGS_FWD);
  return bedrock::read_vector(ARGS_FWD);
}

/**
 * @brief Dump a vector to the stream
 *
 * @tparam GV targeted game version
 * @param strm stream to write to
 * @param state dump state
 * @param value vector to read
 * @return state of the dumping
 */
template<typename T, GameVersion GV = GameVersion::JAVA>
inline DumpResult write_vector(W_ARGS(T)) {
  if constexpr (GV == GameVersion::JAVA)
    return java::write_vector(ARGS_FWD);
  return bedrock::write_vector(ARGS_FWD);
}

#undef ARGS_FWD

#undef R_ARGS
#undef W_ARGS
} // namespace minecraft::nbt::byte

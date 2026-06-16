// ============================================================================
// Project: SOLISMC-FILEIO
//
// NBT list parser & writer implementation
//
// Author    Meltwin (github@meltwin.fr)
// Date      04/06/2026 (created 04/06/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#include "minecraft/io/nbt/bytes/list.hpp" // IWYU pragma: keep
#include <cmath>

namespace minecraft::nbt::byte::base {

// ============================================================================

template <typename T, GameVersion GV>
ParseResult ListByteParser<T, GV>::parse(Stream &strm, Size &n) {
  // Reset parser if last parsing has finished to reset state
  if (is_done())
    reset();

  // Parse list size
  if (!size_parser.is_done()) {
    if (auto ret = size_parser.parse(strm, n); ret != ParseResult::ENDED)
      return ret;

    value.resize(size_parser.get());
  }

  // Parse values
  for (size_t i = read_elements; i < size_parser.get(); i++) {
    if (auto ret = value_parser.parse(strm, n); ret != ParseResult::ENDED)
      break;

    // Save value into the vector
    value[i] = value_parser.get();
    value_parser.reset();
    read_elements++;
  }
  return (is_done()) ? ParseResult::ENDED : ParseResult::UNFINISHED;
}

template <typename T, GameVersion GV>
bool ListByteParser<T, GV>::is_done() const {
  return size_parser.is_done() && read_elements == size_parser.get();
}

template <typename T, GameVersion GV> void ListByteParser<T, GV>::reset() {
  read_elements = 0;
  value = std::vector<T>{};
  size_parser.reset();
}

// ============================================================================
// Force definition of these ByteParser in this library
// ============================================================================
EXPORT_COMMON_NBT_PARSER(GameVersion::JAVA, std::vector<int8_t>,
                         std::vector<int32_t>, std::vector<int64_t>);
EXPORT_COMMON_NBT_PARSER(GameVersion::BEDROCK, std::vector<int8_t>,
                         std::vector<int32_t>, std::vector<int64_t>);

} // namespace minecraft::nbt::byte::base

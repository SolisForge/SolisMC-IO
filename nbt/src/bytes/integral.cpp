// ============================================================================
// Project: SOLISMC-FILEIO
//
// Integral-types NBT parser & writer implementation
//
// Author    Meltwin (github@meltwin.fr)
// Date      04/06/2026 (created 04/06/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#include "minecraft/io/nbt/bytes/integral.hpp"
#include "common.hpp"
#include "minecraft/io/nbt/bytes/interface.hpp"
#include <bit>
#include <cmath>
#include <concepts>
#include <cstdint>

namespace NBT_NAMESPACE(NBT_VARIANT) {

/**
 * @brief Fill a integral value from bytes
 *
 * @param strm the stream to read from
 * @param n the number of bytes left in the stream
 * @param out the integral variable to fill
 * @return the number of bytes used
 */
template <std::integral T>
constexpr uint8_t from_bytes(const Stream &strm, const Size &n, T &out,
                             uint8_t offset) {
  // Compute the loop properties
  constexpr auto TYPE_LENGTH = sizeof(T);
  const auto n_read = static_cast<uint8_t>(std::min(n, sizeof(T) - offset));

  for (uint8_t i = offset; i < offset + n_read; i++) {
    // JAVA byte parsing (values are big-endian)
    if constexpr (NBT_STREAM_BYTE_ORDER == std::endian::big)
      out += cvt_byte<T>(strm[i]) << ((TYPE_LENGTH - i - 1) * BIT_PER_BYTE);
    // BEDROCK byte parsing (values are little-endian)
    else
      out += cvt_byte<T>(strm[i]) << (i * BIT_PER_BYTE);
  }
  return n_read;
}

// ============================================================================

template <std::integral T>
ParseResult IntegralByteParser<T>::parse(Stream &strm, Size &n) {
  // If we are reading a new value
  if (read_bytes == TYPE_LENGTH)
    reset();

  // Read more bytes into the integral value
  auto n_bytes = from_bytes<T>(strm, n, value, read_bytes);
  read_bytes += n_bytes;
  strm += n_bytes;
  n -= n_bytes;
  return (read_bytes == TYPE_LENGTH) ? ParseResult::ENDED
                                     : ParseResult::UNFINISHED;
}

template <std::integral T> void IntegralByteParser<T>::reset() {
  read_bytes = 0;
  value = 0;
}

// ============================================================================
// Common specialization registration
// ============================================================================
// Force definition of these ByteParser in this library
EXPORT_COMMON_NBT_PARSER(int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t,
                         int64_t, uint64_t)

} // namespace NBT_NAMESPACE(NBT_VARIANT)

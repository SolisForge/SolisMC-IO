// ============================================================================
// Project: SOLISMC_IO
//
// Export for byte parsing of common list
//
// Author    Meltwin (github@meltwin.fr)
// Date      18/10/2026 (created 18/10/2026)
// Version   1.0.0
// ----------------------------------------------------------------------------
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#include "minecraft/io/nbt/bytes/stateful/array/vector.hxx"

namespace minecraft::nbt::byte {

#define EXPORT(tag)                                                            \
  template struct Parser<get_type<tag>, GameVersion::JAVA>;                    \
  template struct Parser<get_type<tag>, GameVersion::BEDROCK>;                 \
  template struct Writer<get_type<tag>, GameVersion::JAVA>;                    \
  template struct Writer<get_type<tag>, GameVersion::BEDROCK>;

EXPORT(Tags::BYTE_ARRAY);
EXPORT(Tags::INT_ARRAY);
EXPORT(Tags::LONG_ARRAY);

} // namespace minecraft::nbt::byte

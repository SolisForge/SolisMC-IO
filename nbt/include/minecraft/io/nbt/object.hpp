// ============================================================================
// Project: SOLISMC-FILEIO
//
// NBT Object parsing implementation
//
// Author    Meltwin (github@meltwin.fr)
// Date      09/06/2026 (created 09/06/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#ifndef SOLISMC_IO_NBT_BYTE_PARSING_OBJECT
#define SOLISMC_IO_NBT_BYTE_PARSING_OBJECT

#include "minecraft/io/nbt/bytes/base.hpp"

namespace NBT_NAMESPACE(NBT_VARIANT) {

struct NBTObject {};

/**
 * @brief Parser for NBT objects
 * Act as the default parser
 */
struct NBTObjectParser : ByteParserInterface {};

/**
 * @brief Parser for NBT objects
 * Act as the default parser
 */
struct NBTObjectWriter : ByteWriterInterface {};

// ============================================================================
// Specialization registration
// ============================================================================
template <> REGISTER_BYTE_PARSER(NBTObject, NBTObjectParser);
template <> REGISTER_BYTE_WRITER(NBTObject, NBTObjectWriter);

} // namespace NBT_NAMESPACE(NBT_VARIANT)

#endif
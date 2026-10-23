// ================================================================================================
// Project: SOLISMC_IO
//
// Interface for the parsers objects
//
// Author    Meltwin (github@meltwin.fr)
// Created   21/09/2026
// ================================================================================================

// ============================================================================
// Version   1.0.0
// Modified  23/10/2026
// Copyright Solis Forge | 2026 - 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#pragma once

#include "minecraft/io/nbt/bytes/base/common.hxx"
#include "minecraft/io/nbt/game_info.hxx"
#include "minecraft/io/nbt/lib_export.hxx"

#include <any>
#include <memory>

namespace minecraft::nbt::byte {
// ================================================================================================
// Byte parsing
// ================================================================================================

/**
 * @brief Interface for a byte parsing object
 */
struct NBT_EXPORT ByteParser {
    using SharedPtr = std::shared_ptr<ByteParser>;

    virtual ~ByteParser() = default;

    // ------------------------------------------------------
    // Parsing-related methods
    // ------------------------------------------------------

    /**
     * @brief Has the parser completed its work ?
     */
    [[nodiscard]] virtual bool is_done() const = 0;

    /**
     * @brief Parse the content of the stream
     *
     * @param strm byte stream to read from
     * @return result of the parsing
     */
    virtual ParseResult parse(Stream &strm) = 0;

    /**
     * @brief Reset the internal state of the parser
     */
    virtual void reset() = 0;

    // ------------------------------------------------------
    // Getters
    // ------------------------------------------------------

    /**
     * @brief Get the parsed value as an std::any object
     *
     * Required for generic types (e.g. List, Compound)
     */
    virtual std::any any_get() = 0;
};

/**
 * @brief Type restriction to byte parser implementations
 */
template<typename T>
concept ParserImpl = std::is_base_of_v<ByteParser, T>;

// ================================================================================================
// Byte writing
// ================================================================================================

/**
 * @brief Interface for a byte parsing object
 */
struct NBT_EXPORT ByteWriter {
    using SharedPtr = std::shared_ptr<ByteWriter>;

    virtual ~ByteWriter() = default;

    /**
     * @brief Bind a new value to write
     *
     * @param value the value to write in the stream
     */
    virtual void bind(std::any const &value) = 0;

    /**
     * @brief Has writer parser completed its work ?
     */
    [[nodiscard]] virtual bool is_done() const = 0;

    /**
     * @brief Dump the value into the stream
     *
     * @param strm byte stream to write into
     * @return result of the dump
     */
    virtual DumpResult dump(Stream &strm) = 0;

    /**
     * @brief Reset the internal state of the parser
     */
    virtual void reset() = 0;

protected:
    bool bound_ = false;
};

/**
 * @brief Type restriction to byte writer implementations
 */
template<typename T>
concept WriterImpl = std::is_base_of_v<ByteWriter, T>;

// ================================================================================================
// Declaration of generic parser and writer
// ================================================================================================

template<typename, GameVersion>
struct NBT_EXPORT Parser {};

template<typename, GameVersion>
struct NBT_EXPORT Writer {};
} // namespace minecraft::nbt::byte

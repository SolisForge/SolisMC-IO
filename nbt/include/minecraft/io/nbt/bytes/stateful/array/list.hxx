// ================================================================================================
// Project: SOLISMC_IO
//
// Stateful parser for NBT::List std::vector<std::any>) types
//
// Author    Meltwin (github@meltwin.fr)
// Created   28/09/2026
// ================================================================================================

// ================================================================================================
// Version   1.0.0
// Modified  23/10/2026
// Copyright Solis Forge | 2026 - 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ================================================================================================
#pragma once
#include <cstddef>
#include "minecraft/io/nbt/bytes/base/array/interface.hxx"
#include "minecraft/io/nbt/bytes/stateful/interface.hxx"
#include "minecraft/io/nbt/bytes/tool_box.hxx"

namespace minecraft::nbt::byte {
// ================================================================================================
// Parser definition
// ================================================================================================

/**
 * @brief Parse for the NBT::List object
 */
template<GameVersion GV>
struct Parser<List, GV> final : ByteParser {
    explicit Parser(ToolBoxInterface::SharedPtr);

    /**
     * @brief Parse an integral type value from a stream
     *
     * @param strm stream to parse the integral value from
     * @return result of the parsing
     */
    ParseResult parse(Stream &strm) override;

    /**
     * @brief Reset the internal state of the parser
     */
    void reset() override;

    // ------------------------------------------------------
    // Getters
    // ------------------------------------------------------

    [[nodiscard]] bool is_done() const override;

    [[nodiscard]] auto get() const { return std::move(value_); }

    std::any any_get() override { return get(); }

private:
    ToolBoxInterface::SharedPtr toolbox_; //< Toolbox for any parsing
    ArrayRWState state_; //< Parsing state
    List value_; //< Parsed value
};

// ================================================================================================
// Writer definition
// ================================================================================================

/**
 * @brief Stateful dumper for integral values
 */
template<GameVersion GV>
struct Writer<List, GV> final : ByteWriter {
    explicit Writer(ToolBoxInterface::SharedPtr);

    /**
     * @brief Bind a new value to write
     *
     * @param v the value to write in the stream
     */
    inline void bind(std::any const &v) override { bind(std::any_cast<List>(v)); }

    /**
     * @brief Bind a new value to write
     *
     * @param v the value to write in the stream
     */
    inline void bind(List const &v) {
        value_ = &v;
        bound_ = true;
    }

    /**
     * @brief Has writer parser completed its work ?
     */
    [[nodiscard]] bool is_done() const override;

    /**
     * @brief Dump the value into the stream
     *
     * @param strm byte stream to write into
     * @return result of the dump
     */
    DumpResult dump(Stream &strm) override;

    /**
     * @brief Reset the internal state of the writer
     */
    void reset() override;

private:
    ToolBoxInterface::SharedPtr toolbox_; //< Toolbox for any parsing
    ArrayRWState state_{};
    const List *value_ = std::nullptr_t{};
    bool bound_ = false;
};
} // namespace minecraft::nbt::byte

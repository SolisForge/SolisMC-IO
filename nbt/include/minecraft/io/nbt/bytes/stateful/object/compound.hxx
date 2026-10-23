// ================================================================================================
// Project: SOLISMC_IO
//
// Stateful parser for NBT::Compound (std::map<std::string, std::any>) types
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

#include <cstddef>
#include "minecraft/io/nbt/bytes/stateful/interface.hxx"
#include "minecraft/io/nbt/bytes/stateful/string.hxx"
#include "minecraft/io/nbt/bytes/tool_box.hxx"
#include "minecraft/io/nbt/objects/compound.hxx"

namespace minecraft::nbt::byte {
// ================================================================================================
// Base implementation
// ================================================================================================
/**
 * State for reading / parsing compound objects
 */
struct CompoundRWState {
    // Tag parsing
    Tags tag{Tags::END};

    // Name parsing
    StringRWState name_state;
    std::string name{};

    // Flags
    bool tag_parsed = false;
    bool elem_parsed = false;

    void reset() {
        // Tag
        tag = Tags::END;
        tag_parsed = false;

        // Name
        name_state.reset();
        name.clear();
    }
};

// ================================================================================================
// Parser definition
// ================================================================================================

/**
 * @brief Parse for the NBT::List object
 */
template<GameVersion GV>
struct Parser<Compound, GV> final : ByteParser {
    /**
     * @brief Initialize a new compound parser
     */
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
    void reset() override {
        reset_element();
        value_ = Compound();
    }

    // ------------------------------------------------------
    // Getters
    // ------------------------------------------------------

    bool is_done() const override;

    decltype(auto) get() { return std::move(value_); }

    std::any any_get() override { return value_; }

private:
    ToolBoxInterface::SharedPtr toolbox_; //< Toolbox for any parsing
    Parser<std::string, GV> name_parser_; //< Parser for the field name
    CompoundRWState state_; //< Parsing state
    Compound value_; //< Parsed value

    void reset_element() { state_.reset(); }
};

// ================================================================================================
// Writer definition
// ================================================================================================

/**
 * @brief Stateful dumper for integral values
 */
template<GameVersion GV>
struct Writer<Compound, GV> final : ByteWriter {
    explicit Writer(ToolBoxInterface::SharedPtr);

    /**
     * @brief Bind a new value to write
     *
     * @param v the value to write in the stream
     */
    void bind(std::any const &v) override { bind(std::any_cast<Compound>(v)); }

    /**
     * @brief Bind a new value to write
     *
     * @param v the value to write in the stream
     */
    void bind(Compound const &v) {
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
    CompoundRWState state_{};
    const Compound *value_ = std::nullptr_t{};
    bool bound_ = false;
};
} // namespace minecraft::nbt::byte

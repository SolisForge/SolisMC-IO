// ================================================================================================
// Project: SOLISMC_IO
//
// Stateful parser for string types
//
// Author    Meltwin (github@meltwin.fr)
// Created   25/09/2026
// ================================================================================================

// ================================================================================================
// Version   1.0.0
// Modified  23/10/2026
// Copyright Solis Forge | 2026 - 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ================================================================================================
#pragma once

#include <cstddef>
#include "minecraft/io/nbt/bytes/base/string.hxx"
#include "minecraft/io/nbt/bytes/stateful/interface.hxx"

namespace minecraft::nbt::byte {
// ================================================================================================
// Parser definition
// ================================================================================================

/**
 * @brief Stateful parser for integral types
 */
template<GameVersion GV>
struct Parser<std::string, GV> final : ByteParser {
    /**
     * @brief Parse a string value from a stream
     *
     * @param strm stream to parse the string from
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

    [[nodiscard]] bool is_done() const override {
        return state_.size_state.left(sizeof(uint16_t)) == 0 &&
               state_.data_state.left(state_.size) == 0;
    }

    std::string get() { return std::move(value_); }

    std::any any_get() override { return get(); }

private:
    StringRWState state_; //< Parsing state
    std::string value_; //< Parsed value
};

// ================================================================================================
// Writer definition
// ================================================================================================

/**
 * @brief Stateful dumper for integral values
 */
template<GameVersion GV>
struct Writer<std::string, GV> final : ByteWriter {
    /**
     * @brief Bind a new value to write
     *
     * @param v the value to write in the stream
     */
    void bind(std::any const &v) override { bind(std::any_cast<std::string>(v)); }

    /**
     * @brief Bind a new value to write
     *
     * @param v the value to write in the stream
     */
    void bind(std::string const &v) {
        value_ = &v;
        bound_ = true;
    }

    /**
     * @brief Has writer parser completed its work ?
     */
    [[nodiscard]] bool is_done() const override {
        return state_.size_state.left(sizeof(uint16_t)) == 0 && value_ != std::nullptr_t{} &&
               state_.data_state.left(static_cast<uint16_t>(value_->size())) == 0;
    }

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
    static constexpr std::string_view EMPTY{};

    StringRWState state_{};
    const std::string *value_ = std::nullptr_t{};
    bool bound_ = false;
};
} // namespace minecraft::nbt::byte

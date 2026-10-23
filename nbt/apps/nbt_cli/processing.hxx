// ================================================================================================
// Project: SOLISMC_IO
//
// Bytes decoder
//
// Author    Meltwin (github@meltwin.fr)
// Date      18/10/2026 (created 30/08/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ================================================================================================
#pragma once
#include <format>
#include <string>

#include <solis/utils/errors.hpp>

#include "minecraft/io/nbt/tags.hxx"

using minecraft::nbt::Tags;

namespace minecraft::nbt::app {
// ================================================================================================
struct DecodingNotImplemented : public solis::SolisError {
    explicit DecodingNotImplemented(Tags const tag)
        : solis::SolisError(std::format(
            "Decoding for type {} is not implemented ",
            to_string(tag))) {
    }
};

// ================================================================================================
struct EncodingNotImplemented : public solis::SolisError {
    explicit EncodingNotImplemented(Tags const tag)
        : solis::SolisError(std::format(
            "Encoding for type {} is not implemented ",
            to_string(tag))) {
    }
};

// ================================================================================================
int decode_bytes(std::string &bytes, Tags const tag);

// ================================================================================================
int encode_bytes(std::string_view value, Tags const tag);
} // namespace minecraft::nbt::app
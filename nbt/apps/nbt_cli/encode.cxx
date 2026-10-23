// ================================================================================================
// Project: SOLISMC_IO
//
// Bytes encoder implementation
//
// Author    Meltwin (github@meltwin.fr)
// Date      18/10/2026 (created 10/09/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ================================================================================================
#include "minecraft/io/nbt/bytes/base/common.hxx"
#include "minecraft/io/nbt/bytes/tool_box.hxx"
#include "minecraft/io/nbt/nbt.hxx" // IWYU pragma: keep
#include "processing.hxx"
#include <concepts>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string_view>

#include "objects/list.hxx"

namespace minecraft::nbt::app {
static const byte::DefaultToolBox<GameVersion::JAVA>::SharedPtr NBT_TOOLBOX = {
    std::make_shared<byte::DefaultToolBox<GameVersion::JAVA> >()
};

using byte::DumpResult;
using byte::Stream;

// ================================================================================================
// Helper functions
// ================================================================================================
int display_value(std::string_view encoded_data, DumpResult const &result,
                  std::size_t const &tlen) {
    if (result == DumpResult::ENDED) {
        for (std::size_t i = 0; i < tlen; i++) {
            std::cout << encoded_data[i];
        }
    } else
        std::cerr << "UNFINISHED" << std::endl;
    return (int) (result);
}

// ================================================================================================
// Run the parser for any type
// ================================================================================================
constexpr auto BLOCK_SIZE{1 << 10};

template<typename T>
int encode_any(T &value, std::size_t block_size = BLOCK_SIZE) {
    auto writer = NBT_TOOLBOX->get_writer_for<T>();
    writer->bind(value);

    // Setup the stream
    std::string out_str{};
    out_str.resize(0);
    Stream strm{out_str.data(), out_str.size()};

    // Unknown output size: encode by block
    DumpResult ret;
    std::size_t curr_size = 0;
    std::size_t processed = 0;
    do {
        // Resize output string
        curr_size += block_size;
        out_str.resize(curr_size);
        strm.data = out_str.data() + processed;
        strm.n = block_size;

        // Encode more data
        ret = writer->dump(strm);
        processed += block_size - strm.n;
    } while (ret == DumpResult::UNFINISHED);

    return display_value(std::string_view(out_str).substr(0, processed),
                         ret,
                         processed);
}

// ================================================================================================
// String -> T conversions
// ================================================================================================
template<std::signed_integral T>
int encode_integral(std::string_view value_str) {
    auto value =
            static_cast<T>(std::strtoll(value_str.data(), std::nullptr_t{}, 10));
    return encode_any(value, sizeof(T));
}

// ================================================================================================
template<std::floating_point T>
int encode_float(std::string_view value_str) {
    auto value = static_cast<T>(std::strtod(value_str.data(), std::nullptr_t{}));
    return encode_any(value, sizeof(T));
}

// ================================================================================================
int encode_string(std::string_view value) {
    std::string s{value};
    return encode_any(s);
}

// ================================================================================================
int encode_list(std::string_view value) {
    auto list = list_import(value);
    return encode_any(list);
}

// ================================================================================================
// Main function
// ================================================================================================
int encode_bytes(std::string_view value, const Tags tag) {
    switch (tag) {
            using enum minecraft::nbt::Tags;

        // Integral type
        case BYTE:
            return encode_integral<int8_t>(value);
        case SHORT:
            return encode_integral<int16_t>(value);
        case INT:
            return encode_integral<int32_t>(value);
        case LONG:
            return encode_integral<int64_t>(value);

        // Floating point type
        case FLOAT:
            return encode_float<float>(value);
        case DOUBLE:
            return encode_float<double>(value);

        // STRING
        case STRING:
            return encode_string(value);

        case LIST:
            return encode_list(value);

        default:
            throw EncodingNotImplemented(tag);
    }
}
} // namespace minecraft::nbt::app
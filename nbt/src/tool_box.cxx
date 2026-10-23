// ================================================================================================
// Project: SOLISMC_IO
//
// Parser initializing structure implementation
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
#include "minecraft/io/nbt/bytes/tool_box.hxx"
#include "minecraft/io/nbt/bytes/errors.hxx"
#include "minecraft/io/nbt/tags.hxx"

// Stateful parsers
#include "minecraft/io/nbt/bytes/stateful/array/list.hxx"
#include "minecraft/io/nbt/bytes/stateful/array/vector.hxx"
#include "minecraft/io/nbt/bytes/stateful/float.hxx"
#include "minecraft/io/nbt/bytes/stateful/integral.hxx"
#include "minecraft/io/nbt/bytes/stateful/interface.hxx"
#include "minecraft/io/nbt/bytes/stateful/object/compound.hxx"
#include "minecraft/io/nbt/bytes/stateful/string.hxx"

using minecraft::nbt::errors::UnsupportedTag;

namespace minecraft::nbt::byte {
// ================================================================================================
template<GameVersion GV>
bool DefaultToolBox<GV>::select([[maybe_unused]] std::string_view name, const Tags tag,
                                const bool to_parse) {
    // Selecting parser
    if (to_parse && tag != selected_tag_) {
        writer_ = std::nullptr_t{};
        parser_ = get_default_parser(tag);
    }
    // Selecting writer
    else if (!to_parse && tag != selected_tag_) {
        parser_ = std::nullptr_t{};
        writer_ = get_default_writer(tag);
    }
    selected_tag_ = tag;
    return true;
}

// ================================================================================================
// Parser & Writers initialization functions
// ================================================================================================

template<ParserImpl P, typename Callable = void>
static ByteParser::SharedPtr init_parser(Callable) {
    return std::make_shared<P>();
}

template<ParserWithToolbox P, typename Callable>
static ByteParser::SharedPtr init_parser(Callable c) {
    return std::make_shared<P>(c());
}

template<WriterImpl P, typename Callable = void>
static ByteWriter::SharedPtr init_writer(Callable) {
    return std::make_shared<P>();
}

template<WriterWithToolbox P, typename Callable>
static ByteWriter::SharedPtr init_writer(Callable c) {
    return std::make_shared<P>(c());
}

// ================================================================================================
template<GameVersion GV>
ByteParser::SharedPtr DefaultToolBox<GV>::get_default_parser(Tags tag) const {
    using enum minecraft::nbt::Tags;

    constexpr auto get_default_parser = []() { return std::make_shared<DefaultToolBox<GV>>(); };

    switch (tag) {
#define X(tag)                                                                                     \
    case tag:                                                                                      \
        return init_parser<Parser<get_type<tag>, GV>>(get_default_parser);

#include "minecraft/io/nbt/.xmacros/tags.x"


        default:
            throw UnsupportedTag(tag, "libnbt::get_default_parser");
    }
}

// ================================================================================================
template<GameVersion GV>
ByteWriter::SharedPtr DefaultToolBox<GV>::get_default_writer(Tags tag) const {
    using enum minecraft::nbt::Tags;

    constexpr auto get_default_writer = []() { return std::make_shared<DefaultToolBox<GV>>(); };

    switch (tag) {
#define X(tag)                                                                                     \
    case tag:                                                                                      \
        return init_writer<Writer<get_type<tag>, GV>>(get_default_writer);

#include "minecraft/io/nbt/.xmacros/tags.x"


        default:
            throw UnsupportedTag(tag, "libnbt::get_default_writer");
    }
}

// ================================================================================================
// Getters
// ================================================================================================
template<GameVersion GV>
ByteParser::SharedPtr DefaultToolBox<GV>::get_parser() {
    if (parser_ == std::nullptr_t{})
        throw errors::UninitializedParser{};
    return parser_;
}

// ================================================================================================
template<GameVersion GV>
ByteWriter::SharedPtr DefaultToolBox<GV>::get_writer() {
    if (writer_ == std::nullptr_t{})
        throw errors::UninitializedWriter{};
    return writer_;
}

// ================================================================================================
// Export
// ================================================================================================
#define X_VERSION(GV) template struct DefaultToolBox<GV>;
#include "minecraft/io/nbt/.xmacros/game_version.x"
} // namespace minecraft::nbt::byte

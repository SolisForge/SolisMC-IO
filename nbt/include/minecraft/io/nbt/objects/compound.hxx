// ================================================================================================
// Project: SOLISMC_IO
//
// Definition of the NBT Compound object.
//
// This object behaves as a map which can store any elements
//
// Author    Meltwin (github@meltwin.fr)
// Created   09/10/2026
// ================================================================================================

// ============================================================================
// Version   1.0.0
// Modified  23/10/2026
// Copyright Solis Forge | 2026 - 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#pragma once

#include <functional>
#include <unordered_map>

#include <solis/utils/errors.hpp>

#include "minecraft/io/nbt/errors.hxx"
#include "minecraft/io/nbt/lib_export.hxx"
#include "minecraft/io/nbt/objects/field.hxx"

namespace minecraft::nbt {
// ================================================================================================

/**
 * @brief Heterogenous hasher for unordered_map
 */
struct string_hash {
    using is_transparent = void; // Enables heterogeneous operations.

    [[nodiscard]] size_t operator()(const char *txt) const {
        return std::hash<std::string_view>{}(txt);
    }

    [[nodiscard]] size_t operator()(std::string_view txt) const {
        return std::hash<std::string_view>{}(txt);
    }

    [[nodiscard]] size_t operator()(const std::string &txt) const {
        return std::hash<std::string>{}(txt);
    }
};

template<typename T>
using unordered_string_map = std::unordered_map<std::string, T, string_hash, std::equal_to<>>;

// ================================================================================================

/**
 * @brief NBT Compound type
 *
 * This behaves as a map that can store heterogeneous data.
 */
struct NBT_EXPORT Compound {
    explicit Compound() = default;

    // ------------------------------------------------------
    // Getters
    // ------------------------------------------------------

    /**
     * @brief Return the field stored with the given name
     */
    const NBTField &get(std::string_view name) const {
        auto r = map_.find(name);
        if (r == map_.end())
            throw errors::FieldNotFoundError(name);
        return r->second;
    }

    template<typename T>
    inline T get(std::string_view name) const {
        return get(name).as<T>();
    }

    // ------------------------------------------------------
    // Setters
    // ------------------------------------------------------
    /**
     * @brief Set the given field value
     *
     * @param name name of the field in the map
     * @param field value of the field in the map
     */
    void put(std::string name, NBTField const &field) {
        map_.insert_or_assign(std::move(name), field);
    }

private:
    unordered_string_map<NBTField> map_;
};

// ================================================================================================
// Type <-> Tags
// ================================================================================================

namespace details {
template<>
struct NBT_EXPORT get_type_obj<Tags::COMPOUND> {
    using T = Compound;
};

template<>
NBT_EXPORT constexpr auto get_tag<Compound>() {
    return Tags::COMPOUND;
}
} // namespace details
} // namespace minecraft::nbt

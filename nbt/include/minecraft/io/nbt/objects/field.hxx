// ================================================================================================
// Project: SOLISMC_IO
//
// Field object containing any value
//
// Author    Meltwin (github@meltwin.fr)
// Created   10/10/2026
// ================================================================================================

// ============================================================================
// Version   1.0.0
// Modified  23/10/2026
// Copyright Solis Forge | 2026 - 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#pragma once
#include <any>

#include "minecraft/io/nbt/errors.hxx"
#include "minecraft/io/nbt/tags.hxx"

namespace minecraft::nbt {
// ================================================================================================
struct NBT_EXPORT NBTField {
    Tags tag; //< Tag of the value
    std::any value; //< Value container

    /**
     * @brief Get the value of this field casted as the provided type
     */
    template<typename T>
    T as() const {
        try {
            return std::any_cast<T>(value);
        } catch (std::bad_any_cast &) {
            throw errors::BadAnyCastError(tag, "NBTField::as(...)");
        }
    }
};
} // namespace minecraft::nbt

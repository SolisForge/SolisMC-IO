// ================================================================================================
// Project: SOLISMC_IO
//
// NBT List implementation
//
// Author    Meltwin (github@meltwin.fr)
// Created   14/09/2026
// ================================================================================================

// ============================================================================
// Version   1.0.0
// Modified  23/10/2026
// Copyright Solis Forge | 2026 - 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#pragma once
#include "minecraft/io/nbt/tags.hxx"

#include <any>
#include <type_traits>
#include <vector>

namespace minecraft::nbt {
template<typename T>
struct is_vector : std::false_type {};

template<typename T>
struct is_vector<std::vector<T>> : std::true_type {};

template<typename T>
concept IsVector = is_vector<T>::value;

template<typename T>
struct VecElem;

template<typename E>
struct VecElem<std::vector<E>> {
    using E_t = E;
};

/**
 * @brief NBT List implementation
 */
struct NBT_EXPORT List {
    using SizeField_t = int32_t;

    // ======================================================
    // Initializers
    // ======================================================

    /**
     * @brief Construct a new empty list object
     */
    explicit List() : tag_(Tags::END) {};

    /**
     * @brief Construct a new empty list object
     */
    explicit List(Tags tag) noexcept : tag_(tag) {};

    /**
     * @brief Construct a new List by copying all elements from the given vector.
     *
     * @tparam T type of the vector's elements
     * @param vec the vector to build the list from
     */
    template<typename T>
    List(std::vector<T> vec, Tags tag) noexcept : tag_(tag), container_(std::move(vec)) {}

    /**
     * @brief Construct a new List from an existing vector
     *
     * @tparam T type of the vector's elements
     * @param vec the vector to use the data from
     */
    template<typename T>
    List(std::vector<T> &&vec, Tags tag) noexcept : tag_(tag), container_(std::move(vec)) {}

    // ======================================================
    // Methods
    // ======================================================

    /**
     * @brief Return the list tag
     */
    [[nodiscard]] auto tag() const noexcept { return tag_; }

    /**
     * @brief Set the NBT tag of this list
     */
    void set_tag(Tags tag) noexcept { tag_ = tag; };

    /**
     * @brief Get the element
     */
    [[nodiscard]] auto get(std::size_t i) const;

    /**
     * @brief Append an element to the internal vector
     *
     * @param element the element to add
     */
    void push_back(std::any const &element) { container_.push_back(element); }

    /**
     * @brief Reserve a new size for the vector
     *
     * @param size
     */
    void reserve(std::size_t const &size) { container_.reserve(size); }

    /**
     * @brief Size of the container
     */
    [[nodiscard]] std::size_t size() const { return container_.size(); }

    /**
     * @brief Return the contained data as a std::vector
     *
     * @tparam T the type of the elements of the vector
     * @return a vector with elements casted in the given type
     */
    template<IsVector T>
    T move_cast() {
        return std::move(std::any_cast<T>(container_));
    }

    /**
     * @brief Return the contained data as a std::vector
     *
     * @tparam T the type of the elements of the vector
     * @return a vector with elements casted in the given type
     */
    template<IsVector T>
    T copy_cast() const {
        return std::any_cast<T>(container_);
    }

    // ======================================================
    // Iteration
    // ======================================================
    [[nodiscard]] auto begin() const { return container_.begin(); }

    [[nodiscard]] auto end() const { return container_.end(); }

private:
    Tags tag_{};
    std::vector<std::any> container_{}; //< Data container
};

// ================================================================================================
// Type <-> Tags
// ================================================================================================

namespace details {
template<>
struct NBT_EXPORT get_type_obj<Tags::LIST> {
    using T = List;
};

template<>
NBT_EXPORT constexpr auto get_tag<List>() {
    return Tags::LIST;
}
} // namespace details
} // namespace minecraft::nbt

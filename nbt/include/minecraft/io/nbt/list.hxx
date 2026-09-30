// ============================================================================
// Project: SOLISMC_IO
//
// NBT List implementation
//
// Author    Meltwin (github@meltwin.fr)
// Date      14/09/2026 (created 14/09/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#pragma once
#include "minecraft/io/nbt/tags.hxx"

#include <any>
#include <vector>

namespace minecraft::nbt {

/**
 * @brief NBT List implementation
 *
 */
struct List {

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
  explicit List(Tags tag) : tag_(tag) {};

  /**
   * @brief Construct a new List by copying all elements from the given vector.
   *
   * @tparam T type of the vector's elements
   * @param vec the vector to build the list from
   */
  template <typename T>
  List(std::vector<T> vec, Tags tag) : tag_(tag), container_(std::move(vec)) {}

  /**
   * @brief Construct a new List from an existing vector
   *
   * @tparam T type of the vector's elements
   * @param vec the vector to use the data from
   */
  template <typename T>
  List(std::vector<T> &&vec, Tags tag)
      : tag_(tag), container_(std::move(vec)) {}

  // ======================================================
  // Methods
  // ======================================================

  /**
   * @brief Return the list tag
   */
  auto tag() const { return tag_; }

  /**
   * @brief Set the NBT tag of this list
   */
  void set_tag(Tags tag) { tag_ = tag; };

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
  std::size_t size() const { return container_.size(); }

  /**
   * @brief Return the contained data as a std::vector
   *
   * @tparam T the type of the elements of the vector
   * @return a vector with elements casted in the given type
   */
  template <typename T> std::vector<T> move_cast() {
    return std::move(std::any_cast<std::vector<T>>(container_));
  }

  /**
   * @brief Return the contained data as a std::vector
   *
   * @tparam T the type of the elements of the vector
   * @return a vector with elements casted in the given type
   */
  template <typename T> std::vector<T> copy_cast() const {
    std::vector<T> out;
    out.reserve(container_.size());
    for (auto const &elem : container_)
      out.push_back(std::any_cast<T>(elem));
    return out;
  }

  // ======================================================
  // Iteration
  // ======================================================
  auto begin() const { return container_.begin(); }

  auto end() const { return container_.end(); }

private:
  Tags tag_{};
  std::vector<std::any> container_{}; //< Data container
};

} // namespace minecraft::nbt

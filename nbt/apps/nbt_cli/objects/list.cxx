// ============================================================================
// Project: SOLISMC_IO
//
// Implementation of list encoding / decoding for the nbt utility app
//
// List are represented as "type[contents,...]" in user-friendly format.
//
// Author    Meltwin (github@meltwin.fr)
// Date      07/10/2026 (created 07/10/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#include <ranges>
#include <sstream>
#include <string_view>
#include <vector>

#include "minecraft/io/nbt/bytes/errors.hxx"
#include "minecraft/io/nbt/tags.hxx"

#include "../format.hxx"
#include "list.hxx"
#include "parse_any.hxx"

namespace minecraft::nbt::app {

// ============================================================================
// List import
// ============================================================================
List list_import(std::string_view input_string) {
  List v;

  // Parse list as "type[contents,...]"
  auto start = input_string.find("[");
  auto end = input_string.find("]");
  if (start == std::string::npos || end == std::string::npos)
    return v;

  auto content = input_string.substr(start + 1, end - start - 1);

  // Set type
  v.set_tag(from_string(std::string_view(input_string).substr(0, start)));

  // Parse tag
  for (const auto elem :
       content | std::views::split(',') |
           std::views::transform([](auto &&token) {
             return std::string_view(&*token.begin(),
                                     std::ranges::distance(token));
           })) {
    v.push_back(parse_from_tag(elem, v.tag()));
  }
  return v;
}

// ============================================================================
// List export
// ============================================================================
template <typename T>
void display_vector(std::vector<T> const &value, std::stringstream &ss) {
  // Display values
  std::size_t i{0};
  ss << "[";
  for (auto const &item : value) {
    fmt_value<T>(ss, item);
    if (i++ < value.size() - 1)
      ss << ",";
  }
  ss << "]";
}

template <typename T>
void display_vector(std::vector<std::vector<T>> const &value,
                    std::stringstream &ss) {
  // Display values
  std::size_t i{0};
  ss << "[";
  for (auto const &item : value) {
    display_vector(item, ss);
    if (i++ < value.size() - 1)
      ss << ",";
  }
  ss << "]";
}

// ============================================================================
std::string list_export(const List &list) {
  using enum Tags;
  std::stringstream ss{};
  ss << to_str(list.tag());

  // Export list as "type[contents,...]"
  switch (list.tag()) {
#define X(tag)                                                                 \
  case tag:                                                                    \
    display_vector(list.copy_cast<get_type<tag>>(), ss);                       \
    break;
#include "minecraft/io/nbt/.xmacros/tags.x"

  // Default: raise an exception
  default:
    throw byte::errors::UnsupportedTag(list.tag(), "app::list_export");
  }
  return ss.str();
}

} // namespace minecraft::nbt::app
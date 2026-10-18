// ============================================================================
// Project: SOLISMC_IO
//
// Implementation of list encoding / decoding for the nbt utility app
//
// List are represented as "type[contents,...]" in user-friendly format.
//
// Author    Meltwin (github@meltwin.fr)
// Date      13/10/2026 (created 07/10/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#include <ranges>
#include <string_view>

#include "minecraft/io/nbt/errors.hxx"
#include "minecraft/io/nbt/objects/list.hxx"
#include "minecraft/io/nbt/tags.hxx"

#include "../format.hxx"
#include "list.hxx"
#include "parse_any.hxx"

using minecraft::nbt::IsVector;

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
template <typename T>
inline void fmt_casted_list(std::ostream &os, List const &list) {
  auto l = list.copy_cast<std::vector<T>>();
  fmt_value(os, l);
}

// ============================================================================
void fmt_list(std::ostream &os, List const &list) {
  using enum Tags;
  os << to_string(list.tag());

  // Export list as "type[contents,...]"
  switch (list.tag()) {
#define X(tag)                                                                 \
  case tag:                                                                    \
    fmt_casted_list<get_type<tag>>(os, list);                                  \
    break;
#include "minecraft/io/nbt/.xmacros/tags.x"

  // Default: raise an exception
  default:
    throw errors::UnsupportedTag(list.tag(), "app::list_export");
  }
}

} // namespace minecraft::nbt::app
// ============================================================================
// Project: SOLISMC-FILEIO
//
//
//
// Author    Meltwin (github@meltwin.fr)
// Date      04/06/2026 (created 04/06/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#include "minecraft/io/nbt/bytes.hpp"
#include <iostream>
#include <string>

using namespace minecraft::nbt::byte::java;

int main() {
  auto parser = ByteParser<int>();

  const char strm[4] = {'\x90', '\x00', '\x60', '\xa0'};
  auto p = strm;
  std::size_t N = 2;

  auto ret = parser.parse(p, N);
  N = 2;
  ret = parser.parse(p, N);
  if (ret != ParseResult::ENDED) {
    std::cout << "Parse has not ended ! (error code=" << to_string(ret) << ")"
              << std::endl;
  } else
    std::cout << "Parse result " << parser.get() << std::endl;
}
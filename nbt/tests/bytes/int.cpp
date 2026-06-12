// ============================================================================
// Project: SOLISMC_FILEIO
//
// Unittests for NBT::Int byte parsing.
//
// Author    Meltwin (github@meltwin.fr)
// Date      20/11/2025 (created 20/11/2025)
// Version   1.0.0
// Copyright Solis Forge | 2025
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================

#include "minecraft/io/nbt/bytes.hpp" // IWYU pragma: keep
#include "solismc_io/dataset/0_int.hpp"
#include <cstdint>
#include <doctest/doctest.h>

using namespace minecraft::nbt;

// ============================================================================
TEST_CASE("BytesParser<NBT::Int>") {

  ByteParser<int32_t> parser;

  //  --------------------------------------------------------------------------
  SUBCASE("[INT1] Normal case") {
    auto *p = INT1::BYTES;
    auto n = INT1::N_BYTES;
    auto ret = parser.parse(p, n);

    CHECK_EQ(ret, ParseResult::ENDED);
    CHECK_EQ(parser.get(), INT1::VALUE);
    CHECK_EQ(n, 0);
  }
  //  --------------------------------------------------------------------------
  SUBCASE("[STREAM_INT1] Two ints") {
    auto *p = STREAM_INT1::STREAM;
    auto n = STREAM_INT1::N_BYTES;

    for (std::size_t i = 0; i < STREAM_INT1::N_VALUES; i++) {
      auto ret = parser.parse(p, n);
      CHECK_EQ(ret, ParseResult::ENDED);
      CHECK_EQ(parser.get(), STREAM_INT1::VALUES[i]);
      CHECK_EQ(n, STREAM_INT1::N_BYTES - sizeof(int32_t) * (i + 1));
    }
  }
}
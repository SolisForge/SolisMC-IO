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

#include "solismc_io/dataset/0_int.hpp"
#include "minecraft/io/nbt/bytes.hpp" // IWYU pragma: keep
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
  SUBCASE("[INT2] Negative case") {
    auto *p = INT2::BYTES;
    auto n = INT2::N_BYTES;
    auto ret = parser.parse(p, n);

    CHECK_EQ(ret, ParseResult::ENDED);
    CHECK_EQ(parser.get(), INT2::VALUE);
    CHECK_LT(parser.get(), 0);
    CHECK_EQ(n, 0);
  }
  //  --------------------------------------------------------------------------
  SUBCASE("[INT3] Big value case") {
    auto *p = INT3::BYTES;
    auto n = INT3::N_BYTES;
    auto ret = parser.parse(p, n);

    CHECK_EQ(ret, ParseResult::ENDED);
    CHECK_EQ(parser.get(), INT3::VALUE);
    CHECK_EQ(parser.get(), INT3::VALUE);
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
  //  --------------------------------------------------------------------------
  SUBCASE("[STREAM_INT1] Incomplete stream") {
    auto *p = STREAM_INT1::STREAM;
    // We induce an incomplete stream
    auto n = STREAM_INT1::N_BYTES - 2;

    for (std::size_t i = 0; i < STREAM_INT1::N_VALUES - 1; i++) {
      auto ret = parser.parse(p, n);
      CHECK_EQ(ret, ParseResult::ENDED);
      CHECK_EQ(parser.get(), STREAM_INT1::VALUES[i]);
      CHECK_EQ(n, STREAM_INT1::N_BYTES - 2 - sizeof(int32_t) * (i + 1));
    }

    // Incomplete parsing
    auto ret = parser.parse(p, n);
    CHECK_EQ(ret, ParseResult::UNFINISHED);
    CHECK_EQ(parser.get(), 0);
    CHECK_EQ(n, 0);
  }
}
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

#include "solismc_io/dataset/0_long.hpp"
#include "minecraft/io/nbt/bytes.hpp" // IWYU pragma: keep
#include <cstdint>
#include <doctest/doctest.h>

using namespace minecraft::nbt;

// ============================================================================
TEST_CASE("BytesParser<NBT::Long>") {

  ByteParser<int64_t> parser;

  //  --------------------------------------------------------------------------
  SUBCASE("[LONG1] Normal case") {
    auto *p = LONG1::BYTES;
    auto n = LONG1::N_BYTES;
    auto ret = parser.parse(p, n);

    CHECK_EQ(ret, ParseResult::ENDED);
    CHECK_EQ(parser.get(), LONG1::VALUE);
    CHECK_EQ(n, 0);
  }
  //  --------------------------------------------------------------------------
  SUBCASE("[LONG2] Negative case") {
    auto *p = LONG2::BYTES;
    auto n = LONG2::N_BYTES;
    auto ret = parser.parse(p, n);

    CHECK_EQ(ret, ParseResult::ENDED);
    CHECK_EQ(parser.get(), LONG2::VALUE);
    CHECK_LT(parser.get(), 0);
    CHECK_EQ(n, 0);
  }
  //  --------------------------------------------------------------------------
  SUBCASE("[LONG3] Big value case") {
    auto *p = LONG3::BYTES;
    auto n = LONG3::N_BYTES;
    auto ret = parser.parse(p, n);

    CHECK_EQ(ret, ParseResult::ENDED);
    CHECK_EQ(parser.get(), LONG3::VALUE);
    CHECK_EQ(n, 0);
  }
  //  --------------------------------------------------------------------------
  SUBCASE("[LONG2] Negative case") {
    auto *p = LONG2::BYTES;
    auto n = LONG2::N_BYTES;
    auto ret = parser.parse(p, n);

    CHECK_EQ(ret, ParseResult::ENDED);
    CHECK_EQ(parser.get(), LONG2::VALUE);
    CHECK_LT(parser.get(), 0);
    CHECK_EQ(n, 0);
  }
  //  --------------------------------------------------------------------------
  SUBCASE("[LONG3] Big value case") {
    auto *p = LONG3::BYTES;
    auto n = LONG3::N_BYTES;
    auto ret = parser.parse(p, n);

    CHECK_EQ(ret, ParseResult::ENDED);
    CHECK_EQ(parser.get(), LONG3::VALUE);
    CHECK_EQ(n, 0);
  }
  //  --------------------------------------------------------------------------
  SUBCASE("[STREAM_LONG1] Two shorts") {
    auto *p = STREAM_LONG1::STREAM;
    auto n = STREAM_LONG1::N_BYTES;

    for (std::size_t i = 0; i < STREAM_LONG1::N_VALUES; i++) {
      auto ret = parser.parse(p, n);
      CHECK_EQ(ret, ParseResult::ENDED);
      CHECK_EQ(parser.get(), STREAM_LONG1::VALUES[i]);
      CHECK_EQ(n, STREAM_LONG1::N_BYTES - sizeof(int64_t) * (i + 1));
    }
  }
  //  --------------------------------------------------------------------------
  SUBCASE("[STREAM_LONG1] Incomplete stream") {
    auto *p = STREAM_LONG1::STREAM;
    // We induce an incomplete stream
    auto n = STREAM_LONG1::N_BYTES - 2;

    for (std::size_t i = 0; i < STREAM_LONG1::N_VALUES - 1; i++) {
      auto ret = parser.parse(p, n);
      CHECK_EQ(ret, ParseResult::ENDED);
      CHECK_EQ(parser.get(), STREAM_LONG1::VALUES[i]);
      CHECK_EQ(n, STREAM_LONG1::N_BYTES - 2 - sizeof(int64_t) * (i + 1));
    }

    // Incomplete parsing
    auto ret = parser.parse(p, n);
    CHECK_EQ(ret, ParseResult::UNFINISHED);
    CHECK_EQ(parser.get(), 0);
    CHECK_EQ(n, 0);
  }
}
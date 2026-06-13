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
#include "solismc_io/dataset/0_short.hpp"
#include <cstdint>
#include <doctest/doctest.h>

using namespace minecraft::nbt;

// ============================================================================
TEST_CASE("BytesParser<NBT::Short>") {

  ByteParser<int16_t> parser;

  //  --------------------------------------------------------------------------
  SUBCASE("[SHORT1] Normal case") {
    auto *p = SHORT1::BYTES;
    auto n = SHORT1::N_BYTES;
    auto ret = parser.parse(p, n);

    CHECK_EQ(ret, ParseResult::ENDED);
    CHECK_EQ(parser.get(), SHORT1::VALUE);
    CHECK_EQ(n, 0);
  }
  //  --------------------------------------------------------------------------
  SUBCASE("[SHORT2] Negative case") {
    auto *p = SHORT2::BYTES;
    auto n = SHORT2::N_BYTES;
    auto ret = parser.parse(p, n);

    CHECK_EQ(ret, ParseResult::ENDED);
    CHECK_EQ(parser.get(), SHORT2::VALUE);
    CHECK_LT(parser.get(), 0);
    CHECK_EQ(n, 0);
  }
  //  --------------------------------------------------------------------------
  SUBCASE("[SHORT3] Big value case") {
    auto *p = SHORT3::BYTES;
    auto n = SHORT3::N_BYTES;
    auto ret = parser.parse(p, n);

    CHECK_EQ(ret, ParseResult::ENDED);
    CHECK_EQ(parser.get(), SHORT3::VALUE);
    CHECK_EQ(n, 0);
  }
  //  --------------------------------------------------------------------------
  SUBCASE("[SHORT2] Negative case") {
    auto *p = SHORT2::BYTES;
    auto n = SHORT2::N_BYTES;
    auto ret = parser.parse(p, n);

    CHECK_EQ(ret, ParseResult::ENDED);
    CHECK_EQ(parser.get(), SHORT2::VALUE);
    CHECK_LT(parser.get(), 0);
    CHECK_EQ(n, 0);
  }
  //  --------------------------------------------------------------------------
  SUBCASE("[SHORT3] Big value case") {
    auto *p = SHORT3::BYTES;
    auto n = SHORT3::N_BYTES;
    auto ret = parser.parse(p, n);

    CHECK_EQ(ret, ParseResult::ENDED);
    CHECK_EQ(parser.get(), SHORT3::VALUE);
    CHECK_EQ(n, 0);
  }
  //  --------------------------------------------------------------------------
  SUBCASE("[STREAM_SHORT1] Two shorts") {
    auto *p = STREAM_SHORT1::STREAM;
    auto n = STREAM_SHORT1::N_BYTES;

    for (std::size_t i = 0; i < STREAM_SHORT1::N_VALUES; i++) {
      auto ret = parser.parse(p, n);
      CHECK_EQ(ret, ParseResult::ENDED);
      CHECK_EQ(parser.get(), STREAM_SHORT1::VALUES[i]);
      CHECK_EQ(n, STREAM_SHORT1::N_BYTES - sizeof(int16_t) * (i + 1));
    }
  }
  //  --------------------------------------------------------------------------
  SUBCASE("[STREAM_SHORT1] Incomplete stream") {
    auto *p = STREAM_SHORT1::STREAM;
    // We induce an incomplete stream
    auto n = STREAM_SHORT1::N_BYTES - 2;

    for (std::size_t i = 0; i < STREAM_SHORT1::N_VALUES - 1; i++) {
      auto ret = parser.parse(p, n);
      CHECK_EQ(ret, ParseResult::ENDED);
      CHECK_EQ(parser.get(), STREAM_SHORT1::VALUES[i]);
      CHECK_EQ(n, STREAM_SHORT1::N_BYTES - 2 - sizeof(int16_t) * (i + 1));
    }

    // Incomplete parsing
    auto ret = parser.parse(p, n);
    CHECK_EQ(ret, ParseResult::UNFINISHED);
    CHECK_EQ(parser.get(), 0);
    CHECK_EQ(n, 0);
  }
}
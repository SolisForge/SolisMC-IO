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

#include "solismc_io/dataset/0_byte.hpp"
#include "minecraft/io/nbt/bytes.hpp" // IWYU pragma: keep
#include <cstdint>
#include <doctest/doctest.h>

using namespace minecraft::nbt;

// ============================================================================
TEST_CASE("BytesParser<NBT::Byte>") {

  ByteParser<int8_t> parser;

  //  --------------------------------------------------------------------------
  SUBCASE("[BYTE1] Normal case") {
    auto *p = BYTE1::BYTES;
    auto n = BYTE1::N_BYTES;
    auto ret = parser.parse(p, n);

    CHECK_EQ(ret, ParseResult::ENDED);
    CHECK_EQ(parser.get(), BYTE1::VALUE);
    CHECK_EQ(n, 0);
  }
  //  --------------------------------------------------------------------------
  SUBCASE("[BYTE2] Negative case") {
    auto *p = BYTE2::BYTES;
    auto n = BYTE2::N_BYTES;
    auto ret = parser.parse(p, n);

    CHECK_EQ(ret, ParseResult::ENDED);
    CHECK_EQ(parser.get(), BYTE2::VALUE);
    CHECK_LT(parser.get(), 0);
    CHECK_EQ(n, 0);
  }
  //  --------------------------------------------------------------------------
  SUBCASE("[BYTE3] Big value case") {
    auto *p = BYTE3::BYTES;
    auto n = BYTE3::N_BYTES;
    auto ret = parser.parse(p, n);

    CHECK_EQ(ret, ParseResult::ENDED);
    CHECK_EQ(parser.get(), BYTE3::VALUE);
    CHECK_EQ(parser.get(), BYTE3::VALUE);
    CHECK_EQ(n, 0);
  }
  //  --------------------------------------------------------------------------
  SUBCASE("[STREAM_BYTE1] Two ints") {
    auto *p = STREAM_BYTE1::STREAM;
    auto n = STREAM_BYTE1::N_BYTES;

    for (std::size_t i = 0; i < STREAM_BYTE1::N_VALUES; i++) {
      auto ret = parser.parse(p, n);
      CHECK_EQ(ret, ParseResult::ENDED);
      CHECK_EQ(parser.get(), STREAM_BYTE1::VALUES[i]);
      CHECK_EQ(n, STREAM_BYTE1::N_BYTES - sizeof(int8_t) * (i + 1));
    }
  }
  //  --------------------------------------------------------------------------
  SUBCASE("[STREAM_BYTE1] Incomplete stream") {
    auto *p = STREAM_BYTE1::STREAM;
    // We induce an incomplete stream
    auto n = STREAM_BYTE1::N_BYTES - 1;

    for (std::size_t i = 0; i < STREAM_BYTE1::N_VALUES - 1; i++) {
      auto ret = parser.parse(p, n);
      CHECK_EQ(ret, ParseResult::ENDED);
      CHECK_EQ(parser.get(), STREAM_BYTE1::VALUES[i]);
      CHECK_EQ(n, STREAM_BYTE1::N_BYTES - 1 - sizeof(int8_t) * (i + 1));
    }

    // Incomplete parsing
    auto ret = parser.parse(p, n);
    CHECK_EQ(ret, ParseResult::UNFINISHED);
    CHECK_EQ(parser.get(), 0);
    CHECK_EQ(n, 0);
  }
}
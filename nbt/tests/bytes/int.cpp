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
#include <doctest/doctest.h>

using namespace minecraft::nbt;

// ============================================================================
TEST_CASE("BytesParser<NBT::Int>") {

  ByteParser<int32_t> parser;

  //  --------------------------------------------------------------------------
  SUBCASE("[INT1] Normal case") {
    auto *p = int1::BYTES;
    auto n = int1::N_BYTES;
    auto ret = parser.parse(p, n);

    CHECK_EQ(ret, ParseResult::ENDED);
    CHECK_EQ(parser.get(), int1::VALUE);
    CHECK_EQ(n, 0);
  }
}
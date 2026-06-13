# =============================================================================
# Project: SOLISMC_FILEIO
# 
# This file contains the CMake definitions of NBT-related targets & tests.
# 
# Author    Meltwin (github@meltwin.fr)
# Date      13/06/2026 (created 16/01/2026)
# Version   1.0.0
# Copyright Solis Forge | 2025 
#           Distributed under MIT License (https://opensource.org/licenses/MIT)
# =============================================================================

# =============================================================================
# NBT library: altogether
# =============================================================================
add_solis_library( nbt
    DIRECTORIES "nbt/src"
    PUBLIC_HEADER "nbt/include"
    NAMESPACE solismc
    SHARED
) 
target_link_libraries(nbt solis::utils)

# # =============================================================================
# # Dataset generation
# # =============================================================================
# solis_generate_dataset(TEMPLATE nbt_dataset _gen_dir
#     DIRECTORY "nbt/data"
#     HEADER_DIRECTORIES "solismc_io/dataset"
# )
# # =============================================================================
# # Tests
# # =============================================================================
# add_solis_executable( test_parse
#     DIRECTORIES "nbt/tests/bytes"
#     DEPENDS nbt solis_external::doctest
# )
# target_include_directories(test_parse PRIVATE "${_gen_dir}")
# add_dependencies(test_parse nbt_dataset)
# add_test(NAME test_nbt_parse COMMAND test_parse)
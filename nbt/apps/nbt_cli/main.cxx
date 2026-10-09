// ============================================================================
// Project: SOLISMC_IO
//
// NBT cli entrypoint
// This program allow user to decode / encode NBT from a terminal.
//
// Author    Meltwin (github@meltwin.fr)
// Date      25/08/2026 (created 25/08/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#include "processing.hxx"
#include <cstdio>
#include <cstring>
#include <exception>
#include <filesystem>
#include <iostream>

#include "options.hxx"
#include "readers.hxx"

namespace app = minecraft::nbt::app;

// ============================================================================
int main(int argc, char **argv) {
  auto opts = app::parse_args(argc, argv);

  // Read input
  auto bytes = (opts.input == app::ReadFrom::STDIN)
                   ? from_stdin()
                   : from_file(opts.input_file);

  int exit_code;
  try {
    if (opts.mode == app::ProcessMode::DECODE) {
      exit_code = app::decode_bytes(bytes, opts.data_type);
    } else {
      exit_code = app::encode_bytes(bytes, opts.data_type);
    }
  } catch (std::exception &e) {
    std::cerr << "ERROR: " << e.what() << std::endl;
    exit_code = 1;
  }

  // If stdout is not piped, add a line return at the end
  std::flush(std::cout);
  std::error_code ec;
  if (auto status = std::filesystem::status("/dev/stdout", ec);
      std::filesystem::is_character_file(status)) {
    std::cerr << std::endl;
  }
  return exit_code;
}
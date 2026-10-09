// ============================================================================
// Project: SOLISMC_IO
//
// Option parsing implementation
//
// Author    Meltwin (github@meltwin.fr)
// Date      30/08/2026 (created 30/08/2026)
// Version   1.0.0
// Copyright Solis Forge | 2026
//           Distributed under MIT License (https://opensource.org/licenses/MIT)
// ============================================================================
#include "options.hxx"
#include <algorithm>
#include <cstring>
#include <filesystem>
#include <stdexcept>
#include <string_view>

namespace minecraft::nbt::app {

// ============================================================================
Options parse_args(int argc, char **argv) {
  Options opt{};

  // Skip first argument == program name
  argc--;
  argv++;

  // Parse all arguments
  while (argc > 0) {
    std::string arg0{argv[0]};
    if (auto len = arg0.length(); len < 2)
      throw std::invalid_argument{"Argument should have a length of 2"};

    // File option
    if (arg0.compare("-f") == 0) {
      if (argc == 1)
        throw std::invalid_argument{"Missing path to -f"};
      opt.input = ReadFrom::FILE;
      opt.input_file = std::filesystem::path{argv[1]};
      argc -= 2;
      argv += 2;
    }
    // Type option
    else if (arg0.compare("-t") == 0) {
      if (argc == 1)
        throw std::invalid_argument{"Missing type info to -t"};

      std::string upper{};
      std::ranges::transform(std::string_view{argv[1]},
                             std::back_inserter(upper),
                             [](unsigned char c) { return std::toupper(c); });
      opt.data_type = from_string(upper);
      argc -= 2;
      argv += 2;
    }
    // Encode option
    else if (arg0.compare("-e") == 0) {
      opt.mode = ProcessMode::ENCODE;
      argc -= 1;
      argv += 1;
    }
  }

  return opt;
}

} // namespace minecraft::nbt::app

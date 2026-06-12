
struct ${name} {
  static constexpr auto VALUE{ ${value} };
  static constexpr char BYTES[${n_bytes}] = { ${bytes_str} };
  static constexpr std::size_t N_BYTES{${n_bytes}};
};


struct ${name_upper} {
  static constexpr auto VALUE {${value}};
  static constexpr std::size_t VALUE_LENGTH{${str_len}};
  static constexpr char BYTES[${n_bytes}] = {${bytes_str}};
  static constexpr std::size_t N_BYTES{${n_bytes}};
};

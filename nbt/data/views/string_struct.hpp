
struct ${name_upper} {
  static constexpr char VALUE[${str_len}] = {${str_bytes_str}};
  static constexpr std::size_t VALUE_LENGTH{${str_len}};
  static constexpr char BYTES[${n_bytes}] = {${bytes_str}};
  static constexpr std::size_t N_BYTES{${n_bytes}};
};

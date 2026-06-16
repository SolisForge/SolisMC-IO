
struct ${name_upper} {
  static constexpr ${value_type} VALUE[${n_values}] {${value_list}};
  static constexpr std::size_t N_VALUES{${n_values}};
  static constexpr char BYTES[${n_bytes}] = {${bytes_str}};
  static constexpr std::size_t N_BYTES{${n_bytes}};
};


struct STREAM_${name_upper} {
  static constexpr ${value_type} VALUES[${n_values}] { ${values} };
  static constexpr std::size_t N_VALUES{ ${n_values} };
  static constexpr char STREAM[${n_bytes}] = { ${bytes_str} };
  static constexpr std::size_t N_BYTES{${n_bytes}};
};

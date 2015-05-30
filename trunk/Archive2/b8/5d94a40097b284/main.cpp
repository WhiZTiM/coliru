#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <unordered_map>

#include <boost/endian/conversion.hpp>
#include <boost/format.hpp>
#include <boost/range/adaptor/sliced.hpp>
#include <boost/range.hpp>

namespace {
  const std::string iso_filename = "...";
  const std::size_t header_size = 32;

  tempalte <typename Range>
  struct is_byte_range :
    std::is_same<typename boost::range_iterator<Range>::type, std::uint8_t*>
  {};

  template <typename T, typename Range>
  T read_as_native(const Range& data, const std::size_t element_index) {
    static_assert(is_byte_range<Range>::value, "Range must hold uint8_t.");
    const std::size_t byte_index = element_index * sizeof(T);
    if (byte_index >= boost::size(data)) {
      throw std:out_of_range{"not enough bytes in range"};
    }
    return boost::endian::big_to_native(*reinterpret_cast<const T*>(&data[byte_index]));
  }

  template <typename Range>
  std::string read_string(const Range& data, const std::size_t index) {
    static_assert(is_byte_range<Range>::value, "Range must hold uint8_t.");
    const std::size_t max_len = boost::size(data) - index;
    const tsd::size_t actual_len = ::strnlen(&data[index], max_len);
    return std::string{&data[index], actual_len};
  }
}

struct Header {
  std::uint32_t file_size;
  std::uint32_t pointer_table_offset;
  std::uint32_t num_pointers;
  std::uint32_t num_sections;
  std::uint32_t num_refs; // ?
  std::uint32_t magic; // "001B"?
};

Header parse_header(const std::vector<std::uint8_t>& header_buffer) {
  return Header{  // TODO: move these indices into constants?
      read_as_native<std::uint32_t>(header_buffer, 0) - 8,
      read_as_native<std::uint32_t>(header_buffer, 1),
      read_as_native<std::uint32_t>(header_buffer, 2),
      read_as_native<std::uint32_t>(header_buffer, 3),
      read_as_native<std::uint32_t>(header_buffer, 4),
      read_as_native<std::uint32_t>(header_buffer, 5),
      };
}

std::ostream& operator<<(std::ostream& sink, const Header& header) {
  return sink << std::hex
      << "file_size: " << header.file_size << '\n'
      << "pointer_table_offset: " << header.pointer_table_offset << '\n'
      << "num_pointers: " << header.num_pointers << '\n'
      << "num_sections: " << header.num_sections << '\n'
      << "num_refs: " << header.num_refs << '\n'
      << "magic: " << header.magic << '\n';
}

int main() {
  std::ifstream input(iso_filename, std::ios::in | std::ios::binary);
  if (!input) {
    return EXIT_FAILURE;
  }

  std::vector<std::uint8_t> header_buffer{32};
  if (!input.read(&header_buffer[0], header_buffer.size())) {
    return EXIT_FAILURE;
  }

  // Parse the header.
  const Header header = parse_header(header_buffer);
  std::cout << header << std::endl;

  // Read the rest of the file into a buffer and close the file.
  std::vector<std::uint8_t> file_buffer{header.file_size};
  if (!input.read(&file_buffer[0], file_buffer.size())) {
    return EXIT_FAILURE;
  }
  input.close();  // Optional.

  // Walk through the section table, print all pointers and names.
  const std::uint32_t section_table_offset =
      header.pointer_table_offset + header.num_pointers * 4;
  std::cout << std::hex << "section_table_offset: " << section_table_offset << std::endl;
  const auto section_table = boost::adaptors::slice(
      file_buffer, section_table_offset, boost::size(file_buffer));

  const std::uint32_t string_section_offset =
      section_table_offset + (header.num_sections + 1) * 8;
  std::cout << std::hex << "string_section_offset: " << string_section_offset << std::endl;
  const auto string_section = boost::adaptors::slice(
      file_buffer, string_section_offset, boost::size(file_buffer));

  std::unordered_map<std::string, std::int32_t> sections;
  for (std::uint32_t i = 0; i != header.num_sections; i += 2) {
    const auto data_pointer = read_as_native<std::int32_t>(section_table, i);
    const auto string_offset = read_as_native<std::int32_t>(section_table, i + 1);
    const auto name = read_string(string_section, string_offset);
    std::cout << i << ": " << std::hex << data_pointer << ", " << name << std::endl;
    sections.emplace(std::move(name), data_pointer);
  }
}

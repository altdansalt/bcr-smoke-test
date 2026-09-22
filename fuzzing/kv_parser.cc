#include "fuzzing/kv_parser.h"

namespace smoke {

std::map<std::string, std::string> ParseKeyValues(std::string_view input) {
  std::map<std::string, std::string> out;
  while (!input.empty()) {
    const size_t end = input.find(';');
    const std::string_view segment = input.substr(0, end);
    const size_t eq = segment.find('=');
    if (eq != std::string_view::npos && eq > 0) {
      out[std::string(segment.substr(0, eq))] = std::string(segment.substr(eq + 1));
    }
    if (end == std::string_view::npos) break;
    input.remove_prefix(end + 1);
  }
  return out;
}

}  // namespace smoke

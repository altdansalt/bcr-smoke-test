#ifndef FUZZING_KV_PARSER_H_
#define FUZZING_KV_PARSER_H_

#include <map>
#include <string>
#include <string_view>

namespace smoke {

// Parses "key=value;key2=value2" into a map. Malformed segments are skipped.
std::map<std::string, std::string> ParseKeyValues(std::string_view input);

}  // namespace smoke

#endif  // FUZZING_KV_PARSER_H_

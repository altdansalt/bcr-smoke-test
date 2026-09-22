#include "cc/greeter.h"
#ifndef GREETER_OS
#define GREETER_OS "unset"
#endif
#ifndef GREETER_CPU
#define GREETER_CPU "unset"
#endif
namespace bcr_smoke {
std::string Greet(const std::string& name) { return "Hello, " + name + "!"; }
std::string HostDescription() { return std::string(GREETER_OS) + "/" + GREETER_CPU; }
}  // namespace bcr_smoke

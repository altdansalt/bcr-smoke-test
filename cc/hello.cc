#include <cstdio>
#include "cc/greeter.h"
int main() {
  std::printf("%s (%s)\n", bcr_smoke::Greet("BCR").c_str(), bcr_smoke::HostDescription().c_str());
  return 0;
}

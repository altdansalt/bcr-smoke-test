#include <string>
#include "benchmark/benchmark.h"
static void BM_StringAppend(benchmark::State& state) {
  for (auto _ : state) {
    std::string s;
    for (int i = 0; i < state.range(0); ++i) s += 'x';
    benchmark::DoNotOptimize(s);
  }
}
BENCHMARK(BM_StringAppend)->Arg(64)->Arg(1024);

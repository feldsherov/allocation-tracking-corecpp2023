// Copyright 2023 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <benchmark/benchmark.h>

// Very simple malloc/free benchmark. 
// Resuslts could be used only to estimate order of magnitude of allocations latency.
static void BM_TCMalloc(benchmark::State& state) {
  // Perform allocation and deallocation within the benchmark loop
  for (auto _ : state) {
    void* mem = malloc(state.range(0));
    benchmark::DoNotOptimize(mem);  // Prevent the compiler from optimizing away the allocation
    free(mem);
  }
}
BENCHMARK(BM_TCMalloc)
  ->Arg(64)
  ->Arg(256)
  ->Arg(4096)
  ->Arg(1<<20)
  ->ThreadRange(1,8);

BENCHMARK_MAIN();
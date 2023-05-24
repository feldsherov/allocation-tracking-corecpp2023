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

#include <memory>
#include <string>
#include <iostream>

#include <gperftools/malloc_hook.h>

namespace {

thread_local bool in_hook = false;

/* 
  TCMalloc hooks exposed as part of gperftoos, but looks like it is not exposed in vanilla TCMalloc.
  https://github.com/google/tcmalloc/issues/44
*/

void new_hook(const void *caller, unsigned long size)
{
  // An allocation inside of the hook will lead to infinite recursion and segfault somwhere in allocator. 
  if (in_hook) {
    return;
  }

  in_hook = true;
  std::cout << "malloc(" << size << "} called from " << caller << std::endl;
  in_hook = false;
}

} //  namespace

int main() {
  MallocHook_AddNewHook(&new_hook);

  // Output should be like:
  // malloc(sizeof(std::string)) called from <some pointer> returns <some pointer>
  auto p = std::make_unique<std::string>("abacaba");

  std::cout << "sizeof(std::string) = " << sizeof(std::string) << std::endl;
  std::cout << *p << std::endl;

  return 0;
}
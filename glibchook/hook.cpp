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

#include <malloc.h>

namespace {

/* 
  glibc hooks are deleted since glibc 2.34. Consider this like retrospective example :)  
  https://sourceware.org/pipermail/libc-alpha/2021-August/129718.html
*/

/* Prototypes for our hooks */
void my_init_hook(void);
void *my_malloc_hook(size_t, const void *);

/* Variables to save original hooks */
void *(*old_malloc_hook)(size_t, const void *);

void init_hooks(void)
{
    old_malloc_hook = __malloc_hook;
    __malloc_hook = my_malloc_hook;
}

// Idea of glibc malloc hook is to wrap and allocator for debug purposes,
// so it is more complicated then tcmallock hooks.
void* my_malloc_hook(size_t size, const void *caller)
{
    void *result;

    /* Restore all old hooks */
    __malloc_hook = old_malloc_hook; //  <- Unprotected write to __malloc_hook, so our hook is not thread safe.

    /* Call recursively */
    result = malloc(size); 

    /* Save underlying hooks */
    old_malloc_hook = __malloc_hook;

    /* printf() might call malloc(), so protect it too */
    printf("malloc(%zu) called from %p returns %p\n",
            size, caller, result);

    /* Restore our own hooks */
    __malloc_hook = my_malloc_hook;

    return result;
}

} //  namespace

int main() {
  init_hooks();

  // Should output like:
  // malloc(sizeof(std::string)) called from <some pointer> returns <some pointer>
  auto p = std::make_unique<std::string>("abacaba");

  std::cout << "sizeof(std::string) = " << sizeof(std::string) << std::endl;
  std::cout << *p << std::endl;

  return 0;
}
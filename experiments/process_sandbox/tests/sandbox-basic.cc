// Copyright Microsoft and Project Verona Contributors.
// SPDX-License-Identifier: MIT

#include "cxxapi/cxxsandbox.h"
#include "sandbox.hh"
#include "shared.h"

#include <stdio.h>

using namespace sandbox;

/**
 * The structure that represents an instance of the sandbox.
 */
struct AddSandbox
{
  /**
   * The library that defines the functions exposed by this sandbox.
   */
  SandboxedLibrary lib = {SANDBOX_LIBRARY};
#define EXPORTED_FUNCTION(public_name, private_name) \
  decltype(make_sandboxed_function<decltype(private_name)>(lib)) public_name = \
    make_sandboxed_function<decltype(private_name)>(lib);
  EXPORTED_FUNCTION(sum, ::sum)
};

void test_sum(AddSandbox& sb, int a, int b)
{
  int ret = sb.sum(a, b);
  assert(ret == (a + b));
}

int main()
{
  AddSandbox sandbox;
  AddSandbox sb2;
  AddSandbox sb3;
  test_sum(sandbox, 1, 2);
  test_sum(sandbox, INT_MAX, -1);
  test_sum(sb2, 1, 2);
  test_sum(sb2, INT_MAX, -1);
  test_sum(sb3, 1, 2);
  test_sum(sb3, INT_MAX, -1);
  return 0;
}

// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SANDBOX_LINUX_SECCOMP_BPF_VERIFIER_H__
#define SANDBOX_LINUX_SECCOMP_BPF_VERIFIER_H__

#include <stdint.h>

#include <vector>

#include "base/macros.h"

struct sock_filter;

namespace sandbox {
struct arch_seccomp_data;
class SandboxBPF;
class SandboxBPFPolicy;

class Verifier {
 public:
  // Evaluate the BPF program for all possible inputs and verify that it
  // computes the correct result. We use the "evaluators" to determine
  // the full set of possible inputs that we have to iterate over.
  // Returns success, if the BPF filter accurately reflects the rules
  // set by the "evaluators".
  // Upon success, "err" is set to NULL. Upon failure, it contains a static
  // error message that does not need to be free()'d.
  static bool VerifyBPF(SandboxBPF* sandbox,
                        const std::vector<struct sock_filter>& program,
                        const SandboxBPFPolicy& policy,
                        const char** err);

  // Evaluate a given BPF program for a particular set of system call
  // parameters. If evaluation failed for any reason, "err" will be set to
  // a non-NULL error string. Otherwise, the BPF program's result will be
  // returned by the function and "err" is NULL.
  // We do not actually implement the full BPF state machine, but only the
  // parts that can actually be generated by our BPF compiler. If this code
  // is used for purposes other than verifying the output of the sandbox's
  // BPF compiler, we might have to extend this BPF interpreter.
  static uint32_t EvaluateBPF(const std::vector<struct sock_filter>& program,
                              const struct arch_seccomp_data& data,
                              const char** err);

 private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(Verifier);
};

}  // namespace sandbox

#endif  // SANDBOX_LINUX_SECCOMP_BPF_VERIFIER_H__

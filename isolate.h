// Copyright (c) 2013 The Chromium OS Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef P11NET_ISOLATE_H_
#define P11NET_ISOLATE_H_

#include <string>

#include <base/macros.h>
#include <brillo/secure_blob.h>

#include "p11net.h"

namespace p11net {

const size_t kIsolateCredentialBytes = 16;

// Manages a user's isolate credentials, including saving and retrieval of
// isolate credentials. Sample usage:
//   IsolateCredentialManager isolate_manager;
//   SecureBlob isolate_credential;
//   isolate_manager.GetCurrentUserIsolateCredential(&isolate_credential);
//
// Only virtual to enable mocking in tests.
class IsolateCredentialManager {
 public:
  IsolateCredentialManager();
  virtual ~IsolateCredentialManager();

  // Get the well known credential for the default isolate.
  static brillo::SecureBlob GetDefaultIsolateCredential() {
    // Default isolate credential is all zeros.
    return brillo::SecureBlob(kIsolateCredentialBytes);
  }

  // Get the isolate credential for the current user, returning true if it
  // exists.
  virtual bool GetCurrentUserIsolateCredential(
      brillo::SecureBlob* isolate_credential);

  // Get the isolate credential for the given user name, returning true if it
  // exists.
  virtual bool GetUserIsolateCredential(
      const std::string& user,
      brillo::SecureBlob* isolate_credential);

  // Save the isolate credential such that it can be retrieved with
  // GetUserIsolateCredential. Return true on success and false on failure.
  virtual bool SaveIsolateCredential(
      const std::string& user,
      const brillo::SecureBlob& isolate_credential);

 private:
  DISALLOW_COPY_AND_ASSIGN(IsolateCredentialManager);
};

}  // namespace p11net

#endif  // P11NET_ISOLATE_H_


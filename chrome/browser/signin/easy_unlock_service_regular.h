// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SIGNIN_EASY_UNLOCK_SERVICE_REGULAR_H_
#define CHROME_BROWSER_SIGNIN_EASY_UNLOCK_SERVICE_REGULAR_H_

#include <string>

#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/prefs/pref_change_registrar.h"
#include "chrome/browser/signin/easy_unlock_service.h"

#if defined(OS_CHROMEOS)
#include "chrome/browser/chromeos/login/easy_unlock/short_lived_user_context.h"
#endif

namespace base {
class DictionaryValue;
class ListValue;
}

class EasyUnlockToggleFlow;
class Profile;

// EasyUnlockService instance that should be used for regular, non-signin
// profiles.
class EasyUnlockServiceRegular : public EasyUnlockService {
 public:
  explicit EasyUnlockServiceRegular(Profile* profile);
  virtual ~EasyUnlockServiceRegular();

 private:
  // EasyUnlockService implementation.
  virtual EasyUnlockService::Type GetType() const OVERRIDE;
  virtual std::string GetUserEmail() const OVERRIDE;
  virtual void LaunchSetup() OVERRIDE;
  virtual const base::DictionaryValue* GetPermitAccess() const OVERRIDE;
  virtual void SetPermitAccess(const base::DictionaryValue& permit) OVERRIDE;
  virtual void ClearPermitAccess() OVERRIDE;
  virtual const base::ListValue* GetRemoteDevices() const OVERRIDE;
  virtual void SetRemoteDevices(const base::ListValue& devices) OVERRIDE;
  virtual void ClearRemoteDevices() OVERRIDE;
  virtual void RunTurnOffFlow() OVERRIDE;
  virtual void ResetTurnOffFlow() OVERRIDE;
  virtual TurnOffFlowStatus GetTurnOffFlowStatus() const OVERRIDE;
  virtual std::string GetChallenge() const OVERRIDE;
  virtual std::string GetWrappedSecret() const OVERRIDE;
  virtual void RecordEasySignInOutcome(const std::string& user_id,
                                       bool success) const OVERRIDE;
  virtual void RecordPasswordLoginEvent(
      const std::string& user_id) const OVERRIDE;
  virtual void InitializeInternal() OVERRIDE;
  virtual void ShutdownInternal() OVERRIDE;
  virtual bool IsAllowedInternal() OVERRIDE;

  // Opens the component packaged app responsible for setting up Smart Lock.
  void OpenSetupApp();

  // Callback when the controlling pref changes.
  void OnPrefsChanged();

  // Sets the new turn-off flow status.
  void SetTurnOffFlowStatus(TurnOffFlowStatus status);

  // Callback invoked when turn off flow has finished.
  void OnTurnOffFlowFinished(bool success);

#if defined(OS_CHROMEOS)
  void OnUserContextFromReauth(const chromeos::UserContext& user_context);
  void OnKeysRefreshedForSetDevices(bool success);

  scoped_ptr<chromeos::ShortLivedUserContext> short_lived_user_context_;
#endif

  PrefChangeRegistrar registrar_;

  TurnOffFlowStatus turn_off_flow_status_;
  scoped_ptr<EasyUnlockToggleFlow> turn_off_flow_;

  base::WeakPtrFactory<EasyUnlockServiceRegular> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(EasyUnlockServiceRegular);
};

#endif  // CHROME_BROWSER_SIGNIN_EASY_UNLOCK_SERVICE_REGULAR_H_

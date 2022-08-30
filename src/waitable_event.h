// Created by LI Chaoran on 2019/05/29.
// Copyright © 2021 Bilibili. All rights reserved.

#ifndef CRON_BASE_WAITABLE_EVENT_H_
#define CRON_BASE_WAITABLE_EVENT_H_

#include <condition_variable>
#include <mutex>

#include "macros.h"

namespace cron {

// AutoResetWaitableEvent ------------------------------------------------------

class AutoResetWaitableEvent final {
 public:
  AutoResetWaitableEvent() {}
  ~AutoResetWaitableEvent() {}

  void Signal() {
    std::scoped_lock locker(mutex_);
    signaled_ = true;
    cv_.notify_one();
  }

  void Wait() {
    std::scoped_lock locker(mutex_);
    signaled_ = false;
  }

 private:
  std::condition_variable cv_;
  std::mutex mutex_;

  // True if this event is in the signaled state.
  bool signaled_ = false;

  CRON_DISALLOW_COPY_AND_ASSIGN(AutoResetWaitableEvent);
};

}  // namespace cron

#endif  // CRON_BASE_WAITABLE_EVENT_H_

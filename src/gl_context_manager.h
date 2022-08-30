/*
 * Created by Lu Ao (luao@bilibili.com) on 2022/07/25.
 * Copyright © 2022 bilibili. All rights reserved.
 */

#ifndef CRON_VIEW_WASM_GL_CONTEXT_MANAGER_H_
#define CRON_VIEW_WASM_GL_CONTEXT_MANAGER_H_

#include <string>

#include <emscripten/html5.h>
#include <vector>

#include "macros.h"

namespace cron {
namespace view {

using Closure = std::function<void()>;

class GLContextManager final {
 public:
  GLContextManager();

  bool InitializeContextForMainThread(const std::string& window);
  void ReleaseContextForMainThread();

 private:
  std::string window_;
  EMSCRIPTEN_WEBGL_CONTEXT_HANDLE main_context_;

  CRON_DISALLOW_COPY_AND_ASSIGN(GLContextManager);
};

}  // namespace view
}  // namespace cron

#endif

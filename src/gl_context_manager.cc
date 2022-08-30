/*
 * Created by Lu Ao (luao@bilibili.com) on 2022/07/25.
 * Copyright © 2022 bilibili. All rights reserved.
 */

#include "gl_context_manager.h"

namespace cron {
namespace view {

EmscriptenWebGLContextAttributes CreateDefaultWebGLAttributes() {
  EmscriptenWebGLContextAttributes attrs;
  attrs.majorVersion = 2;
  attrs.minorVersion = 0;
  attrs.explicitSwapControl = EM_TRUE;
  attrs.renderViaOffscreenBackBuffer = EM_TRUE;
  attrs.proxyContextToMainThread = EMSCRIPTEN_WEBGL_CONTEXT_PROXY_ALWAYS;
  return attrs;
}

GLContextManager::GLContextManager() : main_context_{0} {}

bool GLContextManager::InitializeContextForMainThread(
    const std::string& window) {
  ReleaseContextForMainThread();

  const auto attrs = CreateDefaultWebGLAttributes();
  main_context_ = emscripten_webgl_create_context(window.c_str(), &attrs);

  if (main_context_ <= 0) {
    emscripten_console_log("Could not create main GL Context.");
    ReleaseContextForMainThread();
    return false;
  }

  const auto make_current_result =
      emscripten_webgl_make_context_current(main_context_);
  if (make_current_result != EMSCRIPTEN_RESULT_SUCCESS) {
    ReleaseContextForMainThread();
    emscripten_console_log("Could not set current GL context to main context.");
    return false;
  }

  window_ = window;
  return true;
}

void GLContextManager::ReleaseContextForMainThread() {
  if (emscripten_webgl_get_current_context() == main_context_ &&
      main_context_ > 0) {
    emscripten_console_log("GLContextManager::ReleaseContextForMainThread");
    emscripten_webgl_make_context_current(0);
    emscripten_webgl_destroy_context(main_context_);
  }
}

}  // namespace view
}  // namespace cron

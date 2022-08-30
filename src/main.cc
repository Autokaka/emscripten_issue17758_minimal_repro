#include <emscripten/threading.h>
#include <thread>

#include "gl_context_manager.h"
#include "waitable_event.h"

// clang-format off
#include <GLES3/gl3.h>
#include <GLES3/gl2ext.h>
// clang-format on

cron::view::GLContextManager cm1{};
cron::view::GLContextManager cm2{};

std::thread t1;
std::thread t2;

void PlatformLoop() {
  // emscripten_console_log("Platform looping...");
}

int main() {
  cron::AutoResetWaitableEvent latch;
  emscripten_console_log("t1 start [BEGIN]");
  t1 = std::thread{[&latch]() {
    latch.Signal();
    emscripten_console_log("t1 start [END]");

    const auto canvas_id = "#canvas1";
    cm1.InitializeContextForMainThread(canvas_id);

    int width = 0;
    int height = 0;
    emscripten_get_canvas_element_size(canvas_id, &width, &height);
    glViewport(0, 0, width, height);
    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    emscripten_webgl_commit_frame();
  }};
  latch.Wait();

  emscripten_console_log("t2 start [BEGIN]");
  t2 = std::thread{[&latch]() {
    latch.Signal();
    emscripten_console_log("t2 start [END]");

    const auto canvas_id = "#canvas2";
    cm2.InitializeContextForMainThread(canvas_id);

    int width = 0;
    int height = 0;
    emscripten_get_canvas_element_size(canvas_id, &width, &height);
    glViewport(0, 0, width, height);
    glClearColor(0, 1, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    emscripten_webgl_commit_frame();
  }};
  latch.Wait();

  emscripten_set_main_loop(PlatformLoop, 60, EM_TRUE);
  emscripten_exit_with_live_runtime();
  return 0;
}

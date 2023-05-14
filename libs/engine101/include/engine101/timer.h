#pragma once

#include <SDL2/SDL.h>

namespace engine_101 {
class Timer {
 public:
  Timer() = default;
  ~Timer() = default;

  void start();
  void stop();
  void pause();
  void resume();

  Uint64 getTicks();

  bool isStarted();
  bool isPaused();

 private:
  Uint64 start_ticks_ = 0;
  Uint64 paused_ticks_ = 0;

  bool paused_ = false;
  bool started_ = false;
};

}  // namespace engine_101

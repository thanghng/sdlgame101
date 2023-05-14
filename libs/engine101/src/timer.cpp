#include "engine101/timer.h"

namespace engine_101 {

void Timer::start() {
  start_ticks_ = SDL_GetTicks64();
  started_ = true;

  paused_ = false;
  paused_ticks_ = 0;
}

void Timer::stop() {
  started_ = false;
  paused_ = false;

  start_ticks_ = 0;
  paused_ticks_ = 0;
}

void Timer::pause() {
  if (started_ && !paused_) {
    paused_ = true;

    paused_ticks_ = SDL_GetTicks64() - start_ticks_;
    start_ticks_ = 0;
  }
}

void Timer::resume() {
  if (started_ && paused_) {
    paused_ = false;

    start_ticks_ = SDL_GetTicks64() - paused_ticks_;
    paused_ticks_ = 0;
  }
}

Uint64 Timer::getTicks() {
  Uint64 time = 0;

  if (started_) {
    if (paused_) {
      time = paused_ticks_;
    } else {
      time = SDL_GetTicks64() - start_ticks_;
    }
  }

  return time;
}

bool Timer::isStarted() { return started_; }

bool Timer::isPaused() { return paused_; }

}  // namespace engine_101

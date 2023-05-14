#pragma once

#include <map>
#include <string>

#include "core.h"
#include "sprite.h"
#include "timer.h"

namespace engine_101 {
class Window {
 public:
  Window(const String& title, const Dimension& d);
  ~Window();

  bool init();
  void exec();

 private:
  void update();

  String title_;
  Dimension dimension_;

  SDLWindowPtr window_ = nullptr;
  SDLRendererPtr renderer_ = nullptr;
  std::map<String, std::unique_ptr<Sprite>> sprites_;
  Timer fps_timer_;
};

}  // namespace engine_101

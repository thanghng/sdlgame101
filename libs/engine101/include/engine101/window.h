#include "core.h"

namespace engine_101 {

class Window {
 public:
  Window(uint16_t w, uint16_t h);
  ~Window();

  bool init();
  void exec();

 private:
  void update();

  SDLPtrWindow window_;
  SDLPtrRenderer renderer_;
  uint16_t height_;
  uint16_t width_;
};

}  // namespace engine_101

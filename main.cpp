#include "engine101/window.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char *argv[]) {
  engine_101::Window window("SDL GAME 101", {SCREEN_WIDTH, SCREEN_HEIGHT});

  if (window.init()) {
    window.run();
  } else {
    std::cout << "Failed to init windows" << std::endl;
  }

  return 0;
}

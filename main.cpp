#include "engine101/window.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char *argv[]) {
  engine_101::Window window(SCREEN_WIDTH, SCREEN_HEIGHT);

  if (window.init()) {
    window.exec();
  } else {
    cout << "Failed to init windows" << endl;
  }

  return 0;
}

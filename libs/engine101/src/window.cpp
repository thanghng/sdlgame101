#include "engine101/window.h"

#include <SDL2/SDL_image.h>

namespace engine_101 {

const int screen_fps = 60;
const int screen_ticks_per_frame = 1000 / screen_fps;

Window::Window(const String& title, const Dimension& d) {
  title_ = title;
  dimension_ = d;
}

Window::~Window() {
  ENGINE101LOG("Exiting...");

  IMG_Quit();
  SDL_Quit();
}

bool Window::init() {
  ENGINE101LOG("Initialize Window!!");

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    ENGINE101LOG("SDL could not initialize! SDL_Error: ", SDL_GetError());
    return false;
  }

  // Set texture filtering to linear
  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
    ENGINE101LOG("Warning: Linear texture filtering not enabled!");
  }

  // Create window
  window_ =
      SDLWindowPtr(SDL_CreateWindow(title_.c_str(), SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED, dimension_.width,
                                    dimension_.height, SDL_WINDOW_SHOWN),
                   deleter());

  if (!window_) {
    ENGINE101LOG("Window could not be created! SDL_Error: ", SDL_GetError());
    return false;
  }

  // Create vsynced renderer for window_
  renderer_ = SDLRendererPtr(
      SDL_CreateRenderer(window_.get(), -1, SDL_RENDERER_ACCELERATED),
      deleter());

  if (!renderer_) {
    ENGINE101LOG("Renderer could not be created! SDL Error: ", SDL_GetError());
    return false;
  }

  // Initialize renderer_ color
  SDL_SetRenderDrawColor(renderer_.get(), 0xFF, 0xFF, 0xFF, 0xFF);

  // Initialize PNG loading
  int img_flag = IMG_INIT_PNG;
  if (!(IMG_Init(img_flag) & img_flag)) {
    ENGINE101LOG("SDL_image could not initialize! SDL_image Error: ",
                 IMG_GetError());
    return false;
  }

  return true;
}

void Window::exec() {
  ENGINE101LOG("Running Window loop!!");

  auto sprite = std::make_unique<Sprite>(renderer_, "resource/ninja_move.png",
                                         Dimension{45, 33}, Point2D{0, 0}, 6);
  sprites_.emplace("main", std::move(sprite));

  // Hack to get window to stay up
  SDL_Event e;
  bool quit = false;

  while (!quit) {
    fps_timer_.start();

    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) quit = true;
    }

    this->update();
  }

  ENGINE101LOG("Quiting loop...");
}

void Window::update() {
  // Clear screen
  SDL_RenderClear(renderer_.get());

  for (const auto& [_, sprite] : sprites_) {
    sprite->update(renderer_);
  }

  // Update screen
  SDL_RenderPresent(renderer_.get());

  Uint64 frame_ticks = fps_timer_.getTicks();

  if (frame_ticks < screen_ticks_per_frame) {
    SDL_Delay((Uint32)(screen_ticks_per_frame - frame_ticks));
  }
}

}  // namespace engine_101

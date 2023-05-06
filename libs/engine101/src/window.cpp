#include "engine101/window.h"

namespace engine_101 {

Window::Window(uint16_t w, uint16_t h) {
  width_ = w;
  height_ = h;
}

Window::~Window() {
  ENGINE101LOG("Exiting...");
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
  window_ = SDLPtrWindow(SDL_CreateWindow("engine101", SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED, width_,
                                          height_, SDL_WINDOW_SHOWN),
                         deleter());

  if (!window_) {
    ENGINE101LOG("Window could not be created! SDL_Error: ", SDL_GetError());
    return false;
  }

  // Create vsynced renderer for window_
  renderer_ = SDLPtrRenderer(
      SDL_CreateRenderer(window_.get(), -1,
                         SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
      deleter());

  if (!renderer_) {
    ENGINE101LOG("Renderer could not be created! SDL Error: ", SDL_GetError());
    return false;
  }

  // Initialize renderer_ color
  SDL_SetRenderDrawColor(renderer_.get(), 0xFF, 0xFF, 0xFF, 0xFF);

  // Initialize PNG loading
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags)) {
    ENGINE101LOG("SDL_image could not initialize! SDL_image Error: ",
                 IMG_GetError());
    return false;
  }

  return true;
}

void Window::exec() {
  ENGINE101LOG("Running Window loop!!");

  auto screenSurface =
      SDLPtrSurface(SDL_GetWindowSurface(window_.get()), deleter());

  // Fill the surface white
  SDL_FillRect(screenSurface.get(), NULL,
               SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

  // Update the surface
  SDL_UpdateWindowSurface(window_.get());

  // Hack to get window to stay up
  SDL_Event e;
  bool quit = false;
  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) quit = true;
    }
  }

  ENGINE101LOG("Quiting loop...");
}

}  // namespace engine_101

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <memory>
#include <sstream>

using namespace std;

namespace engine_101 {

struct deleter {
  void operator()(SDL_Window *p) const { SDL_DestroyWindow(p); }
  void operator()(SDL_Renderer *p) const { SDL_DestroyRenderer(p); }
  void operator()(SDL_Texture *p) const { SDL_DestroyTexture(p); }
  void operator()(SDL_Surface *p) const { SDL_FreeSurface(p); }
};

using SDLPtrWindow = std::unique_ptr<SDL_Window, deleter>;
using SDLPtrRenderer = std::unique_ptr<SDL_Renderer, deleter>;
using SDLPtrTexture = std::unique_ptr<SDL_Texture, deleter>;
using SDLPtrSurface = std::unique_ptr<SDL_Surface, deleter>;

template <typename... Msg>
void log(Msg &&...msg) {
  std::ostringstream oss;
  (oss << ... << std::forward<Msg>(msg));
  cout << oss.str() << endl;
}

}  // namespace engine_101

#define ENGINE101LOG(...) engine_101::log(__VA_ARGS__)

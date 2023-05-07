#pragma once

#include <SDL2/SDL.h>

#include <iostream>
#include <memory>
#include <sstream>

namespace engine_101 {

using String = std::string;

struct deleter {
  void operator()(SDL_Window *p) const { SDL_DestroyWindow(p); }
  void operator()(SDL_Renderer *p) const { SDL_DestroyRenderer(p); }
  void operator()(SDL_Texture *p) const { SDL_DestroyTexture(p); }
  void operator()(SDL_Surface *p) const { SDL_FreeSurface(p); }
};

using SDLWindowPtr = std::unique_ptr<SDL_Window, deleter>;
using SDLRendererPtr = std::unique_ptr<SDL_Renderer, deleter>;
using SDLTexturePtr = std::unique_ptr<SDL_Texture, deleter>;
using SDLSurfacePtr = std::unique_ptr<SDL_Surface, deleter>;
using Point2D = SDL_Point;

struct Dimension {
  int width;
  int height;

  bool valid() const { return width == 0 || height == 0; }
};

template <typename... Msg>
void log(Msg &&...msg) {
  std::ostringstream oss;
  (oss << ... << std::forward<Msg>(msg));
  std::cout << oss.str() << std::endl;
}

}  // namespace engine_101

#define ENGINE101LOG(...) engine_101::log(__VA_ARGS__)

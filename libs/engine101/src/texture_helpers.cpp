#include "engine101/texture_helpers.h"

#include <SDL2/SDL_image.h>

namespace engine_101 {

namespace texture_helpers {

TextureInfoPtr loadFromFile(const SDLRendererPtr& renderer,
                            const String& path) {
  ENGINE101LOG("Load texture from file!!");
  auto surface = SDLSurfacePtr(IMG_Load(path.c_str()), deleter());
  if (!surface) {
    ENGINE101LOG("Unable to load image ", path,
                 "! SDL_image Error: ", SDL_GetError());
  } else {
    return loadFromSurface(renderer, surface);
  }

  return nullptr;
}

TextureInfoPtr loadFromSurface(const SDLRendererPtr& renderer,
                               const SDLSurfacePtr& surface) {
  ENGINE101LOG("Load texture from surface!!");
  // Color key image
  SDL_SetColorKey(surface.get(), SDL_TRUE,
                  SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));

  auto new_texture = SDLTexturePtr(
      SDL_CreateTextureFromSurface(renderer.get(), surface.get()), deleter());

  if (new_texture) {
    Dimension d{surface->w, surface->h};
    auto res = std::make_unique<TextureInfo>();
    res->texture = std::move(new_texture);
    res->dimension = d;

    ENGINE101LOG("Load texture successful with height = ", d.height,
                 " and width = ", d.width);

    return res;
  }

  ENGINE101LOG("Unable to create texture from surface! SDL Error: ",
               SDL_GetError());
  return nullptr;
}

}  // namespace texture_helpers

}  // namespace engine_101

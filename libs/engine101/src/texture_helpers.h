#pragma once

#include "engine101/core.h"

namespace engine_101 {

namespace texture_helpers {

struct TextureInfo {
  SDLTexturePtr texture;
  Dimension dimension;

  // ??
  // TextureInfo& operator=(const TextureInfo& other) {
  //   this->dimension = other.dimension;
  //   this->texture.reset(other.texture.get());
  //   return *this;
  // }
};

using TextureInfoPtr = std::unique_ptr<TextureInfo>;

TextureInfoPtr loadFromFile(const SDLRendererPtr& renderer, const String& path);
TextureInfoPtr loadFromSurface(const SDLRendererPtr& renderer,
                               const SDLSurfacePtr& surface);

}  // namespace texture_helpers

}  // namespace engine_101

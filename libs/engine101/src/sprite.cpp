#include "engine101/sprite.h"

#include "engine101/texture_helpers.h"

namespace engine_101 {

Sprite::Sprite(const SDLRendererPtr& renderer, const String& path,
               const Dimension& d, const Point2D& p, uint32_t frames) {
  auto info = texture_helpers::loadFromFile(renderer, path);
  texture_ = std::move(info->texture);
  texture_dim_ = info->dimension;

  position_ = p;
  dimension_ = d.valid() ? texture_dim_ : d;
  frames_ = frames;
}

Sprite::Sprite(const SDLRendererPtr& renderer, const SDLSurfacePtr& surface,
               const Dimension& d, const Point2D& p, uint32_t frames) {
  auto info = texture_helpers::loadFromSurface(renderer, surface);
  texture_ = std::move(info->texture);
  texture_dim_ = info->dimension;

  position_ = p;
  dimension_ = d.valid() ? texture_dim_ : d;
  frames_ = frames;
}

Sprite::~Sprite() {}

void Sprite::update(const SDLRendererPtr& renderer) {
  int xSrc = (current_frame_ / frames_) * dimension_.width;

  SDL_Rect renderQuad{position_.x, position_.y, dimension_.width,
                      dimension_.height};
  SDL_Rect srcTexture{xSrc, 0, dimension_.width, dimension_.width};

  // Render sprite
  SDL_RenderCopy(renderer.get(), texture_.get(), &srcTexture, &renderQuad);

  if (++current_frame_ / frames_ >= frames_) {
    current_frame_ = 0;
  }
}

void Sprite::setPosition(const Point2D& p) { position_ = p; }

Point2D Sprite::getPosition() const { return position_; }

}  // namespace engine_101

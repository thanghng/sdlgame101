#pragma once

#include "core.h"

namespace engine_101 {

class Sprite {
 public:
  Sprite(const SDLRendererPtr& renderer, const String& path,
         const Dimension& d = {0, 0}, const Point2D& p = {0, 0},
         uint32_t frames = 1);
  Sprite(const SDLRendererPtr& renderer, const SDLSurfacePtr& surface,
         const Dimension& d = {0, 0}, const Point2D& p = {0, 0},
         uint32_t frames = 1);

  ~Sprite();

  // bool init(); ??
  void update(const SDLRendererPtr& renderer);

  void setPosition(const Point2D& p);
  Point2D getPosition() const;

 private:
  SDLTexturePtr texture_;

  Point2D position_;
  Dimension dimension_;
  Dimension texture_dim_;

  uint32_t current_frame_ = 0;
  uint32_t frames_;
};

}  // namespace engine_101

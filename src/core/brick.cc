#include <core/brick.h>

namespace platformgame {

Brick::Brick(const vec2& position, size_t width, size_t height) :
      position_(position), width_(width), height_(height) {}

vec2 Brick::GetUpsidePosition() const {
  return position_;
}

vec2 Brick::GetDownsidePosition() const {
  return {position_.x + width_, position_.y + height_};
}

vec2 Brick::GetSize() const {
  return {width_, height_};
}
}
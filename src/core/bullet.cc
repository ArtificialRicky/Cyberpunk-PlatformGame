#include <core/bullet.h>

namespace platformgame {

Bullet::Bullet(const vec2 &position, float velocity) :
position_(position), velocity_(velocity) {}

vec2 Bullet::GetPosition() const {
  return position_;
}

void Bullet::UpdatePosition() {
  position_.x += velocity_;
}
}

#include <core/floating_brick.h>

namespace platformgame {

FloatingBrick::FloatingBrick(const vec2& position, size_t width, size_t height, float velocity,
                             const pair<size_t, size_t>& routine)
    : Brick(position,width,height), velocity_(velocity), routine_(routine) {}

float FloatingBrick::GetVelocity() const {
  return velocity_;
}

vec2 FloatingBrick::GetRoutineUpperEnd() const {
  return {position_.x, routine_.first};
}

vec2 FloatingBrick::GetRoutineBottomEnd() const {
  return {position_.x, routine_.second};
}

void FloatingBrick::TurnAround() {
  velocity_ *= -1;
}

void FloatingBrick::MoveForward() {
  position_.y += velocity_;
}
}
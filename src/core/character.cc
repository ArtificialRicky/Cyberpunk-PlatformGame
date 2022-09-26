#include <core/character.h>

namespace platformgame {

Character::Character(const vec2 &position, double size, vec2 &velocity, bool is_facing_left):
      position_(position),
      size_(size), velocity_(velocity),
      is_facing_left_(is_facing_left),
      jumping_time_(0),
      free_fall_time_(0),
      has_double_jump_(false) {
  if (velocity_.y <= 0) {
    throw std::invalid_argument("not a valid y-component velocity");
  }
  if (velocity_.x < 0 && is_facing_left_) {
    throw std::invalid_argument("facing direction should be same as x-component velocity");
  }
}

vec2 Character::GetPosition() const {
  return position_;
}

void Character::SetPosition(const vec2& position) {
  position_ = position;
}

vec2 Character::GetVelocity() const {
  return velocity_;
}

vec2 Character::GetFootPosition() const {
  return {position_.x + size_/3, position_.y + size_};
}

void Character::TurnAround() {
  is_facing_left_ = !is_facing_left_;
  velocity_.x *= -1;
}

bool Character::IsFacingLeft() {
  return is_facing_left_;
}

void Character::MoveForward() {
  position_.x += velocity_.x;
}

void Character::FloatWithBrick(const FloatingBrick &brick) {
  if (brick.GetUpsidePosition() == brick.GetRoutineUpperEnd() ||
      brick.GetUpsidePosition() == brick.GetRoutineBottomEnd()) {
    position_.y -= brick.GetVelocity();
  } else {
    position_.y += brick.GetVelocity();
  }
}

void Character::Shoot() {
  velocity_.x < 0 ?
  bullets_.emplace_back(position_, float(-kBulletSpeed)) :
  bullets_.emplace_back(position_, kBulletSpeed);
}

void Character::Jump() {
  float velocity = velocity_.y + (kAccelerationRate*jumping_time_);
  if (velocity <= 0) {
    jumping_time_ = 0;
  } else {
    position_.y -= velocity;
    ++jumping_time_;
  }
}

void Character::FreeFall() {
  position_.y -= kGravityRate*free_fall_time_;
  ++free_fall_time_;
}

void Character::AddItemToInventory(const Item &item) {
  inventory_.push_back(item);
}

void Character::StopFreeFall() {
  free_fall_time_ = 0;
}

bool Character::IsJumping() {
  return jumping_time_ > 0;
}

void Character::DoubleJump() {
  has_double_jump_ = true;
  jumping_time_ = 0;
  Jump();
}

void Character::CanDoubleJumpAgain() {
  has_double_jump_ = false;
}

bool Character::IsFreeFalling() {
  return free_fall_time_ > 0;
}

bool Character::HasDoubleJumping() {
  return has_double_jump_;
}

vector<Item> Character::GetInventory() const {
  return inventory_;
}
}

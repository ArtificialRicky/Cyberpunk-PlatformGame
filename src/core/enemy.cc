#include <core/enemy.h>

namespace platformgame {

Enemy::Enemy(const vec2& position, float velocity, size_t hit_points, const pair<size_t , size_t>& routine) :
position_(position), velocity_(velocity), hit_points_(hit_points), routine_(routine) {}

vec2 Enemy::GetPosition() const {
  return position_;
}

float Enemy::GetVelocity() const {
  return velocity_;
}

vec2 Enemy::GetRoutineLeftEnd() const {
  return {routine_.first, position_.y};
}

vec2 Enemy::GetRoutineRightEnd() const {
  return {routine_.second, position_.y};
}

void Enemy::TurnAround() {
  velocity_ *= -1;
}

void Enemy::MoveForward() {
  position_.x += velocity_;
}

void Enemy::Shoot() {
  velocity_ < 0 ?
  bullets_.emplace_back(position_, float(-kBulletSpeed)) :
  bullets_.emplace_back(position_, kBulletSpeed);
}

size_t Enemy::GetHitPoints() const {
  return hit_points_;
}
}

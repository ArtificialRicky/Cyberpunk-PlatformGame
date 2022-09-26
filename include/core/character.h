#pragma once

#include "cinder/gl/gl.h"
#include "bullet.h"
#include "item.h"
#include "floating_brick.h"

namespace platformgame {

using glm::vec2;
using std::vector;

class Character {
 public:
  /**
   * parameter constructor
   * @param position
   * @param size
   * @param velocity
   */
  Character(const vec2& position, double size, vec2& velocity, bool is_facing_left);

  /**
   * get position of character
   * @return position
   */
  vec2 GetPosition() const;

  void SetPosition(const vec2& position);

  vec2 GetVelocity() const;

  /**
   * get position of the bottom of character
   * @return position
   */
  vec2 GetFootPosition() const;

  void TurnAround();

  bool IsFacingLeft();

  void MoveForward();

  void FloatWithBrick(const FloatingBrick& brick);

  void Jump();

  void FreeFall();

  void Shoot();

  void AddItemToInventory(const Item& item);

  void StopFreeFall();

  bool IsJumping();

  void DoubleJump();

  void CanDoubleJumpAgain();

  bool IsFreeFalling();

  bool HasDoubleJumping();

  vector<Item> GetInventory() const;


 private:
  /** position of character. */
  vec2 position_;

  /** height of character. */
  double size_;

  /** velocity of character. */
  vec2 velocity_; // TODO: x:moving distance, y: jumping distance

  /** shooting bullets from character. */
  vector<Bullet> bullets_;

  vector<Item> inventory_;

  float kBulletSpeed = 2;

  float kAccelerationRate = -0.38;

  float kGravityRate = -0.38;

  bool is_facing_left_;

  size_t jumping_time_;

  size_t free_fall_time_;

  bool has_double_jump_;
};

}  // namespace platformgame

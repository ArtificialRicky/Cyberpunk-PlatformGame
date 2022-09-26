#pragma once

#include "cinder/gl/gl.h"
#include "bullet.h"

namespace platformgame {

using glm::vec2;
using std::pair;
using std::vector;

class Enemy {
 public:
  /**
   * parameter constructor
   * @param position
   * @param velocity
   * @param hit_points
   * @param routine
   */
  Enemy(const vec2& position, float velocity, size_t hit_points, const pair<size_t , size_t>& routine);

  /**
   * get position of enemy
   * @return position
   */
  vec2 GetPosition() const;

  float GetVelocity() const;

  /**
   * get the left end of enemy moving routine
   * @return
   */
  vec2 GetRoutineLeftEnd() const;

  /**
   * get the right end of enemy moving routine
   * @return
   */
  vec2 GetRoutineRightEnd() const;

  size_t GetHitPoints() const;


  void TurnAround();

  void MoveForward();

  void Shoot();


 private:
  vec2 position_;

  float velocity_;

  size_t hit_points_;

  pair<size_t , size_t> routine_;

  vector<Bullet> bullets_;

  float kBulletSpeed = 2;
};

}

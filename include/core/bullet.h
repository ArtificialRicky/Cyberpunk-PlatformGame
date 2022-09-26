#pragma once

#include "cinder/gl/gl.h"

namespace platformgame {

using glm::vec2;

class Bullet {
 private:
  /** position of bullet. */
  vec2 position_;

  /** moving speed of bullet. */
  float velocity_;

 public:
  Bullet(const vec2& position, float velocity);

  vec2 GetPosition() const;

  /**
   * update position of bullet in one unit time
   */
  void UpdatePosition();
};
}

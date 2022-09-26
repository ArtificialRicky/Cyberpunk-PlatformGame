#pragma once

#include "cinder/gl/gl.h"

namespace platformgame {

using glm::vec2;

class Brick {
 protected:

  /** position of brick. */
  vec2 position_;

  /** size of brick. */
  size_t width_;

  size_t height_;

 public:
  /**
   * parameter constructor.
   * @param length
   */
  Brick(const vec2& position, size_t width, size_t height);

  /**
   * get position
   * @return position
   */
  vec2 GetUpsidePosition() const;


  vec2 GetDownsidePosition() const;

  vec2 GetSize() const;
};

}  // namespace platformgame
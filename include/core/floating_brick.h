#pragma once

#include "brick.h"

namespace platformgame {

using glm::vec2;
using std::pair;

class FloatingBrick : public Brick {
 public:
  FloatingBrick(const vec2& position, size_t width, size_t height, float velocity,
                const pair<size_t, size_t>& routine);

  float GetVelocity() const;


  vec2 GetRoutineUpperEnd() const;


  vec2 GetRoutineBottomEnd() const;

  void TurnAround();

  void MoveForward();

 private:


  float velocity_;

  pair<size_t , size_t> routine_;
};

}

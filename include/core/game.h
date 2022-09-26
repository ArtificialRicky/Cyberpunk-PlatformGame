#pragma once

#include <visualizer/texture.h>
#include "brick.h"
#include "character.h"
#include "floating_brick.h"
#include "cinder/gl/gl.h"
#include "enemy.h"

namespace platformgame {

using glm::vec2;
using std::vector;

class Game {
 public:

  Game(const Texture& texture);

  /**
   * display items in window
   */
  void Display() const;

  /**
   * update positions and status of items in one unit of time
   */
  void AdvanceOneFrame();

  /**
   * move character horizontally for several units of time
   */
  void CharacterJump();

  /**
   * move character for one unit of time
   */
  void CharacterMoveLeft(bool move_left);

  void Restart();

  bool IsWinning();

 private:

  Texture texture_;

  /** character that player controls. */
  Character character_;

  Brick exit_;
  /** enemies on map. */
  vector<Enemy> enemies_;

  vector<FloatingBrick> moving_bricks_;

  vector<Brick> static_bricks_;

  vector<Item> treasures_;


  /**
   * update enemies position in one unit time.
   */
  void UpdateEnemiesPositions();

  void UpdateFloatingBricksPositions();

  /**
   * update bullets position in one unit time.
   */
  void UpdateBulletsPositions();

  /**
   * update character position in one unit time.
   */
  void UpdateCharacterPosition();

  void UpdateTreasuresState();


  bool IsCharacterOnStaticBrick() const;

  bool IsCharacterOnFloatingBrick();

  bool IsCharacterCloseTo(const vec2& position, const vec2& object_size) const;

};
}

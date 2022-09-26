#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "core/character.h"
#include "core/brick.h"
#include "core/enemy.h"
#include "core/item.h"
#include "core/floating_brick.h"

namespace platformgame {

using ci::gl::Texture2d;
using ci::gl::Texture2dRef;
using std::vector;
using std::pair;
using glm::vec2;

class Texture {
 public:
  Texture(size_t window_width, size_t window_height);

  Texture2dRef GetExitImage() const;
  vec2 GetExitPosition() const;
  vec2 GetExitSize() const;
  Brick GetExit() const;

  Character GetCharacter() const;
  Texture2dRef GetCharacterImage() const;
  vec2 GetCharacterStartingPosition() const;
  vec2 GetCharacterSize() const;

  vector<FloatingBrick> GetShortBricks() const;
  Texture2dRef GetShortBrickImage() const;
  vec2 GetShortBrickSize() const;

  vector<Brick> GetLongBricks() const;
  Texture2dRef GetLongBrickImage() const;
  vec2 GetLongBrickSize() const;

  vector<Enemy> GetEnemies() const;
  Texture2dRef GetEnemyImage() const;
  vec2 GetEnemySize() const;

  vector<Item> GetItems() const;
  Texture2dRef GetItemImage(ItemType type) const;
  vec2 GetItemSize() const;


 private:

  size_t window_width_;
  size_t window_height_;

  size_t kCharacterSize = 100; // TODO: combine
  size_t kStandardSize = 100;
  size_t kGroundHeight = 100;
  size_t kHitPoints = 3;
  size_t kMovingSpeed = 2;

  pair<Character, Texture2dRef> character_;
  pair<Brick, Texture2dRef> exit_;
  vector<pair<FloatingBrick, Texture2dRef>> short_bricks_;
  vector<pair<Brick, Texture2dRef>> long_bricks_;
  vector<pair<Enemy, Texture2dRef>> enemies_;
  vector<pair<Item, Texture2dRef>> items_;

  pair<Character, Texture2dRef> ConstructCharacter();

  pair<Brick, Texture2dRef> ConstructExit();

  void ConstructShortBricks();

  void ConstructLongBricks();

  void ConstructEnemies();

  void ConstructItems();
  //TODO: design放这个class
};
}

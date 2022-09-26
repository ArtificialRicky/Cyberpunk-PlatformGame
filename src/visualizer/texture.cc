#include <visualizer/texture.h>

namespace platformgame {

using cinder::gl::Texture2d;
using cinder::gl::Texture2dRef;
using std::string;
using glm::vec2;

Texture::Texture(size_t window_width, size_t window_height) :
      window_width_(window_width), window_height_(window_height),
      character_(ConstructCharacter()), exit_(ConstructExit()) {
  ConstructShortBricks();

  ConstructLongBricks();

  ConstructEnemies();

  ConstructItems();
}


pair<Character, Texture2dRef> Texture::ConstructCharacter() {

  // initialize character
  vec2 char_position = {kCharacterSize / 2, window_height_ - kGroundHeight - kCharacterSize};
  vec2 char_velocity = {kMovingSpeed*10, kMovingSpeed*5};
  Character character(char_position, kCharacterSize, char_velocity, false);

  // import character
  auto char_image = ci::loadImage(ci::app::loadAsset("character.png"));
  Texture2dRef texture = Texture2d::create(char_image);
  return pair<Character, Texture2dRef>(character, texture);
}

void Texture::ConstructShortBricks() {
  auto brick_image = ci::loadImage(ci::app::loadAsset("short_brick.png"));
  Texture2dRef texture = Texture2d::create(brick_image);


  FloatingBrick brick_1({window_width_*3/5, window_height_*3/5}, GetShortBrickSize().x, GetShortBrickSize().y,
                        kMovingSpeed *1.5, {0, window_height_-kStandardSize / 2});
  short_bricks_.emplace_back(brick_1, texture);

  FloatingBrick brick_2({window_width_/2, window_height_/2}, GetShortBrickSize().x, GetShortBrickSize().y,
                        kMovingSpeed *0.7, {0, window_height_-kStandardSize / 2});
  short_bricks_.emplace_back(brick_2, texture);

  FloatingBrick brick_3({window_width_*2 / 5, window_height_ - kGroundHeight}, GetShortBrickSize().x, GetShortBrickSize().y,
                        kMovingSpeed *1.2, {0, window_height_-kStandardSize / 2});
  short_bricks_.emplace_back(brick_3, texture);

  FloatingBrick brick_4({window_width_/3-kCharacterSize, window_height_ * 3 / 4}, GetShortBrickSize().x, GetShortBrickSize().y, kMovingSpeed *2, {0, window_height_ / 2});
  short_bricks_.emplace_back(brick_4, texture);

  FloatingBrick starting_brick({kCharacterSize / 2, window_height_ - kGroundHeight}, GetShortBrickSize().x, GetShortBrickSize().y, 0, {window_height_ - kGroundHeight, window_height_ - kGroundHeight});
  short_bricks_.emplace_back(starting_brick, texture);

  FloatingBrick test({kCharacterSize / 2+kGroundHeight, window_height_ - kGroundHeight}, GetShortBrickSize().x, GetShortBrickSize().y, kMovingSpeed*2, {kGroundHeight*2, window_height_-kStandardSize / 2});
  short_bricks_.emplace_back(test, texture);
}

void Texture::ConstructLongBricks() {
  auto brick_image = ci::loadImage(ci::app::loadAsset("long_brick.png"));
  Texture2dRef texture = Texture2d::create(brick_image);

  Brick brick_1({0, kGroundHeight*2}, GetLongBrickSize().x, GetLongBrickSize().y);
  long_bricks_.emplace_back(brick_1, texture);

  Brick brick_2({brick_1.GetUpsidePosition().x+ kStandardSize, brick_1.GetUpsidePosition().y}, GetLongBrickSize().x, GetLongBrickSize().y);
  long_bricks_.emplace_back(brick_2, texture);

  Brick brick_7({brick_2.GetUpsidePosition().x+ kStandardSize, brick_1.GetUpsidePosition().y}, GetLongBrickSize().x, GetLongBrickSize().y);
  long_bricks_.emplace_back(brick_7, texture);

  Brick brick_3({window_width_-kGroundHeight,window_height_ - 2*kGroundHeight}, GetLongBrickSize().x, GetLongBrickSize().y);
  long_bricks_.emplace_back(brick_3, texture);

  Brick brick_4({window_width_-kGroundHeight*2,window_height_ - 2*kGroundHeight}, GetLongBrickSize().x, GetLongBrickSize().y);
  long_bricks_.emplace_back(brick_4, texture);

  Brick brick_5({window_width_-kGroundHeight*3,window_height_ - 2*kGroundHeight}, GetLongBrickSize().x, GetLongBrickSize().y);
  long_bricks_.emplace_back(brick_5, texture);

  Brick brick_6({window_width_-kGroundHeight*4,window_height_ - 2*kGroundHeight}, GetLongBrickSize().x, GetLongBrickSize().y);
  long_bricks_.emplace_back(brick_6, texture);

  Brick brick_8({GetExitPosition().x- kStandardSize, kStandardSize *2}, GetLongBrickSize().x, GetLongBrickSize().y);
  long_bricks_.emplace_back(brick_8, texture);

  Brick brick_9({GetExitPosition().x- kStandardSize *2,
                 brick_8.GetUpsidePosition().y+GetLongBrickSize().y}, GetLongBrickSize().x, GetLongBrickSize().y);
  long_bricks_.emplace_back(brick_9, texture);

  Brick exit({GetExitPosition().x,brick_8.GetUpsidePosition().y-GetLongBrickSize().y}, GetLongBrickSize().x, GetLongBrickSize().y);
  long_bricks_.emplace_back(exit, texture);
}

void Texture::ConstructEnemies() {
  auto enemy_image = ci::loadImage(ci::app::loadAsset("enemy.png"));
  Texture2dRef texture = Texture2d::create(enemy_image);

  Enemy enemy_1({kStandardSize *2, kGroundHeight}, kMovingSpeed,kHitPoints,
                {kStandardSize *1, kStandardSize*2});
  enemies_.emplace_back(enemy_1, texture);

  Enemy enemy_2({window_width_-kGroundHeight*4, window_height_ - kGroundHeight*3},
      kMovingSpeed,kHitPoints, {window_width_-kGroundHeight*3, window_width_-kGroundHeight*2});
  enemies_.emplace_back(enemy_2, texture);
}

void Texture::ConstructItems() {
  auto diamond_image = ci::loadImage(ci::app::loadAsset("diamond.png"));
  Texture2dRef diamond_texture = Texture2d::create(diamond_image);

  Item diamond(ItemType::Diamond, {window_width_-kGroundHeight, window_height_-kGroundHeight*3}, GetItemSize().x);
  items_.emplace_back(diamond, diamond_texture);

  auto gem_image = ci::loadImage(ci::app::loadAsset("soul_gem.png"));
  Texture2dRef gem_texture = Texture2d::create(gem_image);

  Item gem(ItemType::SoulGem, {0, kGroundHeight}, GetItemSize().x);
  items_.emplace_back(gem, gem_texture);
}

pair<Brick, Texture2dRef> Texture::ConstructExit() {
  auto image = ci::loadImage(ci::app::loadAsset("exit.png"));
  Texture2dRef texture = Texture2d::create(image);

  Brick exit = Brick({window_width_-kGroundHeight, 0}, GetExitSize().x, GetExitSize().y);
  return {exit, texture};
}

Character Texture::GetCharacter() const {
  return character_.first;
}

Texture2dRef Texture::GetCharacterImage() const {
  return character_.second;
}

vec2 Texture::GetCharacterStartingPosition() const {
  return character_.first.GetPosition();
}

vec2 Texture::GetCharacterSize() const {
  return {kCharacterSize, kCharacterSize};
}

vector<FloatingBrick> Texture::GetShortBricks() const {
  vector<FloatingBrick> short_bricks;
  for (auto& brick: short_bricks_) {
    short_bricks.emplace_back(brick.first);
  }
  return short_bricks;
}

Texture2dRef Texture::GetShortBrickImage() const {
  return short_bricks_.front().second;
}

vec2 Texture::GetShortBrickSize() const {
  return {kStandardSize, kStandardSize / 2};
}

Texture2dRef Texture::GetLongBrickImage() const {
  return long_bricks_.front().second;
}

vector<Brick> Texture::GetLongBricks() const {
  vector<Brick> long_bricks;
  for (auto& brick: long_bricks_) {
    long_bricks.emplace_back(brick.first);
  }
  return long_bricks;
}

vec2 Texture::GetLongBrickSize() const {
  return {kStandardSize, kStandardSize / 4};
}

Texture2dRef Texture::GetExitImage() const {
  return exit_.second;
}

vec2 Texture::GetExitPosition() const {
  return exit_.first.GetUpsidePosition();
}

vec2 Texture::GetExitSize() const {
  return {kStandardSize, kStandardSize *2};
}

Brick Texture::GetExit() const {
  return exit_.first;
}

vector<Enemy> Texture::GetEnemies() const {
  vector<Enemy> enemies;
  for (auto& enemy: enemies_) {
    enemies.emplace_back(enemy.first);
  }
  return enemies;
}

Texture2dRef Texture::GetEnemyImage() const {
  return enemies_.front().second;
}

vec2 Texture::GetEnemySize() const {
  return GetCharacterSize();
}

vector<Item> Texture::GetItems() const {
  vector<Item> items;
  for (auto& item: items_) {
    items.emplace_back(item.first);
  }
  return items;
}

Texture2dRef Texture::GetItemImage(ItemType type) const {
  for (auto& item: items_) {
    if (item.first.GetItemType() == type) {
      return item.second;
    }
  }
  throw std::invalid_argument("no image for this type of item");
}

vec2 Texture::GetItemSize() const {
  return {kStandardSize, kStandardSize};
}
}
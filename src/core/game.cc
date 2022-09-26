#include <core/game.h>

#include <utility>

namespace platformgame {


Game::Game(const Texture& texture) : texture_(texture),
      character_(texture_.GetCharacter()),
      exit_(texture_.GetExit()),
      enemies_(texture_.GetEnemies()),
      moving_bricks_(texture_.GetShortBricks()),
      static_bricks_(texture_.GetLongBricks()),
      treasures_(texture_.GetItems()) {}


void Game::Display() const {
  // character displays

  vec2 character_size = texture_.GetCharacterSize();
  if (character_.GetVelocity().x < 0) {character_size.x *= -1;}
  ci::gl::draw(texture_.GetCharacterImage(),
               ci::Rectf(character_.GetPosition(),
                         character_.GetPosition() + character_size));

  // enemies display
  for (const Enemy& enemy: enemies_) {
    vec2 enemy_size = texture_.GetEnemySize();
    if (enemy.GetVelocity() < 0) {enemy_size.x *= -1;}
    ci::gl::draw(texture_.GetEnemyImage(),
                 ci::Rectf(enemy.GetPosition(), enemy.GetPosition() + enemy_size));
  }

  // bricks display
  for (const FloatingBrick& brick: moving_bricks_) {
    ci::gl::draw(texture_.GetShortBrickImage(),
                 ci::Rectf(brick.GetUpsidePosition(),
                  brick.GetUpsidePosition() +
                           texture_.GetShortBrickSize()));
  }

  for (const Item& item: treasures_) {
    ci::gl::draw(texture_.GetItemImage(item.GetItemType()),
                 ci::Rectf(item.GetPosition(),
                           item.GetPosition() +
                           texture_.GetItemSize()));
  }
}

void Game::AdvanceOneFrame() {

  UpdateEnemiesPositions();

  UpdateFloatingBricksPositions();

  UpdateCharacterPosition();

  UpdateTreasuresState();

}

void Game::UpdateCharacterPosition() {
  if (character_.IsJumping()) {
    character_.Jump();
    character_.StopFreeFall();
  } else if (IsCharacterOnFloatingBrick()) {
    character_.StopFreeFall();
    character_.CanDoubleJumpAgain();
  } else if (IsCharacterOnStaticBrick()) {
    character_.StopFreeFall();
    character_.CanDoubleJumpAgain();
  } else {
    character_.FreeFall();
  }
}

void Game::UpdateEnemiesPositions() {
  for(Enemy& enemy: enemies_) {
    if (enemy.GetPosition().x <= enemy.GetRoutineLeftEnd().x &&
        enemy.GetVelocity() < 0) {
      enemy.TurnAround();
    }
    if (enemy.GetPosition().x >= enemy.GetRoutineRightEnd().x &&
        enemy.GetVelocity() > 0) {
      enemy.TurnAround();
    }
    enemy.MoveForward();
  }
}

void Game::UpdateFloatingBricksPositions() {
  for(FloatingBrick& brick: moving_bricks_) {
    if (brick.GetUpsidePosition().y <= brick.GetRoutineUpperEnd().y &&
        brick.GetVelocity() < 0) {
      brick.TurnAround();
    }
    if (brick.GetUpsidePosition().y >= brick.GetRoutineBottomEnd().y &&
        brick.GetVelocity() > 0) {
      brick.TurnAround();
    }
    brick.MoveForward();
  }
}

void Game::UpdateTreasuresState() {

  for(auto iter = treasures_.begin(); iter != treasures_.end();){
    if (IsCharacterCloseTo(iter->GetPosition(),{iter->GetSize(), iter->GetSize()})) {
      character_.AddItemToInventory(*iter);
      iter = treasures_.erase(iter);
    } else {
      ++iter;
    }
  }
}

void Game::CharacterMoveLeft(bool move_left) {
  if (character_.IsFacingLeft() == move_left) {
    character_.MoveForward();
  } else {
    character_.TurnAround();
  }
}

void Game::CharacterJump() {
  if (character_.IsJumping() && !character_.HasDoubleJumping()) {
    character_.DoubleJump();
    std::cout << "double jump" << std::endl;
  }
   else if (character_.IsFreeFalling() && !character_.HasDoubleJumping()) {
    character_.DoubleJump();
  }

  else if (!character_.IsJumping() && (IsCharacterOnStaticBrick() || IsCharacterOnFloatingBrick())) {
    character_.Jump();
  }
}

bool Game::IsCharacterOnStaticBrick() const {

  for (const auto& brick: static_bricks_) {
    if (IsCharacterCloseTo(brick.GetUpsidePosition(), brick.GetSize())) {
      return true;
    }
  }
  return false;
}

bool Game::IsCharacterOnFloatingBrick() {
  for (const FloatingBrick& brick: moving_bricks_) {
    if (IsCharacterCloseTo(brick.GetUpsidePosition(), brick.GetSize())) {
      character_.FloatWithBrick(brick);
      return true;
    }
  }
  return false;
}

bool Game::IsCharacterCloseTo(const vec2& position, const vec2& object_size) const {
  return ((character_.GetFootPosition().x >= position.x) &&
          (character_.GetFootPosition().x < position.x + object_size.x) &&
          (character_.GetFootPosition().y >= position.y) &&
          (character_.GetFootPosition().y < position.y+object_size.y + object_size.y / 3));
}

void Game::Restart() {
  character_.SetPosition(texture_.GetCharacterStartingPosition());
}

bool Game::IsWinning() {
  bool contain_diamond = false;
  bool contain_soul_gem = false;
  bool at_exit = false;
  for (const Item& item: character_.GetInventory()) {
    if (item.GetItemType() == ItemType::SoulGem) {
      contain_soul_gem = true;
    }
    if (item.GetItemType() == ItemType::Diamond) {
      contain_diamond= true;
    }
  }
  if (IsCharacterCloseTo(exit_.GetUpsidePosition(), exit_.GetSize())) {
    at_exit = true;
  }
  return contain_diamond && contain_soul_gem && at_exit;
}

}
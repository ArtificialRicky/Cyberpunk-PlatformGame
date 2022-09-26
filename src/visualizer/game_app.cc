#include <visualizer/game_app.h>

namespace platformgame {

GameApp::GameApp() {
  ci::app::setWindowSize(kWindowWidth, kWindowHeight);
}

void GameApp::draw() {
  ci::Color background_color("black");
  ci::gl::clear(background_color);

  if (game_.IsWinning()) {
    ci::gl::drawStringCentered("Mission Complete!",
                               ci::vec2(kWindowWidth/2, kWindowHeight/2),
                               ci::Color("white"),kUiFont);
  } else {
    for (Brick& brick : texture.GetLongBricks()) {
      ci::gl::draw(
          texture.GetLongBrickImage(),
          ci::Rectf(brick.GetUpsidePosition(),
                    brick.GetUpsidePosition() + texture.GetLongBrickSize()));
    }

    ci::gl::draw(texture.GetExitImage(),
                 ci::Rectf(texture.GetExitPosition(),
                           texture.GetExitPosition() + texture.GetExitSize()));

    game_.Display();
  }
}

void GameApp::update() {
  game_.AdvanceOneFrame();
}

void GameApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_RIGHT:
    case ci::app::KeyEvent::KEY_d:
      game_.CharacterMoveLeft(false);
      break;

    case ci::app::KeyEvent::KEY_LEFT:
    case ci::app::KeyEvent::KEY_a:
      game_.CharacterMoveLeft(true);
      break;

    case ci::app::KeyEvent::KEY_UP:
    case ci::app::KeyEvent::KEY_w:
      game_.CharacterJump();
      break;

    case ci::app::KeyEvent::KEY_RETURN:
      game_.Restart();
      break;
  }
}
}
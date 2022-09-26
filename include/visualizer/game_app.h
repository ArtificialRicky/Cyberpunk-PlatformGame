#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "texture.h"
#include "core/game.h"

namespace platformgame {

class GameApp : public ci::app::App {
 public:
  GameApp();

  void draw() override;
  void update() override;
  void keyDown(ci::app::KeyEvent event) override;


 private:
  const size_t kWindowWidth = 1400;
  const size_t kWindowHeight = 700;
  const ci::Font kUiFont = ci::Font("Arial", 30);

  Texture texture = Texture(kWindowWidth, kWindowHeight);
  Game game_ = Game(texture);
};
}
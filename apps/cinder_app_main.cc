#include <visualizer/game_app.h>

using platformgame::GameApp;

void prepareSettings(GameApp::Settings* settings) {
  settings->setResizable(false);
}

CINDER_APP(GameApp, ci::app::RendererGl, prepareSettings);

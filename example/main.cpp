#include "mars.hpp"

class MyGame : public mars::Engine {
public:
  void OnStart() override {
    std::cout << "Hello world!" << std::endl;
  }
  void OnEnd() override {
    std::cout << "Goodbye world!" << std::endl;
  }
};

int main() {
  MyGame game;
  game.Start();
  while(game.IsRunning()) {
    game.Update();
  }
  game.End();
  return 0;
}
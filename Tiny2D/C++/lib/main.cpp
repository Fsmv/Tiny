#include <stdio.h>
#include "SDL.h"

#include "Game.h"
#include "graphics/Screen.h"
#include "graphics/Sprite.h"

class TestScreen : public Tiny2D::Screen {
public:
    TestScreen() : Tiny2D::Screen(1280, 720), sprite("./icon.png") { this->translate(-50, -50); }

    void tick(unsigned int dt);
    void render();

private:
    Tiny2D::Sprite sprite;
};

void TestScreen::tick(unsigned int dt) {
    this->translate(1, 1);
}

void TestScreen::render() {
    this->sprite.draw(this->surface, 50, 50);
    this->sprite.draw(this->surface, 600, 600);
}

int main(int argc, char *argv[]) {
    Tiny2D::Game game;
    TestScreen test;

    game.start();
    game.setCurrentScreen(&test);
    SDL_Delay(10000);
    game.stop();
}

#include <stdio.h>
#include "SDL.h"

#include "Game.h"
#include "graphics/Screen.h"
#include "graphics/Sprite.h"
#include "graphics/Animation.h"
#include "graphics/Entity.h"
#include "graphics/Text.h"
#include "utils/InputHandler.h"

int numFrames[2] = {2, 2};

class TestScreen : public Tiny2D::Screen {
public:
    TestScreen(Tiny2D::InputHandler *ih) : Tiny2D::Screen(1280, 720, ih) {
        this->translate(-50, -50);
        ih->registerAction("drag", Tiny2D::InputHandler::MOUSE_ONE);
        ih->registerAction("up", SDLK_w);
        ih->registerAction("up", SDLK_UP);
    }

    void load(SDL_Renderer *renderer);
    void tick(unsigned int dt);
    void render(SDL_Renderer *renderer);
private:
    Tiny2D::Sprite sprite;
    Tiny2D::Animation anim;
    Tiny2D::Entity ent;
    Tiny2D::Text text;
};

void TestScreen::load(SDL_Renderer *renderer) {
    sprite.load(renderer, "./icon.png");
    anim.load(renderer, "./anim.png", 4, 32, 32);
    ent.load(renderer, "./anim.png", numFrames, 2, 32, 32);
    text.load(renderer, "Hello World", "./res/OpenSans-Regular.ttf", 12);

    anim.play();
    ent.setCurrentAnimation(1);
    ent.play();
}

void TestScreen::tick(unsigned int dt) {
    if(ih->isPressed("drag")) {
        this->translate(-ih->mouse.dx, -ih->mouse.dy);
        ih->setRelativeMouseMode(true);
    }else{
        ih->setRelativeMouseMode(false);
    }

    if(ih->isPressed("up")) {
        this->translate(0, 10);
    }
    anim.tick(dt);
    ent.tick(dt);
}

void TestScreen::render(SDL_Renderer *renderer) {
    this->sprite.draw(renderer, 50, 50);
    //this->anim.draw(renderer, 600, 600);
    this->ent.draw(renderer);
    //this->text.draw(renderer);
}

int main(int argc, char *argv[]) {
    Tiny2D::InputHandler ih;
    Tiny2D::Game game(&ih);
    TestScreen test(&ih);

    game.start();
    game.setCurrentScreen(&test);

    game.waitThread();

    return 0;
}

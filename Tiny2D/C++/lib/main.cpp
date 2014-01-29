#include <stdio.h>
#include "SDL.h"

#include "Game.h"
#include "graphics/Screen.h"
#include "graphics/Sprite.h"
#include "graphics/Animation.h"
#include "graphics/Entity.h"
#include "utils/InputHandler.h"

int numFrames[2] = {2, 2};

class TestScreen : public Tiny2D::Screen {
public:
    TestScreen(Tiny2D::InputHandler *ih) : Tiny2D::Screen(1280, 720, ih), 
        sprite("./icon.png"), 
        anim("./anim.png", 4, 32, 32),
        ent("./anim.png", numFrames, 2, 32, 32) { 
            this->translate(-50, -50);
            anim.play();
            ent.setCurrentAnimation(1);
            ent.play();

            ih->registerAction("drag", SDL_BUTTON_LEFT);
        }

    void tick(unsigned int dt);
    void render();
private:
    Tiny2D::Sprite sprite;
    Tiny2D::Animation anim;
    Tiny2D::Entity ent;
};

void TestScreen::tick(unsigned int dt) {
    if(ih->isPressed("drag")) {
        this->translate(-ih->mouse.dx, -ih->mouse.dy);
    }
    anim.tick(dt);
    ent.tick(dt);
}

void TestScreen::render() {
    this->sprite.draw(this->surface, 50, 50);
    this->anim.draw(this->surface, 600, 600);
    this->ent.draw(this->surface);
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

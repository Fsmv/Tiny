#include <stdio.h>
#include "Game.h"

int main(int argc, char *argv[]) {
    Tiny2D::Game game;
    game.init();
    game.createWindow();
    game.start();
    SDL_Delay(2000);
    game.stop();
}

#include "Game.h"
#include "Logger.h"

using namespace Tiny2D;

Logger logger("Game");

Game::Game(const char *title, int width, int height) : title(title), width(width), height(height) {
}

Game::~Game() {
}

int Game::run(void *data) {
    Game *g = (Game*) data;

    while(g->running){
        logger.debug("run");
    }
}

void Game::init() {
    logger.debug("Initializing game");
}

void Game::start() {
    logger.debug("Starting game");
    running = true;
    this->thread = SDL_CreateThread(&Game::run, "Game", this);
}

void Game::stop() {
    logger.debug("Stopping game");
    running = false;

    SDL_WaitThread(this->thread, nullptr);

    SDL_DestroyWindow(this->window);
    this->window = nullptr;
    SDL_Quit();
}

void Game::createWindow() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        logger.error("SDL could not initialize");
        logger.error(SDL_GetError());
    }else{
        window = SDL_CreateWindow(this->title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  this->width, this->height, SDL_WINDOW_SHOWN);

        if(this->window == nullptr) {
            logger.error("SDL could not create window");
            logger.error(SDL_GetError());
        }else{
            this->surface = SDL_GetWindowSurface(this->window);
        }
    }
}

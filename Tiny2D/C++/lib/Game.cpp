#include <stdio.h>
#include "SDL_image.h"
#include "Game.h"
#include "utils/Logger.h"

using namespace Tiny2D;

Logger logger("Game");

Game::Game(const char *title, int width, int height) : title(title), width(width), height(height) {
}

Game::~Game() {
}

void Game::tick(unsigned int dt) {
    //this->currentScreen.tick(dt);
}

void Game::render() {
    SDL_FillRect(this->surface, nullptr, SDL_MapRGB(this->surface->format, 0xFF, 0xFF, 0xFF));

    //this->currentScreen.draw(this->surface);

    SDL_UpdateWindowSurface(this->window);
}

int Game::run(void *data) {
    Game *g = (Game*) data;
    
    double unprocessedTicks = 0.0;
    double msPerTick = 1000.0/g->tps;

    double unrenderedFrames = 0.0;
    double msPerFrame = 1000.0/g->fps;

    unsigned int lastUpdateTime = SDL_GetTicks();
    unsigned int lastTickTime = SDL_GetTicks();;

    unsigned int lastFpsTime = SDL_GetTicks();
    int frameCount = 0;
    int tickCount = 0;

    while(g->running){
        if(g->changedRates) {
            if(g->limitTps)
                msPerTick = 1000.0/g->tps;

            if(g->limitFps)
                msPerFrame = 1000.0/g->fps;

            g->changedRates = false;
        }

        unsigned int now = SDL_GetTicks();
        unprocessedTicks += (now - lastUpdateTime) / msPerTick;
        unrenderedFrames += (now - lastUpdateTime) / msPerFrame;
        lastUpdateTime = now;

        if(!g->limitTps || unprocessedTicks >= 1.0) {
            g->tick(now - lastTickTime);
            unprocessedTicks -= 1.0;
            tickCount++;
            //set to now instead of SDL_GetTicks() to count the time to process in the delta time
            lastTickTime = now;
        }

        if(!g->limitFps || unrenderedFrames >= 1.0) {
            g->render();
            unrenderedFrames -= 1.0;
            frameCount++;
        }

        if(g->printFps && SDL_GetTicks() - lastFpsTime > 1000) {
            //don't use logger for this so we don't clutter the log file
            printf("%d fps; %d tps", frameCount, tickCount);
            frameCount = tickCount = 0;
            lastFpsTime = SDL_GetTicks();
        }
    }
}

void Game::start() {
    createWindow();

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
            this->setIcon(this->icon);

            this->surface = SDL_GetWindowSurface(this->window);

            this->setBackgroundColor(this->background);
        }
    }
}

void Game::setIcon(const char *icon) {
    this->icon = icon;

    if(this->window != nullptr) {
        SDL_Surface *image = IMG_Load(icon);
        
        if(image != nullptr) {
            SDL_SetWindowIcon(this->window, image);
            SDL_FreeSurface(image);
        }
    }
}

void Game::setFps(int fps) {
    this->fps = fps;

    this->limitFps = fps <= 0 ? false : true;
    this->changedRates = true;
}

void Game::setTps(int tps) {
    this->tps = tps;
    
    this->limitTps = tps <= 0 ? false : true;
    this->changedRates = true;
}

void Game::setBackgroundColor(unsigned int color) {
    if(this->surface == nullptr) {
        this->background = color;
    }else{
        this->background = SDL_MapRGB(this->surface->format, (color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF);
    }
}

void Game::setPrintFps(bool printFps) {
    this->printFps = printFps;
}

#pragma once
#include "SDL.h"
#include "SDL_thread.h"

namespace Tiny2D {
class Game {
    public:
        Game(const char *title = "Game", int width = 720, int height = 480);
        ~Game();
        
        //static because SDL_CreateThreads needs a C function 
        static int run(void *data);
        void init();
        void start();
        void stop();
        void createWindow();
    
    private:
        const char *title;
        int width;
        int height;
        int fps = 60;
        int tps = 60;
        bool printFPS = true;
        bool running = false;

        SDL_Thread *thread = nullptr;
        SDL_Window *window = nullptr;
        SDL_Surface *surface = nullptr;
};
}

#pragma once

#include "SDL.h"
#include "SDL_thread.h"

#include "graphics/Screen.h"
#include "utils/InputHandler.h"

namespace Tiny2D {
class Game {
    public:
        Game(const char *title = "Game", int width = 720, int height = 480);
        ~Game();

        /**
         * Starts running the game
         *
         * Also creates a window
         */
        void start();
        /**
         * Stops the game
         *
         * Also destroys the window
         */
        void stop();
        void waitThread();

        /**
         * Set the location of the window icon image
         *
         * if null (or not found), do not set an icon
         * default: "/icon.png"
         *
         * @param icon location of the icon image
         */
        void setIcon(const char *icon);
        /**
         * Sets the frames per second to limit rendering to
         *
         * if <= 0 unlimited
         * default: 60
         *
         * @param fps the fps to set
         */
        void setFps(int fps);
        /**
         * Sets the number of updates per second to limit the game to
         *
         * if <= 0 unlimited
         * 
         * @param tps the tps to set
         */
        void setTps(int tps);
        /**
         * Sets the color to use when clearing the screen
         *
         * default: 0x00FFFFFF
         *
         * @param color the color to set to (in the format 0x00RRGGBB)
         */
        void setBackgroundColor(unsigned int color);
        /**
         * Sets whether or not the engine should print the current fps and tps
         *
         * default: true
         *
         * @param printFps if true print the fps and tps on stdout
         */
        void setPrintFps(bool printFps);
        /**
         * Sets the screen to draw and update
         *
         * @param screen the screen to set
         */
        void setCurrentScreen(Tiny2D::Screen *screen);
    private:
        void tick(unsigned int dt);
        void render();
        void createWindow();

        //static because SDL_CreateThreads needs a C function 
        static int run(void *data);
        static void quit(void *g);

        const char *title;
        int width;
        int height;
        const char *icon = "/icon.png";
        int fps = 60;
        int tps = 60;
        bool changedRates = false;
        bool limitFps = true;
        bool limitTps = true;
        bool printFps = true;
        bool running = false;
        unsigned int background = -1;
        Tiny2D::Screen *currentScreen = nullptr;
        Tiny2D::Screen *newScreen = nullptr;
        Tiny2D::InputHandler ih;

        SDL_Thread *thread = nullptr;
        SDL_Window *window = nullptr;
        SDL_Surface *surface = nullptr;
};
}

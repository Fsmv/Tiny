#pragma once
#include "SDL.h"
#include "graphics/Drawable.h"

namespace Tiny2D {
class Animation : virtual public Drawable {
public:
    Animation(const char *imagePath, int numFrames = 1, int width = -1, int height = -1);
    virtual ~Animation();

    void draw(SDL_Surface *surface);
    void draw(SDL_Surface *surface, int x, int y);
    void tick(unsigned int dt);

    void play();
    void pause();
    void restart();
    
    void nextFrame();
    void setCurrentFrame(int frame);

    void setFps(int fps);

protected:
    int numFrames;
    int currentFrame;

private:
    SDL_Surface *spriteSheet;
    SDL_Rect frameRect, drawRect;

    double framesToSkip = 0.0;
    int fps = 10;
    bool isPlaying = false;
};
}

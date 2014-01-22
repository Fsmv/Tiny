#pragma once
#include "SDL.h"
#include "graphics/Drawable.h"

namespace Tiny2D {
class Animation : public Drawable {
public:
    Animation(const char *imagePath, int numFrames, int width, int height);
    ~Animation();

    void draw(SDL_Surface *surface);
    void draw(SDL_Surface *surface, int x, int y);
    void tick(unsigned int dt);

    void play();
    void pause();
    void restart();
    
    void nextFrame();
    void setCurrentFrame(int frame);

    void setFps(int fps);
private:
    SDL_Surface *spriteSheet;
    SDL_Rect frameRect, drawRect;

    int numFrames;
    int currentFrame;
    double framesToSkip = 0.0;
    int fps = 10;
    bool isPlaying = false;
};
}

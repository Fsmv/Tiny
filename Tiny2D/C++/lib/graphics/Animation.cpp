#include <math.h>
#include "SDL_image.h"
#include "graphics/Animation.h"

using namespace Tiny2D;

Animation::Animation(const char *imagePath, int numFrames, int width, int height) {
    this->spriteSheet = IMG_Load(imagePath);
    this->numFrames = numFrames;
    
    if(width > 0)
        this->frameRect.w = this->drawRect.w = width;
    else
        this->frameRect.w = this->drawRect.w = this->spriteSheet->w;

    if(height > 0)
        this->frameRect.h = this->drawRect.h = height;
    else
        this->frameRect.h = this->drawRect.h = this->spriteSheet->h;

    this->frameRect.x = this->frameRect.y = 0;
}

Animation::~Animation() {
    SDL_FreeSurface(this->spriteSheet);
}

void Animation::draw(SDL_Surface *surface) {
    draw(surface, 0, 0);
}

void Animation::draw(SDL_Surface *surface, int x, int y) {
    drawRect.x = x;
    drawRect.y = y;

    SDL_BlitSurface(this->spriteSheet, &frameRect, surface, &drawRect);
}

void Animation::tick(unsigned int dt) {
    if(this->isPlaying) {
        this->framesToSkip += dt / (1000.0/fps);

        if(this->framesToSkip > 1) {
            setCurrentFrame(this->currentFrame + floor(this->framesToSkip));
            this->framesToSkip -= floor(this->framesToSkip);
        }
    }
}

void Animation::play() {
    this->isPlaying = true;
}

void Animation::pause() {
    this->isPlaying = false;
}

void Animation::restart() {
    currentFrame = 0;
}

void Animation::nextFrame() {
    this->setCurrentFrame(this->currentFrame + 1);
}

void Animation::setCurrentFrame(int frame) {
    this->currentFrame = frame % this->numFrames;
    frameRect.x =  (currentFrame * frameRect.w) % spriteSheet->w;
    frameRect.y = ((currentFrame * frameRect.w) / spriteSheet->w) * frameRect.h;
}

void Animation::setFps(int fps) {
    if(fps > 0)
        this->fps = fps;
}

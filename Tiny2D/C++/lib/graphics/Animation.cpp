#include <math.h>
#include "SDL_image.h"
#include "graphics/Animation.h"
#include "utils/Logger.h"

using namespace Tiny2D;

Animation::Animation(SDL_Renderer *renderer, const char *imagePath,
        int numFrames, int width, int height) {
    load(renderer, imagePath, numFrames, width, height);
}

void Animation::load(SDL_Renderer *renderer, const char *imagePath,
        int numFrames, int width, int height) {
    Sprite::load(renderer, imagePath);

    this->numFrames = numFrames;

    int w, h;
    SDL_QueryTexture(this->image, nullptr, nullptr, &w, &h);

    if(width > 0)
        this->frameRect.w = this->drawRect.w = width;
    else
        this->frameRect.w = this->drawRect.w = w;

    if(height > 0)
        this->frameRect.h = this->drawRect.h = height;
    else
        this->frameRect.h = this->drawRect.h = h;

    this->frameRect.x = this->frameRect.y = 0;
}

void Animation::draw(SDL_Renderer *renderer) {
    this->draw(renderer, 0, 0);
}

void Animation::draw(SDL_Renderer *renderer, int x, int y) {
    drawRect.x = x;
    drawRect.y = y;
    SDL_RenderCopy(renderer, this->image, &frameRect, &drawRect);
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
    int w;
    SDL_QueryTexture(this->image, nullptr, nullptr, &w, nullptr);
    frameRect.x =  (currentFrame * frameRect.w) % w;
    frameRect.y = ((currentFrame * frameRect.w) / w) * frameRect.h;
}

void Animation::setFps(int fps) {
    if(fps > 0)
        this->fps = fps;
}

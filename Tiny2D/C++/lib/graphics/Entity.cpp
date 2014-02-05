#include "graphics/Entity.h"

using namespace Tiny2D;

Entity::Entity(SDL_Renderer *renderer, const char *filename) {
    load(renderer, filename);
}

Entity::Entity(SDL_Renderer *renderer, const char *filename, int numFrames[],
        size_t numAnimations, int width, int height) {
    load(renderer, filename, numFrames, numAnimations, width, height);
}

void Entity::load(SDL_Renderer *renderer, const char *filename, int numFrames[],
        size_t numAnimations, int width, int height) {
    this->load(renderer, filename, 0, width, height);

    this->numFramesArr = numFrames;
    this->numAnimations = numAnimations;

    for(int i = 0; i < numAnimations; i++) {
        this->numFrames += numFramesArr[i];
    }
}


void Entity::draw(SDL_Renderer *renderer) {
    Animation::draw(renderer, this->x, this->y);
}

void Entity::tick(unsigned int dt) {
    this->x += this->dx * dt/1000.0;
    this->y += this->dy * dt/1000.0;

    Animation::tick(dt);

    this->setCurrentFrame(((currentFrame - currentStartFrame) % numFramesArr[currentAnimation]) + currentStartFrame);
}

void Entity::restart() {
    play();
    this->currentFrame = this->currentStartFrame;
}

void Entity::setCurrentAnimation(int animation) {
    this->currentAnimation = animation % numAnimations;

    this->currentStartFrame = 0;
    for(int i = 0; i < currentAnimation; i++) {
        this->currentStartFrame += numFramesArr[i];
    }

    Animation::setCurrentFrame(this->currentStartFrame);
}

void Entity::setCurrentFrame(int frame) {
    Animation::setCurrentFrame(currentStartFrame + (frame % numFramesArr[currentAnimation]));
}

void Entity::nextFrame() {
    this->setCurrentFrame(this->currentFrame - this->currentStartFrame + 1);
}

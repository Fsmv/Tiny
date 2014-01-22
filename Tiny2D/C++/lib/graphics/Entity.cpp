#include "graphics/Entity.h"

using namespace Tiny2D;

Entity::Entity(const char *filename, int numFrames[], size_t numAnimations, int width, int height) :
    Animation(filename, 0, width, height), numFramesArr(numFrames), numAnimations(numAnimations) {
    
    //I can't do this sum in the initializer list
    for(int i = 0; i < numAnimations; i++) {
        this->numFrames += numFramesArr[i];
    }
}

void Entity::draw(SDL_Surface *surface) {
    Animation::draw(surface, this->x, this->y);
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

#pragma once

#include "SDL_image.h"
#include "graphics/Drawable.h"
#include "graphics/Animation.h"

#include <cstdio>

namespace Tiny2D {
class Entity : private Tiny2D::Animation, virtual public Tiny2D::Drawable {
public:
    /**
     * Creates an entity with no animation
     *
     * @param filename the path to the entity image
     */
    Entity(const char *filename) : Tiny2D::Animation(filename) {}
    /**
     * Creates an entity from a sprite sheet with multiple animations
     * 
     * @param filename the path to the sprite sheet
     * @param numFrames an array of the numbers of frames for each animation
     * @param numAnimations the number of animations in the sprite sheet (should be the length of the numFrames array)
     * @param width the width of one frame (all frames must have the same size)
     * @param height the height of one frame (all frames must have the same size)
     */
    Entity(const char *filename, int numFrames[], size_t numAnimations, int width, int heigth);
    virtual ~Entity() {};

    void draw(SDL_Surface *surface);
    void tick(unsigned int dt);

    using Tiny2D::Animation::play;
    using Tiny2D::Animation::pause;
    void restart();
    
    void setCurrentAnimation(int animation);
    void setCurrentFrame(int frame);
    void nextFrame();

    using Tiny2D::Animation::setFps;
private:
    double x = 0.0, y = 0.0;
    double dx = 0.0, dy = 0.0;
    int currentAnimation = 0;

    int *numFramesArr;
    size_t numAnimations;
    int currentStartFrame = 0;
};
}

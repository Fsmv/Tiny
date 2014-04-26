#pragma once

#include "SDL_image.h"
#include "graphics/Drawable.h"
#include "graphics/Animation.h"

#include <cstdio>

namespace Tiny2D {
class Entity : private Tiny2D::Animation, virtual public Tiny2D::Drawable {
public:
    Entity() {};
    /**
     * Creates an entity with no animation
     *
     * @param filename the path to the entity image
     */
    Entity(SDL_Renderer *renderer, const char *filename);
    /**
     * Creates an entity from a sprite sheet with multiple animations
     * 
     * @param filename the path to the sprite sheet
     * @param numFrames an array of the numbers of frames for each animation
     * @param numAnimations the number of animations in the sprite sheet (should be the length of the numFrames array)
     * @param width the width of one frame (all frames must have the same size)
     * @param height the height of one frame (all frames must have the same size)
     */
    Entity(SDL_Renderer *renderer, const char *filename, int numFrames[],
            size_t numAnimations, int width, int heigth);
    virtual ~Entity() {};

    using Tiny2D::Animation::load;
    void load(SDL_Renderer *renderer, const char *filename, int numFrames[],
            size_t numAnimations, int width, int height);
    void draw(SDL_Renderer *renderer);
    void tick(unsigned int dt);

    using Tiny2D::Animation::play;
    using Tiny2D::Animation::pause;
    void restart();

    void setCurrentAnimation(int animation);
    void setCurrentFrame(int frame);
    void nextFrame();

    inline void setPos(double x, double y) { this->x = x; this->y = y; }
    inline void setVel(double dx, double dy) { this->dx = dx; this->dy = dy; }

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

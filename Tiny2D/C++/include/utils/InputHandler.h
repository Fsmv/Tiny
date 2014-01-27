#pragma once
#include <map>
#include <utility>
#include "SDL.h"

namespace Tiny2D {
class InputHandler {
public:
    InputHandler();
    ~InputHandler();

    /**
     * Updates the maps, call each frame
     */
    void processEventQueue();

    /**
     * Register keyboard event actions
     */
    void registerAction(const char *name, SDL_Keycode keycode);
    /**
     * Register mouse event actions, use SDL_BUTTION_{LEFT, MIDDLE, RIGHT}
     */
    void registerAction(const char *name, unsigned char button);

    bool isPressed(const char *name);

    void setMouseMoveable(bool letMouseMove);
    void setMouseVisible(bool showMouse);

    void setOnQuitCallback(void (*quit)(void *), void *arg);
    const char *getMouseButtonName(unsigned char button);
private:
    void setState(SDL_Keycode &keycode, bool val);
    void setState(unsigned char button, bool val);

    inline void onMouseMotion(SDL_MouseMotionEvent *event);

    typedef std::pair<const char*, bool> ActionState;
    typedef std::map<const char*, ActionState> ActionList;

    ActionList actions;

    void (*quit)(void *);
    void *quitArg;

    struct {
        int x, y;
        int dx, dy;
    } mouse;

    const char *MOUSE_ONE_NAME = "Mouse 1";
    const char *MOUSE_TWO_NAME = "Mouse 2";
    const char *MOUSE_THREE_NAME = "Mouse 3";
    const char *MOUSE_FOUR_NAME = "Mouse 4";
    const char *MOUSE_FIVE_NAME = "Mouse 5";
};
}

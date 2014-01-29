#pragma once
#include <map>
#include <utility>
#include <string>
#include "SDL.h"

//Work around for the SDLK enum being anonymous
typedef decltype(SDLK_0) keyCode;
//These are #defined as integer literals
typedef int mouseButton;

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
     * Register keyboard event actions, SDLK_* constants
     */
    void registerAction(const char *name, const keyCode keycode);
    /**
     * Register mouse event actions, use SDL_BUTTION_{LEFT, MIDDLE, RIGHT}
     */
    void registerAction(const char *name, const mouseButton button);

    bool isPressed(const char *name);

    void setRelativeMouseMode(bool enable);
    void setMouseVisible(bool showMouse);

    void setOnQuitCallback(void (*quit)(void *), void *arg);
    const char *getMouseButtonName(const mouseButton button);

    struct {
        int x = 0;
        int y = 0;
        int dx = 0;
        int dy = 0;
    } mouse;
private:
    void setState(const keyCode keycode, bool val);
    void setState(const mouseButton button, bool val);

    inline void onMouseMotion(SDL_MouseMotionEvent *event);

    typedef std::pair<std::string, bool> ActionState;
    typedef std::map<std::string, ActionState> ActionList;

    ActionList actions;

    void (*quit)(void *);
    void *quitArg;

    const char *MOUSE_ONE_NAME = "Mouse 1";
    const char *MOUSE_TWO_NAME = "Mouse 2";
    const char *MOUSE_THREE_NAME = "Mouse 3";
    const char *MOUSE_FOUR_NAME = "Mouse 4";
    const char *MOUSE_FIVE_NAME = "Mouse 5";
};
}

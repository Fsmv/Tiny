#pragma once
#include <map>
#include <utility>
#include <string>
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

    void registerAction(const char *name, const SDL_Keycode key) {
        registerAction(name, SDL_GetKeyName(key));
    }
    void registerAction(const char *name, const char *keyname);

    bool isPressed(const char *name);

    void setRelativeMouseMode(bool enable);
    void setMouseVisible(bool showMouse);

    void setOnQuitCallback(void (*quit)(void *), void *arg);
    static const char *getMouseButtonName(int button);

    struct {
        int x = 0;
        int y = 0;
        int dx = 0;
        int dy = 0;
    } mouse;

    static const char *MOUSE_ONE;
    static const char *MOUSE_TWO;
    static const char *MOUSE_THREE;
    static const char *MOUSE_FOUR;
    static const char *MOUSE_FIVE;
private:
    void setState(const char *name, bool val);

    inline void onMouseMotion(SDL_MouseMotionEvent *event);

    typedef std::pair<std::string, bool> ActionState;
    typedef std::multimap<std::string, ActionState> ActionList;

    ActionList actions;

    void (*quit)(void *);
    void *quitArg;
};
}

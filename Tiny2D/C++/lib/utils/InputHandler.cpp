#include <cstring>
#include "utils/InputHandler.h"

using namespace Tiny2D;

const char *InputHandler::MOUSE_ONE = "Mouse 1";
const char *InputHandler::MOUSE_TWO = "Mouse 2";
const char *InputHandler::MOUSE_THREE = "Mouse 3";
const char *InputHandler::MOUSE_FOUR = "Mouse 4";
const char *InputHandler::MOUSE_FIVE = "Mouse 5";

InputHandler::InputHandler() {
}

InputHandler::~InputHandler() {
}

void InputHandler::processEventQueue() {
    mouse.x = mouse.y = mouse.dx = mouse.dy = 0;

    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
        case SDL_QUIT:
            this->quit(this->quitArg);
            break;
        case SDL_KEYDOWN:
            setState(SDL_GetKeyName(event.key.keysym.sym), true);
            break;
        case SDL_KEYUP:
            setState(SDL_GetKeyName(event.key.keysym.sym), false);
            break;
        case SDL_MOUSEBUTTONDOWN:
            setState(getMouseButtonName(event.button.button), true);
            break;
        case SDL_MOUSEBUTTONUP:
            setState(getMouseButtonName(event.button.button), false);
            break;
        case SDL_MOUSEMOTION:
            onMouseMotion(&event.motion);
            break;
        default:
            break;
        }
    }
}

void InputHandler::registerAction(const char *name, const char *keyname) {
    ActionState action;
    action.first = keyname;
    action.second = false;
    actions.insert(std::pair<std::string, ActionState>(name, action));
}

bool InputHandler::isPressed(const char *name) {
    bool result = false;
    for(ActionList::iterator pressed = actions.lower_bound(name);
            pressed != actions.upper_bound(name); pressed++) {
        result |= pressed->second.second;
    }

    return result;
}

void InputHandler::setRelativeMouseMode(bool enable) {
    //I could do something with SDL_WarpMouseInWindow to act like it does is the
    //java version, but I can't think of any reason to keep the mouse visible
    SDL_SetRelativeMouseMode(enable ? SDL_TRUE : SDL_FALSE);
}

void InputHandler::setMouseVisible(bool showMouse) {
    SDL_ShowCursor(showMouse);
}

void InputHandler::setOnQuitCallback(void (*quit)(void *), void *arg) {
    this->quit = quit;
    this->quitArg = arg;
}

void InputHandler::setState(const char *name, bool val) {
    for(ActionList::iterator it = actions.begin(); it != actions.end(); ++it) {
        if(it->second.first.compare(name) == 0) {
            it->second.second = val;
        }
    }
}

const char *InputHandler::getMouseButtonName(const int button) {
    switch(button) {
    case SDL_BUTTON_LEFT:
        return MOUSE_ONE;
    case SDL_BUTTON_RIGHT:
        return MOUSE_TWO;
    case SDL_BUTTON_MIDDLE:
        return MOUSE_THREE;
    case SDL_BUTTON_X1:
        return MOUSE_FOUR;
    case SDL_BUTTON_X2:
        return MOUSE_FIVE;
    default:
        return "not named";
    }
}

void InputHandler::onMouseMotion(SDL_MouseMotionEvent *event) {
    this->mouse.x = event->x;
    this->mouse.y = event->y;

    this->mouse.dx = event->xrel;
    this->mouse.dy = event->yrel;
}

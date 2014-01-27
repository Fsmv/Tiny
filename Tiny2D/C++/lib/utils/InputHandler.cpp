#include "utils/InputHandler.h"

using namespace Tiny2D;

InputHandler::InputHandler() {
}

InputHandler::~InputHandler() {
}

void InputHandler::processEventQueue() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
        case SDL_QUIT:
            this->quit(this->quitArg);
            break;
        case SDL_KEYDOWN:
            setState(event.key.keysym.sym, true);
            break;
        case SDL_KEYUP:
            setState(event.key.keysym.sym, false);
            break;
        case SDL_MOUSEBUTTONDOWN:
            setState(event.button.button, true);
            break;
        case SDL_MOUSEBUTTONUP:
            setState(event.button.button, false);
            break;
        case SDL_MOUSEMOTION:
            onMouseMotion(&event.motion);
            break;
        default:
            break;
        }
    }
}

void InputHandler::registerAction(const char *name, SDL_Keycode keycode) {
    ActionState action = actions[name];
    action.first = SDL_GetKeyName(keycode);
    action.second = false;
}

void InputHandler::registerAction(const char *name, unsigned char button) {
    ActionState action = actions[name];
    action.first = getMouseButtonName(button);
    action.second = false;
}

bool InputHandler::isPressed(const char *name) {
    ActionList::iterator pressed = actions.find(name);
    if(pressed != actions.end()) {
        return pressed->second.second;
    }
}

void InputHandler::setMouseMoveable(bool letMouseMove) {
}

void InputHandler::setMouseVisible(bool showMouse) {
}

void InputHandler::setOnQuitCallback(void (*quit)(void *), void *arg) {
    this->quit = quit;
    this->quitArg = arg;
}

void InputHandler::setState(SDL_Keycode &keycode, bool val) {
    for(ActionList::iterator it = actions.begin();
            it != actions.end(); ++it) {
        if(it->second.first == SDL_GetKeyName(keycode)) {
            it->second.second = val;
        }
    }
}

void InputHandler::setState(unsigned char button, bool val) {
    for(ActionList::iterator it = actions.begin();
            it != actions.end(); ++it) {
        if(it->second.first == getMouseButtonName(button)) {
            it->second.second = val;
        }
    }
}

const char *InputHandler::getMouseButtonName(unsigned char button) {
    switch(button) {
    case SDL_BUTTON_LEFT:
        return MOUSE_ONE_NAME;
    case SDL_BUTTON_RIGHT:
        return MOUSE_TWO_NAME;
    case SDL_BUTTON_MIDDLE:
        return MOUSE_THREE_NAME;
    case SDL_BUTTON_X1:
        return MOUSE_FOUR_NAME;
    case SDL_BUTTON_X2:
        return MOUSE_FIVE_NAME;
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

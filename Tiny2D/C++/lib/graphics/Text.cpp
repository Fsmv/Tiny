#include "graphics/Text.h"
#include "utils/Logger.h"

using namespace Tiny2D;

Text::Text(SDL_Renderer *renderer, std::string str, TTF_Font *font) :
        renderer(renderer), text(str), font(font), color({0,0,0}) {}

Text::Text(SDL_Renderer *renderer, std::string str, std::string font, int size) :
    renderer(renderer), text(str), font(Text::loadFont(font, size)),
    color({0,0,0}){}

Text::~Text() {
    if(this->image != nullptr) {
        SDL_DestroyTexture(this->image);
    }

    if(this->font != nullptr) {
        TTF_CloseFont(font);
    }
}

void Text::load(SDL_Renderer *renderer, std::string str, std::string font, int size) {
    this->renderer = renderer;
    this->text = str;
    this->font = Text::loadFont(font, size);
    color = {0,0,0};
    render();
}

void Text::draw(SDL_Renderer *renderer) {
    draw(renderer, 0, 0);
}

void Text::draw(SDL_Renderer *renderer, int x, int y) {
    this->drawRect.x = x;
    this->drawRect.y = y;
    SDL_RenderCopy(renderer, this->image, nullptr, &this->drawRect);
}

int Text::getWidth() {
    return drawRect.w;
}

int Text::getHeight() {
    return drawRect.h;
}

TTF_Font *Text::loadFont(std::string filename, int size) {
    if(!TTF_WasInit()) {
        if(TTF_Init() == -1) {
            Logger logger("Text");
            logger.error("Could not initialize TTF system");
        }
    }

    TTF_Font *font = TTF_OpenFont(filename.c_str(), size);
    if(font == nullptr) {
        Logger logger("Text");
        logger.error("Could not load font");
    }

    return font;
}

void Text::render() {
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    if(textSurface == nullptr) {
        Logger logger("Text");
        logger.error("Could not render text");
    }else{
        image = SDL_CreateTextureFromSurface(renderer, textSurface);
        if(image == nullptr) {
            Logger logger("Text");
            logger.error("Could not render text");
        }else{
            drawRect.w = textSurface->w;
            drawRect.h = textSurface->h;
        }

        SDL_FreeSurface(textSurface);
    }
}

void Text::setText(std::string text) {
    this->text = text;
    render();
}

void Text::setColor(const SDL_Color &color) {
    this->color = color;
    render();
}

void Text::setFont(TTF_Font *font) {
    this->font = font;
    render();
}

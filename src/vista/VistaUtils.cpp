#include <SDL2/SDL_image.h>
#include "VistaUtils.h"

float VistaUtils::SCALE_X = 1;
float VistaUtils::SCALE_Y = 1;

Uint32 VistaUtils::getColorKeyValue(VistaUtils::COLORKEY color, SDL_Surface* s) {
    switch (color){
        case VistaUtils::BLANCO: return SDL_MapRGB(s->format, 255, 255, 255);
        case VistaUtils::NEGRO: return SDL_MapRGB(s->format, 0, 0, 0);
        default: return 0;
    }
}

SDL_Texture *VistaUtils::createTexture(SDL_Renderer* renderer, float width, float height) {
    int scaledWidth = (int) (width * SCALE_X);
    int scaledHeight = (int) (height * SCALE_Y);
    return SDL_CreateTexture(renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, scaledWidth, scaledHeight);
}

SDL_Texture* VistaUtils::loadTexture(SDL_Renderer *r, std::string path, VistaUtils::COLORKEY colorkey) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == NULL){
        return nullptr;
    }else {
        SDL_SetColorKey(surface, SDL_TRUE, getColorKeyValue(colorkey, surface) );
        SDL_Texture* t = SDL_CreateTextureFromSurface(r, surface);
        SDL_FreeSurface(surface);
        return t;
    }
}

void VistaUtils::copyTexture(SDL_Renderer* r, SDL_Texture *src, SDL_Texture *dst) {
    VistaUtils::copyTexture(r, src, dst, NULL, NULL);
}

void VistaUtils::copyTexture(SDL_Renderer* r, SDL_Texture *src, SDL_Texture *dst, bool flip) {
    VistaUtils::copyTexture(r, src, dst, NULL, NULL, flip);
}

void VistaUtils::copyTexture(SDL_Renderer* r, SDL_Texture *src, SDL_Texture *dst, Trect* rectSrc, Trect* rectDst) {
    copyTexture(r, src, dst, rectSrc, rectDst, false);
}

void VistaUtils::copyTexture(SDL_Renderer *r, SDL_Texture *src, SDL_Texture *dst, Trect* rectSrc, Trect* rectDst, bool flip) {
    SDL_Texture *originalTarget = SDL_GetRenderTarget(r);

    SDL_SetRenderTarget(r, dst);

    // Importante para que se generen las transparencias si se usa colorkey.
    SDL_SetTextureBlendMode(dst, SDL_BLENDMODE_BLEND);

    SDL_Rect* scaledRectSrc = new SDL_Rect();
    SDL_Rect* scaledRectDst = new SDL_Rect();

    if (rectSrc == NULL)
        scaledRectSrc = NULL;
    else {
        scaledRectSrc->x = (int) (rectSrc->p.x * SCALE_X);
        scaledRectSrc->y = (int) (rectSrc->p.y * SCALE_Y);
        scaledRectSrc->w = (int) (rectSrc->w * SCALE_X);
        scaledRectSrc->h = (int) (rectSrc->h * SCALE_Y);
    }
    if (rectDst == NULL)
        scaledRectDst = NULL;
    else{
        scaledRectDst->x = (int) (rectDst->p.x * SCALE_X);
        scaledRectDst->y = (int) (rectDst->p.y * SCALE_Y);
        scaledRectDst->w = (int) (rectDst->w * SCALE_X);
        scaledRectDst->h = (int) (rectDst->h * SCALE_Y);
    }

    if (flip)
        SDL_RenderCopyEx(r, src, scaledRectSrc, scaledRectDst, 0, NULL, SDL_FLIP_HORIZONTAL);
    else
        SDL_RenderCopyEx(r, src, scaledRectSrc, scaledRectDst, 0, NULL, SDL_FLIP_NONE);

    SDL_SetRenderTarget(r, originalTarget);

    delete(scaledRectSrc);
    delete(scaledRectDst);
}

void VistaUtils::cleanTexture(SDL_Renderer* r, SDL_Texture* t){
    SDL_Texture *originalTarget = SDL_GetRenderTarget(r);
    SDL_SetRenderTarget(r, t);

    SDL_SetRenderDrawColor(r, 0, 0, 0, 0);
    SDL_RenderClear(r);

    SDL_SetRenderTarget(r, originalTarget);
}

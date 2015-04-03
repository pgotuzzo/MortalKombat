#include <SDL2/SDL_image.h>
#include "VistaUtils.h"

void VistaUtils::cleanTexture(SDL_Renderer* r){
    SDL_SetRenderDrawColor(r, 0, 0, 0, 0);
    SDL_RenderClear(r);
}

void VistaUtils::copyTexture(SDL_Renderer* r, SDL_Texture *src, SDL_Texture *dst) {
    VistaUtils::copyTexture(r, src, dst, NULL, NULL);
}

Uint32 VistaUtils::getColorKeyValue(VistaUtils::COLORKEY color, SDL_Surface* s) {
    switch (color){
        case VistaUtils::BLANCO: return SDL_MapRGB(s->format, 255, 255, 255);
        case VistaUtils::NEGRO: return SDL_MapRGB(s->format, 0, 0, 0);
        default: return 0;
    }
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

void VistaUtils::copyTexture(SDL_Renderer* r, SDL_Texture *src, SDL_Texture *dst, SDL_Rect* rectSrc, SDL_Rect* rectDst) {
    SDL_Texture *originalTarget = SDL_GetRenderTarget(r);

    SDL_SetRenderTarget(r, dst);

    VistaUtils::cleanTexture(r);

    // Importante para que se generen las transparencias si se usa colorkey.
    SDL_SetTextureBlendMode(dst, SDL_BLENDMODE_BLEND);

    SDL_RenderCopy(r, src, rectSrc, rectDst);

    SDL_SetRenderTarget(r, originalTarget);
}

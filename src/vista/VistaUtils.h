#ifndef MORTALKOMBAT_VISTAUTILS_H
#define MORTALKOMBAT_VISTAUTILS_H

#include <SDL2/SDL_render.h>
#include <string>
#include "../Common.h"

class VistaUtils {

public:

    struct Trect {
        float w;
        float h;
        Posicion p;
    };

    enum COLORKEY{
        BLANCO,
        NEGRO
    };

    static float SCALE_X;
    static float SCALE_Y;

    static SDL_Texture* createTexture(SDL_Renderer* renderer, float width, float height);

    static SDL_Texture* loadTexture(SDL_Renderer* r, std::string path, COLORKEY);

    static SDL_Texture* createTexture(SDL_Renderer *renderer, float width, float height, string path);

    static void copyTexture(SDL_Renderer* r, SDL_Texture* src, SDL_Texture* dst);

    static void copyTexture(SDL_Renderer* r, SDL_Texture* src, SDL_Texture* dst, bool flip);

    static void copyTexture(SDL_Renderer* r, SDL_Texture *src, SDL_Texture *dst, Trect* rectSrc, Trect* rectDst);

    static void copyTexture(SDL_Renderer* r, SDL_Texture *src, SDL_Texture *dst, Trect* rectSrc, Trect* rectDst, bool flip);

    static void copyTextureNoScale(SDL_Renderer* r, SDL_Texture *src, SDL_Texture *dst, Trect* rectSrc, Trect* rectDst);

    /**
     * Limpia la textura
     */
    static void cleanTexture(SDL_Renderer* r, SDL_Texture* t);

private:

    static Uint32 getColorKeyValue(COLORKEY color, SDL_Surface* s);

};


#endif //MORTALKOMBAT_VISTAUTILS_H

#ifndef MORTALKOMBAT_VISTAUTILS_H
#define MORTALKOMBAT_VISTAUTILS_H


#include <SDL2/SDL_render.h>
#include <string>

class VistaUtils {

public:

    enum COLORKEY{
        BLANCO,
        NEGRO
    };

    static SDL_Texture* loadTexture(SDL_Renderer* r, std::string path, COLORKEY);

    static void copyTexture(SDL_Renderer* r, SDL_Texture* src, SDL_Texture* dst);

    static void copyTexture(SDL_Renderer* r, SDL_Texture *src, SDL_Texture *dst, SDL_Rect* rectSrc, SDL_Rect* rectDst);

private:

    static Uint32 getColorKeyValue(COLORKEY color, SDL_Surface* s);

    /**
     * Limpia la textura
     */
    static void cleanTexture(SDL_Renderer* r);
};


#endif //MORTALKOMBAT_VISTAUTILS_H

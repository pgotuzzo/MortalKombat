#include <SDL2/SDL_image.h>
#include <cmath>
#include "VistaUtils.h"

/**
 * Si ratio es menor o igual que cero, la relacion de aspecto será 1.
 *
 * ratio    relacion de aspecto ratio = (ancho / alto)
 * scales   relacion entre pixel y la unidad logica
 */
VistaUtils::VistaUtils(SDL_Renderer* renderer, float ratio, float scales[2]) {
    mRenderer = renderer;
    mRatio = (ratio > 0) ? ratio : 1;
    mScales[0] = scales[0];
    mScales[1] = scales[1];
    mColorChangeEnable = false;
}

/**
 * Habilita el cambio de color al cargar una textura con loadTexture()
 */
void VistaUtils::enableColorChange(bool enable) {
    mColorChangeEnable = enable;
}

/**
 * Define los parametros para el cambio de color cuando este es requerido
 */
void VistaUtils::setColorSetting(TcolorSettings settings) {
    mColorSettings = settings;
}

/**
 * Calcula la escala a utilizar teniendo en cuenta las dimensiones (unidades logicas)
 *  y el tamaño actual de la textura.
 *
 * texture      Si "texture" posee una SDL_Texture* == nullptr entonces toma los valores de escala
 *                  seteados por defecto y que corresponden a la relacion px/ul de la pantalla.
 *                  Esto se inicializa en el constructor "mScales"
 *              En otro caso, se toma el valor de "dimension" dentro de "texture" y calcula la relacion
 *                  de escala entre px/ul
 */
void VistaUtils::getScales(Ttexture texture, float scales[2]){
    if (texture.t == nullptr){
        scales[0] = mScales[0];
        scales[1] = mScales[1];
    } else {
        int w, h;

        SDL_QueryTexture(texture.t, NULL, NULL, &w, &h);
        scales[0] = w / texture.d.w;
        scales[1] = h / texture.d.h;
    }
}

/**
 * Acceso a un pixel por medio de un iterador i
 */
Uint32 VistaUtils::getPixel(SDL_Surface *surface, int i){
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *) surface->pixels + i * bpp;

    switch(bpp) {
        case 1: return *p;
        case 2: return *(Uint16 *)p;
        case 3: {
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
        }
        case 4: return *(Uint32 *)p;
        default: return 0;
    }
}

/**
 * Edicion de un pixel por medio de un iterador.
 */
void VistaUtils::putPixel(SDL_Surface *surface, int i, Uint32 pixel) {
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + i * bpp;

    switch(bpp) {
        case 1:
            *p = (Uint8) pixel;
            break;
        case 2:
            *(Uint16 *)p = (Uint16) pixel;
            break;
        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p[0] = (Uint8) ((pixel >> 16) & 0xff);
                p[1] = (Uint8) ((pixel >> 8) & 0xff);
                p[2] = (Uint8) (pixel & 0xff);
            } else {
                p[0] = (Uint8) (pixel & 0xff);
                p[1] = (Uint8) ((pixel >> 8) & 0xff);
                p[2] = (Uint8) ((pixel >> 16) & 0xff);
            }
            break;
        case 4: {
            *(Uint32 *) p = pixel;
            break;
        }
        default:
            throw new exception;
    }
}

/**
 * Cambia el color pixel por pixel teniendo en cuenta
 *  los valores seteados en el mColorSettings
 */
void VistaUtils::changeColor(SDL_Surface* surface) {
    // Checkeo para hacer lock si es necesario
    if( SDL_MUSTLOCK(surface) ) {
        SDL_LockSurface( surface );
    }

    // cantidad de pixeles
    int pixelNum = surface->w * surface->h;

    // pixel transparente
    Uint32 transparentPixel;
    SDL_GetColorKey(surface, &transparentPixel);

    for(int i = 0; i < pixelNum; i++){
        Uint32 pixel = getPixel(surface, i);

        if (pixel != transparentPixel) {

            // obtengo el RGB del pixel y lo transformo en HSL
            Uint8 r, g, b;
            SDL_GetRGB(pixel, surface->format, &r, &g, &b);

            TcolorHSL hsl = TcolorHSL::fromRGB(r, g, b);


            // Si se encuentra dentro del rango a modificar
            if ((hsl.h >= mColorSettings.hmin) &&
                (hsl.h <= mColorSettings.hmax)) {

                // modifico el hue
                hsl.h = fmod(hsl.h + mColorSettings.delta, 360);

                // creo un pixel con el nuevo color y reemplazo el existente
                TcolorRGB rgb = TcolorRGB::fromHSL(hsl.h, hsl.s, hsl.l);
                pixel = SDL_MapRGB(surface->format, rgb.r, rgb.g, rgb.b);
                putPixel(surface, i, pixel);
            }
        }
    }

    // Checkeo para hacer unlock si es necesario
    if( SDL_MUSTLOCK(surface) ) {
        SDL_UnlockSurface( surface );
    }
}

/**
 * Crea una textura manteniendo la relacion de aspecto
 *  Por lo tanto se crea una textura con dimension
 *  ancho = width * ratio
 *  alto = height / ratio
 *
 *  ancho   pixeles
 *  alto    pixeles
 */
SDL_Texture* VistaUtils::createTexture(Tdimension dimension) {
    int w = (int) (dimension.w * mRatio);
    int h = (int) (dimension.h * mRatio);

    SDL_Texture* t = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, w, h);
    if (t != 0) {
        string message = "Crea textura de dimensiones " + to_string(w) + " x " + to_string(h);
        loguer->loguear(message.c_str(), Log::LOG_DEB);
        return t;
    }
    loguer->loguear("ERROR - No se pudo crear la textura", Log::LOG_ERR);
    return nullptr;
}

/**
 * Crea una textura utilizando un string.
 *
 * fontPath     ruta a la font a utilizar
 * text         texto a imprimir
 * size         tamanio del texto
 */
Ttexture VistaUtils::createTextureFromText(string fontPath, string text, int size) {
    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), size);
    if (font == NULL) {
        loguer->loguear("No se pudo cargar la fuente.", Log::LOG_ERR);
        loguer->loguear(TTF_GetError(), Log::LOG_ERR);
        throw new exception();
    }

    SDL_Color white = {255, 255, 255, 0};

    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), white);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
    SDL_FreeSurface(surface);

    Ttexture returnTexture;
    returnTexture.t = textTexture;
    returnTexture.d = getDimension(textTexture);

    return returnTexture;
}

/**
 * Pone en la textura un string.
 * (Caco way)
 *
 * fontPath     ruta a la font a utilizar
 * text         texto a imprimir
 * size         tamanio del texto
 * texture      textura a cambiar
 */
Ttexture VistaUtils::copyInTextureFromText(string fontPath, string text, int size,Ttexture texture) {
    SDL_DestroyTexture(texture.t);
    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), size);
    if (font == NULL) {
        loguer->loguear("No se pudo cargar la fuente.", Log::LOG_ERR);
        loguer->loguear(TTF_GetError(), Log::LOG_ERR);
        throw new exception();
    }

    SDL_Color white = {255, 255, 255, 0};
    // No encontre una funcion q copie una textura de una surface, pro eso lo hice a lo caco
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), white);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
    SDL_FreeSurface(surface);

    texture.t = textTexture;
    texture.d = getDimension(texture.t);

    return texture;
}

/**
 * Se crea una textura a partir de un path, respetando la relacion de aspecto.
 * Cambiando el color si el flag "mColorChangeEnable" esta en "true"
 */
Ttexture VistaUtils::loadTexture(std::string path) {
    Ttexture returnTexture;

    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == NULL){
        returnTexture.t = nullptr;
    } else {
        string message = "Carga textura desde " + path;
        loguer->loguear(message.c_str(), Log::LOG_DEB);

        if (mColorChangeEnable) {
            SDL_Surface *aux = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGB888, 0);
            if (aux == NULL){
                loguer->loguear("No se pudo convertir la Surface al formato RGB", Log::LOG_ERR);
                loguer->loguear(SDL_GetError(), Log::LOG_ERR);
                throw new exception();
            }else{
                SDL_FreeSurface(surface);
                surface = aux;
                changeColor(surface);
            }
        }

        SDL_Texture* aux = SDL_CreateTextureFromSurface(mRenderer, surface);
        mAuxTextures.push_back(aux);

        SDL_FreeSurface(surface);

        int w, h;
        SDL_QueryTexture(aux, NULL, NULL, &w, &h);
        SDL_Texture* t = createTexture({w, h});
        copyTexture(aux, t);

        returnTexture.t = t;
        returnTexture.d = getDimension(t);
    }
    return returnTexture;
}

void VistaUtils::copyTexture(SDL_Texture *src, SDL_Texture *dst) {
    copyTexture(src, dst, false);
}

/**
 * Se copia el contenido de un textura en otra.
 */
void VistaUtils::copyTexture(SDL_Texture *src, SDL_Texture *dst, bool flip) {
    // guardo el target original
    SDL_Texture *originalTarget = SDL_GetRenderTarget(mRenderer);

    // cambio el target para que apunte a la textura dst
    SDL_SetRenderTarget(mRenderer, dst);

    // Importante para que se generen las transparencias si se usa colorkey.
    SDL_SetTextureBlendMode(dst, SDL_BLENDMODE_BLEND);

    if (flip)
        SDL_RenderCopyEx(mRenderer, src, NULL, NULL, 0, NULL, SDL_FLIP_HORIZONTAL);
    else
        SDL_RenderCopyEx(mRenderer, src, NULL, NULL, 0, NULL, SDL_FLIP_NONE);

    // recupero el target original
    SDL_SetRenderTarget(mRenderer, originalTarget);
}

void VistaUtils::copyTexture(Ttexture src, Ttexture dst, Trect* srcRect, Trect* dstRect) {
    copyTexture(src, dst, srcRect, dstRect, false);
}

/**
 * src      Posee tanto la textura como su tamanio en ul. src.texture == nullptr cuando se trata de la ventana.
 * dst      Posee tanto la textura como su tamanio en ul. dst.texture == nullptr cuando se trata de la ventana.
 * srcRect  Rectangulo que determina la porcion de la textura del "src". Si es "NULL" es toda la textura.
 * dstRect  Rectangulo que determina la porcion de la textura del "dst". Si es "NULL" es toda la textura.
 * flip     true si se debe flippear horizontalmente.
 */
void VistaUtils::copyTexture(Ttexture src, Ttexture dst, Trect* srcRect, Trect* dstRect, bool flip) {
    // guardo el target original
    SDL_Texture *originalTarget = SDL_GetRenderTarget(mRenderer);

    // cambio el target para que apunte a la textura dst
    SDL_SetRenderTarget(mRenderer, dst.t);

    // Importante para que se generen las transparencias si se usa colorkey.
    SDL_SetTextureBlendMode(dst.t, SDL_BLENDMODE_BLEND);

    float scales[2];

    getScales(src, scales);
    SDL_Rect sdlRectSrc;
    if (srcRect != NULL) {
        sdlRectSrc.w = (int) (srcRect->d.w * scales[0]);
        sdlRectSrc.h = (int) (srcRect->d.h * scales[1]);
        sdlRectSrc.x = (int) (srcRect->p.x * scales[0]);
        sdlRectSrc.y = (int) (srcRect->p.y * scales[1]);
    }

    getScales(dst, scales);
    SDL_Rect sdlRectDst;
    if (dstRect != NULL) {
        sdlRectDst.w = (int) (dstRect->d.w * scales[0]);
        sdlRectDst.h = (int) (dstRect->d.h * scales[1]);
        sdlRectDst.x = (int) (dstRect->p.x * scales[0]);
        sdlRectDst.y = (int) (dstRect->p.y * scales[1]);
    }

    SDL_RenderCopyEx(mRenderer,
                     src.t,
                     (srcRect != NULL) ? &sdlRectSrc : NULL,
                     (dstRect != NULL) ? &sdlRectDst : NULL,
                     0,
                     NULL,
                     (flip) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE
    );

    // recupero el target original
    SDL_SetRenderTarget(mRenderer, originalTarget);
}

/**
 * Obtiene la dimension en unidades logicas de una textura.
 *  Utilizando la relacion pixel / unidad logica de la ventana.
 */
Tdimension VistaUtils::getDimension(SDL_Texture *texture){
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    Tdimension dimension = {w / mScales[0], h / mScales[1]};

    return dimension;
}

Tdimension VistaUtils::getDimension(SDL_Texture *texture, float scales[2]) {
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    Tdimension dimension = {w / scales[0], h / scales[1]};

    return dimension;
}

void VistaUtils::freeTextures() {
    for (unsigned i = 0; i < mAuxTextures.size(); i++){
        SDL_DestroyTexture(mAuxTextures.at(i));
    }
}


vector<float> VistaUtils::getEscala() {
    vector<float> escalas;

    escalas.push_back(mScales[0]);
    escalas.push_back(mScales[1]);

    return escalas;
}

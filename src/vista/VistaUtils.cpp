#include <SDL2/SDL_image.h>
#include <cmath>
#include "VistaUtils.h"

/**
 * Si ratio es menor o igual que cero, la relacion de aspecto será 1.
 *
 * ratio    relacion de aspecto ratio = (ancho / alto)
 */
VistaUtils::VistaUtils(SDL_Renderer* renderer, float ratio, float scales[2]) {
    mRenderer = renderer;
    mRatio = (ratio > 0) ? ratio : 1;
    mScales[0] = scales[0];
    mScales[1] = scales[1];
}

void VistaUtils::setColorSetting(TcolorSettings settings) {
    mColorSettings = settings;
}

/**
 * Calcula la escala a utilizar teniendo en cuenta las dimensiones (unidades logicas)
 *  y el tamaño actual de la textura.
 */
void VistaUtils::getScales(SDL_Texture *texture, Tdimension* dimension, float scales[2]){
    if (dimension == NULL){
        scales[0] = mScales[0];
        scales[1] = mScales[1];
    } else {
        int w, h;

        SDL_QueryTexture(texture, NULL, NULL, &w, &h);
        scales[0] = w / dimension->w;
        scales[1] = h / dimension->h;
    }
}


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
/**
                cout << "COLOR RGB ORIGINAL "  << " " << to_string(r) << " " << to_string(g) << " " << to_string(b) << endl;
                cout << "COLOR HSL MOD " << " " << to_string(hsl.h) << " " << to_string(hsl.s) << " " << to_string(hsl.l) << endl;
                cout << "COLOR RGB MOD "  << " " << to_string(rgb.r) << " " << to_string(rgb.g) << " " << to_string(rgb.b) << endl;
*/
                pixel = SDL_MapRGB(surface->format, rgb.r, rgb.g, rgb.b);
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
SDL_Texture *VistaUtils::createTexture(Tdimension dimension) {
    int w = (int) (dimension.w * mRatio);
    int h = (int) (dimension.h * mRatio);

    SDL_Texture * t = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, w, h);
    if (t != 0) {
        string message = "Crea textura de dimensiones " + to_string(w) + " x " + to_string(h);
        loguer->loguear(message.c_str(), Log::LOG_DEB);
        return t;
    }
    loguer->loguear("ERROR - No se pudo crear la textura", Log::LOG_ERR);
    return nullptr;
}

SDL_Texture *VistaUtils::createTexture(string fontPath, string text, int size) {
    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), size);
    if (font == NULL) {
        loguer->loguear("No se pudo cargar la fuente.", Log::LOG_ERR);
        loguer->loguear(TTF_GetError(), Log::LOG_ERR);
        throw new exception();
    }

    SDL_Color black = {255, 255, 255, 0};

    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), black);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
    SDL_FreeSurface(surface);

    return textTexture;
}

/**
 * Se crea una textura a partir de un path, respetando la relacion de aspecto.
 */
SDL_Texture* VistaUtils::loadTexture(std::string path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == NULL){
        return nullptr;
    }else {
        string message = "Carga textura desde " + path;
        loguer->loguear(message.c_str(), Log::LOG_DEB);

        if (mColorSettings.delta != 0) {
            SDL_Surface *aux = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGB888, 0);
            if (aux == NULL){
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

        return t;
    }
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

void VistaUtils::copyTexture(SDL_Texture *src, SDL_Texture *dst, Trect* srcRect, Trect* dstRect, Tdimension* srcDim, Tdimension* dstDim) {
    copyTexture(src, dst, srcRect, dstRect, srcDim, dstDim, false);
}

void VistaUtils::copyTexture(SDL_Texture *src, SDL_Texture *dst, Trect* srcRect, Trect* dstRect, Tdimension* srcDim, Tdimension* dstDim, bool flip) {
    // guardo el target original
    SDL_Texture *originalTarget = SDL_GetRenderTarget(mRenderer);

    // cambio el target para que apunte a la textura dst
    SDL_SetRenderTarget(mRenderer, dst);

    // Importante para que se generen las transparencias si se usa colorkey.
    SDL_SetTextureBlendMode(dst, SDL_BLENDMODE_BLEND);

    float scales[2];

    getScales(src, srcDim, scales);
    SDL_Rect sdlRectSrc;
    if (srcRect != NULL) {
        sdlRectSrc.w = (int) (srcRect->d.w * scales[0]);
        sdlRectSrc.h = (int) (srcRect->d.h * scales[1]);
        sdlRectSrc.x = (int) (srcRect->p.x * scales[0]);
        sdlRectSrc.y = (int) (srcRect->p.y * scales[1]);
    }

    getScales(dst, dstDim, scales);
    SDL_Rect sdlRectDst;
    if (dstRect != NULL) {
        sdlRectDst.w = (int) (dstRect->d.w * scales[0]);
        sdlRectDst.h = (int) (dstRect->d.h * scales[1]);
        sdlRectDst.x = (int) (dstRect->p.x * scales[0]);
        sdlRectDst.y = (int) (dstRect->p.y * scales[1]);
    }

    SDL_RenderCopyEx(mRenderer,
                     src,
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
 * Limpia la textura.
 */
void VistaUtils::cleanTexture(SDL_Texture* t){
    SDL_Texture *originalTarget = SDL_GetRenderTarget(mRenderer);
    SDL_SetRenderTarget(mRenderer, t);

    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0);
    SDL_RenderClear(mRenderer);

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

/**
 * Obtiene la dimension en unidades lógicas de una textura, comparandola con otra
 *  de la cual conocemos sus dimensiones.
 */
Tdimension VistaUtils::getDimension(SDL_Texture* tIndex, Tdimension* dIndex, SDL_Texture *texture) {
    float scales[2];
    getScales(tIndex, dIndex, scales);

    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    Tdimension dimension = {w / scales[0], h / scales[1]};

    return dimension;
}


Tdimension VistaUtils::getDimension(SDL_Texture *texture, float scales[2]) {
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    Tdimension dimension = {w / scales[0], h / scales[1]};

    return dimension;
}

VistaUtils::~VistaUtils() {
    for (unsigned i = 0; i < mAuxTextures.size(); i++){
        SDL_DestroyTexture(mAuxTextures.at(i));
    }
}



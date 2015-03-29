#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

int main() {
    cout << "Empieza el programa." << endl;
    cout << "Se parsea el archivo y se obtienen los datos del ecenario. En este caso se hardcodean." << endl;

    //fondo de pantalla
    static const string mWallpaper = "./img/test_wallpaper.jpeg";

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        cout << "Fallo la inicializacion de SDL." << endl;
    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;
    SDL_Texture *mTexture;

    mWindow = SDL_CreateWindow("TEST", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 400, 400, SDL_WINDOW_SHOWN);
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface *surface = IMG_Load("/home/pablo/Projects/MortalKombat/resources/img/test_wallpaper.jpeg");
    if (surface == NULL)
        cout << "No se cargo la imagen desde el archivo!" << endl;
    mTexture = SDL_CreateTextureFromSurface(mRenderer, surface);

    SDL_RenderClear(mRenderer);
    SDL_RenderCopy(mRenderer, mTexture, NULL, NULL);
    SDL_RenderPresent(mRenderer);

    SDL_Delay(2000);

    cout << "Termino." << endl;

    return 0;
}
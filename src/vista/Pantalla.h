#ifndef _MORTALKOMBAT_PANTALLA_H_
#define _MORTALKOMBAT_PANTALLA_H_


class Pantalla {
private:
    SDL_Renderer *mRender;
    std::vector<Capa> capas;
    // VistaPersonaje vistaPersonaje; clase del personaje deberia tener un metodo q devuelva una textura y unsdlrect para dibujar el sprite

public:
    Pantalla(std::vector<std::string> dirPaths,std::vector<float> anchosCapas,float distTope);
    void dibujar();

};


#endif //_MORTALKOMBAT_PANTALLA_H_

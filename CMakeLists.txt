cmake_minimum_required(VERSION 3.1)
project(MortalKombat)

# Directorios a crear
file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/logs)

# Seteo de los flags a uitlizar a la hora de compilar
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -std=c++11")

# Directorio destino
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Resources
set(RESOURCES resources)
file(COPY ${RESOURCES} DESTINATION ${PROJECT_SOURCE_DIR}/bin)

# Sources
set(SOURCE_FILES

    # Main
    src/main.cpp
    src/Game.h
    src/Game.cpp
    src/Musica.cpp
    src/Musica.h

    # Utils
    src/utils/Common.h
    src/utils/GameUtils.h
    src/utils/PersonajeUtils.h

    # Modelo
    src/modelo/Accionador.h
    src/modelo/Accionador.cpp
    src/modelo/Combo.h
    src/modelo/Combo.cpp
    src/modelo/DetectorDeColisiones.h
    src/modelo/DetectorDeColisiones.cpp
    src/modelo/Golpe.h
    src/modelo/Golpe.cpp
    src/modelo/InteligenciaArtificial.cpp
    src/modelo/InteligenciaArtificial.h
    src/modelo/menu/MenuGameMode.h
    src/modelo/menu/MenuGameMode.cpp
    src/modelo/menu/MenuPlayerSelection.cpp
    src/modelo/menu/MenuPlayerSelection.h
    src/modelo/Mundo.h
    src/modelo/Mundo.cpp
    src/modelo/ObjetoColisionable.h
    src/modelo/Personaje.h
    src/modelo/Personaje.cpp
    src/modelo/Poder.h
    src/modelo/Poder.cpp

    # Parser
    src/parser/config.h
    src/parser/config.cpp
    src/parser/json.h
    src/parser/jsoncpp.cpp
    src/parser/include/json/assertions.h
    src/parser/include/json/autolink.h
    src/parser/include/json/config.h
    src/parser/include/json/features.h
    src/parser/include/json/forwards.h
    src/parser/include/json/json.h
    src/parser/include/json/reader.h
    src/parser/include/json/value.h
    src/parser/include/json/version.h
    src/parser/include/json/writer.h
    src/parser/json/json.h
    src/parser/json/json-forwards.h
    src/parser/log/DebugLog.h
    src/parser/log/DebugLog.cpp
    src/parser/log/ErrorLog.h
    src/parser/log/ErrorLog.cpp
    src/parser/log/Log.h
    src/parser/log/WarningLog.h
    src/parser/log/WarningLog.cpp

    # Vista
    src/vista/VistaUtils.h
    src/vista/VistaUtils.cpp
    src/vista/capas/CapaInfo.h
    src/vista/capas/Capa.cpp
    src/vista/capas/Capa.h
    src/vista/capas/CapaInfo.cpp
    src/vista/capas/CapaInfoPractice.cpp
    src/vista/capas/CapaInfoPractice.h
    src/vista/capas/CapaInfoArcade.cpp
    src/vista/capas/CapaInfoArcade.h
    src/vista/pantallas/PantallaFight.h
    src/vista/pantallas/PantallaFight.cpp
    src/vista/pantallas/PantallaPractice.h
    src/vista/pantallas/PantallaPractice.cpp
    src/vista/pantallas/PantallaArcade.h
    src/vista/pantallas/PantallaArcade.cpp
    src/vista/personajes/PersonajeVista.h
    src/vista/personajes/PersonajeVista.cpp
    src/vista/personajes/PoderVista.h
    src/vista/personajes/PoderVista.cpp
    src/vista/personajes/Sprite.h
    src/vista/personajes/Sprite.cpp
    src/vista/pantallas/menu/PantallaMenuModoJuego.cpp
    src/vista/pantallas/menu/PantallaMenuModoJuego.h
    src/vista/pantallas/menu/PantallaMenuPlayers.cpp
    src/vista/pantallas/menu/PantallaMenuPlayers.h
    src/vista/pantallas/Pantalla.cpp
    src/vista/pantallas/Pantalla.h

    # Controlador
    src/controlador/ControladorTeclado.h
    src/controlador/ControladorTeclado.cpp
    src/controlador/ControladorMouse.h
    src/controlador/ControladorMouse.cpp
    src/controlador/ControladorJoystick.h
    src/controlador/ControladorJoystick.cpp
    src/controlador/ControladorTexto.h
    src/controlador/ControladorTexto.cpp
    )

add_executable(MortalKombat ${SOURCE_FILES})

# Bibliotecas
target_link_libraries(MortalKombat
                        SDL2main
                        SDL2
                        SDL2_image
                        SDL2_ttf
                        SDL2_mixer)


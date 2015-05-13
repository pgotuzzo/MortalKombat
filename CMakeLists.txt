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
    src/modelo/Personaje.h
    src/modelo/acciones/Caminar.h
    src/modelo/acciones/Caminar.cpp
    src/modelo/acciones/Agachar.h
    src/modelo/acciones/SaltoVertical.h
    src/modelo/Mundo.h
    src/modelo/Mundo.cpp
    src/modelo/Accion.cpp
    src/modelo/acciones/Agachar.cpp
    src/modelo/acciones/SaltoOblicuo.h
    src/modelo/Personaje.cpp
    src/modelo/Accion.h
    src/modelo/acciones/SaltoVertical.cpp
    src/modelo/acciones/SaltoOblicuo.cpp
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
    src/parser/log/DebugLog.cpp
    src/parser/log/DebugLog.h
    src/parser/log/ErrorLog.cpp
    src/parser/log/ErrorLog.h
    src/parser/log/Log.h
    src/parser/log/WarningLog.cpp
    src/parser/log/WarningLog.h
    src/parser/json/json.h
    src/parser/json/json-forwards.h
    src/parser/config.cpp
    src/parser/config.h
    src/parser/json.h
    src/parser/jsoncpp.cpp
    src/vista/personajes/PersonajeVista.cpp
    src/vista/personajes/PersonajeVista.h
    src/vista/personajes/Sprite.cpp
    src/vista/personajes/Sprite.h
    src/vista/Capa.cpp
    src/vista/CapaInfo.h
    src/vista/CapaInfo.cpp
    src/vista/Capa.h
    src/vista/Pantalla.cpp
    src/vista/Pantalla.h
    src/vista/VistaUtils.cpp
    src/vista/VistaUtils.h
    src/Common.h
    src/main.cpp
    src/modelo/Colisionador.cpp
    src/modelo/Colisionador.h
    src/modelo/ObjetoColisionable.h
    src/modelo/Poder.h
    src/modelo/Poder.cpp
    src/modelo/Golpe.cpp
    src/modelo/Golpe.h
    src/controlador/ControladorTeclado.cpp
    src/controlador/ControladorTeclado.h
    src/controlador/ControladorJoystick.cpp
    src/controlador/ControladorJoystick.h
    src/vista/personajes/PoderVista.cpp
    src/vista/personajes/PoderVista.h
    )

add_executable(MortalKombat ${SOURCE_FILES})

# Bibliotecas
target_link_libraries(MortalKombat
                        SDL2main
                        SDL2
                        SDL2_image)


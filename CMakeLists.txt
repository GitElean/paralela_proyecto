cmake_minimum_required(VERSION 3.22)

project(ScreenSaver)

# Usar pkg-config para encontrar SDL2 y SDL2_gfx
find_package(PkgConfig REQUIRED)

pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_GFX REQUIRED SDL2_gfx)

# Encontrar OpenMP
find_package(OpenMP REQUIRED)

# Agregar el directorio de los headers
include_directories(${PROJECT_SOURCE_DIR}/src ${SDL2_INCLUDE_DIRS} ${SDL2_GFX_INCLUDE_DIRS})

# Especificar los archivos fuente
set(SOURCES
    src/main.cpp
    src/secuencial.cpp
    src/paralelo.cpp
)

# Crear el ejecutable
add_executable(${PROJECT_NAME} ${SOURCES})

# Enlazar las bibliotecas necesarias
target_link_libraries(${PROJECT_NAME}
  ${SDL2_LIBRARIES}
  ${SDL2_GFX_LIBRARIES}
  OpenMP::OpenMP_CXX
  GL
)

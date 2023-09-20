cmake_minimum_required(VERSION 3.22)

project(ScreenSaver)

# Encontrar SDL2
find_package(SDL2 REQUIRED)

# Encontrar OpenMP
find_package(OpenMP REQUIRED)

# Agregar el directorio de los headers (en este caso, es el mismo que el de los sources)
include_directories(${PROJECT_SOURCE_DIR}/src ${SDL2_INCLUDE_DIRS})

# Especificar los archivos fuente
set(SOURCES
    src/main.cpp
    src/secuencial.cpp
    src/paralelo.cpp
    # Aquí puedes añadir futuros archivos fuente, como src/paralelo.cpp
)

# Crear el ejecutable
add_executable(${PROJECT_NAME} ${SOURCES})

# Enlazar las bibliotecas necesarias
target_link_libraries(${PROJECT_NAME}
  ${SDL2_LIBRARIES}
  OpenMP::OpenMP_CXX
  GL
)
